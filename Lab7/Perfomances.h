#include "main.h"

typedef struct PerfNode
{
	char* genID;
	char* name;
	char* year;
	struct PerfNode* next;
	struct PerfNode* prev;
}PerfNode;

typedef struct PerfList
{
	PerfNode* head;
	PerfNode* tail;
	int size;
	long curPos;
}PerfList;

PerfNode* NodeInit(PerfNode* node);

void AddInfo(PerfNode* node, char* ID, long *curPos);

void PerfPush(PerfList** list, char* ID);

PerfList* PerfCr(PerfList** list);

void PerfInfo(PerfNode* node);

void SearchID(PerfList** list, char* ID);

void SearchName(PerfList** list, char* name);

void PerfClear(PerfList** list);