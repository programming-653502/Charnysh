//---------------------------------------------------------------------------

#pragma hdrstop
//#pragma once
#define BUF_LEN 50
#include "TEVENT.h"





EVENT::EVENT(AnsiString FileName)
{
	DTSTART.SetCurrent();
	SUMMARY = "";
	CATEGORY = "Holidays";
	FILENAME = FileName; //Can bee empty
	ID ="1111";
}
bool EVENT::IfToday()
{
	TrueDate Today;
	Today.SetCurrent();
	if(Today.year == DTSTART.year && Today.month == DTSTART.month && Today.day == DTSTART.day)
		return true;
	else
		return false;
}
bool EVENT::IsNext(bool Soon)
{
	if(this->IfToday())
	{
		TrueDate Now;
		Now.SetCurrent();

		if((Soon == false) && (Now.hour <= DTSTART.hour) && (Now.min <= DTSTART.min)) //Логичнее в Тру ДАта
			return true;
		if(Soon == true && Now.hour == DTSTART.hour && Now.min >= DTSTART.min-1 && Now.min <= DTSTART.min+1)
			return true;
        return false;
	}
	else
		return false;
}


int EVENT::EventSetDlg(AnsiString FileName)
{
	CreateEventDlg1->Edit1->Text = SUMMARY;
	if(CATEGORY == "Holidays")
	{
	   CreateEventDlg1->RadioGroup1->ItemIndex = 0;
	}
	if(DTSTART.day)
	{
		CreateEventDlg1->ComboBox1->ItemIndex = DTSTART.month-1;
		CreateEventDlg1->Calendar1->Day = DTSTART.day;
		CreateEventDlg1->Calendar1->Month = DTSTART.month;
		CreateEventDlg1->Calendar1->Year = DTSTART.year;
		CreateEventDlg1->SpinEdit1->Value = DTSTART.year;
	}
	CreateEventDlg1->Label3->Caption = FileName;
	CreateEventDlg1->Label3->Hint = "Calendar File to add event in: "+FileName;
	switch(CreateEventDlg1->ShowModal())
	{
		case mrOk:
		{

			AnsiString Summ = CreateEventDlg1->Edit1->Text;
			TDateTime NewEventDate = CreateEventDlg1->Calendar1->CalendarDate;
			AnsiString TimeString = CreateEventDlg1->MaskEdit1->Text;


			if(TimeString[1] != ' ' && TimeString[2] != ' ' && TimeString[3] != ' ' && TimeString[4] != ' ')
			{
				NewEventDate += StrToTime(TimeString);
			}
			extern AnsiString Category;
			this->EVENTSet(Summ.c_str(),Category,NewEventDate,FileName);
			//NextEvent->AddToFile(Name);
			//CCalendar1->CalendarDate = OKHelpBottomDlg->Calendar1->CalendarDate;
			return 0;
		}
	}
	return -1;
}
void EVENT::EVENTSet(AnsiString Summary, AnsiString Category, TDateTime Start,AnsiString FileName)
{
	SUMMARY = Summary;
	CATEGORY = Category;
   //	ShowMessage(Start.DateTimeString());
	DTSTART.TDateTimeToTrueDate(&Start);
   //	ShowMessage(DTSTART.DateTimeString());
   FILENAME = FileName;
	AnsiString MyID = FileName;
	MyID += (DTSTART.YYYYMMDD()+DTSTART.HHMM());
	ID = MyID;
}





void EVENT::DateArray(int* Array, AnsiString DateStr)
{
	int Len = DateStr.Length();
	int i = 1;
	while(i < Len)
	{
		if(DateStr[i]<='9' && DateStr[i]>='0')
			break;
		i++;
	}
	if(i == Len)
	{
		ShowMessage("Error in reading date value!");
		return;
	}
	AnsiString PieseOfDate = "";
	int PosCount = 0;//To track position
	while(i <= Len)
	{
		if(DateStr[i] == 'T' || DateStr[i] == 'Z')
		{
			i++;
            PosCount++;
			continue;
		}
		PieseOfDate += DateStr[i];
		PosCount++;
		i++;
		if(PosCount == 4)
		{
			Array[0] = StrToInt(PieseOfDate);
			PieseOfDate = "";
		}
		else if(PosCount == 6)
		{
			Array[1] = StrToInt(PieseOfDate);
			PieseOfDate = "";
		}
		else if(PosCount == 8)
		{
			Array[2] = StrToInt(PieseOfDate);
			PieseOfDate = "";
		}
		else if(PosCount == 11)
		{
			Array[3] = StrToInt(PieseOfDate);
			PieseOfDate = "";
		}
		else if(PosCount == 13)
		{
			Array[4] = StrToInt(PieseOfDate);
			PieseOfDate = "";
			break;
		}
	}
	return;
}





int EVENT::GetEvent(FILE* file, long beginningPos, long endingPos, AnsiString* STR)
{
	fseek(file,beginningPos,0);
	AnsiString ST="";
	long CurrentPos=beginningPos;
	while(CurrentPos<endingPos)
	{
		ST += (char)getc(file);
		CurrentPos = ftell(file);
	}
	*STR = ST;
	return 0;
}






void EVENT::ReadStr(AnsiString tagStr, AnsiString ValueStr)

