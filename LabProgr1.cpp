// LabProgr1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <locale.h>
#include <conio.h>

int main()
{
	setlocale(LC_ALL, "");
	long int n=0;
	char po_vozr=0, po_ubyv=0;
	do {
		printf_s("Ââåäèòå öåëîå ÷èñëî \n");
		
		scanf_s("%d", &n);
		
		do {
			if ((n % 10) >= ((n % 100) / 10))
				po_vozr = 1;
			if ((n % 10) <= ((n % 100) / 10))
				po_ubyv = 1;
			if (po_ubyv == po_vozr) {
				printf("Íå ïî âîçäðàñòàíuþ, íå ïî óáûâàíuþ\n");
				break;
			}
			else
				n /= 10;
		} while (((n / 100)!=0)&&(n%10<10));
		if ((po_vozr == 1) && (po_ubyv == 0))
			printf("Ïî âîçðàñòàíèþ(ñëåâà íàïðàâî)\n");
		if ((po_ubyv == 1) && (po_vozr == 0))
			printf("Ïî óáûâàíèþ(ñëåâà íàïðàâî)\n");
		printf("Ïîâòîðèòü? íàæìèòå Y\n\n\n");
		n = 0;
		
	} while (_getch() == 'y');
	
	return 0;
	
}

