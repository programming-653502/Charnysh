//---------------------------------------------------------------------------

#include <vcl.h>
#include <stdlib.h>
#pragma hdrstop

#pragma once
#include <vector>
#include "Unit6.h"
#include "OKCNHLP.h"
#pragma comment(lib, "urlmon.lib")

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "ccalendr"
#pragma resource "*.dfm"
std::vector  <EVENT> EE;

std::vector <AnsiString> FileNamesVector;
CalendarSettings MainClndr;
TForm6 *Form6;

EVENT* NextEvent = new EVENT("YY.txt");
AnsiString MeinFile = "C:\\Users\\Mikita\\Documents\\Embarcadero\\Studio\\Projects\\Curs\\Win32\\Debug\\namesfile.txt";
bool NoCalendars = false;
int NextFreeCell = 0;

void EVENT::AddToGrid( int i, int VectNo = 0, int cellsCount)
{
	if(cellsCount>0)
	{
	   Form6->StringGrid1->RowCount = cellsCount;
	}
	Form6->StringGrid1->Cells[0][i] = DTSTART.HHMM(true);
	Form6->StringGrid1->Cells[1][i] = DTSTART.YYYYMMDD(true);
	Form6->StringGrid1->Cells[2][i] = CATEGORY;
	Form6->StringGrid1->Cells[3][i] = SUMMARY;
	Form6->StringGrid1->Cells[4][i] = VectNo;
	Form6->StringGrid1->Cells[5][i] = ID;
}
//---------------------------------------------------------------------------

void CalendarSettings::ShowInfoInLabel(AnsiString info)
{
	Form6->Label1->Caption = info;
	EVENT* NextOne = ReturnEvent(NextToday);
    if(NextOne != NULL && NextOne->IsNext())
	{
		Form6->LabelToday->Caption = "NEXT In Your Schedule:\n"+NextOne->StrInfo();
	}
	else
	{
			Form6->LabelToday->Caption = "\n     No more upcomming\n    events for today";
	}
}
//---------------------------------------------------------------------------

void CalendarSettings::NextEvent()
{
	EVENT* NextOne = ReturnEvent(NextToday);
	if(NextOne != NULL && NextOne->IsNext())
	{
		Form6->LabelToday->Caption = "NEXT In Your Schedule:\n"+NextOne->StrInfo();
		if(NextOne->IsNext(true))
		{
			NextToday++;
			NextOne->CompleteReference();
		}
	}
	else
	{
		Form6->LabelToday->Caption = "No more events for today";
		Form6->Timer1->Enabled = false;
	}
}
//---------------------------------------------------------------------------

void CalendarSettings::Print(int* cellNo)
{
	int i = FirstToShow;
	int size = LastToShow-FirstToShow;

	Form6->StringGrid1->RowCount = size+1;

	while(i <= LastToShow)
	{
		EVENT ToPrint = EventsInFile.at(i);
		ToPrint.AddToGrid(*cellNo,i);
		(*cellNo)++;
		i++;
	}

}
//---------------------------------------------------------------------------

AnsiString AnsiFScanf(FILE* dest,char end = '\n')
{
	if(!dest || feof(dest))
		return NULL;
	char NextCh = '\0';
	AnsiString ST = "";
	NextCh = (char)getc(dest);
	while((NextCh) != end && !feof(dest))
	{

		ST +=NextCh;
		NextCh = (char)getc(dest);
	}
	return ST;
}
//---------------------------------------------------------------------------


void LoadToday();
//---------------------------------------------------------------------------

void GetFileNames(std::vector <AnsiString> *Stor, AnsiString FileLocation)
{
	Stor->clear();
	FILE* file = fopen(FileLocation.c_str(),"rt");
	if(!file)
	{
		ShowMessage("The file with refferences to all used cals missing! ReAdd them, please!");
		file = fopen(MeinFile.c_str(),"at");
		fclose(file);
		NoCalendars = true;
		return;
	}
	AnsiString NextName = "";
    char Test;
	int testCount = 0;
	while((Test=getc(file))!=EOF && testCount<3)
	{
		testCount++;
	}
	if(testCount<=2)
	{
		NoCalendars = true;
		fclose(file);
		return;
	}
	fseek(file,0,0);
	bool CurrentFileNeeded = CurrentFile.IsEmpty();
	while(!feof(file))
	{
		NextName = AnsiFScanf(file);
		if(!NextName.IsEmpty())
		{
			if(CurrentFileNeeded)
			{
				CurrentFile = NextName;
			}
			Stor->push_back(NextName);
		}
	}
    fclose(file);

}
//---------------------------------------------------------------------------

