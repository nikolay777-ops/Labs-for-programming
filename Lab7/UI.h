#include "main.h"
#include "Albums.h"
#include "Genres.h"
#include "Perfomances.h"

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
