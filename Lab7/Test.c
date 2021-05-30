#include "Test.h"
#include <assert.h>

void UITest()
{
    struct AlbList* list = NULL;
    struct UserList* usList;
    char* str = (char*)malloc(sizeof(char) * 21);
    assert(str != NULL);
    AlbInit(&list);
    assert(list != NULL);
    assert(list->head == NULL);
    assert(list->tail == NULL);
    AllAlbums(&list);
    assert(strncmp(list->head->perfID, "Kan", 3) == 0);
    assert(strncmp(list->head->next->next->perfID, "Kil", 3) == 0);
    assert(strncmp(list->head->next->next->next->next->perfID, "Emi", 3) == 0);
    assert(strncmp(list->head->next->next->next->next->next->next->perfID, "Dav", 3) == 0);
    usList = (struct UserList*)malloc(sizeof(struct UserList));
    assert(usList != NULL);
    usList->head = (struct User*)malloc(sizeof(struct User));
    usList->head->next = NULL;
    usList->head->prev = NULL;
    assert(usList->head != NULL);
    str = "Kanye West";
    Start(&list, usList->head, 1, "");
    Start(&list, usList->head, 2, "");
    Start(&list, usList->head, 3, "");
    Start(&list, usList->head, 4, str);
    Report(&list, &usList);
    assert(usList->head->totalSum > 0);
    ClearAlb(&list);
    assert(list == NULL);
}

void AlbumsTest()
{
        struct AlbList* albs = NULL;
	struct AlbList* search = NULL;
	struct AlbNode* nodeSearch = NULL;
    	AlbInit(&search);
	AlbInit(&albs);
	AllAlbums(&albs);
	nodeSearch = SearchByAlbum(&albs, "Kamikaze");
	assert(nodeSearch != NULL);
	assert(strncmp(nodeSearch->name, "Kamikaze", 3) == 0);
	search = SearchByPerformer(&albs, "Avicii");
	assert(search->head != NULL);
	assert(strncmp(search->head->name, "TIM", 3) == 0);
	ClearAlb(&albs);
        assert(albs == NULL);
}

void PerfomancesTest()
{
    struct PerfList* list = NULL;
    char* gen;
    gen = (char*)malloc(sizeof(char) * 20);
    gen = "Kanye\0";
    list = PerfCr(&list);
    assert(list != NULL);
    assert(list->head != NULL);
    assert(list->tail != NULL);
    SearchID(&list, "-HHP");
    SearchName(&list, gen);
    PerfClear(&list);
    assert(list == NULL);
}

void GenresTest()
{
        struct GenersList* geners = NULL;
    	assert(geners == NULL);
	geners = ListCr();
    	assert(geners->head != NULL);
    	assert(geners->tail != NULL);
	GenInfo(&geners, 1);
	GenInfo(&geners, 2);
	GenInfo(&geners, 3);
	GenInfo(&geners, 4);
	ClearAll(&geners);
    	assert(geners == NULL);
}

void TestAll()
{
    UITest();
    AlbumsTest();
    PerfomancesTest();
    GenresTest();
    printf("Tests are done!");
}

int main()
{
    PerfomancesTest();
    return 0;
}
