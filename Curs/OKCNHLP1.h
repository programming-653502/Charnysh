//----------------------------------------------------------------------------
#ifndef OkCnHlp1H
#define OkCnHlp1H
//----------------------------------------------------------------------------
#include <OKCANCL1.h>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Buttons.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Graphics.hpp>
#include <System.Classes.hpp>
#include <System.SysUtils.hpp>
#include <Winapi.Windows.hpp>
#include <System.hpp>
#include <Vcl.Grids.hpp>
#include <Vcl.Dialogs.hpp>
#include <vector>
#include <stdio.h>
#include "CalendarFunctions.h"
#include "TEVENT.h"
#include "ExternVars.h"

//#include "VisualFunctions.h"
//----------------------------------------------------------------------------
class TMainFileDlg1 : public TOKBottomDlg
{
__published:
	TLabel *Label1;
	TStringGrid *StringGrid1;
	TOpenDialog *OpenDialog1;
	TButton *Button1;
	TButton *Button2;
	TButton *Button3;
	TButton *Button4;
	TButton *Button5;
	void __fastcall HelpBtnClick(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall Button3Click(TObject *Sender);
	void __fastcall StringGrid1Click(TObject *Sender);
	void __fastcall Button4Click(TObject *Sender);
	void __fastcall Button5Click(TObject *Sender);
private:
public:
	virtual __fastcall TMainFileDlg1(TComponent* AOwner);
};
//----------------------------------------------------------------------------
extern PACKAGE TMainFileDlg1 *MainFileDlg1;
//----------------------------------------------------------------------------
#endif
