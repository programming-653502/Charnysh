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
//	do {

		printf("������� ����� ����� \n");
		long int n = 0;
		//fflush(stdin);
		scanf_s("%d", &n);
		//scanf_s("%d", &n);
		while (n) {
			correct = 1;
			do {
				if ((n % 10) > ((n % 100) / 10))
					po_vozr = 1;
				else if ((n % 10) < ((n % 100) / 10))
					po_ubyv = 1;
				if (po_ubyv == po_vozr) {
					printf("�� �� ����������u�, �� �� ������u�\n");
					break;
				}
				if ((n % 10) == ((n % 100) / 10)) {
					printf("�� �� ����������u�, �� �� ������u�\n");
					break;
				}
					n /= 10;

			} while ((n / 10) != 0);

			if ((po_vozr == 1) && (po_ubyv == 0))
				printf("�� �����������(����� �������)\n");
			if ((po_ubyv == 1) && (po_vozr == 0))
				printf("�� ��������(����� �������)\n");
			n = 0;
			
			
		}
		if (correct == 0)
			printf("�� ��������� ������� ������\n");
		printf(" ����� ������� ��� ������");
		_getch();
		//printf("���������? ������� Y\n\n\n");
		//po_ubyv = 0; po_vozr = 0;
		//correct = 0;
		
	//} while ((_getch() == 'y'));//&& (getchar()) != '\n');

	return 0;

}

