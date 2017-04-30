//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
//---------------------------------------------------------------------------
#include <Vcl.Styles.hpp>
#include <Vcl.Themes.hpp>
USEFORM("OKCNHLP1.cpp", MainFileDlg1);
USEFORM("Unit6.cpp", Form6);
USEFORM("OKCNHLP.cpp", CreateEventDlg1);
USEFORM("c:\program files (x86)\embarcadero\studio\18.0\ObjRepos\EN\Cpp\okcancl1.CPP", OKBottomDlg);
USEFORM("ABOUT.cpp", AboutBox);
//---------------------------------------------------------------------------
int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	try
	{
		Application->Initialize();
		Application->MainFormOnTaskBar = true;
		TStyleManager::TrySetStyle("Amakrits");
		Application->CreateForm(__classid(TForm6), &Form6);
		Application->CreateForm(__classid(TMainFileDlg1), &MainFileDlg1);
		Application->CreateForm(__classid(TCreateEventDlg1), &CreateEventDlg1);
		Application->CreateForm(__classid(TAboutBox), &AboutBox);
		Application->Run();
	}
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
	}
	catch (...)
	{
		try
		{
			throw Exception("");
		}
		catch (Exception &exception)
		{
			Application->ShowException(&exception);
		}
	}
	return 0;
}
//---------------------------------------------------------------------------
