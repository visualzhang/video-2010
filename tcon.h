//---------------------------------------------------------------------------

#ifndef tconH
#define tconH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <Grids.hpp>
#include "active_testLib_OCX.h"
#include <OleCtrls.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class Ttcon_form : public TForm
{
__published:	// IDE-managed Components
        TPageControl *PageControl5;
        TTabSheet *Para;
        TPanel *Panel2;
        TLabel *Label1;
        TLabel *Label2;
        TEdit *Edit2;
        TEdit *Edit3;
        TRadioGroup *RadioGroup7;
        TButton *Button7;
        TTabSheet *Page_R;
        TPanel *Panel1;
        TButton *Button2;
        TButton *Button3;
        TCheckBox *CheckBox1;
        TGroupBox *GroupBox1;
        TLabel *Label5;
        TLabel *Label4;
        TLabel *Label6;
        TLabel *Label7;
        TLabel *Label8;
        TLabel *Label9;
        TLabel *Label10;
        TLabel *Label11;
        TLabel *Label12;
        TCheckBox *CheckBox2;
        TCheckBox *CheckBox3;
        TCheckBox *CheckBox6;
        TCheckBox *CheckBox7;
        TCheckBox *CheckBox8;
        TCheckBox *CheckBox9;
        TCheckBox *CheckBox10;
        TCheckBox *CheckBox11;
        TCheckBox *CheckBox12;
        TCheckBox *CheckBox13;
        TCheckBox *CheckBox14;
        TLabel *Label13;
        TLabel *Label14;
        TLabel *Label15;
        TLabel *Label16;
        TGroupBox *GroupBox2;
        TPanel *Panel3;
        TStringGrid *StringGrid1;
        TStringGrid *StringGrid2;
        TStringGrid *StringGrid3;
        TStringGrid *StringGrid4;
        TStringGrid *StringGrid5;
        TStringGrid *StringGrid6;
        TComboBox *ComboBox1;
        TComboBox *ComboBox2;
        TStringGrid *StringGrid7;
        TEdit *Edit1;
        TLabel *Label3;
        TLabel *Label17;
        TButton *Button1;
        TButton *Button4;
        TButton *Button5;
        TButton *Button6;
        TButton *Button9;
        TImage *Image1;
        TBitBtn *BitBtn1;
        TEdit *Edit4;
        TEdit *Edit5;
        TEdit *Edit6;
        void __fastcall timing_send(TObject *Sender);
        void __fastcall timing_get(TObject *Sender);
        void __fastcall StringGrid1SelectCell(TObject *Sender, int ACol,
          int ARow, bool &CanSelect);
        void __fastcall timing_para(TObject *Sender);
        void __fastcall get_data(TObject *Sender);
        void __fastcall draw_axis_frame(TObject *Sender);
        void __fastcall gamma_curve(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall Ttcon_form(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE Ttcon_form *tcon_form;
//---------------------------------------------------------------------------
#endif
