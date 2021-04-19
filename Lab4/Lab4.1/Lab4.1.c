#include <stdio.h>
#include <stdlib.h>

unsigned long int StoI(char* str, int size)
{
	if(size == 0)
	return str[size] - '0';
	else return ((str[size] - '0') + StoI(str, size - 1) * 10);
}

int StrSize(char* str)
{
	int i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return i;
}

#ifndef TESTING

int main()
{
    char* str = (char*)malloc(sizeof(char) * 12);
    unsigned int temp;
    printf("Enter a number: ");
    scanf("%s", str);
    temp = StoI(str, StrSize(str) - 1);
    printf("Your number in digit format is: %ld", temp);
    return 0;
}
#endif
