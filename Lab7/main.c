#include "main.h"

int StrSize(char* str)
{
	int i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\n')
			break;
		i++;
	}
	return i;
}