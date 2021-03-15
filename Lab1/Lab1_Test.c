#include <stdio.h>
#include "Lab1.h"
#include <assert.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>

void firstTesting()
{
    char* testArr;
    int numb = 7;
    int last = 7;
    testArr = malloc(sizeof(char) * 40);
    int Count = fillingArray(testArr, numb, last);
    numb = pow(numb, 3);
    assert((numb % 10) == (testArr[Count - 1] - '0'));
}

int main()
{
    firstTesting();
    printf("\nTest are done!");
    getchar();
    return 0;
}

