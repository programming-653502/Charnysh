//---------------------------------------------------------------------------

#pragma hdrstop
//#pragma once

#include "CalendarFunctions.h"

long int PositionOfNextEvent(FILE* theFile, long int* NextPos)
{
	long Position = 0;
	char* NextStr = new char[500];
	while(!feof(theFile))
	{
		fscanf(theFile,"\n%s",NextStr);

		if(feof(theFile))
		{
			return -1;
		}
		else if(!strcmp("BEGIN:VEVENT",NextStr))
		{
			Position = *NextPos =  ftell(theFile);
			while(!feof(theFile))
			{
				fscanf(theFile,"\n%s",NextStr);

				if(feof(theFile))
				{
					return -1;
				}
				else if(!strcmp("END:VEVENT",NextStr))
				{
					*NextPos=ftell(theFile);
					return Position;
				}
			}
		}
	}
}
CalendarSettings::CalendarSettings()
{
    DateToday = DateToday.CurrentDate();
	FileName = "";
	FirstToday = LastToday = NextToday = FirstToShow = LastToShow = 0;
}
CalendarSettings::CalendarSettings(AnsiString FName)
{
	DateToday = DateToday.CurrentDate();
	FileName = FName;
	FirstToday = LastToday = NextToday = FirstToShow = LastToShow = 0;
}
CalendarSettings::CalendarSettings(int DayToday, int MonthToday, int YearToday)
{

}
int CalendarSettings::LoadFrom(AnsiString FileName)
{
	this->FileName = FileName;
	FILE* DataFile = fopen(FileName.c_str(),"r");
	if(!DataFile)
	{
		ShowMessage("The file not exist");
		return -1;
	}

	long int Position = 0,NextPosition =0;
	char* NextStr = new char[100];
	while((Position = PositionOfNextEvent(DataFile,&NextPosition))>0)
	{
		if(Position == NextPosition)
		{
			ShowMessage("EmptyFile (or broken one)");
			return -1;
		}
	   //	fseek(DataFile,Position,0);
		EVENT* NewEvent = new EVENT(FileName);
		NewEvent->LoadFromFile(DataFile,Position,NextPosition,FileName);
		EventsInFile.push_back(*NewEvent);

	}
	fclose(DataFile);
}
int  CalendarSettings::LoadFrom()
{
   LoadFrom(FileName);
}
void CalendarSettings::WriteToFile()
{
	WriteToFile(FileName);
}
void CalendarSettings::WriteToFile(AnsiString FileName)
{
	this->FileName = FileName;
	int i = 0;
	int size = EventsInFile.size();

	FILE* fp = fopen(FileName.c_str(),"wt");
    fclose(fp);

	while(i<size)
	{
		EVENT NewEvent = EventsInFile.at(i);
		NewEvent.AddToFile();
		i++;
	}

}
void CalendarSettings::Sort()
{
	int size = EventsInFile.size();
	for (int i = 0; i < size; i++)
	{
		int j = size-1;

		while (j > i)
		{
			EVENT Ev1 = EventsInFile.at(j-1);
			EVENT Ev2 = EventsInFile.at(j);
			TrueDate Dt1 = Ev1.DTSTART, Dt2 = Ev2.DTSTART;
			if (Dt1.Compare(&Dt1, &Dt2,false) > 0)
			{
				EventsInFile.at(j-1) = Ev2;
				EventsInFile.at(j) = Ev1;
			}
			j--;
		}
	}
    size = EventsInFile.size();
}

