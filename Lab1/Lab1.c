#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>
#include <assert.h>

#ifndef TEST
int fillingArray(char* arr, int numb, int last);

int main()
{
	int amount = 40;
	char* array;
	int Switch = 0;
	int help = 0;
	int numb = 0;
	int last = 0;
	printf("Enter the number ");
	scanf("%d", &numb);
	if(numb > 13)
	{
		amount += 20;
	}
	if(numb < 0) 
	{
		exit(1);
	}
	printf("Enter the number of sequence ");
	scanf("%d", &last);
	if(last <= 0)
	{
		printf("You entered a wrong number");
	}
	array = malloc(sizeof(char)*amount);
	if(!array)
	{
		printf("Out of memory.");
	}
	fillingArray(array, numb, last);
	getchar();
	getchar();
}
#endif
int fillingArray(char* arr, int numb, int last)
{
	int i = 1;
	int Count = 0;
	int Switch = 0;
	int help = 0;
	while(i <= numb)
	{
		help = i * i * i;
		while (1)
		{
			if (help / 10 >= 1)
			{
				arr[Count] = '0' + help % 10;
				help /= 10;
				Count++;
				Switch++;
			}
			else
			{
				arr[Count] = '0' + help;
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
				buffer = arr[CountBuffer];
				arr[CountBuffer] = arr[CountBuffer - Switch];
				arr[CountBuffer - Switch] = buffer;
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
				buffer = arr[CountBuffer];
				arr[CountBuffer] = arr[CountBuffer - Switch];
				arr[CountBuffer - Switch] = buffer;
				Switch -= 2;
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
		printf("%c", arr[i]);
		i++;
	}
	printf("\n");
	printf("%c", arr[last - 1]);
	return Count;
}
