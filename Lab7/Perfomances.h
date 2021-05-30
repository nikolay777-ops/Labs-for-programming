#include "main.h"

struct PerfNode
{
	char* genID;
	char* name;
	char* year;
	struct PerfNode* next;
	struct PerfNode* prev;
};

struct PerfList
{
	struct PerfNode* head;
	struct PerfNode* tail;
	int size;
	long curPos;
};

struct PerfNode* NodeInit(struct PerfNode* node);

void AddInfo(struct PerfNode* node, char* ID, long *curPos);

void PerfPush(struct PerfList** list, char* ID);

struct PerfList* PerfCr(struct PerfList** list);

void PerfInfo(struct PerfNode* node);

void SearchID(struct PerfList** list, char* ID);

void SearchName(struct PerfList** list, char* name);

void PerfClear(struct PerfList** list);
