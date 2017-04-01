// ConsoleApplication11.cpp : Defines the entry point for the console application.
//
#define _CRT_SECURE_NO_WARNINGS

#define CST_WORD_LEN 128



#include "stdafx.h"
#include <stdio.h>
#include <conio.h>

char* FOldFile = "first.txt";
char* FVocabulary = "vocabulary.txt";
char* FNewFile = "result.txt";
/* Нужны два файла: first.txt (английские слова, произвольный порядок, разделены пробелами, знаки препинания отделены пробелами так же)*/
/*                  vocabulary.txt(слово исходное и слово-заменитель, каждая пара с новой строки, между словами в парах пробелы) */
/* result.txt создается при отсутствии*/


bool CompareAndChange(char* WordToCompare, char* Dfd, char* Dfn)
{
	int Index = 0;
	bool Similar = false;
	do {
		if (WordToCompare[Index] == '\0' && Dfd[Index] != '\0')
		{
			Similar = false;
			break;
		}
		if(WordToCompare[Index] != '\0' && Dfd[Index] == '\0')
		{
			Similar = false;
			break;
		}
		if (WordToCompare[Index] == Dfd[Index])
		{
			if (WordToCompare[Index] == '\0')
				break;
			Similar = true;
			Index++;
		}
		else
		{
			Similar = false;
			break;
		}
		
	} while (Index < (CST_WORD_LEN - 1));
	Index = 0;
	if (Similar == true)
	{
		while (Index<(CST_WORD_LEN-1) && Dfn[Index]!='\0')
		{
			WordToCompare[Index] = Dfn[Index];
			WordToCompare[Index + 1] = '\0'; 
			Index++;
		}
	}
	return Similar;
}

void CheckList(char* word)
{
	char DFD[CST_WORD_LEN];
	char DFN[CST_WORD_LEN];
	bool found = false;

	FILE* SynonymsList = fopen(FVocabulary, "rt");
	if (!SynonymsList)
	{
		printf("\nError,couldn't open %s", FVocabulary);
		_getch();
		return;
	}
	while (!feof(SynonymsList) && found == false)
	{
		fscanf(SynonymsList, "%s %s\n",DFD, DFN);
		found = CompareAndChange(word, DFD, DFN);
	}
	fclose(SynonymsList);
	
}
void AddToFile(char* word)//, long int Position)
{
	FILE* DestinationFile = fopen(FNewFile, "at");
	if (!DestinationFile)
	{
		printf("\n Error Couldn't open %s", FNewFile);
		_getch();
		return;
	}
	fprintf(DestinationFile, " %s ", word);
	fclose(DestinationFile);

}
void ReadAWord(char* word)
{
		char NextChar = '\0';
		int WordIndex = 0;
		FILE* OriginFile = fopen("first.txt", "rt");
		if (!OriginFile)
		{
			printf("\n Error Couldn't open %s", FOldFile);
			_getch();
			return;
		}
		
		
		while (!feof(OriginFile))
		{
			fscanf(OriginFile, "%s", word);
			CheckList(word);
			AddToFile(word);
		}
		
		fclose(OriginFile);
		return;
	
	
}

int main()
{
	
	char Word[CST_WORD_LEN];
		
	fclose(fopen("result.txt", "wt"));
	ReadAWord(Word);
	
    return 0;
}

