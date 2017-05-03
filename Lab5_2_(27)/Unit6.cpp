//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit6.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm6 *Form6;


WordCount MyTree;

Nde* WordCount::Symmetrica(Nde* next)
{
	if(!next)
		return NULL;

	Nde* temp  = Symmetrica(next->right);
	if(!temp)
	{

		Nde* NextInStack = next->Stack;
		while(NextInStack)
		{
			AnsiString StackWordInfo = NextInStack->Name+" "+IntToStr(NextInStack->Quantity);
			NextInStack = NextInStack->right;
			Form6->Memo1->Lines->Add(StackWordInfo);
		}

		AnsiString ToPrint = next->Name +" "+ IntToStr(next->Quantity);
		Form6->Memo1->Lines->Add(ToPrint);

		temp = Symmetrica(next->left);
		if(!temp)
		{
			return NULL;
		}

	}
}
//---------------------------------------------------------------------------
__fastcall TForm6::TForm6(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm6::LoadAndCountClick(TObject *Sender)
{
    Memo1->Clear();
	AnsiString FILEN = "mytext.txt";
	if(OpenDialog1->Execute())
	{
	   FILEN = OpenDialog1->FileName;
	   Label1->Caption = FILEN;
	   MyTree.LoadFrom(FILEN);
	   MyTree.PrintResult();
	}


}
//---------------------------------------------------------------------------
