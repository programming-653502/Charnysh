//---------------------------------------------------------------------------

#pragma hdrstop

#include "WorkerClass.h"


AnsiString EduStr(Education degree)
{
	//Перевод int значения образования в строку
   AnsiString HisEducation =  "Unknown";
   switch(degree)
   {
		case Associate: HisEducation = "Associate"; return HisEducation;
		case Bachelor: HisEducation = "bachelor"; return HisEducation;
		case Master: HisEducation = "Master"; return HisEducation;
		default: return HisEducation;
   }
}
AnsiString AppointmentStr(Appointment Pos)
{
	//Перевод int значения должности в строку
	AnsiString HisPosition = "Unknown";
	switch(Pos)
	{
		case Washer: HisPosition = "Washer"; return HisPosition;
		case JrDev: HisPosition = "JrDev"; return HisPosition;
		case SeniorDev: HisPosition = "Senior Developer"; return HisPosition;
		case ProjectMgr: HisPosition = "Project Manager"; return HisPosition;
		case Director: HisPosition = "Director"; return HisPosition;
		default:return HisPosition;
	}
}
Enterprise::Enterprise(AnsiString FileName)
{
	LoadFromFile(FileName);
	EnterpriseName = FileName;
}
int Enterprise::LoadFromFile(AnsiString FileName)
{
	ListDestructor();
	try{
	TFileStream *file = new TFileStream(FileName,fmOpenRead);

		TrueDate *Today = new TrueDate;
		Today->SetCurrent();
		int RecordsCount = file->Size/sizeof(Worker);
		int i = 0;
		file->Position = soFromBeginning;
		while(i < RecordsCount)
		{
			Worker *NextOne = new Worker;
			file->Read(NextOne, sizeof(Worker));
			//Проверка на день рождения
			if (NextOne->Birthday.month == Today->month && NextOne->Birthday.day == Today->day) {
				AnsiString Msg = "";
				Msg.printf(NextOne->Name); //Change this
				Msg +=  ", the " + AppointmentStr(NextOne->Position)+ " has Birthday today";
				ShowMessage(Msg);
			}
			AllWorkers.pushItem(NextOne);
			i++;
		}
		delete file;
		file = NULL;

	}
	catch(EFOpenError&)
   {
	   ShowMessage("Error. Sorry, couldn't create a file, please check whether you have enouth free space on the disk");
		TFileStream *file = new TFileStream(FileName,fmCreate);
		delete file;
		return -1;
   }
}


int Enterprise::WriteToFile(AnsiString FileName)
{

   try {
   FILE *fp = fopen(FileName.c_str(),"w");
   fclose(fp);
   TFileStream *file = new TFileStream(FileName,fmOpenWrite);

   for (int i = 0; i < AllWorkers.getSize(); i++) {
		Worker Temp;
		if (!AllWorkers.getItem(i,&Temp))
			file->Write(&Temp,sizeof(Worker));
		else
			break;
   }
   delete file;
   file = NULL;
   return 0;
   }
   catch(EFOpenError&)
   {
	   ShowMessage("Error. Sorry, couldn't create a file, please check whether you have enouth free space on the disk");
		TFileStream *file = new TFileStream(FileName,fmCreate);
		delete file;
		return -1;
   }
}

void Enterprise::PrintReport()
{
	//Функции поиска добаляют номера записей в очередь Report, из нее происходит вывод
	for (int i = 0; i < Report.getSize(); i++) {
		Worker *Temp = new Worker;
		if (AllWorkers.getItem(Report.PopItem(),Temp)>=0) {
			AddToGrid(Temp);
		}
	}
	Report.~ReportList();
}


void Enterprise::PushList(Worker* Next)
{
	AllWorkers.pushItem(Next);
}
int Enterprise::PopListWorker(Worker* Next, int index)
{
	 return AllWorkers.getItem(index,Next);
}

