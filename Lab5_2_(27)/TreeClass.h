//---------------------------------------------------------------------------

#ifndef TreeClassH
#define TreeClassH
#include <vcl.h>
#include <cstdio>
#include <cstring>




struct Nde
{
	Nde* left, *right, *Stack;
	AnsiString Name;
	int Quantity;
};
class WordCount
{
	Nde* Root;//Root of the tree
	Nde *First, *Head;//Stack to count words first
	void PushTree(Nde* );//Pushes Nodes to Tree
	void PushStack(AnsiString name);//Pushes words to stack
	void FromStackToTree();
	Nde* Symmetrica(Nde* next);   //Does print job
	public:
		WordCount();
		void LoadFrom(AnsiString FileName);
		void PrintResult();
};


//---------------------------------------------------------------------------
#endif
