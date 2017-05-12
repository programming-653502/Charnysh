//---------------------------------------------------------------------------

#ifndef TrueDateH
#define TrueDateH
#include <vcl.h>
/*custom class to store date and time providing easy access to all fields and convert functions (из моего курсача))*/
class TrueDate
{
	public:
	int year;
	int month;
	int day;
	int hour;
	int min;
	TrueDate();
	void SetDate(int year, int month, int day);
	void SetTime(int hour, int min);
    void copyDT(TrueDate* From);
	void SetByArray(int * array, int size);
	void SetCurrent();
	void TDateTimeToTrueDate(TDateTime MyDate);
	void TDateTimeToTrueDate(TDateTime* MyDate);
    TDateTime TrueDateToTDateTime();
	int Compare(TrueDate* dt1, TrueDate* dt2, bool DateOnly = true);
	AnsiString YYYYMMDD(bool pointers = false); //Returns date AnsiString with or without separating dots
	AnsiString HHMM(bool pointers = false);
};
//---------------------------------------------------------------------------
#endif
