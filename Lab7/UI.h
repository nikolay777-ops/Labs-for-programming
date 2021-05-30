#include "main.h"
#include "Albums.h"
#include "Genres.h"
#include "Perfomances.h"

typedef struct User
{
    struct User* next;
    struct User* prev;
    int totalSum;
};

typedef struct UserList
{
    User* head;
    User* tail;
    int size;
};

void Start(AlbList** list, User* user, int i, char* str);

void ShowGenres();

void GenresInfo();

void PerfomancesAction(int i, char* str);

void AlbumsAction(AlbList** list, User* user, char* str, int i);

void Report(AlbList** list, UserList** usList);
