#include <stdlib.h>
#include <stdio.h>

void FillingArray(float **arr, int size)
{
	int i = 0;
	int j = 0;
	for(i = 0; i < size; i++)
	{
		for(j = 0; j < size; j++)
		{
			while(!scanf("%f", &arr[i][j]))
			{
				printf("You enter invalid symbols, please try again.\n");
				fflush(stdin);
			}
		}
	}
}

void GetMatrix(float** matrix, float **p, int i, int j, int m)
{
	int ki, kj, di, dj;
	di = 0;
	for (ki = 0; ki < m - 1; ki++)
	{
		if (ki == i)
		di = 1;
		dj = 0;
		for (kj = 0; kj < m - 1; kj++)
		{
			if(kj == j)
			dj = 1;
			p[ki][kj] = matrix[ki + di][kj + dj];
		}
	}
}

int Determinant(float** matrix, int size)
{
	int i, d, k, n;
	float **p;
	p = (float**)malloc(sizeof(float*) * size);
	for(i = 0; i < size; i++)
	{
		p[i] = (float*)malloc(sizeof(float*) * size);
	}
	 d = 0;
	k = 1;
	n = size - 1;
	if (size < 0)
	printf("Determinant doesn't exist.");
	if(size == 1)
	{
		d = matrix[0][0];
		return d;
	}
	if(size == 2)
	{
		d = matrix[0][0] * matrix[1][1] - (matrix[1][0] * matrix[0][1]);
		return d;
	}
	if(size > 2)
	{
		for (i = 0; i < size; i++)
		{
			GetMatrix(matrix, p, i, 0, size);
			d = d + k * matrix[i][0] * Determinant(p, n);
			k = -k;
		}

	}
	return d;
}

float** MatrixCreate(int size)
{
	float** temp;
	int i;
	temp = (float**)malloc(sizeof(float*) * size);
	if(!temp)
	{
		printf("Error with memory.");
	}
	for (i = 0; i < size; i++)
	{
		temp[i] = (float*)malloc(sizeof(float) * size);
	}
	return temp;
}

void FillingBackArray(float** arr, int size)
{
	int i;
	int j;
	for (i = 0; i < size; i++)
	{
		for(j = 0; j < size; j++)
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

void Nulling(float** matrix, float** backMatrix, int size, int firstPos, int secondPos)
{
	int i = firstPos, j = secondPos, k;
	float divider = matrix[firstPos][secondPos];
	float** matrixTemp = (float**)malloc(sizeof(float*) * size);
	float* backMatrixTemp = (float*)malloc(sizeof(float) * size);
	for (k = 0; k < size; k++)
	{
		matrixTemp[k] = (float*)malloc(sizeof(float) * 1);
	}
	for(k = 0; k < size; k++)
	{
		matrixTemp[k][0] = matrix[k][j];
		matrixTemp[k][1] = matrix[i][k];
		backMatrixTemp[k] = backMatrix[k][j];
	}
	while(j != 0)
	{
		--j;
		for (i = 0, k = 0; i < size; i++, k++)
		{
			backMatrix[i][j] -= (backMatrixTemp[k] * matrix[firstPos][j]) / divider;
		}
		i = firstPos;
		for (i = 0; i < size; i++)
		{
			matrix[i][j] -= (matrixTemp[i][0] * matrixTemp[j][1]) / divider;
		}
	}
	j = secondPos;
	k = 0;
	while(j != size - 1)
	{
		++j;
		for (i = 0, k = 0; i < size; i++, k++)
		{
			backMatrix[i][j] -= (backMatrixTemp[k] * matrix[firstPos][j]) / divider;
		}
		for (i = 0; i < size; i++)
		{
			matrix[i][j] -= (matrixTemp[i][0] * matrixTemp[j][1]) / divider;
		}
	}
	j = secondPos;
	for (i = 0; i < size; i++)
	{
		matrix[i][j] /= divider;
		backMatrix[i][j] /= divider;
	}
	for (k = 0; k < size; k++)
	{
		free(matrixTemp[k]);
	}
	free(matrixTemp);
	free(backMatrixTemp);
}

void CountingBackMatrix(float** matrix, float** backMatrix, int size)
{
	int i, j;
	for (i = 0, j = 0; i < size; i++, j++)
	{
		Nulling(matrix, backMatrix, size, i, j);
	}
}

void Info(float** matrix, int size)
{
	int i, j;
	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++)
		{
			printf("%f ", matrix[j][i]);
		}
		printf("\n");
	}
}

#ifndef TESTING

int main()
{
    int N;
    int i;
    float** matrix;
    float** backMatrix;
    printf("Enter N: ");
    scanf("%d", &N);
	matrix = (float**)malloc(sizeof(float*) * N);
	backMatrix = (float**)malloc(sizeof(float*) * N);
	for(i = 0; i < N; i++)
	{
		matrix[i] = (float*)malloc(sizeof(float) * N);
		backMatrix[i] = (float*)malloc(sizeof(float) * N);
	}
	FillingArray(matrix, N);
	FillingBackArray(backMatrix, N);
	printf("Matrix before counting: \n");
	Info(matrix, N);
	printf("Back matrix before counting: \n");
	Info(backMatrix, N);
	CountingBackMatrix(matrix, backMatrix, N);
	printf("Matrix after counting: \n");
	Info(matrix, N);
	printf("BackMatrix after counting: \n");
	Info(backMatrix,N);
	return 0;
}

#endif