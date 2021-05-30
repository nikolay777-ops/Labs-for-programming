#include "UI.h"

void Start(struct AlbList** list, struct User* user, int i, char* str)
{
    printf("Hello! mp3ALL.com glad to see you!\n");
    printf("There you can learn something new about music genres, \n");
    printf("pefromances of every music genre and also buy their albums.\n");
    printf("So, let's start.\n");
    printf("What you want to do?\n");
    printf("1.Show genres.\n");
    printf("2.Show info about genres.\n");
    printf("3.Show perfomances of genre\n");
    printf("4.Show albums with tracks.\n");
    switch (i)
    {
        case 1: ShowGenres();break;
        case 2: GenresInfo();break;
        case 3:
        {
            PerfomancesAction(1, "");
            PerfomancesAction(2, "Kanye West");
            PerfomancesAction(2, "Eminem");
        }break;
        case 4: AlbumsAction(list, user, str, 1);break;
        default: printf("Incorrect input.");break;
    }
}

void ShowGenres()
{
    struct GenersList* geners;
    struct GenersNode* node;
    int i = 1;
    geners = ListCr();
    node = geners->head;
    while(node != NULL)
    {   
        printf("%d.%s", i, node->ID);
        i++;
        node = node->next;
    }
    ClearAll(&geners);
}

void GenresInfo()
{
    	struct GenersList* geners;
	geners = ListCr();
	GenInfo(&geners, 1);
	GenInfo(&geners, 2);
	GenInfo(&geners, 3);
	GenInfo(&geners, 4);
	ClearAll(&geners);
}

void PerfomancesAction(int i, char* str)
{
    struct PerfList* perf;
    perf = PerfCr(&perf);
    printf("1.Show All\n");
    printf("2.Show by name\n");   
    switch (i)
    {
        case 1: 
        {
            SearchID(&perf, "-HHP");
            SearchID(&perf, "-ELEC");
            SearchID(&perf, "-BLU");
            SearchID(&perf, "-JZ");
        }break;
        case 2:
        {
            SearchName(&perf, str);
        }break;
        default: printf("You input incorrect number");break;
    }
    PerfClear(&perf);
    free(str);
}

void AlbumsAction(struct AlbList** list, struct User* user, char* str, int i)
{
    	struct AlbList* search = NULL;
    	printf("Please write the name of performer.");  
    	search = SearchByPerformer(list, str);
	AlbInfo(search->head);
	printf("\nDo you want to buy such album? (Yes/1, No/0)\n");
	if (i == 1)
	{
		search->head->bought++;
		user->totalSum += search->head->price;
	}
	AlbInfo(search->head->next);
	printf("\nDo you want to buy such album? (Yes/1, No/0)\n");
	if (i == 1)
    	{
        	search->head->next->bought++;
        	user->totalSum += search->head->next->price;
    	}
	free(str);
}

void Report(struct AlbList** list, struct UserList** usList)
{
    FILE *fp;
    struct AlbNode* node = (*list)->head;
    struct User* usNode = (*usList)->head;
    int totalCash = 0;
    int totalAlbums = 0;
    while(usNode != NULL)
    {
        totalCash += usNode->totalSum;
        usNode = usNode->next;
    }
    if (!(fp = fopen("Report.txt", "w")))
    {
        printf("An error with Report.txt");
        exit(1);
    }
    else
    {   
        node = (*list)->head;
        while(node != NULL)
        {
            totalAlbums += node->bought;
            fputs(node->name, fp);
            fputc('\n',fp);
            fputs("price: ",fp);
            fputs(IntToStr(node->price), fp);
			fputc('\n',fp);
            fputs("Copies sold: ", fp);
			fputs(IntToStr(node->bought), fp);
			fputc('\n', fp);
			node = node->next;
		}
		fputs("Total copies: ", fp);
		fputc('\n', fp);
		fputs(IntToStr(totalAlbums), fp);
		fputc('\n', fp);
		fputs("Total profit: ", fp);
		fputc('\n', fp);
		fputs(IntToStr(totalCash), fp);
	}
    fclose(fp);
}
/*
int main()
{
    AlbList* list = NULL;
    UserList* usList;
	AlbInit(&list);
    AllAlbums(&list);
    printf("%s", list->head->name);
	usList = (UserList*)malloc(sizeof(UserList));
    usList->head = (User*)malloc(sizeof(User));
	Start(&list, usList->head);
	Report(&list, &usList);
    ClearAlb(&list);
    return 0;
}*/
