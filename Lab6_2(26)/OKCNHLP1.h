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
#include <Vcl.CheckLst.hpp>
#include <Vcl.ComCtrls.hpp>

#include "ExternVars.h"
#include "ReportIncludesList.h"
//----------------------------------------------------------------------------
class TFiltersDlg1 : public TOKBottomDlg
{
__published:
	TButton *HelpBtn;
	TEdit *NameDEdit;
	TComboBox *EduCbox;
	TDateTimePicker *DateBirth;
	TDateTimePicker *DateEmployed;
	TDateTimePicker *DateLastVacations;
	TEdit *PasportNoEdit;
	TEdit *EditSocialCrd;
	TEdit *EditInsurancy;
	TCheckListBox *IncludeBox1;
	TComboBox *AppointmentCbox;
	TEdit *EditSalary;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *Label4;
	TLabel *Label5;
	TLabel *Label6;
	TLabel *Label7;
	TLabel *Label8;
	TLabel *Label10;
	TLabel *Label11;
	void __fastcall HelpBtnClick(TObject *Sender);
	void __fastcall OKBtnClick(TObject *Sender);
private:
public:
	virtual __fastcall TFiltersDlg1(TComponent* AOwner);
};
//----------------------------------------------------------------------------
extern PACKAGE TFiltersDlg1 *FiltersDlg1;
//----------------------------------------------------------------------------
#endif    
