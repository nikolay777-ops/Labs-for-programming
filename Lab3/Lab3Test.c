#include "Lab3.h"
#include <assert.h>

void FirstTesting()
{
    int size = 5;
    float** matrix = MatrixCreate(&size);
    assert(matrix);
}

void SecondTesting()
{
    float** matrix;
    int size = 5;
    matrix = MatrixCreate(&size);
    printf("Enter elements of matrix");
    FillingArray(matrix, &size);
    assert(matrix);
}

void ThirdTesting()
{
    int i;
    int j;
    int sum = 0;
    float** matrix;
    float ** backMatrix;
    int size = 3;
    matrix = MatrixCreate(&size);
    backMatrix = MatrixCreate(&size);
    printf("Enter elements of matrix 3-rd order.");
    FillingArray(matrix, &size);
    CountingBackMatrix(matrix, backMatrix ,&size);
    for (i = 0; i < size; i++)
    {
        for(j = 0; j < size; j++)
        {
            sum += matrix[i][j];
        }
    }
    assert(sum == size);
}

int main()
{
    FirstTesting();
    SecondTesting();
    ThirdTesting();
    printf("Test are done sucessfully!");
    return 0;
}