void LoadAllFiles(CalendarSettings *iCal1, std::vector<AnsiString>* FileNames)
{
	int NumbOfFiles = FileNames->size();
	if(NumbOfFiles == 0)
		return;
	int index = 0;
	while(index < NumbOfFiles)
	{
		if(iCal1->LoadFrom(FileNames->at(index))>0)
		{
			iCal1->Sort();
		}
		index++;
	}
}



//---------------------------------------------------------------------------

void ChangeEvent(EVENT* ToChange)
{
	CalendarSettings TempCal(ToChange->FILENAME);
	TempCal.LoadFrom();
	int ItsPosition = TempCal.Find(ToChange);
	if(ItsPosition<0)
	{
		ShowMessage("Error! No such event found in this file. You can create it.");
		return;
	}
	ToChange->EventSetDlg(ToChange->FILENAME);
	TempCal.AddEventTo(ToChange,ItsPosition);
	TempCal.WriteToFile();
}
//---------------------------------------------------------------------------

void DeleteEvent(EVENT* ToDel)
{
	CalendarSettings TempCal(ToDel->FILENAME);
	TempCal.LoadFrom();
	int ItsPosition = TempCal.Find(ToDel);
	if(ItsPosition<0)
	{
		ShowMessage("Error! No such event found in this file. You can create it.");
		return;
	}

	TempCal.Delete(ItsPosition);
	TempCal.WriteToFile();
}



//---------------------------------------------------------------------------

