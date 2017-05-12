//---------------------------------------------------------------------------

#ifndef WorkersContainerH
#define WorkersContainerH
#include "TrueDate.h"
#include "stdio.h"

enum Education{ Associate = 1, Bachelor, Master };
enum Appointment {Washer = 1, JrDev, SeniorDev,ProjectMgr, Director};

struct Worker
{
	int ID;
	char Name[50];
	char PassportNo[10];
	char InsurancyPolicy[10];
	char SocialCrd[10];
	Education Degree;
	Appointment Position;
	TrueDate Birthday;
	TrueDate Hired;
	TrueDate LastVacations;
	int Salary;
	bool OnDuty;
	char SpecialMarks[50];
	Worker* next;
	Worker* prev;
};
// Класс для реализации 2направленного списка
class WorkersL
{
	Worker *First;
	Worker *Head;
	int Size;
	void Copy(Worker* To, Worker* From);
	public:
	WorkersL();
	void pushItem(Worker * ToPush);
	int changeItem(int index, Worker* Changes);
	int getItem(int index, Worker* Dest);
	int deleteItem(int index);
	int getSize();
	~WorkersL();
};
//---------------------------------------------------------------------------
#endif
