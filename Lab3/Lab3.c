#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

float **MatrixCreate(int* size)
{
	int  i, j;
	float **matrix = (float**)malloc(*size * sizeof(float*));
	if (!matrix)
	{
		printf("Error");
		exit(1);
	}
	for (i = 0; i < *size; i++)
	{
		matrix[i] = (float*)malloc(*size * sizeof(long));
		if (!matrix[i])
		{
			printf("Error");
			exit(1);
		}
	}
	return(matrix);
}

void FillingArray(float **arr, int *size)
{
	int i = 0;
	int j = 0;
	for(i = 0; i < *size; i++)
	{
		for(j = 0; j < *size; j++)
		{
			while(!scanf("%f", &arr[i][j]))
			{
				printf("You enter invalid symbols, please try again.\n");
				fflush(stdin);
			}
		}
	}
}

void FillingBackArray(float** arr, int* size)
{
	int i;
	int j;
	for (i = 0; i < *size; i++)
	{
		for(j = 0; j < *size; j++)
		{
			if (i == j)
			{
				arr[i][j] = 1;
			}
			else
			{
				arr[i][j] = 0;
			}
		}
	}
}

void Info(float **arr, int *size)
{
	int i = 0;
	int j = 0;
	for(j = 0; j < *size; j++)
	{
		for(i = 0; i < *size; i++)
		{
			printf("%f ", arr[i][j]);
		}
		printf("\n");
	}
}

void CountingBackMatrix(float **arr, float **backArr, int *size)
{
    int i;
	int j;
	int k;
	int m;
	float temp;
	for (j = 1; j < *size; j++)
	{
		if(arr[0][j] != 0)
		{
			temp = arr[0][j];
			for (i = 0; i < *size; i++)
			{
				arr[i][j] -= temp;
				backArr[i][j] -= temp;
			}
		}
	}
	for (j = *size - 1; j > 1; j--)
	{
		for (i = 1; i < *size; i++)
		{
			if(i == j) continue;
			if (arr[i][j-1] == 0) temp = 0;
			else temp = arr[i][j] / arr[i][j-1];
			if (temp > 0 && arr[i][j-1] > 0) temp *= -1;
			else if (temp < 0 && arr[i][j-1] < 0) temp *= -1;
			for (k = i; k < *size; k++)
			{
				arr[k][j] = arr[k][j] + arr[k][j-1] * temp;
			}
			for (m = 0; m < *size; m++)
			{
				backArr[m][j] = backArr[m][j] + (backArr[m][j-1] * temp);
			}
		}
	}
	for (i = 0, j = 0; i < *size; i++, j++)
	{
		temp = arr[i][j];
		for (k = 0; k < *size; k++)
		{
			arr[k][j] /= temp;
			backArr[k][j] /= temp;
		}
	}
	for (j = *size - 1, i = *size - 1; j >= 0; j--)
	{
		int help = 1;
		while(arr[i][j] != 0)
		{
            if ((j - help) < 0)
			{
				i--;
				break;
			}
			temp = arr[i][j-help] / arr[i][j];
			if (temp > 0 && arr[i][j-help] > 0)
			{
				temp *= -1;
			}
			else if (temp < 0 && arr[i][j-help] < 0)
			{
				temp *= -1;
			}
			for (k = *size - 1; k >= 0; k--)
			{
				backArr[k][j-help] = backArr[k][j-help] + temp * backArr[k][j];
			}
			arr[i][j-help] = arr[i][j-help] + temp * arr[i][j];
			help++;
			if (i < 0) break;
		}
	}
}

#ifndef TESTING

int main()
{
    int order;
    float** matrix;
	float** backMatrix;
	printf("Enter the matrix order: ");
	scanf("%d", &order);
	matrix = MatrixCreate(&order);
	backMatrix = MatrixCreate(&order);
	FillingBackArray(matrix, &order);
	FillingArray(matrix, &order);
	FillingBackArray(backMatrix, &order);
	CountingBackMatrix(matrix, backMatrix, &order);
	Info(matrix, &order);
	printf("\n");
	Info(backMatrix, &order);
	free(matrix);
	free(backMatrix);
    return 0;
} 
#endif