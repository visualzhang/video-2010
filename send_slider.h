//---------------------------------------------------------------------------
#ifndef Send_Slider_H
#define Send_Slider_H
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>

//---------------------------------------------------------------------------
int _slide_type =1;

enum
{
        LCD_RGB_index =0,
        PANEL_ADJUST_index
};

//---------------------------------------------------------------------------
class TSend_Slider: public TThread
{
private:
protected:
  void __fastcall DisplayIt(void);
  void __fastcall Execute();
public:
	__fastcall TSend_Slider(bool CreateSuspended);

	unsigned char send_array[8096];
	int nSend_Sum ;
	int nSend ;         
	byte nID;
};
//---------------------------------------------------------------------------
#endif
 