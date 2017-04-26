//---------------------------------------------------------------------------

#pragma hdrstop

#include "TreeClass.h"

void WordCount::Push(AnsiString name)
{
	int num = name.Length();
    if(!Root)
	{
		Root = new Nde;
		Root->left = NULL;
		Root->right = NULL;
		Root->Name = name;
		Root->Num = num;
		Root->Quantity=1;

		return;
	}
	Nde *temp = Root;

	while(true)
	{
		if(temp->Num > num )// && strcmp(temp->Name.c_str(), name.c_str()))
		{
			if(temp->left)
				temp =(temp->left);
			else
			{
				temp->left = new Nde;
				temp->left->left = temp->left->right = NULL;
				temp->left->Num = num;
				temp->left->Name = name;
				temp->left->Quantity=1;
				return;
			}

		}
		else if(temp->Num < num)
		{
			if(temp->right)
				temp = temp->right;
			else
			{
				temp->right = new Nde;
				temp->right->left = temp->right->right = NULL;
				temp->right->Num = num;
				temp->right->Name = name;
				temp->right->Quantity=1;
				return;
			}
		}

		else if(temp->Num == num)
		{
			if(!strcmp(temp->Name.c_str(), name.c_str()))
			{
				temp->Quantity++;
				return;
			}
			else
			{
				if(!temp->Stack)
				{
					temp->Stack = new Nde;
					temp->Stack->left = temp->right =NULL;
					temp->Stack->Name = name;
					temp->Stack->Num = num;
					temp->Stack->Quantity = 1;
				}
				else
				{
					Nde* StackHead =  temp->Stack;



					while(StackHead->right)
					{
						if(!strcmp(StackHead->Name.c_str(), name.c_str()))
						{
							StackHead->Quantity++;
							return;
						}
						else
						{
							StackHead = StackHead->right;
						}
					}
					if(!StackHead->right)
					{
						StackHead->right = new Nde;
						StackHead->right->left = temp->right =NULL;
						StackHead->right->Name = name;
						StackHead->right->Num = num;
						StackHead->right->Quantity = 1;
						StackHead->right->left = StackHead;
						return;
					}
				}
			}
		}
	}

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
		if(NextCh = EOF)
		{
			break;
		}
		if((NextCh >= 'A' && NextCh <= 'Z') || (NextCh >= 'a' && NextCh <= 'z'))
		{
			Word+=NextCh;
		}
		else
		{
			Push(Word);
			Word = "";
		}
	}

	fclose(fp);
}
Nde* Symmetric(Nde* next)
{
	if(!next)
		return NULL;

	Nde* temp  = Symmetric(next->right);
	if(!temp)
	{
		AnsiString ToPrint = next->Name +" "+ IntToStr(next->Num);
		Form6->Memo1->Lines->Add(ToPrint);

		temp = Symmetric(next->left);
		if(!temp)
		{
//			AnsiString ToPrint = next->Name +" "+ IntToStr(next->Num);
//			Form6->Memo1->Lines->Add(ToPrint);
			return NULL;
		}

	}
}
void WordCount::PrintResult()
{
	if(Root)
	{
		Symmetric(Root);

	}
}
//---------------------------------------------------------------------------
#pragma package(smart_init)
