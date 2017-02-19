// LabProgr1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <locale.h>
#include <conio.h>

int main()
{
	setlocale(LC_ALL, "");
	long unsigned int n=0;
	char po_vozr=0, po_ubyv=0;
	do {
		printf_s("Введите целое число \n");
		
		scanf_s("%d", &n);
		n = n;
		do {
			if ((n % 10) >= ((n % 100) / 10))
				po_vozr = 1;
			if ((n % 10) <= ((n % 100) / 10))
				po_ubyv = 1;
			if (po_ubyv == po_vozr) {
				printf("Не по воздрастанuю, не по убыванuю\n");
				break;
			}
			else
				n /= 10;
		} while (((n / 100)!=0)&&(n%10<10));
		if ((po_vozr == 1) && (po_ubyv == 0))
			printf("По возрастанию(слева направо)\n");
		if ((po_ubyv == 1) && (po_vozr == 0))
			printf("По убыванию(слева направо)\n");
		printf("Повторить? нажмите Y\n\n\n");
		n = 0;
		
	} while (_getch() == 'y');
	
	return 0;
	
}

