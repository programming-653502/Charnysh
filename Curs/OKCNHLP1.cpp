//---------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "OKCNHLP1.h"
//---------------------------------------------------------------------
#pragma resource "*.dfm"
TMainFileDlg1 *MainFileDlg1;


std::vector <AnsiString> Stor;
AnsiString MeinFile = "C:\\Users\\Mikita\\Documents\\Embarcadero\\Studio\\Projects\\Curs\\Win32\\Debug\\namesfile.txt";

AnsiString AnsiFScanfS(FILE* dest,char end = '\n')
{
	if(!dest || feof(dest))
		return NULL;
	char NextCh = '\0';
	AnsiString ST = "";
	NextCh = (char)getc(dest);
	while((NextCh) != end && !feof(dest))
	{

		ST +=NextCh;
		NextCh = (char)getc(dest);
	}
	return ST;
}


void LoadAndPrintF()
{
	Stor.clear();
	FILE* file = fopen(MeinFile.c_str(),"rt");
	if(!file)
	{
		ShowMessage("The file with refferences to all used cals missing! Add them, please!");
		file = fopen(MeinFile.c_str(),"at");
		fclose(file);
		return;
	}

		AnsiString NextName = "";
	char Test;
	int testCount = 0;
	while((Test=getc(file))!=EOF && testCount<3)
	{
		testCount++;
	}
	if(testCount>=2)
	{
		fseek(file,0,0);
		while(!feof(file))
		{
			NextName = AnsiFScanfS(file);
			if(!NextName.IsEmpty())
			{
				Stor.push_back(NextName);
			}
		}
	}
	int i = 0;
	int size = Stor.size();
	MainFileDlg1->StringGrid1->RowCount = 0;
	MainFileDlg1->StringGrid1->Rows[0]->Clear();
	MainFileDlg1->StringGrid1->RowCount = size;
	while(i<size)
	{
		AnsiString FileNm = Stor.at(i);
		if(FileNm.IsEmpty())
		{
			size--;
			Stor.erase(Stor.begin()+i);
			continue;
		}
		MainFileDlg1->StringGrid1->Cells[0][i] = IntToStr(i);
		MainFileDlg1->StringGrid1->Cells[1][i]= FileNm;
		i++;
	}
}
//---------------------------------------------------------------------
__fastcall TMainFileDlg1::TMainFileDlg1(TComponent* AOwner)
	: TOKBottomDlg(AOwner)
{
 //
}
//---------------------------------------------------------------------
void __fastcall TMainFileDlg1::HelpBtnClick(TObject *Sender)
{
	Application->HelpContext(HelpContext);
}
//---------------------------------------------------------------------
void __fastcall TMainFileDlg1::FormCreate(TObject *Sender)
{
	LoadAndPrintF();
}
//---------------------------------------------------------------------------

void __fastcall TMainFileDlg1::Button1Click(TObject *Sender)
{
	if(OpenDialog1->Execute())
	{
		AnsiString FName = OpenDialog1->FileName;
		Stor.push_back(FName);

		FILE* file = fopen(MeinFile.c_str(),"at");

		if(!file)
		{
			ShowMessage("The file with refferences to all used cals missing! Add them, please!");
			return;
		}

		fprintf(file,"\n%s",FName.c_str());
		//fflush(file);
		fclose(file);

	}
	LoadAndPrintF();

}
//---------------------------------------------------------------------------

void __fastcall TMainFileDlg1::Button2Click(TObject *Sender)
{
	int Selected = StringGrid1->Row;
	int size = Stor.size();
	if(Selected >= size)
		return;
	int i = StrToInt(StringGrid1->Cells[0][Selected]);
	Stor.erase(Stor.begin()+i);
	FILE* file = fopen(MeinFile.c_str(),"wt");
	if(!file)
	{
		ShowMessage("The file with refferences to all used cals missing! Add them, please!");
		return;
	}
	i = 0;
	size = Stor.size();
	while(i<size)
	{
		AnsiString FileNm = Stor.at(i);
		if(FileNm.IsEmpty())
		{
            size--;
			Stor.erase(Stor.begin()+i);
			continue;
		}
		fprintf(file,"%s",FileNm.c_str());
		i++;
		if(i<size)
			fprintf(file,"\n");
	}
	fclose(file);
    LoadAndPrintF();
}
//---------------------------------------------------------------------------

void __fastcall TMainFileDlg1::Button3Click(TObject *Sender)
{
    //create new file
	LoadAndPrintF();
}
//---------------------------------------------------------------------------


void __fastcall TMainFileDlg1::StringGrid1Click(TObject *Sender)
{
	int Selection = StringGrid1->Row;
	ShowMessage(StringGrid1->Cells[1][Selection]);
}
//---------------------------------------------------------------------------

void __fastcall TMainFileDlg1::Button4Click(TObject *Sender)
{
	int Selection = StringGrid1->Row;
	CurrentFile = StringGrid1->Cells[1][Selection];
}
//---------------------------------------------------------------------------

void __fastcall TMainFileDlg1::Button5Click(TObject *Sender)
{
    AboutBox->ShowModal();
}
//---------------------------------------------------------------------------

