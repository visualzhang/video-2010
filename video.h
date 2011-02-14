
////////////////////////////////////////////////////////////////////////////
typedef struct{           //Data Type-1's structure
       unsigned char  rwRegBit;      // 0:写寄存器   1:读寄存器   2:写寄存器的bits  3:读寄存器的bits
       unsigned char  startBit;       // 当rwRegBit=2/3时，开始读写的bit。rwRegBit=0/1时，startBit=0
unsigned short  addReg;      // 希望开始读写的寄存器 
       unsigned short  RegBitLength;  // rwRegBit=0/1时，希望读写多少个寄存器。rwRegBit=2/3时，希望读写多少个bits。
  }PC_rw_register;//={0x00,0x00,0x00??,0x01};  //代表写color management的寄存器0x00??。


typedef struct{
       unsigned char  resev;
       unsigned char  func_id;
unsigned short  datatype;
  }data_type_t;

//////////////////////////////////////////////////////////////////////////////////////
#define _rw_register_default_start_bit 0

enum {
	write_reg =0,
	read_reg ,	

	write_reg_bit,
	read_reg_bit
		
	};


//////////////////////////////////////////////////////////////////////////////////////
bool send_command(data_type_t data_type, PC_rw_register rw_reg, byte *data, int data_size );
bool send_reg_command( byte *data, int data_size , PC_rw_register rw_reg,  
	unsigned char func_id, unsigned char datatype);

