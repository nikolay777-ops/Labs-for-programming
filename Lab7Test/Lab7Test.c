#include "All.h"
#include <assert.h>
#include <sys/stat.h>
#include <sys/types.h>

void AlbumsTest()
{
	struct AlbList* albs = NULL;
	struct AlbList* search = NULL;
	struct AlbNode* nodeSearch = NULL;
	AlbInit(&search);
	AlbInit(&albs);
	AllAlbums(&albs);
	assert(albs != NULL);
	assert(albs->head != NULL);
	assert(albs->tail != NULL);
	assert(strncmp(albs->head->perfID, "Kan", 3) == 0);
	assert(strncmp(albs->head->next->next->perfID, "Kil", 3) == 0);
	assert(strncmp(albs->head->next->next->next->next->perfID, "Emi", 3) == 0);
	assert(strncmp(albs->head->next->next->next->next->next->next->perfID, "Dav", 3) == 0);
	nodeSearch = SearchByAlbum(&albs, "Kamikaze");
	assert(nodeSearch != NULL);
	assert(strncmp(nodeSearch->name, "Kamikaze", 3) == 0);
	search = SearchByPerformer(&albs, "Avicii");
	assert(search->head != NULL);
	assert(strncmp(search->head->name, "TIM", 3) == 0);
}

void PerfomancesTest()
{
	struct PerfList* list = NULL;
        char* gen;
        gen = (char*)malloc(sizeof(char) * 20);
        gen = "Kanye\0";
        PerfCr(&list);
        assert(list != NULL);
        assert(list->head != NULL);
        assert(list->tail != NULL);
        SearchID(&list, "-HHP");
        SearchName(&list, gen);
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
}

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
    	Start(&list, usList->head, 3, "");
    	Start(&list, usList->head, 4, str);
    	Report(&list, &usList);
    	assert(usList->head->totalSum > 0);
}

void TestAll()
{
	UITest();
	PerfomancesTest();
	GenresTest();
	AlbumsTest();
	printf("Tests are done!");
}

int main()
{
	TestAll();
	return 0;
}
