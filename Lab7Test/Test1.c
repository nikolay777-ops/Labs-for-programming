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
   // PerfClear(&list);
    free(list);
}

int main()
{
    PerfomancesTest();
    return 0;
}