#include "All.h"
#include <assert.h>

void FirstTest()
{
    struct AlbList* list = NULL;
    list = (struct AlbList*)malloc(sizeof(struct AlbList));
    list->head = list->tail = NULL;
    char* str = (char*)malloc(sizeof(char) * 15);
    assert(str);
    str = "Kanye West";
    Alb(&list, str);
    assert(list != NULL);
    assert(list->head != NULL);
    assert(list->tail != NULL);
    assert(strncmp(list->head->perfID, "Kan", 3) == 0);
    //assert(strncmp(list->head->next->next->perfID, "Kil", 3) == 0);
   //assert(strncmp(list->head->next->next->next->next->perfID, "Emi", 3) == 0);
    //assert(strncmp(list->head->next->next->next->next->next->next->perfID, "Dav", 3) == 0);
}

int main()
{
    FirstTest();
    return 0;
}
