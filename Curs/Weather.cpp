//---------------------------------------------------------------------------

#pragma hdrstop

#include "Weather.h"
Forecast::Forecast(AnsiString FileName)
{
	this->FileName = FileName;
}

int Forecast::GetWeather()
{
	readStr();
}
AnsiString Forecast::ShowIndo()
{
	AnsiString toReturn = "";
	toReturn += "Weather Today: " + IntToStr(Today.tempMax);
	switch(Today.cloudiness)
	{
	case -1: toReturn += ", Fog"; break;
	case 0: toReturn += ", Clear"; break;
	case 3: toReturn += ", GreyNess"; break;
	case 1: toReturn += ", little clouds"; break;
	case 2: toReturn += ", Cloudy"; break;
	}
	switch(Today.precipitation)
	{
	case 1: toReturn += ", precipitations"; break;
	case 0: toReturn += ", no precipitations"; break;
	}
	return toReturn;
}
int Forecast::readStr(long position)
{
		FILE* fp = fopen(FileName.c_str(),"rt");
		if(!fp)
			return -1;

		char Next = '\0';
		AnsiString TagFinder = "";
		int count = 0;
		while(Next != EOF)
		{
			Next = (char)fgetc(fp);
			if(Next != '<' && Next != '\n' && Next != '\t')
				TagFinder += Next;
			if(Next == '>')
			{
				TagFinder = "";
				count = 0;
			}
			count++;

			if(TagFinder == "PHENO")
			{
               while(Next != EOF && Next != '/')
				{
					Next = (char)fgetc(fp);
					TagFinder += Next;
				}
				parseStr(TagFinder, true);
			}
			if(TagFinder == "TEMP")
			{
				while(Next != EOF && Next != '/')
				{
					Next = (char)fgetc(fp);
					TagFinder += Next;
				}
				parseStr(TagFinder, true);
				break;
			}
		}
		fclose(fp);
}
int Forecast::parseStr(AnsiString data, bool today)
{
	try{
	WeatherBox *ptr = NULL;
	if(today)
		ptr = &this->Today;
	else
		ptr = &this->Tommorow;

	int size = data.Length();
	int i = 1;
	switch(data[1])
	{
	case 'T':
	{
		for (; i <= size; i++)
		{
			char temp = data[i];
			if(temp == 34)
				break;
		}
		AnsiString Val = "";
		Val += data[i+1];
		Val += data[i+2];
		ptr->tempMax = StrToInt(Val);
		break;
	}
	case 'P':
	{
		AnsiString Val = "";

		Val += data[23];
		if(Val[1] == '-')
			ptr->cloudiness = -1;
		else
			ptr->cloudiness = StrToInt(Val);
		Val = "";
		Val += data[53];
		ptr->precipitation = StrToInt(Val);
		break;
	}
	}
	}
	catch(ERangeError&)
	{
		ShowMessage("Sorry, broken weather file, reload it");
		return -1;
	}

}
//int Forecast::executeTag(AnsiString data, AnsiString Tag);
//---------------------------------------------------------------------------
#pragma package(smart_init)
