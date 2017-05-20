//---------------------------------------------------------------------------

#ifndef WeatherH
#define WeatherH
#include <vcl.h>
#include <msxmldom.hpp>
#include <XMLDoc.hpp>
#include <xmldom.hpp>
#include <XMLIntf.hpp>
#include <ComCtrls.hpp>
#include <Dialogs.hpp>

struct WeatherBox
{
	int cloudiness;
	int precipitation;
	int tempMax;
	int tempMin;
};
class Forecast
{
	 WeatherBox Today, Tommorow;
	 AnsiString FileName;
	 int readStr(long position = 0);
	 int parseStr(AnsiString data, bool today);
	 int executeTag(AnsiString data, AnsiString Tag);
	 public:
		 Forecast(AnsiString FileName);

		 int GetWeather();
		 AnsiString ShowIndo();
} ;
//---------------------------------------------------------------------------
#endif
