//#define _AML  //Aml version

////////////////////////////////////////////////////////////////////////////////
//PC requires touch panel setting parameters
#define TPDBG_EVENT_2TP_REQUIRE_SETTING	0x31
//PC sends parameters to reset touch panel setting		
#define TPDBG_EVENT_2TP_SET_SETTING		0x32
//PC requires runtime testing data from touch panel
#define TPDBG_EVENT_2TP_START_SYNC			0x33
//PC stops runtime testing data transition
#define TPDBG_EVENT_2TP_STOP_SYNC			0x34
//PC set DPF touch panel back to default
#define TPDBG_EVENT_2TP_DEFAULT_SETTING	0x35
//PC set DPF sample rate
#define TPDBG_EVENT_2TP_DATA_SYNC_RATE	0x36
//PC requires runtime testing data from touch panel in factory mode
#define TPDBG_EVENT_2TP_FACTORY_START_SYNC	0x37

/* DPF to PC */
//Runtime testing data from touch panel that PC required
#define TPDBG_EVENT_2PC_DATA_SYNC			0x10
//Setting parameters from touch panel that PC required
#define TPDBG_EVENT_2PC_DATA_SETTING		0x20
//Runtime testing data from touch panel that PC required in factory mode
#define TPDBG_EVENT_2PC_FACTORY_DATA_SYNC		0x40


//2008-12-9
/*get screen timing */
#define TPDBG_CS_GET_SCREEN_TIMING	 0x01
/*get screen image */
#define TPDBG_CS_GET_SCREEN_IMAGE	 0x02

/*Screen image timing（data : byte0| byte1	h pixels of timing
							byte2| byte3	v pixels of timing
For example: timing is 800*600,
so data is 0x03|0x20|0x02|0x58)*/
#define TPDBG_CS_SCREEN_IMAGE_TIMING	0x10
/*Screen image data （data : RGB data of screen image) */
#define TPDBG_CS_SCREEN_IMAGE_DATA	0x20
/*Screen image data end */
#define TPDBG_CS_SCREEN_IMAGE_DATA_END	0x30


////////////////////////////////////////////////////////////////////////////////
//2008-12-11
#define TPDBG_LPA_GET_LCD_PARA	 0x01
/*get gamma R parameters*/
#define TPDBG_LPA_GET_GAMMA_R	 0x02
/*get gamma G parameters*/
#define TPDBG_LPA_GET_GAMMA_G	 0x03
/*get gamma B parameters*/
#define TPDBG_LPA_GET_GAMMA_B  0x04

/*set LCD parameters*/
#define TPDBG_LPA_SET_LCD_PARA	 0x05
/*set gamma R parameters*/
#define TPDBG_LPA_SET_GAMMA_R	 0x06
/*set gamma G parameters*/
#define TPDBG_LPA_SET_GAMMA_G	 0x07
/*set gamma B parameters*/
#define TPDBG_LPA_SET_GAMMA_B  0x08

/*set DPF serial number. data: serial number string in ASIC*/  //2009-1-8
#define TPDBG_SN_SET  			0x09
/*get DPF serial number*/
#define TPDBG_SN_GET  			0x0A

/* DPF to PC*/
/*LCD parameters data*/
#define TPDBG_LPA_LCD_PARA_DATA	 0x10
/*LCD gamma R data*/
#define TPDBG_LPA_GAMMA_R_DATA	 0x20
/*LCD gamma G data*/
#define TPDBG_LPA_GAMMA_G_DATA	 0x30
/*LCD gamma B data*/
#define TPDBG_LPA_GAMMA_B_DATA	 0x40

/*serial number. data: data: serial number string in ASIC */
#define TPDBG_SN_DATA	 				0x50

/////////////////////////////////////////////////
#define _Channel_Count 12 //8 //for 12  channels   -2008-12-31
/////////////////////////////////////////////////
#define _Channel_Sum 12//8
#define _Min_Buff_Left_Data 190
struct Channel_Data
{
      unsigned short int sample;
      unsigned short int slow;
      unsigned short int fast ;
      unsigned short int diff  ;
};

#ifdef _AML
struct Channel_SYNC
{
      byte Header[6];

      unsigned char   report_type;
      unsigned char report_pos;
      unsigned short int comm_noise_0;
      unsigned short int comm_noise_1;
      struct Channel_Data   Channel[_Channel_Sum];
};
#else

