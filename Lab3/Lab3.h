#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

void FillingArray(float **arr, int size);

void FillingBackArray(float** arr, int size);

void Nulling(float** matrix, float** backMatrix, int size, int firstPos, int secondPos);

void CountingBackMatrix(float** matrix, float** backMatrix, int size);

void Info(float** matrix, int size);

float** MatrixCreate(int size);

bool ExistingBackMatrix(float **matrix, int size);

void GetMatrix(float** matrix, int **p, int i, int j, int m);

int Determinant(float** matrix, int size);
