#include "Lab4.2.h" 
#include <assert.h>

static int size = 0;

void FirstTest()
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

void SecondTest()
{
    char str1[] = "Aspirin 15.04.99 132 1250";
    char str2[] = "$*(&(! 15.&*.$) &($) *()$!";
    char str3[] = "Aspirin $£!$ 132 1250";
    assert(IsName(str1));
    assert(IsDate(str1));
    assert(IsStandards(str1));
    assert(IsPrice(str1));
    assert(!IsName(str2));
    assert(!IsDate(str2));
    assert(!IsStandards(str2));
    assert(!IsPrice(str2));
    assert(!IsDate(str3));
}

void ThirdTest()
{
    struct pills* test = (struct pills*)malloc(sizeof(struct pills) * 2);
    int temp;
    char str1[] = "Aspirin 15.04.99 125 1300";
    char str2[] = "Insulin 17.02.05 130 1250"; 
    StrToStruct(test, str1);
    StrToStruct(test, str2);
    temp = OverDuePills(test);
    assert(temp == 325000);
    free(test);
}

int main()
{
    FirstTest();
    SecondTest();
    ThirdTest();
    printf("Tests are done sucessfully!");
    return 0;
}
