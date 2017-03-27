// LabProgr3_2_28.cpp : Defines the entry point for the console application.
//
#define _CRT_SECURE_NO_WARNINGS

#include "stdafx.h"

#include <stdio.h>
#include <stdlib.h>

#include <malloc.h>
#include <math.h>
#include <conio.h>


/* run this program using the console pauser or add your own getch, system("pause") or input loop */
int SafeIn(void)
{
	int s = 0;
	while (!scanf("%d", &s))
	{
		rewind(stdin);
		printf("\nSorry, please, type in an integer number only\n");
	}
	return s;
}


float** InPut(int *r)
{
	int R = 0, C = 0;
	int i = 0, j = 0, temp = 0;
	float **Matrix = NULL;

	printf("\nWhat's the number of rows?");
	R = SafeIn();
	*r = R;

	/*printf("\nWhat's the number of rows?");
	C = SafeIn();*/
	//*c = C;
	//Matrix = (float **)malloc(sizeof(float)*R);
	(Matrix = (float **)calloc(R, sizeof(float*)));
	if(Matrix == NULL)
	{
	printf("Cannot find so much free memory for your matrix. Please restart.");
	return NULL;
	}
	for (i = 0; i<R; i++)
	{
		Matrix[i] = (float*)calloc(C, sizeof(float));
		if(Matrix[i] == NULL)
		{
		printf("Cannot find so much free memory for your matrix. Please restart.");
		return NULL;
		}
	}
	for (i = 0; i<R; i++)
	{
		for (j = 0; j<C; j++)
		{
			temp = SafeIn();
			Matrix[i][j] = temp;
		}
	}
	return Matrix;
}
void PrintM(float ** Mtrx, int *r)// , int *c)
{
	int i = 0, j = 0;
	for (; i<(*r); i++)
	{
		for (; j<(*r); j++)
		{
			float temp = Mtrx[i][j];
			printf("%2.f \t",temp);
		}
		j = 0;
		printf("\n");
	}
}
void Diagonale(float** Matrix, int* rows)
{
	int i = 0;
	int j = 0;
	float denom = 1;
	int exchanges = 0;

	for (; i < (*rows)-1; i++)
	{
		int MaxN = i;
		float MaxVal = Matrix[i][i];
		for (j = i+1; j < *rows; j++)
		{
			float Value = fabs(Matrix[i][j]);
			if (Value > MaxVal)
			{
				MaxN = j;
				MaxVal = Value;
			}
			if (MaxN > i)
			{
				float* temp = Matrix[i];
				Matrix[i] = Matrix[MaxN];
				Matrix[MaxN] = temp;
				exchanges++;
			}
			else
			{
				return;
			}
			for (j = i + 1; j < *rows; j++)
			{
				float Value2 = Matrix[j][i];;
				Matrix[j][i] = 0;
				for (int k = i + 1; k < *rows; k++)
				{
					Matrix[j][k] = (Matrix[j][k] * Value - Matrix[j][k] * Value2) / denom;
				}
			}
			denom = Value;
		}
		
	}
	if (exchanges % 2)
		Matrix[*rows - 1][*rows - 1] *= -1;
}
int main(int argc, char *argv[]) {

	float **Matrix;
	int Rows = 0;// Cols = 0;
	int i = 0, j = 0;
	printf("Hello! Matrix rebuilding program. Please, enter the matrix");
	Matrix = InPut(&Rows);// &Cols);
	Diagonale(Matrix, &Rows);
	PrintM(Matrix, &Rows);// &Cols);
	for (i = 0; i<Rows; i++)
	{
		free(Matrix[i]);
	}
	free(Matrix);
	_getch();
	return 0;
}

