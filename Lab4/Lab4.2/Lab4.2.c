#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

static char avgDate[9] = {"12.09.21"};
static int size = 0;

struct pills
{
	char name[15];
	char date[9];
    	int standards;
	int price;
};

bool IsName(char* str)
{
	int j;
	for (j = 0; str[j] != ' '; j++)
	{
		int a = str[j];
		if(!(str[j] >= 65 && str[j] <= 90) && !(str[j] >= 97 && str[j] <= 122))
			return false;
	}
	return true;
}

bool IsDate(char* str)
{
	int i;
	int j = 0;
	while(str[j] != ' ')
		j++;
	j++;
	for (; str[j] != ' '; j++)
	{
		if(!(str[j] >= '0' && str[j] <= '9'))
		{
			if (str[j] == '.' && (str[j-1] >= '0' && str[j-1] <= '9')
			&& (str[j+1] >= '0' && str[j+1] <= '9'))
			{
				continue;
			}
			else
				return false;
		}
	}
	return true;
}

bool IsStandards(char* str)
{
	int j = 0;
	int k = 0;
	while (k != 3)
	{
        if(k == 2 && !(str[j] >= '0' && str[j] <= '9'))
			return false;
		j++;
		if(str[j] == ' ')
		{
			k++; j++;
		}
	}
	return true;
}

bool IsPrice(char* str)
{
	int j = 0;
	int k = 0;
	while(str[j] != '\0')
	{
        if(str[j] == ' ')
		{
			k++; j++;
		}
		if(k == 3 && !(str[j] >= '0' && str[j] <= '9'))
			return false;
		j++;
	}
	return true;
}

void CheckArray(char* arr)
{
	if(!arr)
	{
		printf("Error");
		exit(1);
	}
}

int StoI(char* str, int size)
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

void Empty(char* str)
{
	int i;
	int j;
	i = StrSize(str);
	for(j = 0; j < i; j++)
	{
		str[i] = '\0';
	}
}

void StrToStruct(struct pills* all, char* str)
{
    	int i = 0;
    	int j = 0;
    	char* stndrd;
	char* prc;
	stndrd = (char*)malloc(sizeof(char) * 5);
   	CheckArray(stndrd);
	prc = (char*)malloc(sizeof(char) * 5);
    	CheckArray(prc);
    	while(str[i] != ' ')
    	{
        	all[size].name[i] = str[i];
        	i++;
    	}
    	i++;
    	while(str[i] != ' ')
    	{
        	all[size].date[j] = str[i];
        	j++;
        	i++;
    	}
    	i++;
    	j = 0;
    	while(str[i] != ' ')
    	{	
        	stndrd[j] = str[i];
        	j++;
        	i++;
    	}
    	i++;
	j = 0;
	while(str[i] != '\0')
	{
		prc[j] = str[i];
		i++;
		j++;
	}
	all[size].standards = StoI(stndrd, StrSize(stndrd) - 1);
	all[size].price = StoI(prc, StrSize(prc) - 1);
    	size++;
	free(stndrd);
	free(prc);
}

void Info(struct pills* all, int index)
{
	printf("%s ", all[index].name);
	printf("%s ", all[index].date);
	printf("%d ", all[index].standards);
	printf("%d\n", all[index].price);
}

int OverDuePills(struct pills* all)
{
	int i;
    	int j;
    	int averageLose = 0;
	int helper = 1;
	int avgQuality;
	int pillQuality;
	for(i = 0; i < size; i++)
	{
		avgQuality = 0;
		pillQuality = 0;
		for(j = 7; j >= 0; j--)
		{
			if(avgDate[j] == '.' && all[i].date[j] == '.')
			{
				if(pillQuality < avgQuality)
				{
					averageLose += all[i].standards * all[i].price;
					Info(all, i);
					break;
				}
				else if (j == 5 && pillQuality > 80)
				{
                    averageLose += all[i].standards * all[i].price;
					Info(all, i);
                    helper = 1;
					avgQuality = 0;
					pillQuality = 0;
					break;
				}
				else
				{
					helper = 1;
					avgQuality = 0;
					pillQuality = 0;
					continue;
				}
			}
			else
			{
				avgQuality += (avgDate[j] - '0') * helper;
				pillQuality += (all[i].date[j] - '0') * helper;
				helper *= 10;
			}
		}
	}
	return averageLose;
}

bool EndComp(char* str)
{
	if (str[0] == '\n')
		return false;
	else
		return true;
}

#ifndef TESTING

int main()
{
	struct pills* allPills = (struct pills*)malloc(sizeof(struct pills) * 8);
	char* str;
	int* sizes;
	int i;
	FILE *fp;
	if(!allPills)
	{
		printf("Error with structure");
		exit(1);
	}
	str = (char*)malloc(sizeof(char) * 45);
	CheckArray(str);
	sizes = (int*)malloc(sizeof(int) * 10);
	if(!sizes)
	{
		printf("Error with int massive");
		exit(1);
	}
	if ((fp = fopen("pills.txt", "w")) == NULL)
	{
		printf("An error in writing file.");
	}
	printf("Enter an information about type of pills. (Enter for exit.)");
    	i = 0;
	do
	{
		fputs(gets(str), fp);
		sizes[i] = StrSize(str);
		i++;
		fputs("\n", fp);
		fflush(stdin);
	}
	while(StrSize(str) != 0);
	fclose(fp);
	if((fp = fopen("pills.txt", "r")) == NULL)
	{
		printf("An error in opening file.");
		exit(1);
	}
	i = 0;
	do
	{
		Empty(str);
		fgets(str, sizes[i] + 1, fp);
		if (str[0] == '\n' || str[0] == '\0')
		{
			continue;
		}
		else
		{
			if(IsName(str) && IsDate(str) &&
			IsStandards(str) && IsPrice(str))
			{
				StrToStruct(allPills, str);
				i++;
			}
			else
			{
				printf("You input something wrong please input data in such format: ");
				printf("Name Date Standards Price\n");
			}
		}
		fflush(stdin);
	}
	while(EndComp(str) || StrSize(str) != 0);
	printf("\nThe average cost of loses is: %d", OverDuePills(allPills));
	free(str);
	free(allPills);
	free(sizes);
    	return 0;
}
#endif
