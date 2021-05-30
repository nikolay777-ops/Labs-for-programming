#include "main.h"

struct CompNode
{
	char* name;
	struct CompNode* next;
	struct CompNode* prev;
};

struct CompList
{
	struct CompNode* head;
	struct CompNode* tail;
	int size;
};

struct AlbNode
{
	char* perfID;
	char* name;
	struct CompList* compos;
	struct AlbNode* next;
	struct AlbNode* prev;
	int price;
	int bought;
};

struct AlbList
{
	struct AlbNode* head;
	struct AlbNode* tail;
	int size;
};

void AlbInit(struct AlbList** list);

long FindPos(char* str);

void CompPush(struct CompList** list, long* pos);

void AlbPush(struct AlbList** list, char* str, long* pos);

void Alb(struct AlbList** list, char* str);

struct AlbList* SearchByPerformer(struct AlbList** list, char* name);

struct AlbNode* SearchByAlbum(struct AlbList** list, char* str);

struct AlbNode* SearchByCompose(struct AlbList** list, char* str);

void ClearCompose(struct CompList** list);

void ClearAlb(struct AlbList** list);

void AlbInfo(struct AlbNode* node);

void AllAlbums(struct AlbList** albums);

char* IntToStr(int num);
