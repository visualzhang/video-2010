
////////////////////////////////////////////////////////////////////////////
typedef struct{           //Data Type-1's structure
       unsigned char  rwRegBit;      // 0:д�Ĵ���   1:���Ĵ���   2:д�Ĵ�����bits  3:���Ĵ�����bits
       unsigned char  startBit;       // ��rwRegBit=2/3ʱ����ʼ��д��bit��rwRegBit=0/1ʱ��startBit=0
unsigned short  addReg;      // ϣ����ʼ��д�ļĴ��� 
       unsigned short  RegBitLength;  // rwRegBit=0/1ʱ��ϣ����д���ٸ��Ĵ�����rwRegBit=2/3ʱ��ϣ����д���ٸ�bits��
  }PC_rw_register;//={0x00,0x00,0x00??,0x01};  //����дcolor management�ļĴ���0x00??��


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

