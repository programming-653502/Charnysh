//---------------------------------------------------------------------------

#ifndef WorkerClassH
#define WorkerClassH
#include "TrueDate.h"
#include "vcl.h"
#include "stdio.h"
#include "WorkersContainer.h"
#include "ReportIncludesList.h"
#include <vector>


AnsiString EduStr(Education degree);
AnsiString AppointmentStr(Appointment Pos);

class Enterprise
{
	String EnterpriseName;

	WorkersL AllWorkers;

	ReportList Report;
	void ListDestructor();

	public:
		Enterprise(AnsiString FileName);
		int LoadFromFile(AnsiString FileName);
		void AddNewPerson();
		int ChangeWorker(Worker* Change);
		int WriteToFile(AnsiString FileName);
		void AddToGrid(Worker* Next);
		void PagePrint(Worker* Next);
		void PrintAll();
		void PrintReport();
		//List operations
		void PushList(Worker* Next);
		int PopListWorker(Worker* Next, int index);
		int DeleteWorker(Worker *ToDelete);
		int DeleteWorker(int index);
		//int FindByFields(Worker* ToFind, AnsiString Keys);
		int FindByFields(Worker *Wanted,AnsiString Keys, bool Print = true);
		bool EqualTo(Worker* First, Worker* Second, AnsiString Keys);

};
//---------------------------------------------------------------------------
#endif
