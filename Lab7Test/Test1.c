#include "All.h"
#include <assert.h>

void UITest()
{
    struct AlbList* list = NULL;
    struct UserList* usList = NULL;
    char* str = (char*)malloc(sizeof(char) * 21);
    assert(str != NULL);
    AllAlbums(&list);
    usList = (struct UserList*)malloc(sizeof(struct UserList));
    assert(usList != NULL);
    usList->head = (struct User*)malloc(sizeof(struct User));
    assert(usList->head != NULL);
    usList->head->next = NULL;
    usList->head->prev = NULL;
    str = "Kanye West";
    Start(&list, usList->head, 1, "");
    Start(&list, usList->head, 2, "");
    //Start(&list, usList->head, 3, "");
    //Start(&list, usList->head, 4, str);
    //Report(&list, &usList);
    //assert(usList->head->totalSum > 0);
}

int main()
{
    UITest();
    return 0;
}
