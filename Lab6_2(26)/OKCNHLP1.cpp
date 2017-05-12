//---------------------------------------------------------------------

#include <vcl.h>

#pragma hdrstop

#include "OKCNHLP1.h"
//---------------------------------------------------------------------
#pragma resource "*.dfm"
TFiltersDlg1 *FiltersDlg1;


//---------------------------------------------------------------------
__fastcall TFiltersDlg1::TFiltersDlg1(TComponent* AOwner)
	: TOKBottomDlg(AOwner)
{
}
//--------------------------------------------------------------------- 
void __fastcall TFiltersDlg1::HelpBtnClick(TObject *Sender)
{
	Application->HelpContext(HelpContext);
}
//---------------------------------------------------------------------
void __fastcall TFiltersDlg1::OKBtnClick(TObject *Sender)
{
	AnsiString StrVal = "";
	char Keys[] = {'N','A','D','b','B','h','H','v','V','E','P','S','I','O'};
	KeysToFind = "";
	ReportList Selection;
	for (int i = 0; i < IncludeBox1->Items->Count; i++)
	{
		if (IncludeBox1->Checked[i]) {
			Selection.PushItem(i);
		}
	}
	for(int i = 0; i < Selection.getSize(); i++)
	{
		int NextKey = Selection.PopItem();
		switch(NextKey)
		{
		case 0:
		{
		   StrVal = NameDEdit->Text;
		   strcpy(ToFind->Name,StrVal.c_str());
		   break;
		}
		case 1:
		{

			ToFind->Position = AppointmentCbox->ItemIndex + 1;
			break;
		}
		case 2:
		{
			ToFind->Degree = EduCbox->ItemIndex + 1;
			break;
		}
		case 3:
		case 4:
		{
			TDateTime Birthday =  DateBirth->Date;
			ToFind->Birthday.TDateTimeToTrueDate(Birthday);
			break;
		}
		case 5:
		case 6:
		{
			TDateTime Hired =  DateEmployed->Date;
			ToFind->Hired.TDateTimeToTrueDate(Hired);
			break;
		}
		case 7:
		case 8:
		{
			TDateTime Vacations =  DateLastVacations->Date;
			ToFind->LastVacations.TDateTimeToTrueDate(Vacations);
			break;
		}
		case 9:
		{
			ToFind->Salary = StrToInt(EditSalary->Text);
			break;
		}
		case 10:
		{
			StrVal = PasportNoEdit->Text;
			strcpy(ToFind->PassportNo,StrVal.c_str());
		}
		case 11:
		{
			StrVal =  EditSocialCrd->Text;
			strcpy(ToFind->SocialCrd ,StrVal.c_str());
			break;
		}
		case 12:
		{
			StrVal =  EditInsurancy->Text;
			strcpy(ToFind->InsurancyPolicy,StrVal.c_str());
			break;
		}
		case 13:
		{
		}
		case 14:
		{
			ToFind->OnDuty = true;
		}

		}
		KeysToFind += Keys[NextKey];
	}
	Selection.~ReportList();
}
//---------------------------------------------------------------------------

