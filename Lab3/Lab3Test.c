#include "Lab3.h"
#include <time.h>
#include <assert.h>

void FirstTest()
{
    	float** matrix;
	float** backMatrix;
	int i, j, det;
	int N;
    	srand(time(NULL));
    	N = 3;
	matrix = MatrixCreate(N);
	backMatrix = MatrixCreate(N);
	matrix[0][0] = 1;
	matrix[1][0] = 2;
	matrix[2][0] = 3;
	matrix[0][1] = 4;
	matrix[1][1] = 5;
	matrix[2][1] = 6;
	matrix[0][2] = 7;
	matrix[1][2] = 8;
	matrix[2][2] = 9;
	det = Determinant(matrix, N);
	assert(det == 0);
    	FillingBackArray(backMatrix, N);
    	for (i = 0; i < N; i++)
    	{
        	for(j = 0; j < N; j++)
        	{
           	matrix[i][j] = rand() % 100 - 50;
        	}
    	}
    	det = Determinant(matrix, N);
    	assert(det != 0);
    	for (i = 0; i < N; i++)
    	{
       		free(matrix[i]);
        	free(backMatrix[i]);
    	}
	}

void SecondTest()
{
    	float** matrix;
	float** backMatrix;
	int N, i, j, sum, det;
	srand(time(NULL));
    	sum = 0;
    	N = 3;
	matrix = MatrixCreate(N);
	backMatrix = MatrixCreate(N);
    	FillingBackArray(backMatrix, N);
    	for (i = 0; i < N; i++)
    	{
        	for(j = 0; j < N; j++)
        	{
           	 matrix[i][j] = rand() % 35;
        	}
    	}
	det = Determinant(matrix,N);
	assert(det != 0);
	CountingBackMatrix(matrix, backMatrix, N);
	for(i = 0, j = 0; i < N; i++, j++)
	sum += matrix[i][j];
	assert(sum == 3);
	for (i = 0; i < N; i++)
	{
		free(matrix[i]);
		free(backMatrix[i]);
	}
}

void ThirdTest()
{
    	float** matrix;
	float** backMatrix;
	int N, i, j, sum, det;
	srand(time(NULL));
    	sum = 0;
    	N = 6;
	matrix = MatrixCreate(N);
	backMatrix = MatrixCreate(N);
	FillingBackArray(backMatrix, N);
	for (i = 0; i < N; i++)
	{
		for(j = 0; j < N; j++)
		{
		    matrix[i][j] = rand() % 25;
		}
	}
	det = Determinant(matrix, N);
	CountingBackMatrix(matrix, backMatrix, N);
	for(i = 0, j = 0; i < N; i++, j++)
	sum += matrix[i][j];
	assert(sum == 6);
	for (i = 0; i < N; i++)
    	{
        	free(matrix[i]);
        	free(backMatrix[i]);
    	}
}

int main()
{
    FirstTest();
    SecondTest();
    ThirdTest();
    printf("Tests are done sucessfully!");
    return 0;
}
