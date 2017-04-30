//---------------------------------------------------------------------------

#ifndef TEVENTH
#define TEVENTH
#include <stdio.h>
#include <vcl.h>
//#include "Unit6.h"
#include "TrueDate.h"
#include "OKCNHLP.h"


class EVENT
{
	AnsiString ID;
	AnsiString SUMMARY;
	AnsiString CATEGORY;

	void DateArray(int* Array, AnsiString DateStr);
	void ReadStr(AnsiString tagStr, AnsiString ValueStr);
	void ParseEventStr(AnsiString Str);
	int GetEvent(FILE* file, long beginningPos, long endingPos, AnsiString* STR);

	public:
	TrueDate DTSTART;
	AnsiString FILENAME;

	EVENT(AnsiString FileName);

	int EventSetDlg(AnsiString FileName);
	void EVENTSet(AnsiString Summary, AnsiString Category, TDateTime Start,AnsiString FileName);
	void AddToFile(AnsiString FileName);
	void AddToFile();
	void LoadFromFile(FILE* thefile,long int StartPos, long int EndPos,AnsiString FileName);
	void DeleteFromFile(AnsiString FileName);

	bool IfToday();
	bool IsNext(bool Soon = false);

	void ReturnDate(int* yyyy, int* mm, int*dd);
	void ReturnTime(int* hh, int* mm);

	bool SetTime(int* hh, int* mm);
	bool SetDate(int* yyyy, int* mm, int*dd);
	void AddToGrid(int i, int VectNo);

	void CompleteReference();

	int Compare(EVENT* ToComp);
};
//---------------------------------------------------------------------------
#endif
