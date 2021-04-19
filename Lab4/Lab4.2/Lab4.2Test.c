#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <assert.h>
#include "Lab4.2.h" 

static int size = 0;

void FirstTest()
{
    char* str1;
    char* str2;
    char* str3;
    unsigned long int temp = 0;
    str1 = (char*)malloc(sizeof(char) * 6);
    str2 = (char*)malloc(sizeof(char) * 1);
    str3 = (char*)malloc(sizeof(char) * 12);
    str1 = ("12345\0");
    str2 = ("1000000000\0");
    str3 = ("2147483647\0");
    temp = StoI(str1, StrSize(str1) - 1);
    assert(temp == 12345);
    temp = StoI(str2, StrSize(str2) - 1);
    assert(temp == 1000000000);
    temp = StoI(str3, StrSize(str3) - 1);
    assert(temp == 2147483647);
    free(str1);
    free(str2);
    free(str3);
}

void SecondTest()
{
    char* str1;
    char* str2;
    char* str3;
    str1 = (char*)malloc(sizeof(char) * 30);
    str2 = (char*)malloc(sizeof(char) * 30);
    str3 = (char*)malloc(sizeof(char) * 30);
    str1 = ("Aspirin 15.04.99 132 1250\0");
    str2 = ("$*(&(! 15.&*.$) &($) *()$!\0");
    str3 = ("Aspirin $£!$ 132 1250\0");
    assert(IsName(str1));
    assert(IsDate(str1));
    assert(IsStandards(str1));
    assert(IsPrice(str1));
    assert(!IsName(str2));
    assert(!IsDate(str2));
    assert(!IsStandards(str2));
    assert(!IsPrice(str2));
    assert(!IsDate(str3));
    free(str1);
    free(str2);
    free(str3);
}

void ThirdTest()
{
    struct pills* test = (struct pills*)malloc(sizeof(struct pills) * 2);
    int temp;
    char* str1 = (char*)malloc(sizeof(char) * 35);
    char* str2 = (char*)malloc(sizeof(char) * 35);
    str1 = ("Aspirin 15.04.99 125 1300\0");
    str2 = ("Insulin 17.02.05 130 1250\0"); 
    StrToStruct(test, str1);
    StrToStruct(test, str2);
    temp = OverDuePills(test);
    assert(temp == 3221440);
    free(str1);
    free(str2);
    free(test);
}

int main()
{
    FirstTest();
    SecondTest();
    ThirdTest();
    printf("Tests are done sucessfully!");
    getchar();
    return 0;
}