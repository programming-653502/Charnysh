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
#include "OKCNHLP1.h"
#include "CalendarFunctions.h"
#include <Vcl.JumpList.hpp>
#include <IdBaseComponent.hpp>
#include <IdComponent.hpp>
#include <IdHTTP.hpp>
#include <urlmon.h>
#include <IdTCPClient.hpp>
#include <IdTCPConnection.hpp>;
#include <windows.h>
#include "Weather.h"
#include "TEVENT.h"
#include "ExternVars.h"
#include "ABOUT.h"
AnsiString CurrentFile ="";
//---------------------------------------------------------------------------
class TForm6 : public TForm
{
__published:	// IDE-managed Components
	TSpinButton *SpinButton2;
	TButton *ButtonAdd;
	TButton *ButtonShow;
	TLabel *Label1;
	TButton *ButtonToday;
	TStringGrid *StringGrid1;
	TTimer *Timer1;
	TButton *ButtonMyCals;
	TDateTimePicker *DateTimePicker1;
	TButton *ButtonHlp;
	TLabel *LabelToday;
	TEdit *Edit1;
	TButton *Button1;
	void __fastcall ButtonAddClick(TObject *Sender);
	void __fastcall ButtonShowClick(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall ButtonHlpClick(TObject *Sender);
	void __fastcall ButtonMyCalsClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall DateTimePicker1CloseUp(TObject *Sender);
	void __fastcall StringGrid1Click(TObject *Sender);
	void __fastcall SpinButton2DownClick(TObject *Sender);
	void __fastcall SpinButton2UpClick(TObject *Sender);
	void __fastcall ButtonTodayClick(TObject *Sender);
	void __fastcall Timer1Timer(TObject *Sender);
	bool __fastcall FormHelp(WORD Command, NativeInt Data, bool &CallHelp);
	void __fastcall Edit1DblClick(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	

private:	// User declarations
public:		// User declarations
	__fastcall TForm6(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm6 *Form6;
//---------------------------------------------------------------------------
#endif
