//---------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "About.h"
//--------------------------------------------------------------------- 
#pragma resource "*.dfm"
TAboutBox *AboutBox;
//--------------------------------------------------------------------- 
__fastcall TAboutBox::TAboutBox(TComponent* AOwner)
	: TForm(AOwner)
{
}
//---------------------------------------------------------------------
void __fastcall TAboutBox::TabControl1Change(TObject *Sender)
{
	Memo1->Visible = false;
	Memo2->Visible = false;
	Memo3->Visible = false;
	int Index = TabControl1->TabIndex;
	switch(Index)
	{
		case 0: Memo1->Visible = true; break;
		case 1: Memo2->Visible = true; break;
		case 2: Memo3->Visible = true; break;
	}
}
//---------------------------------------------------------------------------


