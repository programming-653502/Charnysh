//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "FormUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TForm6 *Form6;
int NextFreeCell = 1;
Enterprise *MyEnterprise;
AnsiString DBFileName = "Enterprise1.dbf";
AnsiString KeysToFind ="";
int selectedID = 0;
ReportList includesList;
int ShowingCell = -1;
enum Mode{View, Edit, Add} AppMode;


Worker *Selected;
Worker *ToFind;

int Enterprise::ChangeWorker(Worker* Change)
{
	
	AllWorkers.changeItem(Change->ID,Change);
}

void Enterprise::PagePrint(Worker* Next)
{
	// Вывод одной записи в строки страничного вида
	AnsiString StrVal = "";
	StrVal.cat_printf(Next->Name);
	Form6->NameEdit->Text = StrVal;
	Form6->DateBirth->Date = Next->Birthday.TrueDateToTDateTime();
	Form6->DateEmployed->Date = Next->Hired.TrueDateToTDateTime();
	Form6->DateLastVacations->Date = Next->LastVacations.TrueDateToTDateTime();
	Form6->PassportNoEdit->Text = (String) Next->PassportNo;
	Form6->EditSocialCrd->Text = (String)Next->SocialCrd;
	Form6->InsurancyEdit->Text = (String) Next->InsurancyPolicy;
	Form6->SpecialMks->Text = (String) Next->SpecialMarks;
	Form6->AppointmentCbox->ItemIndex = Next->Position-1;
	Form6->EducationCbox->ItemIndex = Next->Degree-1;
	Form6->OnDutyChckBox->Checked = Next->OnDuty;
	
}
void PageViewElementsEnabled(Mode appMode)
{
	//В зависимости от режима программы, включает/отключает кнопки, ввод
	bool editsEnabled = true;
	bool buttonsEnabled = true;
	bool editButtonsEnabled = true;
	switch (appMode) {
	case View:
		editsEnabled = false;
		editButtonsEnabled = false;
		break;
	case Add:
		editButtonsEnabled = false;
		buttonsEnabled = false;
		break;
	case Edit:
		break;
	}

	Form6->NameEdit->Enabled = editsEnabled;
	Form6->DateBirth->Enabled = editsEnabled;
	Form6->DateEmployed->Enabled = editsEnabled;
	Form6->DateLastVacations->Enabled = editsEnabled;
	Form6->PassportNoEdit->Enabled = editsEnabled;
	Form6->EditSocialCrd->Enabled = editsEnabled;
	Form6->InsurancyEdit->Enabled = editsEnabled;
	Form6->SpecialMks->Enabled = editsEnabled;
	Form6->Salary->Enabled = editsEnabled;
	Form6->EducationCbox->Enabled = editsEnabled;
	Form6->AppointmentCbox->Enabled = editsEnabled;
	Form6->ButtonNextPg->Enabled = buttonsEnabled;
	Form6->ButtonPrevPg->Enabled = buttonsEnabled;
	Form6->ButtonFire->Enabled = editButtonsEnabled;
	Form6->ButtonVacations->Enabled = editButtonsEnabled;
	Form6->OnDutyChckBox->Enabled = editsEnabled;
}
void SetWorker(Worker* ToSet)
{
	//Копирование инфы из строк ввода в переменную типа Worker
	Form6->PageControl1->ActivePageIndex = 1;
	AnsiString AnsiVal = Form6->NameEdit->Text;
	strcpy(ToSet->Name,AnsiVal.c_str());
	AnsiVal = Form6->PassportNoEdit->Text;
	strcpy(ToSet->PassportNo,AnsiVal.c_str());
	AnsiVal = Form6->InsurancyEdit->Text;
	strcpy(ToSet->InsurancyPolicy,AnsiVal.c_str());
	AnsiVal = Form6->EditSocialCrd->Text;
	strcpy(ToSet->SocialCrd,AnsiVal.c_str());
	ToSet->Degree = Form6->EducationCbox->ItemIndex + 1;
	ToSet->Position = Form6->AppointmentCbox->ItemIndex + 1;
	ToSet->Birthday.TDateTimeToTrueDate(Form6->DateBirth->Date);
	ToSet->Hired.TDateTimeToTrueDate(Form6->DateEmployed->Date);
	ToSet->LastVacations.TDateTimeToTrueDate(Form6->DateLastVacations->Date);
	ToSet->Salary = StrToInt(Form6->Salary->Text);
	AnsiVal = Form6->SpecialMks->Text;
	strcpy(ToSet->SpecialMarks,AnsiVal.c_str());
	ToSet->OnDuty = Form6->OnDutyChckBox->Checked;
}
void Enterprise::AddNewPerson()
{
	// Добаление нового работника
	Worker* NewGuy = new Worker;
	SetWorker(NewGuy);
	AllWorkers.pushItem(NewGuy);
}
void Enterprise::AddToGrid(Worker* Next)
{
	//Вывод следующей записи в таблицу
	//Она служит еще и как массив выбранных по определенным условиям записей, из нее составляем рапорты
	//При изменении фильтров перезагружается.
	Form6->StringGrid1->RowCount=NextFreeCell+1;
	Form6->StringGrid1->Cells[0][NextFreeCell] = IntToStr(Next->ID);
	Form6->StringGrid1->Cells[1][NextFreeCell] = Next->Name;
	Form6->StringGrid1->Cells[3][NextFreeCell] = AppointmentStr(Next->Position);
	AnsiString isOnDuty = "On duty";
	if(!Next->OnDuty)
		isOnDuty = "Off duty";
	Form6->StringGrid1->Cells[2][NextFreeCell] = isOnDuty;
	Form6->StringGrid1->Cells[4][NextFreeCell] = Next->Birthday.YYYYMMDD(true);
	Form6->StringGrid1->Cells[5][NextFreeCell] = Next->Hired.YYYYMMDD(true);
	Form6->StringGrid1->Cells[6][NextFreeCell] = Next->LastVacations.YYYYMMDD(true);
	Form6->StringGrid1->Cells[7][NextFreeCell] = Next->PassportNo;
	Form6->StringGrid1->Cells[9][NextFreeCell] = Next->InsurancyPolicy;
	Form6->StringGrid1->Cells[8][NextFreeCell] = Next->SocialCrd;
	Form6->StringGrid1->Cells[10][NextFreeCell] = EduStr(Next->Degree);
	Form6->StringGrid1->Cells[11][NextFreeCell] = Next->SpecialMarks;
	Form6->StringGrid1->Cells[12][NextFreeCell] = IntToStr(Next->Salary);
	(NextFreeCell)++;

}
void StringGridClear()
{
	NextFreeCell = 1;
	Form6->StringGrid1->RowCount = 2;
	Form6->StringGrid1->Rows[1]->Clear();
	ShowingCell = -1;
}
void Enterprise::PrintAll()
{
	StringGridClear();
	for (int i = 0; i < AllWorkers.getSize(); i++) {
		Worker Guy;
		if (!AllWorkers.getItem(i,&Guy)) {
            AddToGrid(&Guy);
			ShowingCell = 1;
		} else {
			break;
		}

	}
}
void RefreshAndPrint(AnsiString Filter = "")
{
	MyEnterprise->WriteToFile(DBFileName);
	MyEnterprise->LoadFromFile(DBFileName);
	Worker Temp;
	MyEnterprise->FindByFields(&Temp,Filter);
	MyEnterprise->PrintReport();
}
//---------------------------------------------------------------------------
__fastcall TForm6::TForm6(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm6::TabSheetPageShow(TObject *Sender)
{
	 TabSheetPage->Visible = true;
	 TabSheetTable->Visible = false;
	 TabSheetBriefs->Visible = false;
}
//---------------------------------------------------------------------------
void __fastcall TForm6::TabSheetTableShow(TObject *Sender)
{
	TabSheetPage->Visible = false;
	TabSheetTable->Visible = true;
	TabSheetBriefs->Visible = false;
}
//---------------------------------------------------------------------------
void __fastcall TForm6::TabSheetBriefsShow(TObject *Sender)
{
	TabSheetPage->Visible = false;
	TabSheetTable->Visible = false;
	TabSheetBriefs->Visible = true;
}
//---------------------------------------------------------------------------
void __fastcall TForm6::FormCreate(TObject *Sender)
{
	MyEnterprise = new Enterprise(DBFileName);
    PageControl1->ActivePageIndex = 0;
	MyEnterprise->PrintAll();
	// Заполнение заголков столбцов в таблице
	AnsiString ColumnNames[] = {"ID","Name","On Duty","Appointment","Birthday","Employed since","Last Vacations","Passport No","Social Card","Insurance","Degree","Special Marks"};
	for (int i = 0; i < 12; i++) {
		StringGrid1->Cells[i][0] = ColumnNames[i];
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm6::ModeBoxChange(TObject *Sender)
{
	//По переключению режимов все изменения из списка переносятся в файл
	MyEnterprise->WriteToFile(DBFileName);
	MyEnterprise->LoadFromFile(DBFileName);
	MyEnterprise->PrintAll();


	switch (ModeBox->ItemIndex) {
	case 1:
	{
		ButtonFilters->Enabled = true;
		ButtonCommit->Visible = true;
		ButtonAdd->Visible = false;
		PageViewElementsEnabled(Edit);
		StringGrid1->Enabled = true;
		break;
	}
	case 0:
	{
		ButtonFilters->Enabled = true;
		ButtonCommit->Visible = false;
		ButtonAdd->Visible = false;
		PageViewElementsEnabled(View);
		StringGrid1->Enabled = true;
		AppMode = View;
		break;
	}
	case 2:
	{
        ButtonFilters->Enabled = false;
		ButtonCommit->Visible = false;
		ButtonAdd->Visible = true;
		PageControl1->ActivePageIndex = 1;
		StringGrid1->Enabled = false;
		PageViewElementsEnabled(Add);
	}
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm6::ButtonAddClick(TObject *Sender)
{
	MyEnterprise->AddNewPerson();
}
//---------------------------------------------------------------------------
void __fastcall TForm6::StringGrid1Click(TObject *Sender)
{
	selectedID = StrToInt(StringGrid1->Cells[0][StringGrid1->Row]);
	ShowingCell = StringGrid1->Row;
	Selected = new Worker;

	if (!MyEnterprise->PopListWorker(Selected, selectedID)) {
		MyEnterprise->PagePrint(Selected);
		Form6->PageControl1->ActivePageIndex = 1;
		if (ModeBox->ItemIndex == 1) {
			ButtonCommit->Enabled = true;
			AppMode = Edit;
		}
	} else {
		delete Selected;
		Selected = NULL;
		ShowMessage("Misclick");
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm6::ButtonCommitClick(TObject *Sender)
{
	   SetWorker(Selected);
	   MyEnterprise->ChangeWorker(Selected);
}
//---------------------------------------------------------------------------
void __fastcall TForm6::FiltersDlgButtonClick(TObject *Sender)
{
	ShowingCell == -1;
	ToFind = new Worker;
	if (FiltersDlg1->ShowModal() == idOK) {
		StringGridClear();
		if (MyEnterprise->FindByFields(ToFind,KeysToFind)>=0) {
			MyEnterprise->PrintReport();
			ShowingCell = 1;
		}
		else
			ShowingCell = -1;
	}
	delete ToFind;


}
//---------------------------------------------------------------------------
void __fastcall TForm6::ButtonNextPgClick(TObject *Sender)
{
	 Selected = new Worker;
	 if (ShowingCell == -1) {
		ShowMessage("Nothing to show with selected filtering");
		AppMode = 0;
		return;
	 }
	 if (ShowingCell == 0) {
		ShowingCell = 1;
	 }
	 if (ShowingCell >= StringGrid1->RowCount)
		ShowingCell = 1;
	 if (ShowingCell >= 1 && ShowingCell < StringGrid1->RowCount) {
		int ID = StrToInt(StringGrid1->Cells[0][ShowingCell]);
		MyEnterprise->PopListWorker(Selected,ID);
		MyEnterprise->PagePrint(Selected);
	 }
	 if(ModeBox->ItemIndex == 1)
		AppMode = Edit;
	 ShowingCell++;
}
//---------------------------------------------------------------------------
void __fastcall TForm6::ButtonPrevPgClick(TObject *Sender)
{

	 Selected = new Worker;
	 if (ShowingCell == -1) {
		 ShowMessage("Nothing to show with selected filtering");
		 AppMode = 0;
		 return;
	 }
	 if (ShowingCell == 0) {
		 ShowingCell = StringGrid1->RowCount-1;
	 }
	 if (ShowingCell >= StringGrid1->RowCount)
		 ShowingCell = StringGrid1->RowCount-1;
	 if (ShowingCell >= 1 && ShowingCell < StringGrid1->RowCount) {
		 int ID = StrToInt(StringGrid1->Cells[0][ShowingCell]);
		 MyEnterprise->PopListWorker(Selected,ID);
		 MyEnterprise->PagePrint(Selected);
	 }
	 if(ModeBox->ItemIndex == 1)
		 AppMode = Edit;
	 ShowingCell--;
}
//---------------------------------------------------------------------------

void __fastcall TForm6::ButtonComposeClick(TObject *Sender)
{
	int ItemsCount = StringGrid1->RowCount;
	int i = 1;
	//Из блока checkbox кнопок проверяем, какие из них отмечены, и их номера во вспомогательный список includesList
    for(int i = 0; i < IncludeBox1->Items->Count; i++)  
	{
		if(IncludeBox1->Checked[i])
			includesList.PushItem(i);
	}
	while(i<ItemsCount)
	{
		//Из соответствующей ячейки в таблице инфа заносится в текстовое поле, в котором пользователь составляет рапорт
		int Field;
		AnsiString OneLine = " ";
		while ((Field = includesList.PopItem())>=0) {
		   if(Field != 1 && Field != 2)
             		 OneLine += StringGrid1->Cells[Field][0] + ": ";
		   OneLine += StringGrid1->Cells[Field][i] + ", ";
		}
		RichEdit1->Lines->Add(OneLine);
		i++;
	}
	includesList.~ReportList();
}
//---------------------------------------------------------------------------



void __fastcall TForm6::ButtonClearBriefClick(TObject *Sender)
{
    RichEdit1->Clear();
}
//---------------------------------------------------------------------------

void __fastcall TForm6::ButtonSaveClick(TObject *Sender)
{
	if (SaveTextFileDialog1->Execute()) {
		String FileName = SaveTextFileDialog1->FileName;
		RichEdit1->Lines->SaveToFile(FileName);
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm6::ButtonVacationsClick(TObject *Sender)
{
	// кнопка Отправить в отпуск с сегодняшнего дня
	DateLastVacations->Date = TDateTime::CurrentDate();
	OnDutyChckBox->Checked = false;
	SetWorker(Selected);
	MyEnterprise->ChangeWorker(Selected);
	String Msg = NameEdit->Text + " is on vacations since today! Thank you!";
	RefreshAndPrint();
	ShowMessage(Msg);
}
//---------------------------------------------------------------------------

void __fastcall TForm6::ButtonFireClick(TObject *Sender)
{
	//Кнопка увольнения (и удаления из файла) работника.
	String Msg = NameEdit->Text+" Do you really want to fire this worker?";
	if (MessageDlg(Msg,mtConfirmation, TMsgDlgButtons()<<mbYes<<mbNo,0) == idYes) {
		MyEnterprise->DeleteWorker(Selected->ID);
	}
	RefreshAndPrint();
	ButtonNextPgClick(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TForm6::PageControl1Change(TObject *Sender)
{
	 if(PageControl1->ActivePageIndex == 1) {
		 ButtonNextPgClick(Sender);
	 } else if (ModeBox->ItemIndex == 2) {
		 PageControl1->ActivePageIndex = 1;
	 }
}
//----------------------------------------------------------------------
