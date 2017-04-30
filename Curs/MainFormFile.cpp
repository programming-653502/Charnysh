//---------------------------------------------------------------------------

#include <vcl.h>
#include <stdlib.h>
#pragma hdrstop

#pragma once
#include <vector>
#include "Unit6.h"
#include "OKCNHLP.h"


//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "ccalendr"
#pragma resource "*.dfm"
std::vector  <EVENT> EE;

std::vector <AnsiString> FileNamesVector;//Vextor to store .ics file names
CalendarSettings MainClndr;//Main storage for all the events
TForm6 *Form6;

EVENT* NextEvent = new EVENT("YY.txt");
// Main file with references to all other files
AnsiString MeinFile = "C:\\Users\\Mikita\\Documents\\Embarcadero\\Studio\\Projects\\Curs\\Win32\\Debug\\namesfile.txt";
bool NoCalendars = false;
int NextFreeCell = 0;

void EVENT::AddToGrid( int i, int VectNo = 0)
{
	Form6->StringGrid1->Cells[0][i] = DTSTART.HHMM(true);
	Form6->StringGrid1->Cells[1][i] = DTSTART.YYYYMMDD(true);
	Form6->StringGrid1->Cells[2][i] = CATEGORY;
	Form6->StringGrid1->Cells[3][i] = SUMMARY;
	Form6->StringGrid1->Cells[4][i] = VectNo;
	Form6->StringGrid1->Cells[5][i] = ID;
}
void CalendarSettings::ShowInfoInLabel(AnsiString info)
{
	Form6->Label1->Caption = info;
}
void CalendarSettings::NextEvent()
{
	EVENT* NextOne = ReturnEvent(NextToday);//Gets next event
	if(NextOne != NULL && NextOne->IsNext(true)) //If it's in 1minute before or ahead or right now
	{
		NextToday++; //Nextevent is next
		NextOne->CompleteReference(); //SHow info
	}
	else
        Form6->Timer1->Enabled = false;

}
void CalendarSettings::Print(int* cellNo)
{
/*Print one event to cellNo position in table*/
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
AnsiString AnsiFScanf(FILE* dest,char end = '\n')
{
/*fscanf function for AnsiString*/
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


void LoadToday();
void GetFileNames(std::vector <AnsiString> *Stor, AnsiString FileLocation)
{
	/*This function loads all used calendar file names from special file into a Stor vector*/
	Stor->clear();
	FILE* file = fopen(FileLocation.c_str(),"rt");
	if(!file)
	{
		ShowMessage("The file with refferences to all used cals missing! ReAdd them, please!");
		file = fopen(MeinFile.c_str(),"at"); //If the file is missing it will be created
		fclose(file);
		NoCalendars = true; //The flag for future ask to add some calendars
		return;
	}
	AnsiString NextName = "";
    char Test;
	int testCount = 0;
	while((Test=getc(file))!=EOF && testCount<3)  // Checking whether the file is empty or not
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
	bool CurrentFileNeeded = CurrentFile.IsEmpty(); // If current default file isn't set
	while(!feof(file))
	{
		NextName = AnsiFScanf(file);
		if(!NextName.IsEmpty())
		{
			if(CurrentFileNeeded)
			{
				CurrentFile = NextName;  // It will be set here automatically
			}
			Stor->push_back(NextName);
		}
	}
    fclose(file);

}
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



void ChangeEvent(EVENT* ToChange)
{
/*To change the event temporarly rewrites the file with it*/
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
void DeleteEvent(EVENT* ToDel)
{
/*Rewrites the file without selected event ToDel*/
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

void LoadToday(){	/*Activates functions to read all .ics files, load all the events	to find today events, and the next one,	and starts 30sec timer to track time*/	NextFreeCell = 0;	Form6->StringGrid1->RowCount = 0;	MainClndr.ClearCalendar();	GetFileNames(&FileNamesVector,MeinFile);	LoadAllFiles(&MainClndr,&FileNamesVector);
	MainClndr.PrintToday(&NextFreeCell);	TDateTime Curr;	Form6->DateTimePicker1->DateTime = Curr.CurrentDateTime();    Form6->Timer1->Enabled = true;}void AddCalendar()
{
/*Shows dialog if there is no calendars in main file*/
	if(MessageDlg("There are no calendars added. Would you like to add any?",mtWarning,TMsgDlgButtons()<< mbYes << mbNo,0) == idYes)
	{
		if(MainFileDlg1->ShowModal() == idOK)
		{
			LoadToday();
			return;

		}
	}

}
void EVENT::CompleteReference()
{
	AnsiString ToGet = SUMMARY+ " IS NEXT in your calendar !\n At: "+DTSTART.HHMM(true);
	MessageBeep(MB_ICONINFORMATION);
	MessageDlg(ToGet,mtInformation, TMsgDlgButtons() << mbOK,0);
}


__fastcall TForm6::TForm6(TComponent* Owner)
	: TForm(Owner)
{

}
//---------------------------------------------------------------------------
void __fastcall TForm6::ButtonAddClick(TObject *Sender)
{
   /* Adding event button click*/
	EVENT* NewEvent = new EVENT(CurrentFile);
	if(!NewEvent->EventSetDlg(CurrentFile))
	{
		NewEvent->AddToFile();
		LoadToday();
	}

}
//---------------------------------------------------------------------------
void __fastcall TForm6::ButtonShowAllClick(TObject *Sender)
{
	//Print all button click
	NextFreeCell = 0;
	MainClndr.PrintAll(&NextFreeCell);
}
//---------------------------------------------------------------------------


void __fastcall TForm6::FormCreate(TObject *Sender)
{
	LoadToday();
}

//---------------------------------------------------------------------------




void __fastcall TForm6::ButtonHelpClick(TObject *Sender)
{
	//Help button click
	  AboutBox->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TForm6::ButtonMyCalsClick(TObject *Sender)
{
// MyClandars button click . Shows dialog to add, remove, set default .ics calendars
		if(MainFileDlg1->ShowModal() == idOK)
		{
			LoadToday();
		}	//LoadToday();
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
	//Show required date events(selected in DatePicker)
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
	/*Showing Dlg with info about clicked event
	buttons to change or delete it*/
    	int SelectedEvent = StringGrid1->Row;
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

void __fastcall TForm6::SpinButtonDaysDownClick(TObject *Sender)
{
/*Going day back on spin button down click*/
	TDateTime ToShow = DateTimePicker1->DateTime;
	ToShow--;
	DateTimePicker1->DateTime = ToShow;
	DateTimePicker1CloseUp(Sender);

}
//---------------------------------------------------------------------------

void __fastcall TForm6::SpinButtonDaysUpClick(TObject *Sender)
{
	//Going day ahead
	TDateTime ToShow = DateTimePicker1->DateTime;
	ToShow++;
	DateTimePicker1->DateTime = ToShow;
	DateTimePicker1CloseUp(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TForm6::ButtonTodayClick(TObject *Sender)
{
	//Today button click
    TDateTime ToShow = DateTimePicker1->DateTime;
	ToShow = ToShow.CurrentDateTime();
	DateTimePicker1->DateTime = ToShow;
	DateTimePicker1CloseUp(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TForm6::Timer1Timer(TObject *Sender)
{
//Timer to check if it's time for some events
	MainClndr.NextEvent();
}
//---------------------------------------------------------------------------


bool __fastcall TForm6::FormHelp(WORD Command, NativeInt Data, bool &CallHelp)
{
	AboutBox->ShowModal();
}
//---------------------------------------------------------------------------
