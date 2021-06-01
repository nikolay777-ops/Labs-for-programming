#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

int StrSize(char* str);

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

void CompPush(struct CompList** list, long *pos);

void AlbPush(struct AlbList** list, char* str, long *pos);

void Alb(struct AlbList** list, char* str);

struct AlbList* SearchByPerformer(struct AlbList** list, char* name);

struct AlbNode* SearchByAlbum(struct AlbList** list, char* str);

struct AlbNode* SearchByCompose(struct AlbList** list, char* str);

void ClearCompose(struct CompList** list);

void ClearAlb(struct AlbList** list);

void AlbInfo(struct AlbNode* node);

void AllAlbums(struct AlbList** albums);

char* IntToStr(int num);

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

void AddInfo(struct PerfNode* node, char* ID, long *curPos);

void PerfPush(struct PerfList** list, char* ID);

void PerfCr(struct PerfList** list);

void PerfInfo(struct PerfNode* node);

void SearchID(struct PerfList** list, char* ID);

void SearchName(struct PerfList** list, char* name);

void PerfClear(struct PerfList** list);

struct User
{
    struct User* next;
    struct User* prev;
    int totalSum;
};

struct UserList
{
    struct User* head;
    struct User* tail;
    int size;
};

void Start(struct AlbList** list, struct User* user, int i, char* str);

void ShowGenres();

void GenresInfo();

void PerfomancesAction(int i, char* str);

void AlbumsAction(struct AlbList** list, struct User* user, char* str, int i);

void Report(struct AlbList** list, struct UserList** usList);

void NodeInit(struct PerfNode** node);
