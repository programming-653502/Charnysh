//---------------------------------------------------------------------------

#pragma hdrstop

#include "WorkersContainer.h"
WorkersL::WorkersL()
{
	First = Head = 0;
}
void WorkersL::Copy(Worker* To, Worker *From)
{
	To->ID = From->ID;
	strcpy(To->Name,From->Name);
	strcpy(To->PassportNo,From->PassportNo);
	strcpy(To->InsurancyPolicy,From->InsurancyPolicy);
	strcpy(To->SocialCrd,From->SocialCrd);
	strcpy(To->SpecialMarks,From->SpecialMarks);
	To->Birthday.copyDT(&From->Birthday);
	To->Hired.copyDT(&From->Hired);
	To->LastVacations.copyDT(&From->LastVacations);
	To->Degree = From->Degree;
	To->Position = From->Position;
	To->Salary = From->Salary;
	To->OnDuty = From->OnDuty;
}
void WorkersL::pushItem(Worker * ToPush)
{
	if(!First)
	{
		Size = 1;
		First = new Worker;
		Copy(First,ToPush);
		First->ID = 0;
		First->next = First->prev = 0;
		Head = First;
		return;
	}
	Worker* Temp = First;
	while(Temp->next)
		Temp = Temp->next;
	Temp->next = new Worker;
	Copy(Temp->next,ToPush);
	Temp->next->ID = Temp->ID + 1;
	Temp->next->prev = Temp;
	Temp->next->next = 0;
	Size++;
}
int WorkersL::getItem(int index, Worker* Dest)
{
	if (index >= Size)
		return -1;
	Worker* Temp = First;
	for (int i = 0; i<index; i++)
	{
		Temp = Temp->next;
	}
	Copy(Dest,Temp);
	return 0;
}
int WorkersL::deleteItem(int index)
{
	if (index >= Size)
		return -1;
	Worker* Temp = First;
	Worker* Next = NULL;
	for (int i = 0; i<index; i++) {
		Temp = Temp->next;
	}
	if (Temp == First) {
		Temp = First->next;
		if(First->next)
			First->next->prev = 0;
		delete First;
		First = Temp;
		Size--;
        Next = Temp;
        while(Next)
		{
			Next->ID--;
			Next = Next->next;
		}
		return 0;
	}
	if (Temp->prev)
		Temp->prev->next = Temp->next;
	if (Temp->next) {
		Next = Temp->next;
		Temp->next->prev = Temp->prev;
	}
	delete Temp;
	while(Next)
	{
		Next->ID--;
		Next = Next->next;
	}
	Temp = 0;
	Size--;
	return 0;
}
int WorkersL::changeItem(int index, Worker* Changes)
{
    if (index >= Size)
		return -1;
	Worker* Temp = First;
	for (int i = 0; i<index; i++)
	{
		Temp = Temp->next;
	}
	Copy(Temp,Changes);
	Temp->ID = index;
	return 0;
}
int WorkersL::getSize()
{
	return Size;
}
WorkersL::~WorkersL()
{
	while(First)
	{
		Worker* Temp = First->next;
		delete First;
		First = Temp;
	}
	Size = 0;
}
//---------------------------------------------------------------------------
#pragma package(smart_init)
