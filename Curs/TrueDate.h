//---------------------------------------------------------------------------

#ifndef TrueDateH
#define TrueDateH
#include <vcl.h>

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
	void TDateTimeToTrueDate(TDateTime* MyDate);
	int Compare(TrueDate* dt1, TrueDate* dt2, bool DateOnly);
	AnsiString YYYYMMDD(bool pointers = false);
	AnsiString HHMM(bool pointers = false);
};
//---------------------------------------------------------------------------
#endif
