#include "main.h"

typedef struct GenersNode
{
	char* ID;
	char** article;
	struct GenersNode* next;
	struct GenersNode* prev;
}GenersNode;

typedef struct GenersList
{
	GenersNode* head;
	GenersNode* tail;
	int size;
}GenersList;

bool GenExists(GenersList* list, char* str);

GenersNode* GenSearch(GenersList* list, char* str);

GenersNode* GenCr(GenersNode* node);

void SetArticle(GenersNode* node, long* curPos);

void GenPush(GenersList** list, char* str);

GenersList* ListCr();

void GenInfo(GenersList** geners, int num);

void ClearAll(GenersList** list);