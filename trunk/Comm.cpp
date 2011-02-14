///////////////////////////////////////////////////////////////////////////
//
#include <inifiles.hpp>
#include <vcl\vcl.h>

///////////////////////////////////////////////////////////////////////////
HANDLE hComm = NULL;

COMMTIMEOUTS ctmoNew = {0}, ctmoOld;
char _Comm_Buff[100];

///////////////////////////////////////////////////////////////////////////
HANDLE Open_Comm(AnsiString sCOM);
void Close_Comm();

int Read_Comm(char *Data_Buf, int nLen);

AnsiString Get_Comm_From_File();

AnsiString _sRate;

///////////////////////////////////////////////////////////////////////////

int nLarge_Buff_Len =0;

unsigned char InBuff[800];

//---------------------------------------------------------------------------
HANDLE  Open_Comm(AnsiString sCOM)
{
      DCB dcbCommPort;

      HANDLE  h_Comm = hComm;
      if(h_Comm != NULL)
	  	return h_Comm;
	  
      // OPEN THE COMM PORT.
      if(sCOM.IsEmpty())
           sCOM = Get_Comm_From_File(); //return false;

      h_Comm = CreateFile(//"COM1",
                          sCOM.c_str(),
                          GENERIC_READ | GENERIC_WRITE,
                          0,
                          0,
                          OPEN_EXISTING,
                          0,
                          0);

      // IF THE PORT CANNOT BE OPENED, BAIL OUT.

      if(h_Comm == INVALID_HANDLE_VALUE)
      { //Application->Terminate();
         ShowMessage("Open COM failed!");
         hComm = NULL;
         return h_Comm;
      }

      hComm = h_Comm;	
      // SET THE COMM TIMEOUTS.

      GetCommTimeouts(h_Comm,&ctmoOld);
      ctmoNew.ReadTotalTimeoutConstant = 100;
      ctmoNew.ReadTotalTimeoutMultiplier = 0;
      ctmoNew.WriteTotalTimeoutMultiplier = 0;
      ctmoNew.WriteTotalTimeoutConstant = 0;
      SetCommTimeouts(h_Comm, &ctmoNew);

      SetCommMask(h_Comm,   EV_RXCHAR   )   ; 


      // SET BAUD RATE, PARITY, WORD SIZE, AND STOP BITS.
      // THERE ARE OTHER WAYS OF DOING SETTING THESE BUT THIS IS THE EASIEST.
      // IF YOU WANT TO LATER ADD CODE FOR OTHER BAUD RATES, REMEMBER
      // THAT THE ARGUMENT FOR BuildCommDCB MUST BE A POINTER TO A STRING.
      // ALSO NOTE THAT BuildCommDCB() DEFAULTS TO NO HANDSHAKING.

      dcbCommPort.DCBlength = sizeof(DCB);
      GetCommState(h_Comm, &dcbCommPort);
      AnsiString sDef = _sRate;
      if(sDef.IsEmpty())
        sDef = "115200,N,8,1";
      else
          sDef += ",N,8,1";
      
      BuildCommDCB( sDef.c_str(), &dcbCommPort);
      SetCommState(h_Comm, &dcbCommPort);

      // ACTIVATE THE THREAD. THE FALSE ARGUMENT SIMPLY MEANS IT HITS THE
      // GROUND RUNNING RATHER THAN SUSPENDED.

      return h_Comm;
}

////////////////////////////////////////////////////////////////////////////////
AnsiString Get_Comm_From_File()
{
     AnsiString SystemDir = GetCurrentDir();
     TIniFile *pIniFile = new TIniFile(SystemDir + "\\Project.ini") ;

     AnsiString str = pIniFile->ReadString("Comm", "Comm", "");

     delete  pIniFile;

     if(str.IsEmpty()) str = "COM1";
     return str;
}

////////////////////////////////////////////////////////////////////////////////
void Close_Comm()
{
   if(hComm)
   {
     CloseHandle(hComm);
   }
   
   hComm = NULL;
}

