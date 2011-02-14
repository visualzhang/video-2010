//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

// YOU MUST INCLUDE THE HEADER FOR UNIT1
//#include "Unit1.h"
#include "Unit2.h"

//#define _Save_Prime_Data
///////////////////////////////////////////////////////////////////////////////
#include <stdio.h>

#include <algorithm.h>

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////
extern struct Channel_SYNC _Channel_SYNC_Data;
///////////////////////////////////////////////////////////////////////////////
extern HANDLE hComm;
extern char _Comm_Buff[100];

extern void Close_Comm();
extern void Clear_Comm();
extern void Stop_Comm();

///////////////////////////////////////////////////////////////////////////////
extern int _nReceive_Data_From_Comm=0;
extern int _nReceive_Empty_Data_Count=0;

///////////////////////////////////////////////////////////////////////////////
AnsiString  _sTest_File_Name;  //"\\TouchPanel_result.dat" ;
FILE *_pTest_Data_File = 0;
FILE *_pLog_File = 0;

void Write_File();
void Open_File();

FILE * Open_Log_File(AnsiString sFile_Name);
extern void Write_Log(FILE *pFile, AnsiString sItem, AnsiString sValue);
extern void Start_Detect();

AnsiString  Get_Float(AnsiString str);
AnsiString Get_Current_Time();
///////////////////////////////////////////////////////////////////////////////
//---------------------------------------------------------------------------
//   Important: Methods and properties of objects in VCL can only be
//   used in a method called using Synchronize, for example:
//
//      Synchronize(UpdateCaption);
//
//   where UpdateCaption could look like:
//
//      void __fastcall TRead::UpdateCaption()
//      {
//        Form1->Caption = "Updated in a thread";
//      }
//---------------------------------------------------------------------------
__fastcall TRead::TRead(bool CreateSuspended)
	: TThread(CreateSuspended)
{

}
//---------------------------------------------------------------------------
void __fastcall TRead::DisplayIt(void)
{
//  Form1->Memo1->SetSelTextBuf(InBuff);
//    BasicForm->Display();
}

///////////////////////////////////////////////////////////////////////
void Close_File()
{
   FILE *pTmp = _pTest_Data_File;
   if(pTmp)
   {
     fclose(pTmp);
     _pTest_Data_File = 0;
   }
}

///////////////////////////////////////////////////////////////////////
void Open_File()
{
      FILE *pTmp = _pTest_Data_File;
      if( !pTmp)
      {
          AnsiString sFile;
          AnsiString SystemDir = GetCurrentDir();
          if(!_sTest_File_Name.IsEmpty() )
          {
              sFile =  SystemDir + _sTest_File_Name ;  //"\\TouchPanel_result.dat" ;
              pTmp = fopen(sFile.c_str(), "wb") ;

              if(pTmp) _pTest_Data_File =  pTmp;
              else
                 ShowMessage("Create result file failed!");
          }   
      }
}

///////////////////////////////////////////////////////////////////////
FILE * Open_Log_File(AnsiString sFile_Name)
{
      FILE *_pTest_Data_File = 0;
      FILE *pTmp = _pTest_Data_File;
      if( !pTmp)
      {
          AnsiString sFile;
          AnsiString SystemDir = GetCurrentDir();
          //sFile_Name = "\\abc.log" ;
          if(!sFile_Name.IsEmpty() )
          {
              sFile =  SystemDir + "\\" + sFile_Name ;  //"\\TouchPanel_result.dat" ;
              pTmp = fopen(sFile.c_str(), "a+") ;

              if(pTmp)
              {
                  //_pTest_Data_File =  pTmp;
                  AnsiString str;
                  str += "\r\n/****************************************************/\r\n";

                  TDateTime   datetime;
                  datetime = datetime.CurrentDateTime();
                  //Add("*  Created: 5/7/2008 2:03PM");
                  //str += datetime.FormatString("dd'/'mm'/'yyyy  hh:nn:am/pm'");
                  str += datetime.FormatString("yyyy'-'mm'-'dd  hh:nn:am/pm'");
                  str += "\r\n";

                  fwrite(str.c_str(),1,str.Length(), pTmp);
              }
              else
                 ShowMessage("Create file failed!");
          }
      }
      return   pTmp;
}

void Write_Log(FILE *pFile, AnsiString sItem, AnsiString sValue)
{
      if(!pFile) return;
      
      AnsiString str = sItem;
      str += "\t";
      fwrite(str.c_str(),1,str.Length(), pFile);
      str = sValue;
      str += "\r\n";
      fwrite(str.c_str(),1,str.Length(), pFile);
}
///////////////////////////////////////////////////////////////////////
void Write_File()
{
     FILE *pTmp = _pTest_Data_File;
     if(pTmp)
     {
        //fwrite(&_Channel_SYNC_Data,1,sizeof(Channel_SYNC), pTmp);
     }
}

//---------------------------------------------------------------------------
AnsiString  Get_Float(AnsiString str)
{
      AnsiString sFloat = str;

      int nIndex = str.Pos(".");
      if( nIndex )
      {
          sFloat = str.SubString(0, nIndex + 2);
      }
      return   sFloat;
}

//---------------------------------------------------------------------------
AnsiString Get_Current_Time()
{
        AnsiString str;

        TDateTime   datetime;
        datetime = datetime.CurrentDateTime();
        //Add("*  Created: 5/7/2008 2:03PM");
        //str += datetime.FormatString("dd'/'mm'/'yyyy  hh:nn:am/pm'");
        str += datetime.FormatString("dd'/'mm'/'yyyy  hh:nn:ss:am/pm'");
        return str;
}  
//---------------------------------------------------------------------------


void Test_Data()
{
}

//---------------------------------------------------------------------------
void __fastcall TRead::Execute()
{
  DWORD dwBytesRead;

  // MAKE THE THREAD OBJECT AUTOMATICALLY DESTROYED WHEN THE THREAD
  // TERMINATES.

  FreeOnTerminate = true;
  Sleep(100);
  //while(1)
  {
    Test_Data();
    // SEE IF THERE ARE ANY CHARACTERS IN THE INTERNAL RECEIVE BUFFER.
    // IF THERE ARE, READ THEM. OTHERWISE, WAIT FOR CHARACTERS
    // TO ARRIVE OR LEAVE IF THE THREAD IS TERMINATED.

    /*if(Terminated) return;
    ReadFile(hComm, _InBuff, 50, &dwBytesRead, NULL);
    if(dwBytesRead)
    {
      _InBuff[dwBytesRead] = 0; // NULL TERMINATE THE STRING
      Synchronize(DisplayIt);
    }*/
  }
}

