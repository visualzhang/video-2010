//---------------------------------------------------------------------------

#ifndef U_AdjustH
#define U_AdjustH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class Tpanel_adjust_form : public TForm
{
__published:	// IDE-managed Components
        TScrollBar *ScrollBar9;
        TScrollBar *ScrollBar10;
        TEdit *Edit4;
        TEdit *Edit5;
        TButton *Button1;
        TButton *Button2;
        TButton *Button3;
        TEdit *Edit1;
        TMemo *m_get_data;
        TEdit *Edit2;
        TEdit *Edit3;
        TEdit *Edit6;
        TScrollBar *ScrollBar1;
        TEdit *Edit7;
        TScrollBar *ScrollBar2;
        TEdit *Edit8;
        TEdit *Edit9;
        TEdit *Edit10;
        TScrollBar *ScrollBar3;
        TEdit *Edit11;
        TEdit *Edit12;
        TGroupBox *GroupBox1;
        TLabel *Label10;
        TLabel *Label11;
        TLabel *Label12;
        TLabel *Label13;
        TButton *Button4;
        TButton *Button5;
        TButton *Button6;
        TGroupBox *GroupBox2;
        TLabel *Label8;
        TLabel *Label9;
        TLabel *Label14;
        TLabel *Label15;
        TLabel *Label16;
        TLabel *Label1;
        TLabel *Label2;
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall Button2Click(TObject *Sender);
        void __fastcall Button3Click(TObject *Sender);
        void __fastcall ScrollBar9Change(TObject *Sender);
        void __fastcall Button6Click(TObject *Sender);
        void __fastcall Button5Click(TObject *Sender);
        void __fastcall Button4Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall Tpanel_adjust_form(TComponent* Owner);

        void __fastcall Scroll_Bar1_Change();
        TScrollBar *_pScroll_bar;

        HANDLE hComm;
};
//---------------------------------------------------------------------------
extern PACKAGE Tpanel_adjust_form *panel_adjust_form;
//---------------------------------------------------------------------------
#endif
