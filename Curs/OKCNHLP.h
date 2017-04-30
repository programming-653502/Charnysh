//----------------------------------------------------------------------------
#ifndef OKCNHLPH
#define OKCNHLPH
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
#include <Vcl.Mask.hpp>
#include <Vcl.Samples.Calendar.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Samples.Spin.hpp>
#include "ABOUT.h"
//----------------------------------------------------------------------------
class TCreateEventDlg1 : public TOKBottomDlg
{
__published:
	TButton *HelpBtn;
	TCalendar *Calendar1;
	TEdit *Edit1;
	TMaskEdit *MaskEdit1;
	TRadioGroup *RadioGroup1;
	TEdit *Edit2;
	TLabel *Label1;
	TLabel *Label2;
	TComboBox *ComboBox1;
	TSpinEdit *SpinEdit1;
	TLabel *Label3;
	void __fastcall HelpBtnClick(TObject *Sender);
	void __fastcall OKBtnClick(TObject *Sender);
	void __fastcall ComboBox1CloseUp(TObject *Sender);
	void __fastcall SpinEdit1Change(TObject *Sender);
private:
public:
	virtual __fastcall TCreateEventDlg1(TComponent* AOwner);
};
//----------------------------------------------------------------------------
extern PACKAGE TCreateEventDlg1 *CreateEventDlg1;
//----------------------------------------------------------------------------
#endif    
