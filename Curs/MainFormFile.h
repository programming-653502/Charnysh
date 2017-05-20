//---------------------------------------------------------------------------

#ifndef Unit6H
#define Unit6H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "ccalendr.h"
#include <Vcl.Grids.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Samples.Spin.hpp>
#include <System.Win.TaskbarCore.hpp>
#include <Vcl.Taskbar.hpp>
#include <Vcl.ComCtrls.hpp>
#include <stdlib.h>
#include "OKCNHLP1.h"
#include "CalendarFunctions.h"
#include <Vcl.JumpList.hpp>;
//#include "VisualFunctions.h"
#include "TEVENT.h"
#include "ExternVars.h"
#include "ABOUT.h"
#include "Weather.h"
AnsiString CurrentFile ="";
//---------------------------------------------------------------------------
class TForm6 : public TForm
{
__published:	// IDE-managed Components
	TSpinButton *SpinButton1;
	TButton *Button1;
	TButton *Button2;
	TLabel *Label1;
	TButton *Button4;
	TStringGrid *StringGrid1;
	TTimer *Timer1;
	TButton *Button5;
	TDateTimePicker *DateTimePicker1;
	TButton *Button3;
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall Button3Click(TObject *Sender);
	void __fastcall Button5Click(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall DateTimePicker1CloseUp(TObject *Sender);
	void __fastcall StringGrid1Click(TObject *Sender);
	void __fastcall SpinButton1DownClick(TObject *Sender);
	void __fastcall SpinButton1UpClick(TObject *Sender);
	void __fastcall Button4Click(TObject *Sender);
	void __fastcall Timer1Timer(TObject *Sender);
	bool __fastcall FormHelp(WORD Command, NativeInt Data, bool &CallHelp);


private:	// User declarations
public:		// User declarations
	__fastcall TForm6(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm6 *Form6;
//---------------------------------------------------------------------------
#endif
