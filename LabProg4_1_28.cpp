// LabProg4_1_28.cpp : Defines the entry point for the console application.
//
#define CST_LEN 100

#include "stdafx.h"
#include <stdio.h>
#include <locale.h>
#include <malloc.h>
#include <conio.h>


void Add(char *buffer)
{
	printf("\nThe program to invert shortest word of each sentence and the longest one\n Type your text here. No more than 100 characters will be processed.\n");
	gets_s(buffer, CST_LEN-1);
	
	/*char ch = 0;
	while ((ch=getchar()))
	{
		
	}*/
}
void Printer(char *buffer)
{
	
	printf("\n%s", buffer);
}


int FindNextDot(int *previousDot, int *nextDot, char* Buffer)
{
	while (*previousDot < CST_LEN - 1)// && Buffer[*previousDot] != '.') Troubles with dot number two.
	{
		*previousDot=*previousDot+1;
		if (Buffer[*previousDot] == '.' || Buffer[*previousDot]=='\0')
			break;
	}
	if (Buffer[*previousDot] == '\0')
		return 0;
	int temp = *previousDot;
	*previousDot = *nextDot;
	*nextDot = temp;
	return *nextDot;
}


int FirstWord(int *start, int* Shortest, int *Longest, int* ShortPos, int*LongPos, char* Buffer)
{
	int BufferPosition = 0;
	while (*start<(CST_LEN - 1) && (Buffer[*start] == ' ' || Buffer[*start] == '.'))
		*start=*start+1;
	BufferPosition = *start;

	while (BufferPosition <(CST_LEN - 1) && Buffer[BufferPosition] != ' ' &&Buffer[BufferPosition] != '\0')
		BufferPosition++;

	*Longest = BufferPosition - *start;
	*Shortest = BufferPosition - *start;
	*LongPos = *ShortPos = *start;
	return BufferPosition;
}


void PutWordsToStr(int PreviousDot, int NextDot, int* Shortest, char*shortWord, int *Longest, char* longWord, int* ShortPos, int*LongPos, char* Buffer)// char* NewBuffer)
{
	int pos = *ShortPos;
	int index = 0;
	while (pos < *Shortest + *ShortPos)
	{
		shortWord[index] = Buffer[pos];
		shortWord[index + 1] = '\0';
		pos++;
		index++;
	}
	index = 0;
	pos = *LongPos;
	while (pos < *LongPos + *Longest)//< only and up
	{
		longWord[index] = Buffer[pos];
		longWord[index + 1] = '\0';
		pos++;
		index++;
	}

}


void SentenceAnaliser(int PreviousDot, int NextDotPos, char*buffer, int* Shortest, int *Longest, int* ShortPos, int*LongPos, char* Buffer)
{
	int i=FirstWord(&PreviousDot, Shortest, Longest, ShortPos, LongPos, buffer);
	int count = 0;
	while (i < NextDotPos)
	{
		while ((i < (CST_LEN - 1)) && Buffer[i] == ' ')
			i++;
		count = 0;
		while (i < (CST_LEN - 1) && Buffer[i] != ' ' && Buffer[i] != '\0')
		{

			if (buffer[i] == '.')
			{
				break;
			}
			count++;
			i++;

		}
		if (count > *Longest)
		{
			*LongPos = i - count;
			*Longest = count;
			count = 0;
		}
		if ((count < *Shortest) && (count != 0))
		{
			*ShortPos = i - count;
			*Shortest = count;
			count = 0;
		}
	}
}
void NewLineWrite(int nextDot, int previousDot, char* longWord, int LongPos, int Longest, char* ShortWord, int ShortPos, int Shortest, char* Buffer, char* NewBuffer)
{
	int BufferPosition = previousDot;
	int NewBufferPosiotion = previousDot;
	while (BufferPosition<(CST_LEN-1)&&(Buffer[BufferPosition] == '.' || Buffer[BufferPosition] == ' '))
	{
		NewBuffer[NewBufferPosiotion] = Buffer[BufferPosition];
		NewBufferPosiotion++;
		BufferPosition++;
	}
	int StopPosition = BufferPosition;
	while (BufferPosition < nextDot)
	{

		while (BufferPosition < nextDot && BufferPosition != LongPos && BufferPosition != ShortPos)
		{
			NewBuffer[NewBufferPosiotion] = Buffer[BufferPosition];
			BufferPosition++;
			NewBufferPosiotion++;
			StopPosition++;

		}
		if (BufferPosition < nextDot && BufferPosition == LongPos)
		{
			int WordPosition = 0;
			while (WordPosition < Shortest)
			{
				NewBuffer[NewBufferPosiotion] = ShortWord[WordPosition];
				WordPosition++;
				NewBufferPosiotion++;
				BufferPosition++;
			}
			BufferPosition = StopPosition + Longest;
			StopPosition = BufferPosition;
		}
		if (BufferPosition < nextDot && BufferPosition == ShortPos)
		{
			int WordPosition = 0;
			while (WordPosition < Longest)
			{
				NewBuffer[NewBufferPosiotion] = longWord[WordPosition];
				WordPosition++;
				NewBufferPosiotion++;
				BufferPosition++;
			}
			BufferPosition = StopPosition + Shortest;
			StopPosition = BufferPosition;
		}
	}
	NewBuffer[nextDot] = '.';
	NewBuffer[nextDot + 1] = '\0';


}

void Function(char *Buffer, char *NewBuffer)
{
	int Shortest = 0, Longest = 0, LongPos = 0, ShortPos = 0, PreviousDot = 0, NextDot = 0;
	char ShortWord[CST_LEN];
	char LongWord[CST_LEN];
	while (FindNextDot(&PreviousDot, &NextDot, Buffer))
	{
		SentenceAnaliser(PreviousDot, NextDot, Buffer, &Shortest, &Longest, &ShortPos, &LongPos, Buffer);
		PutWordsToStr(PreviousDot, NextDot, &Shortest, ShortWord, &Longest, LongWord, &ShortPos, &LongPos, Buffer);
		NewLineWrite(NextDot, PreviousDot, LongWord, LongPos, Longest, ShortWord, ShortPos, Shortest, Buffer, NewBuffer);
		PreviousDot = NextDot;
		Longest = 0;
		Shortest = 0;
		ShortWord[0] = '\0';
		LongWord[0] = '\0';
	}
}

int main()
{
	int size = 100;
	char *buffer = (char*)malloc(CST_LEN * sizeof(char));
	char NewLine[CST_LEN];
	setlocale(LC_ALL, "");
	Add(buffer);
	//Printer(buffer);
	Function(buffer, NewLine);
	Printer(NewLine);

	_getch();
    return 0;
}

