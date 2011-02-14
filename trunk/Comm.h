#ifndef Comm_H
#define Comm_H

HANDLE hComm;

AnsiString _sRate;

char _Comm_Buff[100];

int nLarge_Buff_Len ;
unsigned char InBuff[800];
///////////////////////////////////////////////////////////////////////////
HANDLE Open_Comm(AnsiString sCOM);
void Close_Comm();

int Read_Comm(char *Data_Buf, int nLen=-1);

AnsiString Get_Comm_From_File();

AnsiString  write_command_line(HANDLE  hComm, AnsiString str);
AnsiString  write_register(HANDLE  hComm, int addr, int data);

char   *replace(char   *str,   char   srch,   char   tgch , int length);
#endif 


