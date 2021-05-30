#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct CompNode
{
	char* albID;
	char* name;
	char* text;
	unsigned short int year;
	struct CompNode* next;
	struct CompNode* prev;
}CompNode;

typedef struct CompList
{
	CompNode* head;
	CompNode* tail;
	int size;
}CompList;

typedef struct AlbNode
{
	char* perfID;
	char* name;
	CompList* compos;
	struct AlbNode* next;
	struct AlbNode* prev;
	int price;
}AlbNode;

typedef struct AlbList
{
	AlbNode* head;
	AlbNode* tail;
	int size;
}AlbList;


