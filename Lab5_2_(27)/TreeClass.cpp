//---------------------------------------------------------------------------

#pragma hdrstop

#include "TreeClass.h"


WordCount::WordCount()
{
    Root = First = Head = NULL;
}
void WordCount::PushTree(Nde* Next)
{

	if(!Root)
	{
		Root = new Nde;
		Root->left = NULL;
		Root->right = NULL;
		Root->Stack = NULL;
		Root->Name = Next->Name;
		Root->Quantity=Next->Quantity;
		return;
	}
	int QuantNext = Next->Quantity;
	Nde *temp = Root;

	while(true)
	{
		if(temp->Quantity > QuantNext )// && strcmp(temp->Name.c_str(), name.c_str()))
		{
			if(temp->left)
				temp =(temp->left);
			else
			{
				temp->left = new Nde;
				temp->left->left = temp->left->right = temp->left->Stack = NULL;

				temp->left->Name = Next->Name;
				temp->left->Quantity=QuantNext;
				return;
			}

		}
		else if(temp->Quantity < QuantNext)
		{
			if(temp->right)
				temp = temp->right;
			else
			{
				temp->right = new Nde;
				temp->right->left = temp->right->right = temp->right->Stack = NULL;

				temp->right->Name = Next->Name;
				temp->right->Quantity=QuantNext;
				return;
			}
		}

		else if(temp->Quantity == QuantNext)
		{


				if(!temp->Stack)
				{
					temp->Stack = new Nde;
					temp->Stack->left = temp->Stack->right =NULL;
					temp->Stack->Name = Next->Name;

					temp->Stack->Quantity = QuantNext;
					return;
				}
				else
				{
					Nde* StackHead =  temp->Stack;
					while(StackHead->right)
					{
						StackHead = StackHead->right;
					}
					StackHead->right = new Nde;
					StackHead->right->left = StackHead->right->right =NULL;
					StackHead->right->Name = Next->Name;
					StackHead->right->Quantity = QuantNext;
					StackHead->right->left = StackHead;
					return;
			}
		}
	}

}

void WordCount::PushStack(AnsiString Word)
{
	if(!First)
	{
		First = new Nde;
		First->right = First->left = NULL;
		First->Name = Word;
		First->Quantity = 1;
		Head = First;
		return;
	}
	Nde *Temp = First;

	if(Temp->Name == Word)
	{
		Temp->Quantity++;
		return;
	}
	while(Temp->right)
	{
		if(Temp->right->Name == Word)
		{
			Temp->right->Quantity++;
			return;
		}
		else
		Temp = Temp->right;
	}
	Temp->right = new Nde;
	Temp->right->right = NULL;
	Temp->right->left = Temp;
	Temp->right->Name = Word;
	Temp->right->Quantity = 1;
	return;
}


void WordCount::LoadFrom(AnsiString FileName)
{
	FILE* fp  = fopen(FileName.c_str(),"rt");
	if(!fp)
	{
		return;
	}
	AnsiString Word = "";
	char NextCh = '\0';
	while(!feof(fp))
	{
		NextCh = getc(fp);
		if(NextCh == EOF)
		{
			if(!Word.IsEmpty())
			   PushStack(Word);

			break;
		}
		if((NextCh >= 'A' && NextCh <= 'Z') || (NextCh >= 'a' && NextCh <= 'z') || NextCh == '\'')
		{
			Word+=NextCh;
		}
		else if(Word.IsEmpty())
		{
			continue;
		}
		else
		{
			PushStack(Word);
			Word = "";
		}
	}

	fclose(fp);
}
void WordCount::FromStackToTree()
{
	while(First)
	{
		PushTree(First);
		delete First;
		First = First->right;
	}
}
void WordCount::PrintResult()
{

	FromStackToTree();
	if(Root)
	{
		Symmetrica(Root);

	}
}
//---------------------------------------------------------------------------
#pragma package(smart_init)
