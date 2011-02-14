//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "U_LCD_RGB.h"

//---------------------------------------------------------------------------
//#include "panel_tuning.cpp"

//---------------------------------------------------------------------------
//#include "U_Setting.h"

                       
#include "send_slider.h"  //thread
//---------------------------------------------------------------------------
//add
#include "DPF.h"
#include "comm.h"

#include "video.h"

#include<math.h>
#include<stdio.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TLCD_RGB *LCD_RGB;

////////////////////////////////////////////////////////////////////////////

//#define debug_test

////////////////////////////////////////////////////////////////////////////
//add
#define _version  "Platform display adjust  1.1.0"

#define video_adjust

TScrollBar *_pScroll_bar=0;

////////////////////////////////////////////////////////////////////////////

int  _color_index=0;
TStringGrid *_pGrid=NULL;

////////////////////////////////////////////////////////////////////////////

bool send_color_command(PC_rw_register rw_reg, byte *data, int data_size =1);

////////////////////////////////////////////////////////////////////////////
int  CMTbl[8][6]={
				{0x8A188A38, 0x004404E1, 0x00001E1E, 0x1433DC13, 0xCD33F50A, 0x3333CE17},
				{0x82208A5D, 0x00230078, 0x00003A84, 0x0633CD17, 0xE144FA02, 0x3433DC08},
				{0x0A3C005D, 0x004402E3, 0x00001e1e, 0x1E22DC13, 0xCD22F50A, 0x22226B01},
	   			{0x024C0044, 0x004402E3, 0x00001e1e, 0x0622CD17, 0xE133FA02, 0x3211F56E},
				{0x8A208250, 0x008B2C7C, 0x00000ebc, 0x1433DC13, 0xCD33F50A, 0x3333CE17},
				{0x8A208A44, 0x00B43DDC, 0x00000b61, 0x0633CD17, 0xE144FA02, 0x3433DC08},
				{0x88208030, 0x007A0EFC, 0x000010C9, 0x1433DC13, 0xCD33F50A, 0x3333CE17},
				{0x8A208844, 0x00391E70, 0x000023EE, 0x0633CD17, 0xE144FA02, 0x3433DC08} };


/*int color_management_[49] = { 0x8A188A38, 0x004404E1, 0x00001E1E, 0x1433DC13, 
	0xCD33F50A, 	0x3333CE17, 0x82208A5D, 0x00230078, 
	
	0x00003A84, 	0x0633CD17, 0xE144FA02,0x3433DC08, 
	0x0A3C005D, 0x004402E3, 	0x00001e1e, 0x1E22DC13,
	
	0xCD22F50A, 0x22226B01, 0x024C0044,	0x004402E3, 
	0x00001e1e, 0x0622CD17, 0xE133FA02, 0x3211F56E,
	
	0x8A208250, 0x008B2C7C, 0x00000ebc, 0x1433DC13,
	0xCD33F50A, 0x3333CE17, 0x8A208A4,   0x00B43DDC,   //0x8A208A4 , 0x8A208A44
	0x00000b61, 0x0633CD17, 0xE144FA02, 0x3433DC08,
	0x88208030, 0x007A0EFC, 0x000010C9, 0x1433DC13, 
	0xCD33F50A, 0x3333CE17, 0x8A208844, 0x00391E70,
	0x000023EE, 0x0633CD17, 0xE144FA02, 0x3433DC08,
0x80000024

};*/

bool _clear_all_color = false;

int  color_management[50]={	0x8A008A00, 0x007F5800, 0x00001020, 0x1033E010, 0xE033F50A, 0x3333E010,
				0x8A008A00, 0x007F1800, 0x00001020, 0x1033E010, 0xE033F50A, 0x3333E010,
				0x8A008A00, 0x007F3800, 0x00001020, 0x1033E010, 0xE033F50A, 0x3333E010,
	   			0x8A008A00, 0x003F2C00, 0x00002082, 0x1033E010, 0xE033F50A, 0x3333E010,
				0x8A008A00, 0x003F4C00, 0x00002082, 0x1033E010, 0xE033F50A, 0x3333E010,
				0x8A008A00, 0x003F0C00, 0x00002082, 0x1033E010, 0xE033F50A, 0x3333E010,
				0x8A008A00, 0x001D0A22, 0x00002082, 0x1033E010, 0xE033F50A, 0x3333E010,

				0x8A008A00, 0x00000000, 0x00000000, 0x0033FF00, 0xFF33FF00, 0x3333FF00,
0x80000024,
0x80000000
};
int  clear_color_management[49]={	
				0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
				0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,

				0x8A008A00, 0x00000000, 0x00000000, 0x0033FF00, 0xFF33FF00, 0x3333FF00,
0x80000024};



/*int color_management[49] ={	0x8A008A00, 0x003F5C00, 0x00002082, 0x1033E010, 0xE033F50A, 0x3333E010,
				0x8A008A00, 0x003F1C00, 0x00002082, 0x1033E010, 0xE033F50A, 0x3333E010,
				0x8A008A00, 0x003F3C00, 0x00002082, 0x1033E010, 0xE033F50A, 0x3333E010,
	   			0x8A008A00, 0x003F2C00, 0x00002082, 0x1033E010, 0xE033F50A, 0x3333E010,
				0x8A008A00, 0x003F4C00, 0x00002082, 0x1033E010, 0xE033F50A, 0x3333E010,
				0x8A008A00, 0x003F0C00, 0x00002082, 0x1033E010, 0xE033F50A, 0x3333E010,
				0x8A008A00, 0x001D0A22, 0x00002082, 0x1033E010, 0xE033F50A, 0x3333E010,
				0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
0x80000024};

*/

////////////////////////////////////////////////////////////////////////////
enum DATATYPE {
    RESERVED         = 0x0000,  //保留
    RW_REGISTER_BITS =0x0001,  //读写寄存器或寄存器的某些bits
    EN_DIS_HUE_SAT   =0x0002,   //开启关闭hue/saturation功能
    CM_SET_DEFAULT  =0x0003,   //设置color management初始值
};

enum FuncID{
    nRESERVED =0,                    // 保留
    CHROMACORING=0x01,           // chroma coring
    COLORMANAGEMENT =0x02,     // color management
 };

////////////////////////////////////////////////////////////////////////
enum color_index {
	red  =0 ,
	green,
	blue,
	cyan,
	magenta,
	yellow,
	flesh
	
};

RGBTRIPLE  color_group[] =
	{
                0x00 , 0x0 ,0xff,
		0x00 , 0xff ,0x0,
                0xff , 0x0 ,0x0,

                0xff , 0xff ,0x0,

	 	0xff , 0x0 ,0xff,
                0x0 , 0xff ,0xff,

                106 , 181 , 0xff
	};

byte _color_hue_register_group[] = { 0,0,0, 0,0,0, 0,0}; 
byte _color_sat_register_group[] = { 0,0,0, 0,0,0, 0,0}; 

PC_rw_register color_set_group[] ={
	{2,9,0x0000,2},
	{2,8,0x0000,3},
	{2,8,0x0000,3},

	{2,25,0x0000,2},//+0x01，即设置寄存器0x00,bit25~bit26=0x01;
	{2,24,0x0000,3},//+0x00，即设置寄存器0x00,bit25~bit26=0x00;
	{2,24,0x0000,3},//+0x00，即设置寄存器0x00,bit25~bit26=0x00;
	
	{2,0,0x0003,8},//+用户设置的值(0~255)，即设置寄存器0x03,bit0~bit7;
	{2,16,0x0003,4},////+用户设置的值(0-7)，即设置寄存器0x03,bit16~bit19;
	{2,20,0x0003,4},////+用户设置的值(0~7)，即设置寄存器0x03,bit20~bit23;
	{2,8,0x0003,8},//+用户设置的值(0~255)，即设置寄存器0x03,bit8~bit15;
	{2,0,0x0004,8},//+用户设置的值(0~255)，即设置寄存器0x04,bit0~bit7; 
	{2,16,0x0004,4},//+用户设置的值(0~7)，即设置寄存器0x04,bit16~bit19;
	{2,20,0x0004,4},//+用户设置的值(0~7)，即设置寄存器0x04,bit20~bit23;
	{2,8,0x0004,8},//+用户设置的值(0~255)，即设置寄存器0x04,bit8~bit15;

	{2,24,0x0003,8},//  +用户设置的值(0~255)，即设置寄存器0x03,bit24~bit31;
	{2,24,0x0005,4},//  +用户设置的值(0~7)，即设置寄存器0x05,bit24~bit27;
	{2,28,0x0005,4},//  +用户设置的值(0~7)，即设置寄存器0x05,bit28~bit31;
	{2,24,0x0004,8},//  +用户设置的值(0~255)，即设置寄存器0x04,bit24~bit31;
	{2,0,0x0005,8},//  +用户设置的值(0~255)， 即设置寄存器0x05,bit0~bit7; 
	{2,16,0x0005,4},//  +用户设置的值(0~7)，即设置寄存器0x05,bit16~bit19;
	{2,20,0x0005,4},//  +用户设置的值(0~7)，即设置寄存器0x05,bit20~bit23;
	{2,8,0x0005,8},//  +用户设置的值(0~255)，即设置寄存器0x05,bit8~bit15;

};


