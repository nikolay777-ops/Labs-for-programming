#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>

#ifndef TEST

int main()
{
	int numb = 0;
	int last = 0;
	int amount = 40;
	printf("Enter the number ");
	scanf("%d", &numb);
	if(numb > 13)
	{
		amount += 20;
	}
	printf("Enter the number of sequence ");
	scanf("%d", &last);
    char *array;
	array = malloc(amount);
	if(!array)
	{
		printf("Out of memory.");
		exit(1);
	}
	int Count = 0;
	int i = 1;
	Count = 0;
	int Switch = 0;
	int help = 0;
	while(i <= numb)
	{
		help = i * i * i;
		while (1)
		{
			if (help / 10 >= 1)
			{
				array[Count] = '0' + help % 10;
				help /= 10;
				Count++;
				Switch++;
			}
			else
			{
				array[Count] = '0' + help;
				Count++;
                break;
			}
		}

		if (Switch % 2 == 0)
		{
			int CountBuffer = Count - 1;
			while(Switch > 0)
			{
				char buffer;
				buffer = array[CountBuffer];
				array[CountBuffer] = array[CountBuffer - Switch];
				array[CountBuffer - Switch] = buffer;
				if (Switch == 2)
				{
					Switch = 0;
				}
				else
				{
					Switch-=2;
				}
				CountBuffer--;
			}
		}
		else
		{
			int CountBuffer = Count - 1;
			while(Switch > 0)
			{
				char buffer;
				buffer = array[CountBuffer];
				array[CountBuffer] = array[CountBuffer - Switch];
				array[CountBuffer - Switch] = buffer;
				Switch-=2;
				CountBuffer--;
			}
		}
		if (Switch < 0)
		{
			Switch = 0;
		}
		i++;
	}
    i = 0;
    while(i < Count)
    {
        printf("%c", array[i]);
        i++;
    }
	printf("\n");
	printf("%c", array[last-1]);
	free(array);
	getchar();
	getchar();
	return 0;
}
#endif

int checkTrueEntering(int numb, int last)
{
	if(numb <= 0)
	{
		return 0;
	}
	else if (last <= 0)
	{
		return 0;
	}
	return 1;
}