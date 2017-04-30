//---------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "OKCNHLP.h"
//---------------------------------------------------------------------
#pragma resource "*.dfm"
TCreateEventDlg1 *CreateEventDlg1;
AnsiString Category;
//--------------------------------------------------------------------- 
__fastcall TCreateEventDlg1::TCreateEventDlg1(TComponent* AOwner)
	: TOKBottomDlg(AOwner)
{

}
//--------------------------------------------------------------------- 
void __fastcall TCreateEventDlg1::HelpBtnClick(TObject *Sender)
{
    AboutBox->ShowModal();
	Application->HelpContext(HelpContext);
}
//---------------------------------------------------------------------

void __fastcall TCreateEventDlg1::OKBtnClick(TObject *Sender)
{

	switch(RadioGroup1->ItemIndex)
	{
		case 0: Category = "Holidays";break;
		case 1: Category = "Aniverseries";break;
		case 2: Category = Edit2->Text;break;
	}
}
//---------------------------------------------------------------------------

void __fastcall TCreateEventDlg1::ComboBox1CloseUp(TObject *Sender)
{
	Calendar1->Month = ComboBox1->ItemIndex+1;
}
//---------------------------------------------------------------------------



void __fastcall TCreateEventDlg1::SpinEdit1Change(TObject *Sender)
{
		Calendar1->Year = StrToInt(SpinEdit1->Text);
}
//---------------------------------------------------------------------------

