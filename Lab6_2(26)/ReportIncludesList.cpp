//---------------------------------------------------------------------------

#pragma hdrstop

#include "ReportIncludesList.h"

ReportList::ReportList()
{
	Size = 0;
	First = Next = 0;
}

void ReportList::PushItem(int No)
{
	if (!First) {
		First = new ReportItem;
		First->next = 0;
		First->Cell = No;
		Size = 1;
		Next = First;
		return;
	}
	ReportItem *Temp = First;
	while(Temp->next)
		Temp = Temp->next;
	Temp->next = new ReportItem;
	Temp->next->Cell = No;
	Temp->next->next = 0;
	Size++;
}
int ReportList::PopItem()
{
	if (!First && !Next)
	   return -1;
	if (!Next) {
		Next = First;
		return -1;
	}
	int ToReturn = Next->Cell;
	Next = Next->next;
	return ToReturn;
}
ReportList::~ReportList()
{
	while(First) {
		ReportItem *Temp = First->next;
		delete First;
		First = Temp;
	}
	First = Next = 0;
	Size = 0;
}
int ReportList::getSize()
{
	return Size;
}
//---------------------------------------------------------------------------
#pragma package(smart_init)
