//---------------------------------------------------------------------------
#ifndef Unit2H
#define Unit2H
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
//---------------------------------------------------------------------------
class TRead : public TThread
{
private:
protected:
  void __fastcall DisplayIt(void);
  void __fastcall Execute();
public:
	__fastcall TRead(bool CreateSuspended);
};
//---------------------------------------------------------------------------
#endif
 