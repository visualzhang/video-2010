#include <vcl.h>

#include "video.h"
#include "dpf.h"
//#include <stdio.h>

////////////////////////////////////////////////////////////////////////////////////////
bool send_command(data_type_t data_type, PC_rw_register rw_reg, byte *pdata, int data_size )
{
#ifndef debug_test
       	if(Initial_Comm_4_DPF())
#else			
        if(1)
#endif						
       {
		int header_size = sizeof(data_type);
              int reg_size = sizeof(rw_reg);
		unsigned char Array[600];	  

		memset(Array, NULL, sizeof(Array));
		
		//////////////////////////////////////////////////////////////////
               memcpy(Array, (char *)&data_type, header_size );
               memcpy(Array + header_size, (char *)&rw_reg, reg_size);

		if(data_size)
			memcpy(Array + header_size +reg_size ,(char *)pdata, data_size);

               //Send_Data(Array, sizeof(set) +  sizeof(rw_reg)  + sizeof(reg), TTY_SERVICE_ID_DISPLAY);
               Send_Data(Array, header_size +  reg_size  +data_size, 0x0a);
        }
	else
		return false;

	return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool send_reg_command( byte *pdata, int data_size , PC_rw_register rw_reg,  
	unsigned char func_id, unsigned char datatype)
{
	data_type_t data_type;
	//PC_rw_register rw_reg;

	////////////////////////////////////////////////////////////////
	memset((char *)&data_type, NULL, sizeof(data_type) );
	//memset((char *)&rw_reg, NULL, sizeof(rw_reg));
		
	data_type.func_id = func_id;
	data_type.datatype = datatype;
	
	////////////////////////////////////////////////////////////////
	send_command(data_type, rw_reg, pdata,  data_size );

	return true;
}


