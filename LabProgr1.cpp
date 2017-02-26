// LabProgr1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <locale.h>
#include <conio.h>

int main()
{
	setlocale(LC_ALL, "");
	char po_vozr = 0, po_ubyv = 0;
	char correct = 0;


		printf("Ââåäèòå öåëîå ÷èñëî \n");
		long int n = 0;
		
		scanf_s("%d", &n);
		
		while (n) {
			correct = 1;
			do {
				if ((n % 10) > ((n % 100) / 10))
					po_vozr = 1;
				else if ((n % 10) < ((n % 100) / 10))
					po_ubyv = 1;
				if (po_ubyv == po_vozr) {
					printf("Íå ïî âîçäðàñòàíuþ, íå ïî óáûâàíuþ\n");
					break;
				}
				if ((n % 10) == ((n % 100) / 10)) {
					printf("Íå ïî âîçäðàñòàíuþ, íå ïî óáûâàíuþ\n");
					break;
				}
					n /= 10;

			} while ((n / 10) != 0);

			if ((po_vozr == 1) && (po_ubyv == 0))
				printf("Ïî âîçðàñòàíèþ(ñëåâà íàïðàâî)\n");
			if ((po_ubyv == 1) && (po_vozr == 0))
				printf("Ïî óáûâàíèþ(ñëåâà íàïðàâî)\n");
			n = 0;
			
			
			}
		if (correct == 0)
			printf("Íå ïðàâèëüíî ââåäåíû äàííûå\n");
		printf(" Ëþáàÿ êëàâèøà äëÿ âûõîäà");
		_getch();
		
	return 0;

}