int CalendarSettings::Day(unsigned Day, unsigned Month, unsigned Year)
{
	FirstToShow = LastToShow = 0;
   bool FirstFound = false;
   TrueDate TheDay;
   TheDay.SetDate(Year, Month, Day);
	int size = EventsInFile.size();
	int i = 0;
	while(i <size)
	{
		EVENT NextEv = EventsInFile.at(i);
		if((FirstFound == false) && (TheDay.Compare(&TheDay, &NextEv.DTSTART,true) == 0))
		{
			FirstFound = true;
			FirstToShow = i;
		}
		if((FirstFound == true) && (TheDay.Compare(&TheDay, &NextEv.DTSTART,true) == 0))
		{
			LastToShow = i;
			//return;
		}
		i++;
	 }
	 if(FirstToShow == LastToShow)
	 {
		EVENT NextEv = EventsInFile.at(LastToShow);
		if(NextEv.DTSTART.year != Year || NextEv.DTSTART.month != Month || NextEv.DTSTART.day != Day )
		{
			AnsiString Info = "Nothing was found for this day";
			//ShowMessage(Info);
			ShowInfoInLabel(Info);
			return -1;
		}
	 }
	 ShowInfoInLabel("Events for this day:");
	 return 0;
}
int CalendarSettings::Today()
{
	FirstToShow = LastToShow = FirstToday = LastToday = NextToday = 0;
	bool FirstTodayFound = false, NextTodayFound = false;
	int size = EventsInFile.size();
	int i = 0;
	while(i <size)
	{
		EVENT NextEv = EventsInFile.at(i);
		if(!FirstTodayFound)
		{
			if(NextEv.IfToday())
			{
				FirstToday = i;
				FirstTodayFound = true;
				LastToday = i;
				i++;
				if(NextEv.IsNext() == true)
				{
					NextTodayFound = i;
					NextTodayFound = true;
				}
				continue;
			}
		}
		if(NextEv.IfToday() == true)
		{
			LastToday = i;
			if(NextTodayFound == false && NextEv.IsNext() == true)
			{
				NextToday = i;
				NextTodayFound = true;
			}
			//i++;

		}
		i++;
	}
	if(FirstToday == LastToday)
	 {
		EVENT NextEv = EventsInFile.at(LastToday);
		if(!NextEv.IfToday())
		{
			AnsiString Info = "Nothing was found for today";
			ShowMessage(Info);
			ShowInfoInLabel(Info);
			return -1;
		}
	 }
	 ShowInfoInLabel("Events for today day:");
	 return 0;
}

void CalendarSettings::PrintAll(int *cellNo)
{
	if(EventsInFile.empty())
		return;
	LastToShow = EventsInFile.size() - 1;
	FirstToShow = 0;
	Print(cellNo);
}
void CalendarSettings::PrintDay(int DayToPrint, int MonthToPrint, int YearToPrint, int* cellNo)
{
	if(EventsInFile.empty())
		return;
	if(!Day(DayToPrint, MonthToPrint, YearToPrint))
		Print(cellNo);

}
void CalendarSettings::PrintToday(int* cellNo)
{
	if(EventsInFile.empty())
		return;
   if(FirstToday == LastToday)
   {
		if(Today()<0)
			return;
   }
   FirstToShow = FirstToday;
   LastToShow = LastToday;
   Print(cellNo);
}
EVENT* CalendarSettings::ReturnEvent(int VectNo)
{
	if(VectNo > EventsInFile.size())
		return NULL;
	else
		return &EventsInFile.at(VectNo);
}
int CalendarSettings::Find(EVENT* Ev)
{
	if(EventsInFile.empty())
		return -1;
	int i = 0;
	int size = EventsInFile.size();
	while(i<size)
	{
		EVENT Next = EventsInFile.at(i);
		if(Ev->Compare(&Next) == 6)
			return i;
		i++;
	}
	return -1;
}

void CalendarSettings::AddEventTo(EVENT* ToAdd, int where)
{
	int size = EventsInFile.size();
	if(where>size)
		return;
	 EventsInFile.at(where) = *ToAdd;
     size = EventsInFile.size();
	 Sort();
}
void CalendarSettings::ClearCalendar()
 {
	FirstToShow = LastToShow = FirstToday = LastToday = NextToday = 0;
	EventsInFile.clear();
 }
void CalendarSettings::Delete(int Position)
{
	EventsInFile.erase(EventsInFile.begin()+ Position);
}


//---------------------------------------------------------------------------
#pragma package(smart_init)
