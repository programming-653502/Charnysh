// ConsoleApplication8.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <conio.h>
#include <locale.h>

const float WindowH = 2.15, WindowW = 1.5, DoorH = 2.05, DoorW = 0.9;
const float TubeLength = 10, Height = 2.6, TubeWidth = 0.5, CostGlue = 2.5, GlueEnoughFor = 5;
struct Room
{
	float Length=0;
	float Width=0;
	int Doors=0;
	int Windows = 0;
	float Cost=0;
	float S = 0;
	int TubesNumb = 0;
	float ForAll = 0;
} a;

void check(Room *r1)
{
	if (!r1->Length)
	{
		printf("\n���i �����, �����i�� ������: "); 
		scanf_s("%f", &r1->Length);
	}
	if (!r1->Width)
	{
		printf("\n���i �����, �����i�� ������: ");
		scanf_s("%f", &r1->Width);
	}
	
}
char Menu(Room r1)
{
	char ch = 0;
	setlocale(LC_ALL, "");
	printf("\n1. ���� �����i (����� %.2f) i �����i(����� %.2f) �����\n 2. ���� ��������i �����( %.2d )\n 3. ���� ��������i �������( %d )\n 4. ���� ����� ����� �����i ������� (����� %.2f $)\n 5. ����i� ������ �������i - (%.2f)\n 6. ����i� ���������� ��������i ������ �������   - (%d)\n 7. ����i� ����� ������� (%.2f)\n 8. �����", r1.Length, r1.Width,r1.Windows, r1.Doors,r1.Cost,r1.S,r1.TubesNumb,r1.ForAll );
	 (ch)=_getch();
	 return ch;
}

void Area(Room *r1)
{
	check(r1);
	float MinusWindows = r1->Windows*WindowH*WindowW;
	float MinusDoors = r1->Doors*DoorH*DoorW;
	r1->S= (r1->Length*Height * 2 + r1->Width*Height * 2 - MinusWindows - MinusDoors);
}

void WalpapersNumber(Room *r1)
{
	check(r1);
	float real = r1->S / (TubeLength*TubeWidth);
	if (((int)(real * 10)) % 10)
		real += 1;
	r1->TubesNumb = (int)real;
}

void Glue(Room *r1)
{
	check(r1);
	if (!r1->Cost)
	{
		printf("\n���i �����, �����i�� ���� �� ���� ������: ");
		scanf_s("%f", &a.Cost);
	}
	if (!r1->S)
	{
		Area(r1);
	}
	if (!r1->TubesNumb)
	{
		WalpapersNumber(r1);
	}
	
	float GlueAmount = r1->TubesNumb / 5;
	if (GlueAmount - ((int)(GlueAmount)))
	{
		GlueAmount++;
	}
	r1->ForAll=r1->Cost*r1->TubesNumb + CostGlue*((int)GlueAmount);
}

int main()
{
	setlocale(LC_ALL, "");
	char choise = 0;
	while (choise != '8')
	{
		choise = Menu(a);
		switch (choise)
		{
			case '1': a.Length = 0; a.Width = 0; check(&a); break;
			case '2': printf("\n ���i �����, �����i�� ��������� ����� "); scanf_s("%d", & a.Windows); break;
			case '3': printf("\n ���i �����, �����i�� ��������� �������  ");  scanf_s("%d", &a.Doors); break;
			case '4': printf("\n���i �����, �����i�� ���� �� ���� ������: "); scanf_s("%f", &a.Cost); break;
			case '5':  Area(&a); printf("\n������ ��� ��������i  = %.2f", a.S); break;
			case '6': WalpapersNumber(&a); printf("��������� ������ ������� = %d", a.TubesNumb); break;
			case '7': Glue(&a); printf("\n���� �������(��i������� ���� ����) = %.2f", a.ForAll); break;
			default:
				choise = '8';break;
		}
		if (choise != '8')
		{
			printf("\n��� ����������, ���ic�i��, ���i �����, ����-������� ������\n");
			_getch();
		}

		 printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
		fflush(stdin);
	}
	//_getch();
    return 0;
}

