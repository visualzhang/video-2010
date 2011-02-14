//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

// YOU MUST INCLUDE THE HEADER FOR UNIT1

/////////////////////////////////////////////////////////////////////////////// 
#include "send_slider.h"

#include "U_LCD_RGB.h"
#include "U_Adjust.h"

///////////////////////////////////////////////////////////////////////////////
#include <stdio.h>

#include <algorithm.h>

//---------------------------------------------------------------------------
bool _Is_End_Thread = false;
#if 0

#endif

///////////////////////////////////////////////////////////////////////////////
AnsiString  _sTest_File_Name;  //"\\TouchPanel_result.dat" ;
FILE *_pTest_Data_File = 0;
FILE *_pLog_File = 0;

void Write_File();
void Open_File();

FILE * Open_Log_File(AnsiString sFile_Name);
extern void Write_Log(FILE *pFile, AnsiString sItem, AnsiString sValue);

AnsiString  Get_Float(AnsiString str);     
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
__fastcall TSend_Slider::TSend_Slider(bool CreateSuspended)
	: TThread(CreateSuspended)
{

}
//---------------------------------------------------------------------------
void __fastcall TSend_Slider::DisplayIt(void)
{
//  Form1->Memo1->SetSelTextBuf(InBuff);
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

}     
//---------------------------------------------------------------------------
int _Count=0;

int  x_count =0;
int  y_count =0;
void Test_Data()
{}

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
int Save_Graph(FILE *pFile, char *InBuff, int nSum, int *nLess, bool *Is_End)
{
return 0;
}

void Transfer_To_Graph()
{}

//---------------------------------------------------------------------------
void __fastcall TSend_Slider::Execute()
{
    DWORD dwBytesRead;

    // MAKE THE THREAD OBJECT AUTOMATICALLY DESTROYED WHEN THE THREAD
    // TERMINATES.
    //Transfer_To_Graph();
    //return;
    int i =0;
    _slide_type = LCD_RGB_index;
    
      while(1)
      {
        if(_Is_End_Thread)
        {
            break;
        }
        switch(_slide_type)
        {
                 case LCD_RGB_index:
                        LCD_RGB->Scroll_Bar1_Change() ;
                         break;                        
                 case PANEL_ADJUST_index:
                         panel_adjust_form->Scroll_Bar1_Change();
                         break;

        }

        Sleep(1);
       } 
    
}

