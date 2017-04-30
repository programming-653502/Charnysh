//---------------------------------------------------------------------------

#ifndef CalendarFunctionsH
#define CalendarFunctionsH
#pragma once
#include <vcl.h>
#include <vector>
#include "TEVENT.h"
#include "TrueDate.h"
//#include "Unit6.h"


class CalendarSettings
{
	TDateTime DateToday;
	std::vector <EVENT> EventsInFile;
	AnsiString FileName;
	//If it is nessesary?
	int FirstToday, LastToday, NextToday;
	int FirstToShow, LastToShow;
	public:
		CalendarSettings();
		CalendarSettings(AnsiString FName);
		CalendarSettings(int DayToday, int MonthToday, int YearToday);
		int LoadFrom();
		int LoadFrom(AnsiString FileName);
		int Day(unsigned Day, unsigned Month, unsigned Year);
		int Today();
		//void TodayToVector(std::vector<EVENT> TodayEvents)
		void Sort();
		void WriteToFile(AnsiString FileName);
		void WriteToFile();
		void NextEvent();
		int Next(AnsiString* Summary);
		void PrintAll(int*);
		void PrintDay(int DayToPrint, int MonthToPrint, int YearToPrint, int*);
		void PrintToday(int*);
		void Print(int*);
		void ShowInfoInLabel(AnsiString info);

		EVENT* ReturnEvent(int VectNo);
		int Find(EVENT* Ev);
		void Delete(int Position);
		void AddEventTo(EVENT* ToAdd, int where);
		void ClearCalendar();
};



//---------------------------------------------------------------------------
#endif
