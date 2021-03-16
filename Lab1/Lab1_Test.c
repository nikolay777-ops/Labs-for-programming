#include "Lab1.h"

void firstTesting()
{
    char* testArr;
    int numb = 7;
    int last = 7;
    testArr = malloc(sizeof(char) * 40);
    int Count = fillingArray(testArr, numb, last);
    numb = pow(numb, 3);
    numb %= 10;
    int Compar = testArr[Count - 1] - '0';
    assert(numb == Compar);
    free(testArr);
}

int main()
{
    firstTesting();
    printf("\nTest are done!");
    return 0;
}

