//---------------------------------------------------------------------------

#ifndef U_LCD_RGBH
#define U_LCD_RGBH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Chart.hpp>
#include <ExtCtrls.hpp>
#include <Series.hpp>
#include <TeEngine.hpp>
#include <TeeProcs.hpp>
#include <ComCtrls.hpp>
#include <Graphics.hpp>
#include <Grids.hpp>
#include <jpeg.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TLCD_RGB : public TForm
{
__published:	// IDE-managed Components
        TChart *Chart1;
        TLineSeries *Winter;
        TLineSeries *Summer;
        TLineSeries *Series1;
        TLineSeries *Series4;
        TButton *Button1;
        TPageControl *PageControl5;
        TTabSheet *Para;
        TTabSheet *Page_R;
        TScrollBar *ScrollBar1;
        TImage *Image1;
        TImage *Image2;
        TPanel *Panel1;
        TStringGrid *reg_grid;
        TImage *Image3;
        TImage *Image4;
        TImage *Image5;
        TCheckBox *CheckBox2;
        TCheckBox *CheckBox3;
        TImage *Image6;
        TScrollBar *ScrollBar2;
        TImage *Image9;
        TTabSheet *Page_G;
        TImage *Image8;
        TStringGrid *StringGrid1;
        TStringGrid *StringGrid2;
        TRadioGroup *RadioGroup2;
        TRadioGroup *RadioGroup1;
        TRadioGroup *RadioGroup3;
        TRadioGroup *RadioGroup15;
        TRadioGroup *RadioGroup16;
        TRadioGroup *RadioGroup17;
        TRadioGroup *RadioGroup18;
        TRadioGroup *RadioGroup19;
        TRadioGroup *RadioGroup20;
        TRadioGroup *RadioGroup21;
        TRadioGroup *RadioGroup22;
        TImage *Image10;
        TComboBox *ComboBox1;
        TLabel *Label1;
        TLabel *Label2;
        TLabel *Label3;
        TEdit *edit_row;
        TButton *Button2;
        TPanel *Panel2;
        TButton *Button3;
        TImage *Image11;
        TImage *Image12;
        TImage *Image13;
        TImage *Image14;
        TImage *Image15;
        TImage *Image16;
        TImage *Image17;
        TImage *Image18;
        TImage *Image19;
        TImage *Image20;
        TImage *Image21;
        TCheckBox *CheckBox1;
        TEdit *Edit1;
        TButton *Button5;
        TEdit *Edit2;
        TEdit *Edit3;
        TRadioGroup *RadioGroup6;
        TRadioGroup *RadioGroup7;
        TBitBtn *Button6;
        TButton *Button4;
        TButton *Button7;
        TRadioGroup *RadioGroup10;
        TRadioGroup *RadioGroup12;
        TRadioGroup *RadioGroup14;
        TRadioGroup *RadioGroup4;
        TRadioGroup *RadioGroup5;
        TButton *Button8;
        TGroupBox *GroupBox1;
        TLabel *Label4;
        TEdit *Edit4;
        TScrollBar *ScrollBar9;
        TLabel *Label5;
        TEdit *Edit5;
        TScrollBar *ScrollBar10;
        TRadioGroup *RadioGroup8;
        TRadioGroup *RadioGroup9;
        TImage *Image7;
        TLabel *Label6;
        TLabel *Label7;
        TLabel *Label8;
        TLabel *Label9;
        TLabel *Label10;
        TLabel *Label11;
        TLabel *Label12;
        TLabel *Label13;
        TLabel *Label14;
        TButton *Button9;
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall Send_1_reg(TObject *Sender);
        void __fastcall reg_gridSelectCell(TObject *Sender, int ACol,
          int ARow, bool &CanSelect);
        void __fastcall ScrollBar1Change(TObject *Sender);
        void __fastcall PageControl5Change(TObject *Sender);
        void __fastcall CheckBox1Click(TObject *Sender);
        void __fastcall ComboBox1Change(TObject *Sender);
        void __fastcall Get_RGB(TObject *Sender);
        void __fastcall Red_click(TObject *Sender);
        void __fastcall Image16Click(TObject *Sender);
        void __fastcall Image17Click(TObject *Sender);
        void __fastcall Image18Click(TObject *Sender);
        void __fastcall Image19Click(TObject *Sender);
        void __fastcall Image20Click(TObject *Sender);
        void __fastcall Image21Click(TObject *Sender);
        void __fastcall Set_default(TObject *Sender);
        void __fastcall Image8Click(TObject *Sender);
        void __fastcall enable(TObject *Sender);
        void __fastcall set_shape(TObject *Sender);
        void __fastcall Set_shape_RadioGroup2Click(TObject *Sender);
        void __fastcall StringGrid1SelectCell(TObject *Sender, int ACol,
          int ARow, bool &CanSelect);
        void __fastcall RadioGroup1Click(TObject *Sender);
        void __fastcall RadioGroup15Click(TObject *Sender);
        void __fastcall RadioGroup6Click(TObject *Sender);
        void __fastcall set_default(TObject *Sender);
        void __fastcall get_shape(TObject *Sender);
        void __fastcall Get_hue_sat(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall Edit2KeyPress(TObject *Sender, char &Key);
        void __fastcall reg_gridDrawCell(TObject *Sender, int ACol,
          int ARow, TRect &Rect, TGridDrawState State);
        void __fastcall Image7Click(TObject *Sender);
        void __fastcall Clear_color(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TLCD_RGB(TComponent* Owner);
        void __fastcall Scroll_Bar1_Change();

        HANDLE m_hComm;

        //__fastcall  Scroll_Bar1_Change();
};
//---------------------------------------------------------------------------
extern PACKAGE TLCD_RGB *LCD_RGB;
//---------------------------------------------------------------------------
#endif
