#include "Lab4.1.h"


void FirstTest()
{   
    int i;
    int j;
    int temp;
    char* str1;
    char* str2;
    str1 = (char*)malloc(sizeof(char) * 6);
    str1 = ("00000\0");
    temp = StrSize(str1);
    assert(temp == 5);
    str2 = (char*)malloc(sizeof(char) * 16);
    for (i = 0; i < 16; i++)
    {
        str2[i] = 'G';
    }
    str2[16] = '\0';
    temp = StrSize(str2);
    assert(temp == 16);
    free(str2);
}

void SecondTest()
{
    char str1[] = "12345";
    char str2[] = "1000000000";
    char str3[] = "2147483647";
    unsigned long int temp = 0;
    temp = StoI(str1, StrSize(str1) - 1);
    assert(temp == 12345);
    temp = StoI(str2, StrSize(str2) - 1);
    assert(temp == 1000000000);
    temp = StoI(str3, StrSize(str3) - 1);
    assert(temp == 2147483647);
}

int main()
{
    FirstTest();
    SecondTest();
    printf("Tests are done sucessfully!");
    return 0;
}