{
	enum Tags{CREATED,UID,SUMMARY,CATEGORIES, DTSTART,END};
	Tags Tag; //Начинается ли с нуля
	AnsiString TagWords[] = {"CREATED","UID","SUMMARY","CATEGORIES","DTSTART","END"};
	TrueDate DateOfEvent;
	AnsiString StrofEvent;

	char MultyPurposeCh ='\0';
	int i = 0;
	while(i<6)
	{
		if(!strcmp(TagWords[i].c_str(),tagStr.c_str()))
		{
			Tag = i;
            break;
		}
		i++;
	}
	switch(Tag)
	{
		case DTSTART:
		{
			int DateVals[]={0,0,0,0,0};
			DateArray(DateVals,ValueStr);
			TrueDate MyDate; // = new TrueDate();
			MyDate.SetByArray(DateVals,5);
			this->DTSTART = MyDate;

			break;
		}
		case UID:
		{
			int index = 0;
			 while(index < ValueStr.Length() && (MultyPurposeCh = ValueStr.c_str()[index]) != '\n')
			 {
				StrofEvent+= MultyPurposeCh;
				 index++;
			 }
			 this->ID = StrofEvent;
			 break;
		}
		case SUMMARY:
		{
			int index = 0;
			 while(index < ValueStr.Length() && (MultyPurposeCh = ValueStr.c_str()[index]) != '\n')
			 {
				StrofEvent+= MultyPurposeCh;
				 index++;
			 }
			 this->SUMMARY = StrofEvent;
			 break;
		}
		case CATEGORIES:
		{
			 int index = 0;
			 while(index < ValueStr.Length() && (MultyPurposeCh = ValueStr.c_str()[index]) != '\n')
			 {
				StrofEvent+= MultyPurposeCh;
				 index++;
			 }
			 this->CATEGORY = StrofEvent;
			 break;
		}

		case END:
		{
			//ShowMessage("End reached!)");
			return;
		}
		default:
		{
			//ShowMessage("Something different, no problem;)");
			return;
		}
	}


}




void EVENT::ParseEventStr(AnsiString Str)
{
	int StrLength = Str.Length();
	int i = 0;
    AnsiString TagStr = "";
	AnsiString DataStr = "";
	while(i<StrLength)
	{

		char NextCh = Str.c_str()[i];

		if(NextCh != ';' && NextCh != ':')
		{
			if(NextCh == '\n')
			{
				i++;
				continue;
			}
			TagStr += NextCh;
            i++;
		}
		else
		{

			i++;
			NextCh = Str.c_str()[i];
		   while(i<StrLength && NextCh != '\n')
		   {
				DataStr += NextCh;
				i++;
				NextCh = Str.c_str()[i];
		   }
		   ReadStr(TagStr,DataStr);
		   TagStr = "";
           DataStr = "";
		}
	}
}





void EVENT::AddToFile(AnsiString FileName)
{
	char TheEndOfFile[] = "END:VCALENDAR";
	FILE* Destination = fopen(FileName.c_str(),"r+");
	bool WasJustCreated = false;
	if(!Destination)
	{
	//If the file does not exist, it'll be created
		AnsiString info = "Sorry,"+FileName+" file doesn't exist. Create it?";

		if(MessageDlg(info,mtInformation, TMsgDlgButtons() << mbYes << mbNo,0) == idYes)
		{
		   delete Destination;
		   Destination = fopen(FileName.c_str(),"w+");
		   WasJustCreated = true;
		}
		else
		 return;
	}

	char Test;
	int testCount = 0;
	while((Test=getc(Destination))!=EOF && testCount<3)
	{
		testCount++;
	}
	if(testCount<=2)
	{
		WasJustCreated = true;
	}

	long int Position = 0;
	while(!feof(Destination)) //Looking for the last record in file, to rewrite it
	{
		AnsiString NextLine="";
		Position = ftell(Destination);
		fscanf(Destination,"\n%s",NextLine.c_str());//Ona ne poluchaet nichegp
		if(!strcmp(NextLine.c_str(),TheEndOfFile))
		{
			break;
		}

	}
	fseek(Destination, Position, 0);
//
	AnsiString DateString = DTSTART.YYYYMMDD() +"T"+DTSTART.HHMM()+"Z";
//
	if(WasJustCreated)
	{
		fprintf(Destination,"BEGIN:VCALENDAR\nPRODID:-//CursLabCalendar V1.0//EN\nVERSION:1.0");
	}

	//Printing EVENT to a file
	fprintf(Destination,"\nBEGIN:VEVENT\nCREATED:%s\nUID:%s\nSUMMARY:%s\nCATEGORIES:%s\nDTSTART;VALUE=DATE:%s\nDTEND;VALUE=DATE:%s\nTRANSP:TRANSPARENT\nEND:VEVENT\n",DateString.c_str(),ID.c_str(),SUMMARY.c_str(),CATEGORY.c_str(),DateString.c_str(),DateString.c_str());
	fprintf(Destination,"END:VCALENDAR");
	fclose(Destination);
}
void EVENT::AddToFile()
{
	AddToFile(FILENAME);
}



void EVENT::LoadFromFile(FILE* thefile, long int StartPos,long int EndPos, AnsiString FileName)
{

	//char TagWords[][10] = {"DTSTART","UID","SUMMARY","CATEGORY"};
		FILENAME = FileName;
		AnsiString NextString="";
		GetEvent(thefile,StartPos,EndPos,&NextString);
		ParseEventStr(NextString);

}


int EVENT::Compare(EVENT* ToCmp)
{
	int Answer = 0;
	if(this->DTSTART.Compare(&this->DTSTART,&ToCmp->DTSTART,false) == 0)
		Answer += 1;
	if(this->SUMMARY == ToCmp->SUMMARY)
		Answer += 2;
	if(this->CATEGORY == ToCmp->CATEGORY)
		Answer += 3;
	return Answer;
}


//---------------------------------------------------------------------------
#pragma package(smart_init)
