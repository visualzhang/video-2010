//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "U_Adjust.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
Tpanel_adjust_form *panel_adjust_form;

#include "send_slider.h"  //thread

#include "comm.h"

TScrollBar *_pScrollBar;



//---------------------------------------------------------------------------
__fastcall Tpanel_adjust_form::Tpanel_adjust_form(TComponent* Owner)
        : TForm(Owner)
{
	//TSend_Slider *psend_slider_thread;
	//psend_slider_thread = new TSend_Slider(false);

        _slide_type = 1;

        hComm = Open_Comm("COM1");

        if(hComm == NULL)
                ShowMessage("can not open com1");

        TScrollBar *pScrollBar_group[] = {ScrollBar9, ScrollBar10, ScrollBar1, ScrollBar2, ScrollBar3 };

        ///////////////////////////////////////////////////////
       for(int i=0; i<5;i++)
       {
                pScrollBar_group[i]->SmallChange =1 ;
                pScrollBar_group[i]->Max =100;
                pScrollBar_group[i]->Min =1;
       }
}
//---------------------------------------------------------------------------
void __fastcall Tpanel_adjust_form::Scroll_Bar1_Change()
{
        //TScrollBar *pScrollBar = _pScroll_bar;;
	//_pScroll_bar = NULL;

}
//---------------------------------------------------------------------------
void __fastcall Tpanel_adjust_form::Button1Click(TObject *Sender)
{
        char buf[800]  ;
        DWORD write_transfered, dwBytesRead;
        AnsiString str;
        AnsiString str_group[] = { " \> /sys/class/video/brightness\r\n",
        "  \> /sys/class/video/contrast\r\n",
        
        " \> /sys/class/video/saturation_hue\r\n",
        " \> /sys/class/video/saturation_hue\r\n",
        " \> /sys/class/video/brightness\r\n"};;


        TScrollBar *pScrollBar_group[] = {ScrollBar9, ScrollBar10, ScrollBar1, ScrollBar2, ScrollBar3 };
        int i =0;

        ///////////////////////////////////////////////////////
       for(i=0; i<5;i++)
       {
                if(pScrollBar_group[i] == _pScrollBar)
                        break;
       }

        if(hComm != NULL)
        {

                str = "echo " + IntToStr( (_pScrollBar->Position -50)*2)+ str_group[i];
                //memcpy(buf, Edit1->Text.c_str(), Edit1->Text.Length());
                memcpy(buf, str.c_str(), str.Length());

                WriteFile(hComm, buf , str.Length(),  &write_transfered, NULL);
                Edit2->Text = IntToStr(write_transfered);

                //buf[0] ='\n';
                //buf[1] = 0;
                //WriteFile(hComm, buf , 2,  &write_transfered, NULL);

                                        //replace(buf, '@',' ', dwBytesRead);
                        //replace(buf, '^',' ', dwBytesRead);

                 ReadFile(hComm, buf, 800, &dwBytesRead, NULL);
                 Edit3->Text = IntToStr(dwBytesRead);
                 if(dwBytesRead)
                 {
                        str.sprintf( "%s",(char*)buf);
                        m_get_data->Lines->Add(str);
                 }
        }
}
//---------------------------------------------------------------------------
void __fastcall Tpanel_adjust_form::Button2Click(TObject *Sender)
{
       AnsiString str= "COM1";
       hComm = Open_Comm(str);

        if(hComm == NULL)
                ShowMessage("can not open " + str);
}
//---------------------------------------------------------------------------
void __fastcall Tpanel_adjust_form::Button3Click(TObject *Sender)
{
        char buf[] ="echo 99 > /sys\/class\/video\/brightness";
        DWORD write_transfered;

        if(hComm != NULL)
        {
                WriteFile(hComm,  &buf, 200,  &write_transfered, NULL);
        }
}
//---------------------------------------------------------------------------



void __fastcall Tpanel_adjust_form::ScrollBar9Change(TObject *Sender)
{
        TScrollBar *pScrollBar = (TScrollBar *)Sender;
        TScrollBar *pScrollBar_group[] = {ScrollBar9, ScrollBar10, ScrollBar1, ScrollBar2, ScrollBar3 };
        TEdit   *pEdit[] = {Edit4, Edit5, Edit6, Edit7, Edit10};;
	int data=pScrollBar->Position  ;

        _pScrollBar = pScrollBar;
        ///////////////////////////////////////////////////////
       for(int i=0; i<5;i++)
       {
                if( pScrollBar == pScrollBar_group[i] )
                {
                        pEdit[i]->Text = IntToStr(pScrollBar->Position);
                        Button1Click(this);
                }
       }
}
//---------------------------------------------------------------------------



void __fastcall Tpanel_adjust_form::Button6Click(TObject *Sender)
{
        char buf[800]  ;
        DWORD write_transfered, dwBytesRead;
        AnsiString str;

        if(hComm != NULL)
        {

                str = "cat /sys/class/video/brightness\r\n";
                //memcpy(buf, Edit1->Text.c_str(), Edit1->Text.Length());
                memcpy(buf, str.c_str(), str.Length());

                WriteFile(hComm, buf , Edit1->Text.Length(),  &write_transfered, NULL);
                Edit2->Text = IntToStr(write_transfered);

                 ReadFile(hComm, buf, 800, &dwBytesRead, NULL);
                 Edit3->Text = IntToStr(dwBytesRead);
                 if(dwBytesRead)
                 {
                        str.sprintf( "%s",(char*)buf);
                        m_get_data->Lines->Add(str);
                 }
        }  
}
//---------------------------------------------------------------------------

void __fastcall Tpanel_adjust_form::Button5Click(TObject *Sender)
{
// cat /sys/class/video/axis
        AnsiString str =  "cat /sys/class/video/axis";
       str = write_command_line(hComm, "cat /sys/class/video/axis");
       panel_adjust_form->m_get_data->Lines->Add(str);

}
//---------------------------------------------------------------------------

void __fastcall Tpanel_adjust_form::Button4Click(TObject *Sender)
{
// echo 1 > /sys/class/video/screen_mode
// echo h-start v-start h-end v-end > /sys/class/video/axis
      AnsiString str   ;
       str = write_command_line(hComm, "echo 1 > /sys/class/video/screen_mode");
       panel_adjust_form->m_get_data->Lines->Add(str);

       str = "echo " +  Edit8->Text + " " + Edit9->Text + " " + Edit11->Text + " "  + Edit12->Text + " > /sys/class/video/axis";
        str = write_command_line(hComm, str);
        panel_adjust_form->m_get_data->Lines->Add(str);
}
//---------------------------------------------------------------------------

