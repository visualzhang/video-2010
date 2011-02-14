#include <vcl\vcl.h>
#include "dpf.h"
#include "Comm.h"

#include <stdio.h>
//---------------------------------------------------------------------------
/*
struct Channel_SYNC _Channel_SYNC_Data;

#ifdef _AML
   #define _Channel_SYNC_Len 70 + 6
#else
   #define _Channel_SYNC_Len 22 + 6
#endif               */

//---------------------------------------------------------------------------
void Tty_Head_Set(tty_scmd_head_t *pTty_scmd_head, unsigned char id, unsigned short nLen)
{
     memset(pTty_scmd_head, NULL , sizeof(tty_scmd_head_t) );

     pTty_scmd_head->tag = 0x53434d44;       // ;//  0x444d4353
     pTty_scmd_head->ver = 0x31;

     pTty_scmd_head->id = id;
     pTty_scmd_head->id_not = ~id;

     pTty_scmd_head->seq = 0x01;

     pTty_scmd_head->packet_len = nLen;
     pTty_scmd_head->check_sum = 0x0;//0x3333;
}

//---------------------------------------------------------------------------
void Send_Data(char *Data, int nLen,  unsigned char id)
{
  
  if(hComm)
  {

      DWORD write_transfered;
      unsigned char Array[600];   // 2008-12-12
      int nSum=0;
      tty_scmd_head_t Tty;

      //////////////////////////////////////////////////////////////////////////
      if( !id ) id = TTY_SERVICE_ID_TOUCH;
      //tty
      Tty_Head_Set( &Tty, id, nLen);

      //checksum data
      memset(Array, NULL, sizeof(Array) );
      if( sizeof(Array) > nLen)
          memcpy(Array, Data, nLen);
      else
      {
          ShowMessage("Data Error! Please contact with software developer! ");
          return ;
      }
      for(int i =0; i<sizeof(Array); i++)
         nSum += Array[i];
      //checksum tty
      memset(Array, NULL, sizeof(Array) );
      memcpy(Array, &Tty, sizeof(Tty) );
      for(int i =0; i<sizeof(Array); i++)
         nSum += Array[i];

      unsigned short nTmp = nSum;
      Tty.check_sum = nTmp;
      /////////////////////////////////////////////////////////////////////////
      //44 4d 43 53 31 00 00 00 02 fd 01 00 03 00 33 33 
      WriteFile(hComm,  &Tty, sizeof(Tty),  &write_transfered, NULL);

      WriteFile(hComm,  Data, nLen,  &write_transfered, NULL);

//      Sleep(10);
     // memcpy(Array +  sizeof(Tty), Data, nLen );
     // WriteFile(hComm,  Array, nLen+  sizeof(Tty),  &write_transfered, NULL);
  }

}

//---------------------------------------------------------------------------



int Get_From_Comm();

void Start_Detect();

bool Clear_Comm_4_DPF();
void Stop_Comm_4_DPF();

void Sent_Graph_Command();
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
bool  Initial_Comm_4_DPF(AnsiString str)
{
      if(!Open_Comm(str))
         return false;

       //////////////////////////////////////////////////////////////////
       Stop_Comm_4_DPF();
       Sleep(1000);   //delay 1 s
       if( !Clear_Comm_4_DPF() )
           return false;

       //Is_Run= true;
       return true;
}

//---------------------------------------------------------------------------
bool Clear_Comm_4_DPF()
{
      //stop
      if(!hComm) return false;
      char   InBuff[4028];

       //clear comm buffer
       DWORD dwBytesRead;
       //while(1)
       for(int i =0; i < 10; i++)
       {
            ReadFile(hComm, InBuff, 4028, &dwBytesRead, NULL);
            if(!dwBytesRead)
            {
                    break;
            }        
            else
            {
                if(i == 9)  //tip
                {
                    ShowMessage("Comm can not be empty, please check it!");
                    return false;
                }
            }
       }

       return true;

}

void Stop_Comm_4_DPF()
{
      //stop
      if(!hComm) return;

       {
       char set[] = {0xd2,0x2d,0x04,0x00,0x00,0x05}; //"04" is stop
       set[2] = TPDBG_EVENT_2TP_STOP_SYNC; // stop
       Send_Data(set, 6);
       }

}


//---------------------------------------------------------------------------
extern unsigned char ProcessorID[17], KeyID[17];
extern unsigned char PromptID[65], VerifyID[65];

extern void Create_VerifyID(void); // ;

extern void Create_PromptID(void);
extern bool Verify_SN(void);

extern bool extend_str65_to_str71(unsigned char *x, unsigned char *y);
extern bool compress_str71_to_str65(unsigned char *x, unsigned char *y);

//---------------------------------------------------------------------------

