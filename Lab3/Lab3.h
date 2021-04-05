#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

float **MatrixCreate(int* size);
void FillingArray(float **arr, int *size);
void FillingBackArray(float** arr, int* size);
void Info(float **arr, int *size);
void CountingBackMatrix(float **arr, float **backArr, int *size);
