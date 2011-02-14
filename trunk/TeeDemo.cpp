//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
USEFORM("U_LCD_RGB.cpp", LCD_RGB);
USEFORM("tcon.cpp", tcon_form);
USEFORM("U_Adjust.cpp", panel_adjust_form);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    try
    {
        Application->Initialize();
        Application->CreateForm(__classid(Ttcon_form), &tcon_form);
                 Application->CreateForm(__classid(TLCD_RGB), &LCD_RGB);
                 Application->CreateForm(__classid(Tpanel_adjust_form), &panel_adjust_form);
                 Application->Run();
    }
    catch (Exception &exception)
    {
        Application->ShowException(&exception);
    }
    return 0;
}
//---------------------------------------------------------------------------