bool Enterprise::EqualTo(Worker* First, Worker* Second, AnsiString Keys)
{
	//Сравнение полей у First и Second, указанных в Keys
	int Count = 1;
	int KeysNum = Keys.Length();

	bool Equal = true;

	while (Count<=KeysNum)
	{
		switch (Keys[Count])
		{
		case '#':
		{
			if(First->ID == Second->ID)
			Equal = true;
			else
			{
				return  false;
			}
			break;
		}
		case 'N':
		{
			if(!strcmp(First->Name,Second->Name))
			Equal = true;
			else
			{
				return  false;
			}
			break;
		}
		case 'B':
		{
			if(!First->Birthday.Compare(&First->Birthday,&Second->Birthday,true))
				Equal = true;
			else
			{
				return false;
			}
			break;
		}
		case 'H':
		{
		   if(!First->Hired.Compare(&First->Hired,&Second->Hired,true))
			Equal = true;
			else
			{
				return false;

			}
			break;
		}
		case 'h':
		{
		   if(First->Hired.Compare(&First->Hired,&Second->Hired,true) < 0)
			Equal = true;
			else
			{
				return false;

			}
			break;
		}
		case 'V':
		{
			if(!First->LastVacations.Compare(&First->LastVacations,&Second->LastVacations,true))
				Equal = true;
			else
			{
				return false;
			}
			break;
		}
		case 'v':
		{
			if(First->LastVacations.Compare(&First->LastVacations,&Second->LastVacations) <= 0)
				Equal = true;
			else
			{
				return false;
			}
			break;
		}
		case 'P':
		{
			if(!strcmp(First->PassportNo,Second->PassportNo))
				Equal = true;
			else
			{
				return false;
			}
			break;
		}
		case 'I':
		{
			if(!strcmp(First->InsurancyPolicy,Second->InsurancyPolicy))
				Equal = true;
			else
			{
				return false;
			}
			break;
		}
		case 'S':
		{
			if(!strcmp(First->SocialCrd,Second->SocialCrd))
			Equal = true;
			else
			{
				return false;
			}
			break;
		}
		case 'D':
		{
			if(First->Degree == Second->Degree)
				Equal = true;
			else
			{
				return false;
			}
			break;
		}
		case 'A':
		{
			if(First->Position == Second->Position)
			Equal = true;
			else
			{
				return false;

			}
			break;
		}
		case 'O':
		{
			if(First->OnDuty == Second->OnDuty)
			Equal = true;
			else
			{
				return false;
			}
			break;
		}
		case 'E':
		{
			if(First->Salary == Second->Salary)
			Equal = true;
			else
			{
				return false;

			}
			break;
		}
		}
				Count++;
		}



	return Equal;
}


int Enterprise::FindByFields(Worker *Wanted, AnsiString Keys)
{
	//Поиск по полям объекта Wanted, указанных в Keys
	int Result = -1;
	for(int i = 0; i < AllWorkers.getSize(); i++)
	{
		Worker *Temp = new Worker;
		if (AllWorkers.getItem(i,Temp) < 0)
            return -1;
		if (!EqualTo(Wanted, Temp,Keys))
			continue;
		else {
			Result = i;
			Temp->ID = i;
			Report.PushItem(i); //Добавлени номера найденного в очередь для последующей обработки
		}

	}

	return Result;
}

int Enterprise::DeleteWorker(Worker *ToDelete)
{
	//Удаление по ID объекта
	int index  = 0;
	if ((index = FindByFields(ToDelete,"#")) >= 0) {
		 AllWorkers.deleteItem(index);
		 return 0;
	}
	return -1;

}
int Enterprise::DeleteWorker(int index)
{
	//Удаление по номеру объекта в списке
	return AllWorkers.deleteItem(index);
}
void Enterprise::ListDestructor()
{
	//Очищение 2направленного списка хранения
	AllWorkers.~WorkersL();
}
//---------------------------------------------------------------------------
#pragma package(smart_init)
