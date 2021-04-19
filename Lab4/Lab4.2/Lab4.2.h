#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct pills
{
    char name[15];
    char date[9];
    int standards;
	int price;
};

void CheckArray(char* arr);

int StoI(char* str, int size);

int StrSize(char* str);

void Empty(char* str);

void StrToStruct(struct pills* all, char* str);

void Info(struct pills* all, int index);

int OverDuePills(struct pills* all);

bool IsName(char* str);

bool IsDate(char* str);

bool IsStandards(char* str);

bool IsPrice(char* str);