int default_hue[]= { 0x10, 3,3, 0xE0, 0x0a, 3,3, 0xf5};
int default_sat[]= { 0x10, 3,3, 0xE0, 0x10, 3,3, 0xe0};
////////////////////////////////////////////////////////////////////////////

RGBTRIPLE rgb[2000][2000];

Graphics::TBitmap *bitmap;

//用来存放变换后的位图

int i,j,width,height;


 double max(double a, double b)
{
    if (a>b)
        return a;
    else
        return b;
}

 double min(double a, double b)
{
    if (a<b)
        return a;
    else
        return b;
}

 //===================================================================
double  __fooHuetoRGB (double m1, double m2, double h)
{
	if (h < 0)
		h += 1.0 ;
	if (h > 1)
		h -= 1.0 ;
	if (6.0*h < 1)
		return (m1+(m2-m1)*h*6.0) ;
	if (2.0*h < 1)
		return m2 ;
	if (3.0*h < 2.0)
		return (m1+(m2-m1)*((2.0/3.0)-h)*6.0) ;
	return m1 ;
}


//////////////////////////////////////////////////////////////////////////
void fooRGBtoHLS (RGBTRIPLE rgb, double * H, double * L, double * S)
{
	double		delta ;
	double		r = (double) rgb.rgbtRed / 255 ;
	double		g = (double) rgb.rgbtGreen / 255 ;
	double		b = (double) rgb.rgbtBlue / 255 ;
	double		cmax = max(r, max (g, b)) ;
	double		cmin = min(r, min (g, b)) ;
	*L = (cmax+cmin) / 2.0 ;
	if (cmax == cmin)
	{
		*S = 0 ;
		*H = 0 ;
	}
	else
	{
		if (*L < 0.5)
			*S = (cmax-cmin) / (cmax+cmin) ;
		else
			*S = (cmax-cmin) / (2.0-cmax-cmin) ;
		delta = cmax - cmin ;
		if (r == cmax)
			*H = (g-b) / delta ;
		else
			if (g == cmax)
				*H = 2.0 + (b-r) / delta ;
			else
				*H = 4.0 + (r-g) / delta ;
		*H /= 6.0 ;
		if (*H < 0.0)
			*H += 1 ;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////
RGBTRIPLE  fooHLStoRGB (const double& H, const double& L, const double& S)
{
	double		r, g, b ;
	double		m1, m2 ;

	if (S == 0)
		r = g = b = L ;
	else
	{
		if (L <= 0.5)
			m2 = L * (1.0+S) ;
		else
			m2 = L + S - L*S ;
		m1 = 2.0*L - m2 ;
		r = __fooHuetoRGB (m1, m2, H+1.0/3.0) ;
		g = __fooHuetoRGB (m1, m2, H) ;
		b = __fooHuetoRGB (m1, m2, H-1.0/3.0) ;
	}
	RGBTRIPLE		retRGB ;
	retRGB.rgbtRed = max (min ((int)(r*255), 0xFF), 0) ;
	retRGB.rgbtGreen = max (min ((int)(g*255), 0xFF), 0) ;
	retRGB.rgbtBlue = max (min ((int)(b*255), 0xFF), 0) ;
	return retRGB ;
}

////////////////////////////////////////////////////////////////////////////////////////////
//hue
//sat
byte _enable_group[]=
{   0x32, 0x30,
    0x11, 0x10,
    0x21, 0x20,
};

PC_rw_register hue_sat_group_1[] ={
        {write_reg_bit,11, 0x0000,1},
        {write_reg_bit,27, 0x0000,1}
}  ;

PC_rw_register chroma_group[] ={
        {write_reg_bit,0, 0x0031,8},
        {write_reg_bit,8, 0x0031,4}
}  ;
PC_rw_register hue_sat_group[] ={ 
	{2,0, 0x0000,8},
	{2,16, 0x0000,8},
	 
	{2,16, 0x002B,8} ,
	{2,0, 0x002C,8},
	{2,8, 0x002C,8},

	{2,0, 0x002B,8},
	{2,8, 0x002B,8},
}  ;


bool send_black_extend( byte *data, int data_size , PC_rw_register rw_reg);

////////////////////////////////////////////////////////////////////////////
bool send_black_extend( byte *pdata, int data_size , PC_rw_register rw_reg)
{
	send_reg_command( pdata,  data_size, rw_reg, 3, 1 );

	return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool send_chroma( byte *pdata, int data_size , PC_rw_register rw_reg)
{
	send_reg_command( pdata,  data_size, rw_reg, 1, 1 );

	return true;
}
//////////////////////////////////////////////////////////////////////////////
//---------------------------------------------------------------------------
__fastcall TLCD_RGB::TLCD_RGB(TComponent* Owner)
        : TForm(Owner)
{
      Caption = _version;

	TSend_Slider *psend_slider_thread;	  
	psend_slider_thread = new TSend_Slider(false);

	//////////////////////////////////////////////

	for(i = 0; i< Image9->Width; i++)
	for(int j = 0; j< Image9->Height; j++)
	{
		Image9->Canvas->Pixels[i][j]=RGB(0xff , 0x0 ,0x0);;
	Image10->Canvas->Pixels[i][j]=RGB(0xff , 0x0 ,0x0);;

	}

	////////////////////////////////////////////////////////////////////////
	m_hComm = Open_Comm("COM1");

        if(m_hComm == NULL)
                ShowMessage("can not open com1");
			
      ////////////////////////////////////////////////////////////////////////
	TStringGrid *pGrid = reg_grid;
	AnsiString str;	


        pGrid->RowCount = 0x32;
        pGrid->ColCount = 5;

	pGrid->DefaultColWidth = 50;
        int i =0;

        ////////////////////////////////////////////////////////////////////////
        for(i =0; i< (pGrid->RowCount -1) ; i++)
        {
	        pGrid->Cells[0][i+1] = str.sprintf("%2X", i);   //row index

        }
         for(i =0; i< (pGrid->ColCount -1); i++)
        {
             pGrid->Cells[i+1][0] = str.sprintf("%2X", i);     //col  index
        }
        ////////////////////////////////////////////////////////////////

	 for(i =0; i< ( pGrid->RowCount -1); i++)
        {
             int value =   	color_management[i];
            for(int k =0; k< (pGrid->ColCount-1); k++)
            	{
            	     int reg = value>>( 8 * k);
		     reg &= 0xff;			  
	             pGrid->Cells[pGrid->ColCount - k-1][i+1] = str.sprintf("%2X",  reg);   //row index
            	}

        }
         edit_row->Text = "1";

         /////////////////////////////////////////////////
         int cell_width = 76;
	  int col_count = 10;
         pGrid = StringGrid1;
         pGrid->DefaultColWidth = 80;
         pGrid->ColWidths[0] = 110;
         pGrid->RowHeights[0] = 1;

        pGrid->ColCount = col_count;
        pGrid->RowCount = 9;
        pGrid->Width = 780 +cell_width;
        //pGrid_1->Col[0]-> = 9;

        i =1;
        pGrid->Rows[i++]->Text = "hue_luma_low";
        pGrid->Rows[i++]->Text = "hue_luma_low_slope";
        pGrid->Rows[i++]->Text = "hue_luma_high_slope";
        pGrid->Rows[i++]->Text = "hue_luma_high";
        pGrid->Rows[i++]->Text = "hue_sat_low";
        pGrid->Rows[i++]->Text = "hue_sat_low_slope";
        pGrid->Rows[i++]->Text = "hue_sat_high_slope";
        pGrid->Rows[i++]->Text = "hue_sat_high";

      int row,col;
	for(row =0; row< pGrid->RowCount -1; row++)
		for( col =0; col< (pGrid->ColCount-1); col++)
            	{
            	     pGrid->Cells[col+1][row +1] = str.sprintf("%2X",  default_hue[row] );
		    
            	}

 	/////////////////////////////////////////////////
         pGrid = StringGrid2;
         pGrid->DefaultColWidth = 80;
         pGrid->ColWidths[0] = 110;
         pGrid->RowHeights[0] = 1;

        pGrid->ColCount = col_count;
        pGrid->RowCount = 9;
        pGrid->Width = 770 +cell_width;
        //pGrid_1->Col[0]-> = 9;

        i =1;
        pGrid->Rows[i++]->Text = "sat_luma_low";
        pGrid->Rows[i++]->Text = "sat_luma_low_slope";
        pGrid->Rows[i++]->Text = "sat_luma_high_slope";
        pGrid->Rows[i++]->Text = "sat_luma_high";
        pGrid->Rows[i++]->Text = "sat_sat_low";
        pGrid->Rows[i++]->Text = "sat_sat_low_slope";
        pGrid->Rows[i++]->Text = "sat_sat_high_slope";
        pGrid->Rows[i++]->Text = "sat_sat_high";

	for(row =0; row< pGrid->RowCount -1; row++)
		for( col =0; col< (pGrid->ColCount-1); col++)
            	{
            	     pGrid->Cells[col+1][row +1] = str.sprintf("%2X",  default_sat[row] );
		    
            	}
       
	//////////////////////////////////////////////////////////////////////////	
	     TRadioGroup *pGroup[] = {
        RadioGroup1, RadioGroup2,
        RadioGroup3, RadioGroup4,
        RadioGroup5, RadioGroup10,

        RadioGroup12,
         RadioGroup14,
          RadioGroup8,
          
        RadioGroup15, RadioGroup16,
        RadioGroup17, RadioGroup18,
        RadioGroup19, RadioGroup20,
        RadioGroup21, RadioGroup22,
        RadioGroup9
         };

      for(int i = 0; i< sizeof(pGroup)/sizeof(TRadioGroup *); i++)
      {
              pGroup[i]->Height = 68;;// pGroup[i]->Items = TempList;
              pGroup[i]->Width = 30;

              pGroup[i]->Top = 48 + (i /9) *270;
              pGroup[i]->Left = 152 + (i %9) * 80;
       }
}
//---------------------------------------------------------------------------
void __fastcall TLCD_RGB::Button1Click(TObject *Sender)
{
      int n = sizeof(bool);
      n = sizeof(int);
      ////////////////////////////////////////////////////////////////
      TStringGrid *pGrid = reg_grid;
      int row ;
      int byte;
      int reg =0;

      char *stop;
      row = 1;

      for(int k =0; k< (pGrid->ColCount-1); k++)
      {
           byte = strtol( pGrid->Cells[pGrid->ColCount - k-1][row +1].c_str() , &stop, 16);
           reg |= byte<<( 8 * k);
      }
      return;
 //Chart1->Series[0]->FillSampleValues(_Axis_X_Len);
       int nY = 100;
       Chart1->Width = 800;
       Chart1->Height = 600;
       Chart1->LeftAxis->SetMinMax(0, 1024);
       int nIndex =0;
       for(int nX =0; nX < 255; nX++)
       {
          nY = nX * 3.5;
          for(int nIndex =0; nIndex < 3; nIndex++)
                Chart1->Series[nIndex]->AddXY(nX,  nY+nIndex * 39,  "",  clTeeColor);
       }
}

//---------------------------------------------------------------------------
void send_color_group_command()
{
	int color_index = _color_index;
	int i =0;
	char *stop;

	PC_rw_register rw_reg;
	byte data;

	TStringGrid *pGrid = LCD_RGB->StringGrid1;


        TRadioGroup *radio_group[]={ LCD_RGB->RadioGroup1, LCD_RGB->RadioGroup2, LCD_RGB->RadioGroup3, LCD_RGB->RadioGroup4, LCD_RGB->RadioGroup5,
				LCD_RGB->RadioGroup10,LCD_RGB->RadioGroup12,LCD_RGB->RadioGroup14, LCD_RGB->RadioGroup8, 
				LCD_RGB->RadioGroup15,LCD_RGB->RadioGroup16, LCD_RGB->RadioGroup17, LCD_RGB->RadioGroup18, LCD_RGB->RadioGroup19,
				LCD_RGB->RadioGroup20,LCD_RGB->RadioGroup21, LCD_RGB->RadioGroup22, LCD_RGB->RadioGroup9};

	///////////////////////////////////////////////////////
	for(i = 0;i < sizeof(color_set_group)/sizeof(rw_reg)  ; i++)
	{
		memcpy(&rw_reg, (char *)&color_set_group[i], sizeof(rw_reg) );
		rw_reg.addReg += color_index*6 ;

		///////////////////////////////////////////////
		//data
		if(i <4)
		{
			if(radio_group[color_index]->ItemIndex == 0)
	                data = 1;
			else
				data =0;
		}
		else
            	{
            	      int flag =12;
            		if(i < flag) 
            		{
				pGrid = LCD_RGB->StringGrid1;
				data = strtol( pGrid->Cells[ color_index +2][i +1].c_str() , &stop,  16);
            		}	
			else
			{
				pGrid = LCD_RGB->StringGrid2;		
				data = strtol( pGrid->Cells[ color_index +2][i +1 -flag].c_str() , &stop,  16);
			}	
            	}
		///////////////////////////////////////////////
		bool re = send_color_command(rw_reg, &data);
		if(!re) break;
	}	
}
//---------------------------------------------------------------------------

bool send_color_command(PC_rw_register rw_reg, byte *data, int data_size )
{
#ifndef debug_test
       	if(Initial_Comm_4_DPF())
#else			
        if(1)
#endif						
       {

              unsigned char Array[600];

              data_type_t data_type;

              int header_size = sizeof(data_type);
              int reg_size = sizeof(rw_reg);

              memset(Array, NULL, sizeof(Array));
              memset((char *)&data_type, NULL, sizeof(data_type));

	      ////////////////////////////////////////////////////////////////
		data_type.func_id = 2;
		data_type.datatype = 1;
		
		//////////////////////////////////////////////////////////////////
               memcpy(Array, (char *)&data_type, header_size );
               memcpy(Array + header_size, (char *)&rw_reg, reg_size);

		if(data_size)
			memcpy(Array + header_size +reg_size ,(char *)data, data_size);

               //Send_Data(Array, sizeof(set) +  sizeof(rw_reg)  + sizeof(reg), TTY_SERVICE_ID_DISPLAY);
               Send_Data(Array, header_size +  reg_size  +data_size, 0x0a);
        }
	else
		return false;


	return true;

}
bool send_color_command_1(PC_rw_register rw_reg, byte data, int data_size =1)
{
       	if(Initial_Comm_4_DPF())
      //  if(1)
       {
		//char set[] = {0x00,0x02,0x01,0x00}; //
		unsigned char Array[600];
		
		data_type_t data_type;
		//PC_rw_register rw_reg;

		int header_size = sizeof(data_type);
              int reg_size = sizeof(rw_reg);
		if(!data_size)	  
              data_size= sizeof(data);;

		memset(Array, NULL, sizeof(Array));
		memset((char *)&data_type, NULL, sizeof(data_type));
		//memset((char *)&rw_reg, NULL, sizeof(rw_reg));
		
	      ////////////////////////////////////////////////////////////////
		data_type.func_id = COLORMANAGEMENT;
		data_type.datatype =  EN_DIS_HUE_SAT;
		
		//////////////////////////////////////////////////////////////////
		reg_size = 0;
               memcpy(Array, (char *)&data_type, header_size );
               //memcpy(Array + header_size, (char *)&rw_reg, reg_size);
		
		//memcpy(Array + header_size +reg_size ,(char *)&data, data_size);
		if(data_size)
			memcpy(Array + header_size  ,(char *)&data, data_size);

               //Send_Data(Array, sizeof(set) +  sizeof(rw_reg)  + sizeof(reg), TTY_SERVICE_ID_DISPLAY);
               Send_Data(Array, header_size +  reg_size  +data_size, 0x0a);
        }
	else
		return false;


	return true;

}
/////////////////////////////////////////////////////////////////////////
void __fastcall TLCD_RGB::Send_1_reg(TObject *Sender)
{
       if(Initial_Comm_4_DPF())
       {
           //send command
          data_type_t data_type;

          PC_rw_register rw_reg;

          unsigned char Array[600];

          memset(Array, NULL, sizeof(Array));
          memset((char *)&data_type, NULL, sizeof(data_type));
          memset((char *)&rw_reg, NULL, sizeof(rw_reg));

          ////////////////////////////////////////////////////////////////
          TStringGrid *pGrid = reg_grid;
          int row ;
          int byte;
          int reg =0;

          char *stop;
          row = strtol(edit_row->Text.c_str(), &stop, 16);

          for(int k =0; k< (pGrid->ColCount-1); k++)
          {
               byte = strtol( pGrid->Cells[pGrid->ColCount - k-1][row +1].c_str() , &stop,  16);
               reg |= byte<<( 8 * k);
          }


          data_type.func_id = 2;
          data_type.datatype = 1;

          rw_reg.addReg =row;
          rw_reg.RegBitLength = 1;
          //////////////////////////////////////////////////////////////////
          int header_size = sizeof(data_type);
          int datatype_size = sizeof(rw_reg);
          int reg_size;

          reg_size = sizeof(reg);

          //////////////////////////////////////////////////////////////////
          #if 0
          int color_array[49];
          memset(color_array, NULL, sizeof(color_array) );
          for(int i=0; i<pGrid->RowCount-1 ;i++)
          for(int k =0; k< (pGrid->ColCount-1); k++)
          {
               byte = strtol( pGrid->Cells[pGrid->ColCount - k-1][i+1].c_str() , &stop,  16);
               color_array[i] |= byte<<( 8 * k);
          }

          reg_size   = sizeof(color_array);//
          rw_reg.addReg =0; // row;
          rw_reg.RegBitLength =49;;
          #endif
          //////////////////////////////////////////////////////////////////
          memcpy(Array, (char *)&data_type, header_size );
          memcpy(Array + header_size, (char *)&rw_reg, datatype_size);
          memcpy(Array + header_size +datatype_size , (char *)&reg, reg_size);

          //memcpy(Array + header_size +datatype_size ,(char *)&color_array, reg_size);

          //Send_Data(Array, sizeof(set) +  sizeof(rw_reg)  + sizeof(reg), TTY_SERVICE_ID_DISPLAY);
          Send_Data(Array, header_size +  datatype_size  +reg_size, 0x0a);
        }
}
//---------------------------------------------------------------------------


void __fastcall TLCD_RGB::reg_gridSelectCell(TObject *Sender, int ACol,
      int ARow, bool &CanSelect)
{
         AnsiString str;
         edit_row->Text = str.sprintf("%X", ARow-1) ;
}
//---------------------------------------------------------------------------
void __fastcall TLCD_RGB::ScrollBar1Change(TObject *Sender)
{
	_pScroll_bar =  (TScrollBar *)Sender;
        return;

        ///////////////////////////////////////////////////////

	TEdit *pEdit;
	TScrollBar *pScrollBar = (TScrollBar *)Sender;

	PC_rw_register rw_reg;
	byte data;
	int color_index;

	TColor color;

	width=Image9->Picture->Width;
	height=Image9->Picture->Height;

	bitmap=new Graphics::TBitmap;

	bitmap->Width=width;
	bitmap->Height=height;

	data=pScrollBar->Position  ;
        ///////////////////////////////////////////////////////
       if(pScrollBar == ScrollBar1)
       {
		pEdit = Edit2;
		memcpy(&rw_reg, (char *)&hue_sat_group[0], sizeof(rw_reg) );
       }
	else
	{
		pEdit = Edit3;
		memcpy(&rw_reg, (char *)&hue_sat_group[1], sizeof(rw_reg) );
	}

	color_index = ComboBox1->ItemIndex;
	pEdit->Text = IntToStr(data);

	rw_reg.addReg += color_index*6 ;

	bool re = send_color_command(rw_reg, &data);
        ///////////////////////////////////////////////////////

	for(i=0;i< width-1;i++)
		for(j=0;j< height-1;j++)
		{
        		color=Image9->Canvas->Pixels[i][j];

			rgb[i][j].rgbtRed=GetRValue(color);
			rgb[i][j].rgbtGreen=GetGValue(color);
			rgb[i][j].rgbtBlue=GetBValue(color);

			////////////////////////////////////////////////////
			static int k =33;
			k+=3;
                        int	iPercentHue = k; //128 * iPercentHue / 100 ; // 转换成x/128
                        int	iPercentSat = 95;//128 * iPercentSat / 100 ; // 转换成x/128

                        iPercentHue = ScrollBar1->Position;
                        iPercentSat = ScrollBar2->Position;

			iPercentSat = 128 * iPercentSat / 100 ;
			iPercentHue = 128 * iPercentHue / 100 ;

					double		H, L, S ;
			fooRGBtoHLS (*(RGBTRIPLE *)&rgb[i][j], &H, &L, &S);
                        if (iPercentHue != 128)
                                H = H * iPercentHue / 128 ;
                        if (iPercentSat != 128)
                                S = S * iPercentSat / 128 ;
			//* (RGBTRIPLE *) rgb = fooHLStoRGB (H, L, S) ;
			//bitmap->Canvas->Pixels[i][j]=RGB(rgb[i][j].rgbtRed , rgb[i][j].rgbtGreen, rgb[i][j].rgbtBlue);;

			/////////////////////////////////////
			//RGBTRIPLE  rgb_0 = fooHLStoRGB (H, L, S) ;
			//bitmap->Canvas->Pixels[i][j]=RGB(rgb_0.rgbtRed , rgb_0.rgbtGreen,rgb_0.rgbtBlue);;

			* (RGBTRIPLE *) &rgb[i][j] = fooHLStoRGB (H, L, S) ;
			bitmap->Canvas->Pixels[i][j]=//RGB(rgb[i][j].rgbtRed , rgb[i][j].rgbtGreen, rgb[i][j].rgbtBlue);;
                                        RGB(rgb[i][j].rgbtBlue , rgb[i][j].rgbtGreen, rgb[i][j].rgbtRed);;


		}
	Image9->Picture->Bitmap->Assign(bitmap);


}

//---------------------------------------------------------------------------
/*
sample:
pls input start degree :60
0x2B[Byte0~1]-->0x1000

pls input range  :30
0x2B[Byte2]-->0x3f  ;
0x2C[Byte0~1]:=0x2082 !

*/

void __fastcall TLCD_RGB::Scroll_Bar1_Change()
{
	TEdit *pEdit;
	TScrollBar *pScrollBar = _pScroll_bar;;// = (TScrollBar *)Sender;
	_pScroll_bar = 0;
	PC_rw_register rw_reg;
	unsigned int data;
	unsigned int value;
	int color_index;
        bool re;
	TColor color;

	if(!pScrollBar) return;

	data=pScrollBar->Position  ;
  	color_index = ComboBox1->ItemIndex;
	
        ///////////////////////////////////////////////////////
       if(pScrollBar == ScrollBar1)		//hue
       {
		pEdit = Edit2;
		memcpy(&rw_reg, (char *)&hue_sat_group[0], sizeof(rw_reg) );
       }	
	else if(pScrollBar == ScrollBar2)		//saturation
	{
		pEdit = Edit3;	
		memcpy(&rw_reg, (char *)&hue_sat_group[1], sizeof(rw_reg) );

		///////////////////////////////////////////////////////////
                write_register(m_hComm, 0, 0x8aff8aff);
                #if 0

                AnsiString str, stmp;
		{
			stmp.sprintf("%d", 0)  ;
			str = "echo wc 0x1d70  " + stmp + "  > /sys/bus/pseudo/drivers/amlogic_debug/amlogic_reg" ;
		        str = write_command_line(m_hComm, str);

			stmp.sprintf("0x%x", 0x8aff8aff)  ;
			str = "echo wc 0x1d71  " + stmp + "  > /sys/bus/pseudo/drivers/amlogic_debug/amlogic_reg" ;
			str = write_command_line(m_hComm, str);   
		}
                #endif
		return;
		///////////////////////////////////////////////////////////

	}
	else if(pScrollBar == ScrollBar9)	//range
	{
		pEdit = Edit4;	
		pEdit->Text = IntToStr(data);
		
		memcpy(&rw_reg, (char *)&hue_sat_group[2], sizeof(rw_reg) );
		//rw_reg.addReg += color_index*6 ;
		//data  // (int)(((float)0x100/120)*(拖动条的值))
		data = (int)(((float)0xff/120)*data);
		bool re = send_color_command(rw_reg, (char *)&data);

		
		//data //      ((1<<20)/(int)(((float)0x100/120)*(拖动调的值))+1)>>1 
		data=pScrollBar->Position  ;
		value = ((1<<20)/(int)(((float)0xff/120)*data)+1)>>1 ;

		memcpy(&rw_reg, (char *)&hue_sat_group[3], sizeof(rw_reg) );
		data = (value&0xff);
		re = send_color_command(rw_reg, (char *)&data);

		memcpy(&rw_reg, (char *)&hue_sat_group[4], sizeof(rw_reg) );
		data = (value>>8);
		re = send_color_command(rw_reg, (char *)&data);
		
		
		return;
		
	}
	else if(pScrollBar == ScrollBar10)	//start degree
	{
		pEdit = Edit5;	
		pEdit->Text = IntToStr(data);
		
		//data //(int)(((float)0x6000/360)*(拖动条的值))
		value = (int)(((float)0x6000/360)*data);
		
		memcpy(&rw_reg, (char *)&hue_sat_group[5], sizeof(rw_reg) );
		data = (value&0xff);
		re = send_color_command(rw_reg, (char *)&data);

		memcpy(&rw_reg, (char *)&hue_sat_group[6], sizeof(rw_reg) );
		data = (value>>8);
		re = send_color_command(rw_reg, (char *)&data);
		return;
	}

	rw_reg.addReg += color_index*6 ;
	pEdit->Text = IntToStr(data);
	
	re = send_color_command(rw_reg, (char *)&data);
///////////////////////////////////////////////////////
#if 0

	width=Image9->Picture->Width;
	height=Image9->Picture->Height;

	bitmap=new Graphics::TBitmap;

	bitmap->Width=width;
	bitmap->Height=height;
	
	for(i=0;i< width-1;i++)
		for(j=0;j< height-1;j++)
		{

			color=Image9->Canvas->Pixels[i][j];

			rgb[i][j].rgbtRed=GetRValue(color);
			rgb[i][j].rgbtGreen=GetGValue(color);
			rgb[i][j].rgbtBlue=GetBValue(color);

			////////////////////////////////////////////////////
			static int k =33;
			k+=3;
				int	iPercentHue = k; //128 * iPercentHue / 100 ; // 转换成x/128
				int	iPercentSat = 95;//128 * iPercentSat / 100 ; // 转换成x/128

                                iPercentHue = ScrollBar1->Position;
                                iPercentSat = ScrollBar2->Position;

			iPercentSat = 128 * iPercentSat / 100 ;
			iPercentHue = 128 * iPercentHue / 100 ;

					double		H, L, S ;
			fooRGBtoHLS (*(RGBTRIPLE *)&rgb[i][j], &H, &L, &S);
								if (iPercentHue != 128)
	     								H = H * iPercentHue / 128 ;
								if (iPercentSat != 128)
									S = S * iPercentSat / 128 ;
			//* (RGBTRIPLE *) rgb = fooHLStoRGB (H, L, S) ;
			//bitmap->Canvas->Pixels[i][j]=RGB(rgb[i][j].rgbtRed , rgb[i][j].rgbtGreen, rgb[i][j].rgbtBlue);;

			/////////////////////////////////////
			//RGBTRIPLE  rgb_0 = fooHLStoRGB (H, L, S) ;
			//bitmap->Canvas->Pixels[i][j]=RGB(rgb_0.rgbtRed , rgb_0.rgbtGreen,rgb_0.rgbtBlue);;

			* (RGBTRIPLE *) &rgb[i][j] = fooHLStoRGB (H, L, S) ;
			bitmap->Canvas->Pixels[i][j]=//RGB(rgb[i][j].rgbtRed , rgb[i][j].rgbtGreen, rgb[i][j].rgbtBlue);;
                                        RGB(rgb[i][j].rgbtBlue , rgb[i][j].rgbtGreen, rgb[i][j].rgbtRed);;


		}
	Image9->Picture->Bitmap->Assign(bitmap);
#endif	
        
}

void __fastcall TLCD_RGB::PageControl5Change(TObject *Sender)
{
#if 0
     TRadioGroup *pGroup[] = {
        RadioGroup1, RadioGroup2,
        RadioGroup3, RadioGroup4,
        RadioGroup5, RadioGroup10,

        RadioGroup12,
         RadioGroup14,
        RadioGroup15, RadioGroup16,
        RadioGroup17, RadioGroup18,
        RadioGroup19, RadioGroup20,
        RadioGroup21, RadioGroup22,
         };
  return;

         bool visible = false;
         if(PageControl5->ActivePage != Page_G)
    {
        visible = false;
    }
    else
    {
        visible = true;
    }

    for(int i = 0; i< sizeof(pGroup)/sizeof(TRadioGroup *); i++)
             pGroup[i]->Visible = visible;
#endif	

}
//---------------------------------------------------------------------------

void __fastcall TLCD_RGB::CheckBox1Click(TObject *Sender)
{
/*
        TCheckBox *pGroup[] = {CheckBox1, CheckBox4,
                CheckBox6 ,CheckBox8 ,
                CheckBox9 ,CheckBox10 ,
                CheckBox11,CheckBox12 ,
                CheckBox13 ,CheckBox14 ,
                CheckBox15 ,CheckBox16 ,
                CheckBox17 ,CheckBox18 ,
                CheckBox19 ,CheckBox20 ,
                CheckBox21 ,CheckBox22 ,
                 CheckBox23 ,CheckBox24 ,
                CheckBox25 ,CheckBox26 ,
                CheckBox27 ,CheckBox28 ,
                CheckBox29 ,CheckBox30 ,
                 CheckBox31 ,CheckBox32 ,
                CheckBox33 ,CheckBox34 ,
                CheckBox35 ,CheckBox36 ,

                };
        TCheckBox *pOne_Check = (TCheckBox *)Sender;
        TCheckBox *pAnother_Check = 0;

        if(0)
        if(!pOne_Check->Checked )
        {
             pOne_Check->Checked = true;
                 return;
         }        


        for(int i = 0; i< sizeof(pGroup)/sizeof(TCheckBox *); i++)
        {
             pGroup[i]->Visible = false;
             
             if(pGroup[i] ==  pOne_Check)
             {
                 if(i%2)
                   pAnother_Check = pGroup[i-1];
                 else
                   pAnother_Check = pGroup[i+1];

                 if(pOne_Check->Checked )
                        pAnother_Check->Checked = false;
                              
               return;  

             }

        }
        */
        //ShowMessage("a");       
}
//---------------------------------------------------------------------------

void __fastcall TLCD_RGB::ComboBox1Change(TObject *Sender)
{
	int i;

        int index = ComboBox1->ItemIndex;
	if(index == (ComboBox1->DropDownCount -1))	
	{
		Image10->Visible = false;
		Button7->Visible = false;
		
		GroupBox1->Visible = true;
		Button9->Visible = true;
	}
	else
	{
		Image10->Visible = true;
		Button7->Visible = true;

		GroupBox1->Visible = false;
		Button9->Visible = false;
		
	        for(i = 0; i< Image9->Width; i++)
	        for(int j = 0; j< Image9->Height; j++)
	        {
	        	Image9->Canvas->Pixels[i][j]=RGB(color_group[index].rgbtRed , color_group[index].rgbtGreen, color_group[index].rgbtBlue);
			Image10->Canvas->Pixels[i][j]=RGB(color_group[index].rgbtRed , color_group[index].rgbtGreen, color_group[index].rgbtBlue);

	        }
	}

	 int color_index = ComboBox1->ItemIndex;
	 TEdit *pEdit=0;
	 TScrollBar *pScrollBar;

	 int data = _color_hue_register_group[color_index];
	 pEdit = Edit2;;
	 pScrollBar = ScrollBar1 ;
	 pEdit->Text = IntToStr(data);
	 pScrollBar->Position   = data ;

	 data = _color_sat_register_group[color_index];
	 pEdit = Edit3;;
	 pScrollBar = ScrollBar2;
	 pEdit->Text = IntToStr(data);
	 pScrollBar->Position   = data ;

}
//---------------------------------------------------------------------------

void __fastcall TLCD_RGB::Get_RGB(TObject *Sender)
{
      TStringGrid *pGrid = reg_grid;
      AnsiString str;

      Button3->Enabled = false;
	int reg_value[49];
        memset(&reg_value, 0, sizeof(reg_value));
     ////////////////////////////////////////////////////////////////////////////
      //send get command
	PC_rw_register rw_reg= {read_reg,  _rw_register_default_start_bit, 0x0000, 49};
       // rw_reg.RegBitLength =1;
	byte data;

	bool re = send_color_command(rw_reg, &data, 0);
	
	if(!re)
        {
        Button3->Enabled = true;
         return;
        }
	/////////////////////////////////////////////////////////////////////
      //read comm
      
	char  buf[1024];
        int nread_len =  Read_Comm( buf ,sizeof(reg_value));
	if( nread_len >= sizeof(reg_value) )           //
        {
               memcpy(reg_value,  buf + sizeof(PC_rw_register), sizeof(reg_value) );
        }
        else
        {
            ShowMessage("read data number : " +  IntToStr(nread_len));
        }

      //display
	 for(i =0; i< ( pGrid->RowCount -1); i++)
        {
             int value =   	reg_value[i];
             
            for(int k =0; k< (pGrid->ColCount-1); k++)
            	{
            	     int reg = value>>( 8 * k);
		     reg &= 0xff;			  
	             pGrid->Cells[pGrid->ColCount - k-1][i+1] = str.sprintf("%2X",  reg);   //row index
            	}

        }
        Button3->Enabled = true;

}
//---------------------------------------------------------------------------

void __fastcall TLCD_RGB::Red_click(TObject *Sender)
{
        _color_index = 0;        
	//send_color_group_command();
}
//---------------------------------------------------------------------------

void __fastcall TLCD_RGB::Image16Click(TObject *Sender)
{
        _color_index = 1;        
	//send_color_group_command();
}
//---------------------------------------------------------------------------

void __fastcall TLCD_RGB::Image17Click(TObject *Sender)
{
         _color_index = 2;       
	//send_color_group_command();
}
//---------------------------------------------------------------------------

void __fastcall TLCD_RGB::Image18Click(TObject *Sender)
{
        _color_index = 3;      
	//send_color_group_command();
}
//---------------------------------------------------------------------------

void __fastcall TLCD_RGB::Image19Click(TObject *Sender)
{
        _color_index = 4;        
	//send_color_group_command();
}
//---------------------------------------------------------------------------

void __fastcall TLCD_RGB::Image20Click(TObject *Sender)
{
        _color_index = 5;        
	//send_color_group_command();
}
//---------------------------------------------------------------------------

void __fastcall TLCD_RGB::Image21Click(TObject *Sender)
{
        _color_index = 6;
	//send_color_group_command();		
}
//---------------------------------------------------------------------------

void __fastcall TLCD_RGB::Set_default(TObject *Sender)
{
	AnsiString str, stmp;
       str.sprintf("0x%d", 0x100)  ;

	//第一条命令写地址，第二条命令把值写入地址：
	//echo wc 0x1d70 address > /sys/bus/pseudo/drivers/amlogic_debug/amlogic_reg
	//echo wc 0x1d71 32bit_value >  /sys/bus/pseudo/drivers/amlogic_debug/amlogic_reg
	//color_management	

	for(int i = 0; i < 50; i++)
	{
                write_register(m_hComm, i, color_management[i]);
                
                #if 0
		stmp.sprintf("0x%x", i)  ;
		str = "echo wc 0x1d70  " + stmp + "  > /sys/bus/pseudo/drivers/amlogic_debug/amlogic_reg" ;
	        str = write_command_line(m_hComm, str);

		stmp.sprintf("0x%x", color_management[i])  ;
		str = "echo wc 0x1d71  " + stmp + "  > /sys/bus/pseudo/drivers/amlogic_debug/amlogic_reg" ;
		str = write_command_line(m_hComm, str);
                #endif 
	}

	
	
}
#if 0
{
        AnsiString str;
        str.sprintf("0x%d", 0x100)  ;
       if(Initial_Comm_4_DPF())
       {
           //send command
          data_type_t data_type;

          PC_rw_register rw_reg;

          //char ur_rw_register[]={0x00,0x00,0x0000,0x01};
          unsigned char Array[600];

          memset(Array, NULL, sizeof(Array));
          memset((char *)&data_type, NULL, sizeof(data_type));
          memset((char *)&rw_reg, NULL, sizeof(rw_reg));

          ////////////////////////////////////////////////////////////////
          TStringGrid *pGrid = reg_grid;
          int row ;
          int byte;
          int reg =0;

          char *stop;
          row = strtol(edit_row->Text.c_str(), &stop, 16);

          for(int k =0; k< (pGrid->ColCount-1); k++)
          {
               byte = strtol( pGrid->Cells[pGrid->ColCount - k-1][row +1].c_str() , &stop,  16);
               reg |= byte<<( 8 * k);
          }


          data_type.func_id = 2;
          data_type.datatype = 1;

          rw_reg.addReg =row;
          rw_reg.RegBitLength = 1;
          //////////////////////////////////////////////////////////////////
         int header_size = sizeof(data_type);
         int datatype_size = sizeof(rw_reg);
         int reg_size;

         reg_size = sizeof(reg);

          //////////////////////////////////////////////////////////////////
          #if 1
          int color_array[49];
          memset(color_array, NULL, sizeof(color_array) );
          for(int i=0; i<pGrid->RowCount-1 ;i++)
          for(int k =0; k< (pGrid->ColCount-1); k++)
          {
               byte = strtol( pGrid->Cells[pGrid->ColCount - k-1][i+1].c_str() , &stop,  16);
               color_array[i] |= byte<<( 8 * k);
          }

          reg_size   = sizeof(color_array);//
          rw_reg.addReg =0; // row;
         rw_reg.RegBitLength =49;;
          #endif
		

          //////////////////////////////////////////////////////////////////
         memcpy(Array, (char *)&data_type, header_size );
         memcpy(Array + header_size, (char *)&rw_reg, datatype_size);
          memcpy(Array + header_size +datatype_size , (char *)&reg, reg_size);

          //memcpy(Array + header_size +datatype_size ,(char *)&color_array, reg_size);
          //default
          if(_clear_all_color == true)
                  memcpy(Array + header_size +datatype_size ,(char *)&clear_color_management, reg_size);
          else
                  memcpy(Array + header_size +datatype_size ,(char *)&color_management, reg_size);

         //Send_Data(Array, sizeof(set) +  sizeof(rw_reg)  + sizeof(reg), TTY_SERVICE_ID_DISPLAY);
         Send_Data(Array, header_size +  datatype_size  +reg_size, 0x0a);
        }
}
#endif
//---------------------------------------------------------------------------

void __fastcall TLCD_RGB::Image8Click(TObject *Sender)
{
	TStringGrid *pGrid = StringGrid1;
	int row, col;
	
	for(row =0; row< pGrid->RowCount -1; row++)
		for( col =0; col< (pGrid->ColCount-1); col++)
            	{
            	     pGrid->Cells[col+1][row +1] =  pGrid->Cells[1][row +1];
		    
            	}

	pGrid = StringGrid2;
	for(row =0; row< pGrid->RowCount -1; row++)
		for( col =0; col< (pGrid->ColCount-1); col++)
            	{
            	     pGrid->Cells[col+1][row +1] = pGrid->Cells[1][row +1];
		    
            	}	
	//Image11Click(this);
	Image16Click(this);
	Image17Click(this);
	Image18Click(this);
	Image19Click(this);
	Image20Click(this);
	Image21Click(this);
}
//---------------------------------------------------------------------------
void __fastcall TLCD_RGB::enable(TObject *Sender)
{
	PC_rw_register rw_reg;
	byte data;
	TCheckBox *pControl = (TCheckBox *)Sender;

	int i;
        ////////////////////////////////////////////////////
	TCheckBox *enable_control_group[]=
	{   
		CheckBox1,CheckBox2,CheckBox3,
	};
	
       for(i =0; i< sizeof(enable_control_group)/sizeof(TCheckBox *);i++)
       {
          if(pControl == enable_control_group[i])
          {
              if(pControl->Checked)
                data = _enable_group[i*2 ];
              else
                data = _enable_group[i*2 +1];

                send_color_command_1(rw_reg,  data);
                    break;
              }
	}

}
//---------------------------------------------------------------------------


void __fastcall TLCD_RGB::set_shape(TObject *Sender)
{
	int color_index = _color_index;
	int i =0;
	char *stop;
	int row;

	PC_rw_register rw_reg;
	byte data;

	TStringGrid *pGrid =_pGrid;	// LCD_RGB->StringGrid1;

        Button5->Enabled = false;
	if(!_pGrid) return;

	row = strtol(Edit1->Text.c_str(), &stop, 10);

	///////////////////////////////////////////////////////
	int radio_numbr =6;
	{
	       if( pGrid ==  LCD_RGB->StringGrid1)
			i = row + radio_numbr ;
		else if( pGrid ==  LCD_RGB->StringGrid2)   
			i= row + radio_numbr + 8 ;

		memcpy(&rw_reg, (char *)&color_set_group[i], sizeof(rw_reg) );
		
		rw_reg.addReg += color_index*6 ;

		///////////////////////////////////////////////
            	{
			data = strtol( pGrid->Cells[ color_index +2][row +1].c_str() , &stop,  16);
            	}
		
		///////////////////////////////////////////////
		bool re = send_color_command(rw_reg, &data);
	       //	if(!re) break;
	}
        Button5->Enabled = true;	
}
//---------------------------------------------------------------------------

void __fastcall TLCD_RGB::Set_shape_RadioGroup2Click(TObject *Sender)
{
	int color_index = _color_index;
	int i =0;
	char *stop;
	int row;

	PC_rw_register rw_reg;
	byte data;
	int radio_index = 0;

        TRadioGroup *pControl = (TRadioGroup *)Sender;

	////////////////////////////////////////////////////////////////////
	row = strtol(Edit1->Text.c_str(), &stop, 10);

	TRadioGroup *radio_group[]={// LCD_RGB->RadioGroup1,
				LCD_RGB->RadioGroup2, LCD_RGB->RadioGroup3, LCD_RGB->RadioGroup4, LCD_RGB->RadioGroup5,
				LCD_RGB->RadioGroup10,LCD_RGB->RadioGroup12,LCD_RGB->RadioGroup14,LCD_RGB->RadioGroup8,
				
				//LCD_RGB->RadioGroup15,
				LCD_RGB->RadioGroup16, LCD_RGB->RadioGroup17, LCD_RGB->RadioGroup18, LCD_RGB->RadioGroup19,
				LCD_RGB->RadioGroup20,LCD_RGB->RadioGroup21, LCD_RGB->RadioGroup22, LCD_RGB->RadioGroup9,};

	///////////////////////////////////////////////////////
	int nRadio_sum = sizeof(radio_group)/sizeof(TRadioGroup*)  ;
	int nHalf_Radio_sum = (nRadio_sum/2);
	for(i = 0;i <  nRadio_sum; i++)
	{
		if(Sender == radio_group[i])
		{
			color_index = i%nHalf_Radio_sum;

			if(i/nHalf_Radio_sum)
				radio_index = 3;
			else
				radio_index = 0;

                        break;        
		}
	}
	
	{
	       memcpy(&rw_reg, (char *)&color_set_group[radio_index + (pControl->ItemIndex)], sizeof(rw_reg) );
		rw_reg.addReg += color_index*6 ;	   

		///////////////////////////////////////////////
		//data
	       switch(pControl->ItemIndex )
	       {
	       	case 0:
				data = 1;
				break;
			case 1:
				data = 1; //33;
				break;	
			case 2:
				data = 0;// 2;
				break;		
				
	       }
	
		
	}	
	///////////////////////////////////////////////
        bool re = send_color_command(rw_reg, &data);
}
//---------------------------------------------------------------------------
void __fastcall TLCD_RGB::StringGrid1SelectCell(TObject *Sender, int ACol,
      int ARow, bool &CanSelect)
{
         AnsiString str;
         Edit1->Text = str.sprintf("%d", ARow-1) ;

         _color_index = ACol -2;
         _pGrid = (TStringGrid *)Sender;
}
//---------------------------------------------------------------------------

void __fastcall TLCD_RGB::RadioGroup1Click(TObject *Sender)
{
	int i =0;
	int radio_index = 0;

	////////////////////////////////////////////////////////////////////
	TRadioGroup *radio_group[]={// LCD_RGB->RadioGroup1,
				LCD_RGB->RadioGroup2, LCD_RGB->RadioGroup3, LCD_RGB->RadioGroup4, LCD_RGB->RadioGroup5,
				LCD_RGB->RadioGroup10,LCD_RGB->RadioGroup12,LCD_RGB->RadioGroup14,
				
				};

	///////////////////////////////////////////////////////
	radio_index = LCD_RGB->RadioGroup1->ItemIndex ;
	for(i = 0;i < sizeof(radio_group)/sizeof(TRadioGroup*)  ; i++)
	{
	        //radio_group[i]->ItemIndex = radio_index;
	}

}
//---------------------------------------------------------------------------

void __fastcall TLCD_RGB::RadioGroup15Click(TObject *Sender)
{
	int i =0;
	int radio_index = 0;

	////////////////////////////////////////////////////////////////////
	TRadioGroup *radio_group[]={// LCD_RGB->RadioGroup1,
				//LCD_RGB->RadioGroup15,
				LCD_RGB->RadioGroup16, LCD_RGB->RadioGroup17, LCD_RGB->RadioGroup18, LCD_RGB->RadioGroup19,
				LCD_RGB->RadioGroup20,LCD_RGB->RadioGroup21, LCD_RGB->RadioGroup22};

	///////////////////////////////////////////////////////
	radio_index = LCD_RGB->RadioGroup15->ItemIndex ;
	for(i = 0;i < sizeof(radio_group)/sizeof(TRadioGroup*)  ; i++)
	{
	        //radio_group[i]->ItemIndex = radio_index;
	}
        
}
//---------------------------------------------------------------------------

void __fastcall TLCD_RGB::RadioGroup6Click(TObject *Sender)
{
//
	PC_rw_register rw_reg;
	byte data;

	int color_index;
	TRadioGroup *pControl = (TRadioGroup *)Sender;
	
	///////////////////////////////////////////////////
        if(Button7->Enabled == false) return;
	
	color_index = ComboBox1->ItemIndex;
	
       if(pControl ==  RadioGroup6)
       {
	
		memcpy(&rw_reg, (char *)&hue_sat_group_1[0], sizeof(rw_reg) );
       }	
	else
	{
	
		memcpy(&rw_reg, (char *)&hue_sat_group_1[1], sizeof(rw_reg) );
	}

	if(pControl->ItemIndex)
		data = 0;
	else
		data =1;
	

	rw_reg.addReg += color_index*6 ;
	
	bool re = send_color_command(rw_reg, &data);
}
//---------------------------------------------------------------------------
void __fastcall TLCD_RGB::set_default(TObject *Sender)
{
     Button8->Enabled = false;
     Set_default(this);
     Button8->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TLCD_RGB::get_shape(TObject *Sender)
{
	int color_index = _color_index;
	int i =0;
	char *stop;
	TStringGrid *pGrid =_pGrid;	// L

	Button4->Enabled = false;
	PC_rw_register rw_reg = {read_reg_bit, 0,0x0000,49};;
	byte data;

	//TStringGrid *pGrid = LCD_RGB->StringGrid1;


        TRadioGroup *radio_group[]={ LCD_RGB->RadioGroup1, LCD_RGB->RadioGroup2, LCD_RGB->RadioGroup3, LCD_RGB->RadioGroup4, LCD_RGB->RadioGroup5,
				LCD_RGB->RadioGroup10,LCD_RGB->RadioGroup12,LCD_RGB->RadioGroup14, LCD_RGB->RadioGroup8,
				LCD_RGB->RadioGroup15,LCD_RGB->RadioGroup16, LCD_RGB->RadioGroup17, LCD_RGB->RadioGroup18, LCD_RGB->RadioGroup19,
				LCD_RGB->RadioGroup20,LCD_RGB->RadioGroup21, LCD_RGB->RadioGroup22, LCD_RGB->RadioGroup9, };


        ////////////////////////////////////////////////////////////////////////////
      //send get command
      int  max = 0;
	int current_grid_row =0;
	max = sizeof(color_set_group)/sizeof(rw_reg) ;

	int row = strtol(Edit1->Text.c_str(), &stop, 10);

	int radio_numbr =6;

	///////////////////////////////////////////////////////
	{
	       if( pGrid ==  LCD_RGB->StringGrid1)
			current_grid_row = row + radio_numbr  ;
		else if( pGrid ==  LCD_RGB->StringGrid2)   
			current_grid_row= row + radio_numbr+ 8 ;
	}
	  
	///////////////////////////////////////////////////////
	//for(color_index = 0; color_index< 7; color_index++)
	for(i = 0;i <  max; i++)
	{
		memcpy(&rw_reg, (char *)&color_set_group[i], sizeof(rw_reg) );
		rw_reg.addReg += color_index*6 ;
		rw_reg.rwRegBit = 3;//for read;

		if( ( i < 3) || (current_grid_row == i) )
		{
		bool re = send_color_command(rw_reg, &data, 0);
		if(!re) return;
		}
		else 
			continue;

	/////////////////////////////////////////////////////////////////////
      //read comm
	char  buf[1024];
	int read_len = sizeof(data);
	AnsiString str;
	
	if( Read_Comm( buf , read_len)>= read_len )           //
       {
               memcpy(&data,  buf + sizeof(PC_rw_register), read_len );
      		///////////////////////////////////////////////
		//radio group
		
		if(i <4)
		{
			switch(data)
		       {
		       	case 1:
					radio_group[color_index]->ItemIndex = 0;
					break;
				case 2:
					radio_group[color_index]->ItemIndex = 2;
					break;	
				case 3:
					radio_group[color_index]->ItemIndex = 1;
					break;		
					
		       }
		}
		else //grid
            	{
            	      int flag = radio_numbr +8;
            		if(i < flag) 
            		{
				pGrid = LCD_RGB->StringGrid1;
				pGrid->Cells[ color_index +2][row +1] = str.sprintf("%2X",  data);   //row index;
				
            		}	
			else
			{
				pGrid = LCD_RGB->StringGrid2;		
				pGrid->Cells[ color_index +2][row+1] = str.sprintf("%2X",  data);   //row index;
			}	
            	}
	}
	else
		ShowMessage("read shape data error!");
	///////////////////////////////////////////////

	}	

	Button4->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TLCD_RGB::Get_hue_sat(TObject *Sender)
{
	int color_index = ComboBox1->ItemIndex;
	int i =0;
	char *stop;

	PC_rw_register rw_reg;
	byte data;
	char  buf[1024];
       int read_len = sizeof(data)+ sizeof(PC_rw_register);

       Button7->Enabled = false;
	///////////////////////////////////////////////////////
	//for(color_index = 0; color_index< 7; color_index++)
	//for(i = 0;i < sizeof(color_set_group)/sizeof(rw_reg)  ; i++)
	{
		memcpy(&rw_reg, (char *)&hue_sat_group[0], sizeof(rw_reg) );
		rw_reg.rwRegBit = read_reg_bit;//for read;
		rw_reg.addReg += color_index*6 ;

		/////////////////////////////////////////////////////////////
		//hue scroll bar
		bool re = send_color_command(rw_reg, &data, 0);
		if(!re) return;

	      //read comm
		AnsiString str;
		
		if( Read_Comm( buf , read_len)>= read_len )           //
		{
		   memcpy(&data,  buf + sizeof(PC_rw_register), read_len );
		}
		_color_hue_register_group[color_index] = data;

		///////////////////////////////////////////////////////////////
		//sat  scroll bar
		memcpy(&rw_reg, (char *)&hue_sat_group[1], sizeof(rw_reg) );
		rw_reg.addReg += color_index*6 ;
		rw_reg.rwRegBit = read_reg_bit;//for read;

		re = send_color_command(rw_reg, &data, 0);
		if(!re) return;
                            
	      //read comm
		if( Read_Comm( buf , read_len)>= read_len )           //
	           {
	               memcpy(&data,  buf + sizeof(PC_rw_register), read_len );
	           }
		_color_sat_register_group[color_index] = data;

		/////////////////////////////////////////////////////////////////
		//two radio group
		TRadioGroup *pControl[] = {RadioGroup6, RadioGroup7};
                //if(0)
		for(int k=0;k<2; k++)
		{
			memcpy(&rw_reg, (char *)&hue_sat_group_1[k], sizeof(rw_reg) );
			rw_reg.rwRegBit = read_reg_bit;//for read;

			bool	re = send_color_command(rw_reg, &data, 0);
			if(!re) return;
	                            
		      //read comm
			if( Read_Comm( buf , read_len)>= read_len )           //
		           {
		               memcpy(&data,  buf + sizeof(PC_rw_register), read_len );
					   pControl[k]->ItemIndex = !data;
		           }
			else
                          ShowMessage("read clockwise parater error!");
		}
		/////////////////////////////////////////////////////////////
		//check box (enable parameter)
		{
			TCheckBox *pControl = (TCheckBox *)Sender;

			int i;
		        ////////////////////////////////////////////////////
			TCheckBox *enable_control_group[]=
			{   
				CheckBox1,CheckBox2,CheckBox3,
			};

			////////////////////////////////////////////////////////////
		       //for(i =0; i< sizeof(enable_control_group)/sizeof(TCheckBox *);i++)
		       {
		       	//rw_reg
				send_color_command_1(rw_reg,  data, 0);

				if( Read_Comm( buf , read_len)>= read_len )           //
			           {
			               memcpy(&data,  buf + sizeof(PC_rw_register), read_len );
					CheckBox1->Checked = data;
			           }
			}
		}
	}

	//////////////////////////////////////////////////////////////////
        Sleep(100);
        Button7->Enabled = true;
	ComboBox1Change(Sender);
}
//---------------------------------------------------------------------------


extern bool    _Is_End_Thread;

void __fastcall TLCD_RGB::FormClose(TObject *Sender, TCloseAction &Action)
{
  _Is_End_Thread = true;        
}
//---------------------------------------------------------------------------

void __fastcall TLCD_RGB::Edit2KeyPress(TObject *Sender, char &Key)
{
 /*      if( Key == VK_RETURN	)
       {
       _pScroll_bar =  ScrollBar1;

if(Edit2->Text.Length())
{
        int data = StrToInt(Edit2->Text);
      if (( data <_pScroll_bar->Min) || ( data >_pScroll_bar->Max))
      return;
_pScroll_bar->Position  = data;
}
}
  */            

	TEdit  *pEdit_Group[]={Edit2, Edit3, Edit4, Edit5};
	TScrollBar *pScrollBar_Group[]={ScrollBar1, ScrollBar2, ScrollBar9, ScrollBar10};
	
	if( Key == VK_RETURN	)
	{
		for(int i=0; i< sizeof(pEdit_Group)/sizeof(TEdit  *); i++)
		{
			if( Sender == pEdit_Group[i])
			{
			       _pScroll_bar =  pScrollBar_Group[i];

				if(pEdit_Group[i]->Text.Length())
				{
				      int data = StrToInt(pEdit_Group[i]->Text);
				      if (( data <_pScroll_bar->Min) || ( data >_pScroll_bar->Max))
				      return;
					_pScroll_bar->Position  = data;
				}
				return;
			}
		}
       }
	   
}
//---------------------------------------------------------------------------

 
TColor  color_grid_group[] =
	{
                0x0000ff,
		0x00ff00,
                0xff0000,

                0xffff00,

	 	0xff00ff,
                0x00ffff,

                0x6ab5ff,
                0xc0c0c0
	};


void __fastcall TLCD_RGB::reg_gridDrawCell(TObject *Sender, int ACol,
      int ARow, TRect &Rect, TGridDrawState State)
{
	AnsiString str;

	if ( ACol == 0 &&  ARow >=1 && ( ARow < 0x2c ) ) //指定单元格
        //if (   ARow >=1 && ( ARow < 0x26 ) ) //指定单元格
	{
		int nIndex = (ARow-1)%6;
		if( nIndex==0 )
		{
			reg_grid->Canvas->Brush->Color = color_grid_group[ (ARow-1)/6 ];
			reg_grid->Canvas->FillRect(Rect);
                        reg_grid->Canvas->Font->Color = clBlack;

                        //if( (ARow-1)/6  == 2)   reg_grid->Canvas->Font->Color = clWhite;

			reg_grid->Canvas->TextOutA(Rect.left+2,Rect.top+2,reg_grid->Cells[ACol][ARow]);
			//reg_grid->Canvas->TextOutA(Rect.left+2,Rect.top+2,str.sprintf("%2X", (ARow-1)) );
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TLCD_RGB::Image7Click(TObject *Sender)
{
    _color_index = 7;        
}
//---------------------------------------------------------------------------

void __fastcall TLCD_RGB::Clear_color(TObject *Sender)
{
     Button9->Enabled = false;
	 _clear_all_color = true;
     Set_default(this);
	 _clear_all_color = false;
     Button9->Enabled = true;//        
}
//---------------------------------------------------------------------------