struct Channel_SYNC
{
      byte Header[6];
      
      unsigned char report_type;
      unsigned char report_pos;
      //unsigned short comm_noise[2];
      unsigned short int comm_noise_0;
      unsigned short int comm_noise_1;

      unsigned short diff[_Channel_Sum];
};

#endif

////////////////////////////////////////////////////////////////////////////////
struct DPF_Comm_Header
{
      unsigned short  Header;
      byte Event;
      byte sub_event;

      //unsigned short length;
      unsigned char length_High;
      unsigned char length_Low;
};
////////////////////////////////////////////////////////////////////////////////
typedef struct tty_scmd_head{
    unsigned int tag;
    unsigned char ver;
    unsigned char flag;
    unsigned short reserved;
    unsigned char id;
    unsigned char id_not;
    unsigned short seq;
    unsigned short packet_len;
    unsigned short check_sum;
}tty_scmd_head_t;

////////////////////////////////////////////////////////////////////////////////
enum TTY_SERVICE_ID_e{
    TTY_SERVICE_ID_0 = 0,
    TTY_SERVICE_ID_SYSTEM = 1,
    TTY_SERVICE_ID_TOUCH = 2,
    TTY_SERVICE_ID_LCD = 3,
    TTY_SERVICE_ID_RTC = 4,
    TTY_SERVICE_ID_USB = 5,
    TTY_SERVICE_ID_CARDREADER = 6,
    TTY_SERVICE_ID_BLUETOOTH = 7,
    TTY_SERVICE_ID_NETWORK = 8,
    TTY_SERVICE_ID_SCR_CAP = 9,

//TTY_SERVICE_ID_DISPLAY = 10,	
    TTY_SERVICE_ID_DISPLAY = 0x10,	

    TTY_SERVICE_ID_CUST_START = 128
};


////////////////////////////////////////////////////////////////////////////////
#define TPDBG_EVT_LCD_PARA_ADJUST	0x08

/*SUB EVENT:
Length	1byte
Data
 PC to DPF */
/*get LCD parameters*/
#define TPDBG_SEVT_LPA_GET_LCD_PARA	 0x01
/*set screen parameters（data : struct in email) */
#define TPDBG_SEVT_LPA_SET_LCD_PARA	 0x02

/* DPF to PC*/
/*set LCD parameters（data : struct in email) */
#define TPDBG_SEVT_SPA_LCD_PARA_DATA	 0x10


////////////////////////////////////////////////////////////////////////////////

typedef struct {
    // -1000~0
    int Brightness;
    
    // -1000~+1000
    int Contrast;
    
    // -1000~+1000
    int Saturation;
    
    // -1000~+1000
    int Hue;
} video_adjustment_t;


typedef struct{
  video_adjustment_t video_adjust_datas;  
//rgb gamma    
 unsigned short data_r[256];    //gamma值，range: 0-1023
 unsigned short data_g[256];   //gamma值，range: 0-1023
 unsigned short data_b[256];   //gamma值，range: 0-1023

//dim effection, optional
 unsigned short dim_step;
 unsigned short dim_duration;
 unsigned short dim_timer; 
//logo pwm ctrl, optional
 unsigned short logo_darkness;     //led最低亮度，range: 0-100
 unsigned short logo_brightness;   //led最高亮度（百分数），range: 0-100
 unsigned short logo_rise_time;    //led渐变亮的时间，range: 100 - 20000, 单位ms
 unsigned short logo_fall_time;     //led渐变暗的时间，range: 100 - 20000, 单位ms
}  LCD_Para_t;


///////////////////////////////////////////////////////////////////////////////////
enum TI_TYPE_e{
    TI_NULL        = 0,
    TI_RELEASE     = 1,
    TI_TOUCH       = 2,     //
    TI_TAP         = 3,     //
    TI_DOUBLE_TAP  = 4,
    TI_HOLD        = 5,
    TI_SLIDE_LEFT  = 6,     //
    TI_SLIDE_RIGHT = 7,     //
    TI_MAX         = 8,
};    

///////////////////////////////////////////////////////////////////////////////////
void Tty_Head_Set(tty_scmd_head_t *pTty_scmd_head, unsigned char id, unsigned short nLen);
void Send_Data(char *Data, int nLen,  unsigned char id = 0);
bool Initial_Comm_4_DPF(AnsiString str="");


