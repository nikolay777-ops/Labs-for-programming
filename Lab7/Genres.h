#include "main.h"

struct GenersNode
{
	char* ID;
	char** article;
	struct GenersNode* next;
	struct GenersNode* prev;
};

struct GenersList
{
	struct GenersNode* head;
	struct GenersNode* tail;
	int size;
};

bool GenExists(struct GenersList* list, char* str);

struct GenersNode* GenSearch(struct GenersList* list, char* str);

struct GenersNode* GenCr(struct GenersNode* node);

void SetArticle(struct GenersNode* node, long* curPos);

void GenPush(struct GenersList** list, char* str);

struct GenersList* ListCr();

void GenInfo(struct GenersList** geners, int num);

void ClearAll(struct GenersList** list);
