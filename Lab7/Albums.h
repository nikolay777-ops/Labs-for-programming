#include "main.h"

typedef struct CompNode
{
	char* name;
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
	int bought;
}AlbNode;

typedef struct AlbList
{
	AlbNode* head;
	AlbNode* tail;
	int size;
}AlbList;

void AlbInit(AlbList** list);

long FindPos(char* str);

void CompPush(CompList** list, long* pos);

void AlbPush(AlbList** list, char* str, long* pos);

void Alb(AlbList** list, char* str);

AlbList* SearchByPerformer(AlbList** list, char* name);

AlbNode* SearchByAlbum(AlbList** list, char* str);

AlbNode* SearchByCompose(AlbList** list, char* str);

void ClearCompose(CompList** list);

void ClearAlb(AlbList** list);

void AlbInfo(AlbNode* node);

void AllAlbums(AlbList** albums);

char* IntToStr(int num);