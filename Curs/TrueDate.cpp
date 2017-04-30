//---------------------------------------------------------------------------

#pragma hdrstop
#include "TrueDate.h"
#pragma once


TrueDate::TrueDate()
{
 year = month = day = hour = min = 0;
}
void TrueDate::SetDate(int year, int month, int day)
{
	this->year = year;
	this->month = month;
	this->day = day;
}
void TrueDate::SetTime(int hour, int min)
{
	this->hour = hour;
	this->min = min;
}
void TrueDate::copyDT(TrueDate* From)
{
	year = From->year;
	month = From->month;
	day  = From->day;
	hour = From->hour;
	min = From->min;
}
void TrueDate::SetCurrent()
{

	TDateTime DT = TDateTime::CurrentDateTime();
	this->TDateTimeToTrueDate(&DT);
}
void TrueDate::SetByArray(int * YearMonthDayHourMin, int size)
{
	int i = 0;

		if(size>=1)
			year = YearMonthDayHourMin[0];
		if(size>=2)
			month = YearMonthDayHourMin[1];
		if(size >= 3)
			day = YearMonthDayHourMin[2];
		if(size >= 4)
			hour = YearMonthDayHourMin[3];
		if(size == 5)
			min = YearMonthDayHourMin[4];

}
void TrueDate::TDateTimeToTrueDate(TDateTime* DT)
{
	unsigned short yyyy,mm,dd,hh,min;
	DT->DecodeDate(&yyyy,&mm,&dd);
	this->year = yyyy;
	this->month = mm;
	this->day = dd;
	DT->DecodeTime(&hh,&min,&yyyy, &mm);//Requires to much params
	this->hour = hh;
	this->min = min;
}
AnsiString TrueDate::YYYYMMDD(bool pointers)
{
	AnsiString MonthDay="";
	if(month<10)
	{
		MonthDay+='0';
		MonthDay+=IntToStr(month);
	}
	else
		MonthDay+=IntToStr(month);
	if(pointers)
	if(pointers)
		MonthDay += '.';
	if(day<10)
	{
		MonthDay+='0';
		MonthDay+=IntToStr(day);
	}
	else
		MonthDay+=IntToStr(day);

	AnsiString Date = IntToStr(year);
	if(pointers)
		Date += '.';
	Date += MonthDay;
	return Date;
}
AnsiString TrueDate::HHMM(bool pointers)
{
	AnsiString Time ="";
	if(hour<10)
	{
		Time += '0';
		Time += IntToStr(hour);
	}
	else
	 Time+=IntToStr(hour);
	if(pointers)
		Time += ':';
	if(min<10)
	{
		Time += '0';
		Time += IntToStr(min);
	}
	else
	 Time+=IntToStr(min);
	return Time;
}
int TrueDate::Compare(TrueDate* dt1, TrueDate* dt2, bool DateOnly = true)
{
	if(dt1->year < dt2->year)
	{
	return -1;
	}
	else if(dt1->year > dt2->year)
	{
		return 1;
	}
	else
	{
		if(dt1->month < dt2->month)
		{
			return -1;
		}
		else if(dt1->month > dt2->month)
		{
			return 1;
		}
		else
		{
			if(dt1->day < dt2->day)
			{
				return -1;
			}
			else if(dt1->day > dt2->day)
			{
				return 1;
			}
			else
			{
				if(DateOnly == false)
				{
					if(dt1->hour < dt2->hour)
					{
						return -1;
					}
					else if(dt1->hour > dt2->hour)
					{
						return 1;
					}
					else
					{
						if(dt1->min < dt2->min)
						{
							return -1;
						}
						else if(dt1->min > dt2->min)
						{
							return 1;
						}
						else
						{
							return 0;
						}
					}
				}
				else
                    return 0;
			}
		}
	}
}
//---------------------------------------------------------------------------
#pragma package(smart_init)
