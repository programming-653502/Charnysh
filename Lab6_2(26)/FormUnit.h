//---------------------------------------------------------------------------

#ifndef FormUnitH
#define FormUnitH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Grids.hpp>
#include "WorkerClass.h"
#include "ExternVars.h"
#include "stdio.h"
#include <Vcl.ExtCtrls.hpp>
#include "OKCNHLP1.h"
#include <Vcl.CheckLst.hpp>
#include "ReportIncludesList.h"
#include <Vcl.Dialogs.hpp>
#include <Vcl.ExtDlgs.hpp>

//Главная форма

//---------------------------------------------------------------------------
class TForm6 : public TForm
{
__published:	// IDE-managed Components
	TPageControl *PageControl1;
	TTabSheet *TabSheetTable;
	TTabSheet *TabSheetPage;
	TEdit *NameEdit;
	TDateTimePicker *DateBirth;
	TDateTimePicker *DateEmployed;
	TDateTimePicker *DateLastVacations;
	TEdit *PassportNoEdit;
	TEdit *EditSocialCrd;
	TEdit *InsurancyEdit;
	TTabSheet *TabSheetBriefs;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *Label4;
	TLabel *Label5;
	TLabel *Label6;
	TLabel *Label7;
	TEdit *Salary;
	TLabel *Label8;
	TLabel *Label9;
	TEdit *SpecialMks;
	TButton *ButtonNextPg;
	TButton *ButtonPrevPg;
	TLabel *ModeLabel;
	TComboBox *EducationCbox;
	TComboBox *AppointmentCbox;
	TLabel *Label10;
	TLabel *Label11;
	TCheckBox *OnDutyChckBox;
	TComboBox *ModeBox;
	TButton *ButtonCommit;
	TStringGrid *StringGrid1;
	TButton *ButtonAdd;
	TRichEdit *RichEdit1;
	TButton *ButtonCompose;
	TCheckListBox *IncludeBox1;
	TLabel *Label12;
	TButton *ButtonClearBrief;
	TButton *ButtonSave;
	TSaveTextFileDialog *SaveTextFileDialog1;
	TButton *ButtonVacations;
	TButton *ButtonFire;
	TButton *ButtonFilters;
	void __fastcall TabSheetPageShow(TObject *Sender);
	void __fastcall TabSheetTableShow(TObject *Sender);
	void __fastcall TabSheetBriefsShow(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall ModeBoxChange(TObject *Sender);
	void __fastcall ButtonAddClick(TObject *Sender);
	void __fastcall StringGrid1Click(TObject *Sender);
	void __fastcall ButtonCommitClick(TObject *Sender);
	void __fastcall FiltersDlgButtonClick(TObject *Sender);
	void __fastcall ButtonNextPgClick(TObject *Sender);
	void __fastcall ButtonPrevPgClick(TObject *Sender);
	void __fastcall ButtonComposeClick(TObject *Sender);
	void __fastcall ButtonClearBriefClick(TObject *Sender);
	void __fastcall ButtonSaveClick(TObject *Sender);
	void __fastcall ButtonVacationsClick(TObject *Sender);
	void __fastcall ButtonFireClick(TObject *Sender);
	void __fastcall PageControl1Change(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TForm6(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm6 *Form6;
//---------------------------------------------------------------------------
#endif
