//---------------------------------------------------------------------------

#ifndef WorkerClassH
#define WorkerClassH
#include "TrueDate.h"
#include "vcl.h"
#include "stdio.h"
#include "WorkersContainer.h"
#include "ReportIncludesList.h"
#include <vector>

//Класс для обработки всех записей базы данных
AnsiString EduStr(Education degree);
AnsiString AppointmentStr(Appointment Pos);

class Enterprise
{
	String EnterpriseName;

	WorkersL AllWorkers;// 2направленный список всех записей

	ReportList Report; //Однонаправленный список номеров для вывода
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
		void PushList(Worker* Next);
		int PopListWorker(Worker* Next, int index);
		int DeleteWorker(Worker *ToDelete);
		int DeleteWorker(int index);
		int FindByFields(Worker *Wanted,AnsiString Keys);
		bool EqualTo(Worker* First, Worker* Second, AnsiString Keys);

};
//---------------------------------------------------------------------------
#endif