void LoadToday(){	NextFreeCell = 0;	Form6->StringGrid1->RowCount = 0;    Form6->StringGrid1->Rows[0]->Clear();	MainClndr.ClearCalendar();	GetFileNames(&FileNamesVector,MeinFile);	LoadAllFiles(&MainClndr,&FileNamesVector);
	MainClndr.PrintToday(&NextFreeCell);	TDateTime Curr;	//MainClndr.ShowInfoInLabel("Events for today");	Form6->DateTimePicker1->DateTime = Curr.CurrentDateTime();	Form6->Timer1->Enabled = true;	MainClndr.NextEvent();}//---------------------------------------------------------------------------void AddCalendar()
{
	if(MessageDlg("There are no calendars added. Would you like to add any?",mtWarning,TMsgDlgButtons()<< mbYes << mbNo,0) == idYes)
	{
		if(MainFileDlg1->ShowModal() == idOK) //flag
		{
			LoadToday();
			return;

		}
	}

}
//---------------------------------------------------------------------------
void EVENT::CompleteReference()
{
	AnsiString ToGet = SUMMARY+ " IS NEXT in your calendar !\n At: "+DTSTART.HHMM(true);
	MessageBeep(MB_ICONINFORMATION);
	MessageDlg(ToGet,mtInformation, TMsgDlgButtons() << mbOK,0);
}
//---------------------------------------------------------------------------
__fastcall TForm6::TForm6(TComponent* Owner)
	: TForm(Owner)
{

}
//---------------------------------------------------------------------------
void __fastcall TForm6::ButtonAddClick(TObject *Sender)
{
	EVENT* NewEvent = new EVENT(CurrentFile);
	if(!NewEvent->EventSetDlg(CurrentFile))
	{
		NewEvent->AddToFile();
		LoadToday();
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm6::ButtonShowClick(TObject *Sender)
{
	NextFreeCell = 0;
	MainClndr.PrintAll(&NextFreeCell);
}
//---------------------------------------------------------------------------


void __fastcall TForm6::FormCreate(TObject *Sender)
{
	LoadToday();
}

//---------------------------------------------------------------------------


void __fastcall TForm6::ButtonHlpClick(TObject *Sender)
{
	  AboutBox->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TForm6::ButtonMyCalsClick(TObject *Sender)
{
	if(MainFileDlg1->ShowModal() == idOK)
	{
		LoadToday();
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm6::FormShow(TObject *Sender)
{
    if(NoCalendars)
	 {
		AddCalendar();
		LoadToday();
	 }
}
//---------------------------------------------------------------------------

void __fastcall TForm6::DateTimePicker1CloseUp(TObject *Sender)
{
	TDateTime DateToShow = DateTimePicker1->DateTime;
	unsigned short day, year, month;
	DateToShow.DecodeDate(&year,&month,&day);
	NextFreeCell = 0;
	StringGrid1->RowCount = 0;
	StringGrid1->Rows[0]->Clear();
	MainClndr.PrintDay(day,month,year,&NextFreeCell);
}
//---------------------------------------------------------------------------

void __fastcall TForm6::StringGrid1Click(TObject *Sender)
{
    int SelectedEvent = StringGrid1->Row;
	if(StringGrid1->Cells[4][SelectedEvent].IsEmpty())
	{
		ShowMessage("There are no events here");
		return;
	}


	AnsiString Info = "Event: "+StringGrid1->Cells[3][SelectedEvent]+"\n In "+StringGrid1->Cells[1][SelectedEvent]+"\nAt "+StringGrid1->Cells[0][SelectedEvent];
	Info+=" \nTo change press Yes, to delete press No, to close press OK";
	switch(MessageDlg(Info,mtInformation, TMsgDlgButtons() <<mbOK<< mbYes << mbNo,0))
	{
	case  idYes:
	{

		int Number = StrToInt(StringGrid1->Cells[4][SelectedEvent]);
		EVENT* ToChange = MainClndr.ReturnEvent(Number);
		ChangeEvent(ToChange);
		LoadToday();
		break;
	}
	case idNo:
	{
		int Number = StrToInt(StringGrid1->Cells[4][SelectedEvent]);
		EVENT* ToChange = MainClndr.ReturnEvent(Number);
		DeleteEvent(ToChange);
		LoadToday();
		break;
	}
	}

}
//---------------------------------------------------------------------------

void __fastcall TForm6::SpinButton2DownClick(TObject *Sender)
{
	TDateTime ToShow = DateTimePicker1->DateTime;
	ToShow--;
	DateTimePicker1->DateTime = ToShow;
	DateTimePicker1CloseUp(Sender);

}
//---------------------------------------------------------------------------

void __fastcall TForm6::SpinButton2UpClick(TObject *Sender)
{
	TDateTime ToShow = DateTimePicker1->DateTime;
	ToShow++;
	DateTimePicker1->DateTime = ToShow;
	DateTimePicker1CloseUp(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TForm6::ButtonTodayClick(TObject *Sender)
{
    TDateTime ToShow = DateTimePicker1->DateTime;
	ToShow = ToShow.CurrentDateTime();
	DateTimePicker1->DateTime = ToShow;
	DateTimePicker1CloseUp(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TForm6::Timer1Timer(TObject *Sender)
{
	MainClndr.NextEvent();
}
//---------------------------------------------------------------------------


bool __fastcall TForm6::FormHelp(WORD Command, NativeInt Data, bool &CallHelp)
{
	AboutBox->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TForm6::Edit1DblClick(TObject *Sender)
{
	NextFreeCell = 0;
	StringGrid1->RowCount = 0;
	StringGrid1->Rows[0]->Clear();
	MainClndr.Find(Edit1->Text,&NextFreeCell);

}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------



//---------------------------------------------------------------------------

void __fastcall TForm6::Button1Click(TObject *Sender)
{
	String URL = "http://xml.meteoservice.ru/export/gismeteo/point/34.xml";
//
	String FileName = "file.xml";
//
	if( URLDownloadToFileW( 0,URL.w_str(), FileName.w_str(),  0, 0) != S_OK)
	{
         Button1->Caption == "No Connection. Click to try adain";
		return;
	}
	Forecast *FC = new Forecast(FileName);
	FC->GetWeather();
	Button1->Caption = FC->ShowIndo();
}
//---------------------------------------------------------------------------

