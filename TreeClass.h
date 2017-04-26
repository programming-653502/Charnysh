//---------------------------------------------------------------------------

#ifndef TreeClassH
#define TreeClassH
#include <vcl.h>
#include <cstdio>
#include <cstring>

#include "Unit6.h"

struct Nde
{
	Nde* left, *right, *Stack;
	AnsiString Name;
	int Num;
	int Quantity;
};
class WordCount
{
	Nde* Root;
	void Push(AnsiString name);
	void PushStack(AnsiString name, Nde* stack);
	AnsiString PopStack(Nde* stack);

	Nde* Symmetric(Nde* next);
	public:
		void LoadFrom(AnsiString FileName);
		void PrintResult();
};
//---------------------------------------------------------------------------
#endif
