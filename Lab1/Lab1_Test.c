#include <stdio.h>
#include "Lab1.h"

void firstTesting()
{   
    int result = checkTrueEntering(-7, 13);
    if(result)
    {
        printf("All entered numbers are true.\n");
    }
    else
    {
        printf("You entered invalid numbers, please reload program.\n");
    }
}

void secondTesting()
{
    int result = checkTrueEntering(13, -15);
    if(result)
    {
        printf("All entered numbers are true.\n");
    }
    else
    {
        printf("You entered invalid numbers, please reload program.\n");
    }
}

void thirdTesting()
{
    int result = checkTrueEntering(-13, -17);
    if(result)
    {
        printf("All entered numbers are true.\n");
    }
    else
    {
        printf("You entered invalid numbers, please reload program.\n");
    }
}
void fourthTesting()
{   
    int result = checkTrueEntering(15, 17);
    if(result)
    {
        printf("All entered numbers are true.\n");
    }
    else
    {
        printf("You entered invalid numbers, please reload program.\n");
    }
}

int main()
{
    firstTesting();
    secondTesting();
    thirdTesting();
    fourthTesting();
    printf("Tests are done!\n");
    return 0;
}

