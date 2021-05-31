#include "All.h"
#include <assert.h>

void PerfomancesTest()
{
    struct PerfList* list = NULL;
    char* gen = NULL;
    gen = (char*)malloc(sizeof(char) * 8);
    gen = "Kanye\0";
    PerfCr(&list);
    assert(list != NULL);
    assert(list->head != NULL);
    assert(list->tail != NULL);
    SearchID(&list, "-HHP");
    SearchName(&list, gen);
    //PerfClear(&list);
   // free(list);
}

void FirstTest()
{
    struct AlbList* list = NULL;
    list = (struct AlbList*)malloc(sizeof(struct AlbList));
    list->head = list->tail = NULL;
    char* str = (char*)malloc(sizeof(char) * 15);
    assert(str);  
    str = "Kanye West";
    Alb(&list, str);
    str = (char*)malloc(sizeof(char) * 15);
    str = "Killstation";
    Alb(&list, str);
    assert(list != NULL);
    assert(list->head != NULL);
    assert(list->tail != NULL);
    assert(strncmp(list->head->perfID, "Kan", 3) == 0);
    assert(strncmp(list->head->next->next->perfID, "Kil", 3) == 0);
    //assert(strncmp(list->head->next->next->next->next->perfID, "Emi", 3) == 0);
    //assert(strncmp(list->head->next->next->next->next->next->next->perfID, "Dav", 3) == 0);
}

int main()
{
    PerfomancesTest();
    FirstTest();
    return 0;
}