int Read_Comm(char *Data_Buf, int nLen)
{
        return 0;
}

///////////////////////////////////////////////////////////////////////////////////////
AnsiString  write_command_line(HANDLE  hComm, AnsiString str)
{
	AnsiString sRe;
        char buf[800]  ;
        DWORD write_transfered, dwBytesRead;

        str+="\r\n";

        if(hComm != NULL)
        {
                memcpy(buf, str.c_str(), str.Length());

                WriteFile(hComm, buf , str.Length(),  &write_transfered, NULL);

                 ReadFile(hComm, buf, 800, &dwBytesRead, NULL);

                 if(dwBytesRead)
                 {
                 	//   replace(buf, '@',' ', dwBytesRead);	
                        sRe.sprintf( "%s",(char*)buf);
                 }
        }
        return sRe;
}


////////////////////////////////////////////////////////////////////////////////////
int  read_register(HANDLE  hComm, int addr)
{
		AnsiString str, stmp;
		int data;
		
		stmp.sprintf("0x%x", addr)  ;
		str = "echo wc 0x1d70  " + stmp + "  > /sys/bus/pseudo/drivers/amlogic_debug/amlogic_reg" ;
	        str = write_command_line(hComm, str);

		#if 0
                # echo rc 0x1d71 > /sys/bus/pseudo/drivers/amlogic_debug/amlogic_reg
		[ 5227.580000] rc 0x1d71
		[ 5227.580000] rc: 0x1d71 --> 0x8aff8a00
		#endif
		
		str = "echo rc 0x1d71 > /sys/bus/pseudo/drivers/amlogic_debug/amlogic_reg" ;
		str = write_command_line(hComm, str);

		char *stop;
		int nIndex = str.Pos("rc: 0x1d71 --> 0x");
		str = str.SubString(nIndex, str.Length()-nIndex);

             data = strtol( str.c_str() , &stop,  16);

              return data;
}
////////////////////////////////////////////////////////////////////////////////////
AnsiString  write_register(HANDLE  hComm, int addr, int data)
{
		AnsiString str, stmp;
		
		stmp.sprintf("0x%x", addr)  ;
		str = "echo wc 0x1d70  " + stmp + "  > /sys/bus/pseudo/drivers/amlogic_debug/amlogic_reg" ;
	        str = write_command_line(hComm, str);

		stmp.sprintf("0x%x", data)  ;
		str = "echo wc 0x1d71  " + stmp + "  > /sys/bus/pseudo/drivers/amlogic_debug/amlogic_reg" ;
		str = write_command_line(hComm, str);

                return str;
}


////////////////////////////////////////////////////////////////////////////////////
int  read_bit(HANDLE  hComm, int addr, int start, int len)
{
		AnsiString str, stmp;
		int data;

		//read reg
		data = read_register(hComm, addr);

		data= (data>>start) & (0xffffffff >>(32-len));

		return data;

}

////////////////////////////////////////////////////////////////////////////////////
AnsiString  write_bit(HANDLE  hComm, int addr, int start, int len, int bit_data)
{
		AnsiString str, stmp;
		int data, ntmp;

		ntmp = (0xffffffff <<(len + start)) || (0xffffffff >>( 32- start)) ;

		bit_data = (bit_data<<start) ||  ntmp;

		//read reg
		data = read_register(hComm, addr);
		data = data || (~ntmp);

		data = data|| bit_data;
				
		//write reg
		write_register(hComm, addr, data);

              return str;
}

///////////////////////////////////////////////////////////////////////////////////////
char   *replace(char   *str,   char   srch,   char   tgch , int length)
{ 
      char   *p   =   str; 
      //  while(*p   !=   '\0 ')
      for(int i=0; i< length; i++)
      {
              if(*p   ==   srch)
                    *p   =   tgch;
              p   ++; 
      } 
      return   str;       
}

