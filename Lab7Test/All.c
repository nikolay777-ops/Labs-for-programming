#include "All.h"

long curPos = 0;

void AlbInit(struct AlbList** list)
{
	*list = (struct AlbList*)malloc(sizeof(struct AlbList));
	(*list)->head = NULL;
	(*list)->tail = NULL;
}

long FindPos(char* str)
{
	FILE *fp;
	char* temp = (char*)malloc(sizeof(char) * 36);
	long fPos = 0;
	if (!(fp = fopen("Albums.txt", "r")))
	{
		printf("An error with opening Albums.txt");
		exit(1);
	}
	else
	{
		do
		{
			fgets(temp, 36, fp);
			fflush(stdin);
		} while (strncmp(temp, str, 3) != 0);
		fPos = ftell(fp);
		free(temp);
		fclose(fp);
	}
	return fPos;
}

void CompPush(struct CompList** list, long *pos)
{
	FILE *pf;
	char* temp;
	struct CompNode* point = (*list)->head;
	if (!(pf = fopen("Albums.txt", "r")))
	{
		printf("An error with opening Albums.txt");
		exit(1);
	}
	else
	{
		fseek(pf, *pos, 0);
		while(true)
		{
			temp = (char*)malloc(sizeof(char) * 40);	
			fgets(temp, 36, pf);
			if (temp[StrSize(temp)-1] == '$')
			{
				temp[StrSize(temp)-1] = '\0';
				point->name = temp;
				break;
			}
			point->name = temp;
			fflush(stdin);
			point->next = (struct CompNode*)malloc(sizeof(struct CompNode));
			point->next->next = NULL;
			point->next->prev = point;
			point = point->next;
            (*list)->size++;
		}
		(*list)->tail = point;
		*pos = ftell(pf);
		fclose(pf);
	}
}

void AlbPush(struct AlbList** list, char* str, long *pos)
{
	FILE *fp;
	char* temp;
	struct AlbNode* temporary = NULL;
	srand(time(NULL));
	if (!(fp = fopen("Albums.txt", "r")))
	{
		printf("An error with opening Albums.txt");
		exit(1);
	}
	else
	{
		if (!(*list)->head)
		{
			fseek(fp, *pos, 0);
			(*list)->head = (struct AlbNode*)malloc(sizeof(struct AlbNode));
			(*list)->head->next = (*list)->head->prev = NULL;
			(*list)->head->perfID = (char*)malloc(sizeof(char) * 4);
			strncpy((*list)->head->perfID, str, 3);
			temp = (char*)malloc(sizeof(char) * 40);
			fgets(temp, 36, fp);
			fflush(stdin);
			(*list)->head->compos = (struct CompList*)malloc(sizeof(struct CompList));
			(*list)->head->compos->head = (struct CompNode*)malloc(sizeof(struct CompNode));
			(*list)->head->name = temp;
			*pos = ftell(fp);
			CompPush(&((*list)->head->compos), pos);
			(*list)->head->price = rand() % 100 + 50;
			(*list)->size++;
			(*list)->head->bought = 0;
			(*list)->tail = (*list)->head;
		}
		else
		{
			temporary = (*list)->head;
			while(temporary->next != NULL)
				temporary = temporary->next;
			fseek(fp, *pos, 0);
			temporary->next = (struct AlbNode*)malloc(sizeof(struct AlbNode));
			temporary->next->next = NULL;
			temporary->next->perfID = (char*)malloc(sizeof(char) * 4);
			strncpy(temporary->next->perfID, str, 3);
			temp = (char*)malloc(sizeof(char) * 40);
			fgets(temp, 36, fp);
			fflush(stdin);
			temporary->next->compos = (struct CompList*)malloc(sizeof(struct CompList));
			temporary->next->compos->head = (struct CompNode*)malloc(sizeof(struct CompNode));
			temporary->next->name = temp;
			temporary->next->bought = 0;
			temporary->next->price = rand() % 100;
			*pos = ftell(fp);
			CompPush(&(temporary->next->compos), pos);
			temporary->next->prev = temporary;
			(*list)->tail = temporary->next;
			(*list)->size++;
		}
	}
	fclose(fp);
}

void Alb(struct AlbList** list, char* str)
{
	FILE *pf;
	long pos = 0;
	char* temp = (char*)malloc(sizeof(char) * 40);
	if (!temp)
	{
		printf("Memory error in ALB");
		exit(1);
	}
	pos = FindPos(str);
	if (!(pf = fopen("Albums.txt", "r")))
	{
		printf("An error with Albums.txt");
		exit(1);
	}
	else
	{
		do
		{
			fseek(pf, pos, 0);
			fgets(temp, 36, pf);
			AlbPush(&(*list), str, &pos);
		}while(temp[StrSize(temp)-1] != '$');
	}
	fclose(pf);
}

struct AlbList* SearchByPerformer(struct AlbList** list, char* name)
{
	struct AlbNode* temp = (*list)->head;
	struct AlbList* performer = (struct AlbList*)malloc(sizeof(struct AlbList));
	performer->head = (struct AlbNode*)malloc(sizeof(struct AlbNode));
	performer->head->next = (struct AlbNode*)malloc(sizeof(struct AlbNode));
	while(strncmp(temp->perfID, name, 3) != 0)
		temp = temp->next;
	performer->head = temp;
	if (strncmp(temp->next->perfID, name, 3) == 0)
	{
		temp = temp->next;
		performer->head->next = temp;
	}
	return performer;
}

struct AlbNode* SearchByAlbum(struct AlbList** list, char* str)
{
	struct AlbNode* temp = (*list)->head;
	while(strncmp(temp->name, str, 3) != 0)
	{
		temp = temp->next;
	}
	return temp;
}

void AlbInfo(struct AlbNode* node)
{
	struct CompNode* temp = node->compos->head;
	printf("name: %s", node->name);
	printf("price: %s\n", IntToStr(node->price));
	while(temp != NULL)
	{
		printf("%s", temp->name);
		temp = temp->next;
	}
}

void AllAlbums(struct AlbList** albums)
{
	AlbInit(albums);
	Alb(albums, "Kanye West");
	Alb(albums, "Killstation");
	Alb(albums, "Eminem");
	Alb(albums, "David Guetta");
	Alb(albums, "Major Lazer");
	Alb(albums, "Avicii");
	Alb(albums, "Howlin' Wolf");
	Alb(albums, "Big Joe Turner");
	Alb(albums, "John Lee Hocker");
	Alb(albums, "Louis Armstrong");
	Alb(albums, "Miles Davis");
	Alb(albums, "Billy Holiday");
}

char* IntToStr(int num)
{
	char* str = (char*)malloc(sizeof(char) * 6);
	int i = 0, help = num;
	for (i = -1; help != 0; i++)
		help /= 10;
	do
	{
		str[i] = (num % 10) + '0';
		num /= 10;
		i--;
		if (num == 0)
            break;
	}
	while(true);
	return str;
}

int StrSize(char* str)
{
	int i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\n')
			break;
		i++;
	}
	return i;
}

struct GenersNode* GenSearch(struct GenersList* list, char* str)
{
	struct GenersNode* temp;
	for (temp = list->head; temp != list->tail; temp = temp->next)
	{
		if (temp->ID == str)
		{
			return temp;
		}
	}
	return NULL;
}

struct GenersNode* GenCr(struct GenersNode* node)
{
	int i;
	node = (struct GenersNode*)malloc(sizeof(struct GenersNode));
	node->next = NULL;
	node->article = (char**)malloc(sizeof(char*) * 4);
	for (i = 0; i < 4; i++)
	{
		node->article[i] = (char*)malloc(sizeof(char) * 72);
	}
	return node;
}

void SetArticle(struct GenersNode* node, long* curP)
{
	FILE *pp;
	int i;
	if (!(pp = fopen("Article.txt", "r")))
	{
		printf("Problems with Article.txt");
		exit(1);
	}
	else
	{
		fseek(pp, *curP, 0);
		for (i = 0; i < 4; i++)
		{
		fgets(node->article[i], 71, pp);
		fflush(stdin);
		}
		*curP = ftell(pp);
		fclose(pp);
	}
}

void GenPush(struct GenersList** list, char* str)
{
	if(!(*list))
	{
		*list = (struct GenersList*)malloc(sizeof(struct GenersList));
		(*list)->head = GenCr((*list)->head);
		(*list)->head->ID = str;
		SetArticle((*list)->head, &curPos);
		(*list)->tail = (*list)->head;
		(*list)->size++;
	}
	else
	{
		struct GenersNode* buf = NULL;
		struct GenersNode* help = (*list)->head;
		buf = GenCr(buf);
		buf->ID = str;
		SetArticle(buf, &curPos);
		while(help->next != NULL)
			help = help->next;
		help->next = buf;
		buf->prev = help;
		(*list)->tail = buf;
		(*list)->size++;
	}
}

struct GenersList* ListCr()
{
	FILE *fp;
	struct GenersList* geners;
	int i;
	char* str;
	str = NULL;
	geners = NULL;
	i = 0;
	if (!(fp = fopen("Genres.txt", "r")))
	{
		printf("Error with opening Genres.txt\n");
		exit(1);
	}
	else
	{
		for (i = 0; i < 4; i++)
		{
			str = (char*)malloc(sizeof(char) * 7);
			fgets(str, 7, fp);
			GenPush(&geners, str);
			fflush(stdin);
		}
	}
	fclose(fp);
	return geners;
}

void GenInfo(struct GenersList** geners, int num)
{
	struct GenersNode* temp;
	int i;
	int j;
	num--;
	for (i = 0, temp = (*geners)->head; i < num;i++, temp = temp->next);
	for (i = 0, j = 0; temp->ID[i] != '\0' ; i++)
	{
		if (temp->ID[i] == '\n')
			continue;
		j += temp->ID[i];
	}
	switch(j)
	{
		case 269: printf("%s\n", "Hip hop");break;
		case 326: printf("%s\n", "Electronic");break;
		case 272: printf("%s\n", "Blues");break;
		case 209: printf("%s\n", "Jazz");break;
	}
	for (i = 0; i < 4; i++)
	{
		printf("%s", temp->article[i]);
	}
}

void NodeInit(struct PerfNode** node)
{
    *node = (struct PerfNode*)malloc(sizeof(struct PerfNode));
	(*node)->name = (char*)malloc(sizeof(char) * 21);
	if (StrSize((*node)->name) != 0)
		(*node)->name = (char*)malloc(sizeof(char) * 21);
	(*node)->year = (char*)malloc(sizeof(char) * 4);
	if (StrSize((*node)->year) != 0)
		(*node)->year = (char*)malloc(sizeof(char) * 4);
    (*node)->next = NULL;
}

void AddInfo(struct PerfNode* node, char* ID, long *curPos)
{
    FILE *fp;
    node->genID = ID;
	if (!(fp = fopen("Perf.txt", "r")))
    {
        printf("Error with Perf.txt");
        exit(1);
    }
    else
    {
        fseek(fp, *curPos, 0);
        fgets(node->name, 20, fp);
        fflush(stdin);
        fgets(node->year, 4,fp);
        *curPos = ftell(fp);
    }
    fclose(fp);
}

void PerfPush(struct PerfList** list, char* ID)
{
    if (!(*list))
    {
        *list = (struct PerfList*)malloc(sizeof(struct PerfList));
        NodeInit(&((*list)->head));
        (*list)->curPos = 0;
        AddInfo((*list)->head, ID, &((*list)->curPos));
        (*list)->size++;
    }
    else
    {
        struct PerfNode *temp, *buf;
        temp = (*list)->head;
        NodeInit(&buf);
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        AddInfo(buf, ID, &((*list)->curPos));
        temp->next = buf;
        buf->prev = temp;
        (*list)->tail = buf;
        (*list)->size++;
    }
}

void PerfCr(struct PerfList** list)
{
    char* gen;
    gen = (char*)malloc(sizeof(char) * 7);
    if (!gen)
    {
        printf("Memory problem.");
        exit(1);
    }
    *list = NULL;
    gen = "-HHP\0";
    PerfPush(&(*list), gen);
    PerfPush(&(*list), gen);
    PerfPush(&(*list),gen);
    gen = (char*)malloc(sizeof(char) * 6);
    if (!gen)
    {
        printf("Memory problem.");
        exit(1);
    }
    gen = "-ELEC\0";
    PerfPush(&(*list), gen);
    PerfPush(&(*list), gen);
    PerfPush(&(*list),gen);
    gen = (char*)malloc(sizeof(char) * 4);
    if (!gen)
    {
        printf("Memory problem.");
        exit(1);
    }
    gen = "-BLU\0";
    PerfPush(&(*list), gen);
    PerfPush(&(*list), gen);
    PerfPush(&(*list),gen);
    gen = (char*)malloc(sizeof(char) * 4);
    if (!gen)
    {
        printf("Memory problem.");
        exit(1);
    }
    gen = "-JZ\0";
    PerfPush(&(*list), gen);
    PerfPush(&(*list), gen);
	PerfPush(&(*list),gen);
}

void PerfInfo(struct PerfNode* node)
{
    int i, j;
    for (i = 0, j = 0; node->genID[i] != '\0' ; i++)
	{
		if (node->genID[i] == '\n')
			continue;
		j += node->genID[i];
	}
	switch(j)
	{
		case 269: printf("%s\n", "Hip hop");break;
		case 326: printf("%s\n", "Electronic");break;
		case 272: printf("%s\n", "Blues");break;
		case 209: printf("%s\n", "Jazz");break;
	}
    printf("Name: %s", node->name);
    printf("Years: %s", node->year);
}

void SearchID(struct PerfList** list, char* ID)
{
    struct PerfNode* temp = (*list)->head;
    while (temp != NULL)
    {
        if (strcmp(temp->genID, ID) == 0)
        {
            PerfInfo(temp);
        }
        temp = temp->next;
    }
}

void SearchName(struct PerfList** list, char* name)
{
    struct PerfNode* temp = (*list)->head;
    while(temp != NULL)
    {
        if (strncmp(temp->name, name, 3) == 0)
        {
            PerfInfo(temp);
            break;
        }
        temp = temp->next;
    }
}

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
}

void GenresInfo()
{
    struct GenersList* geners;
	geners = ListCr();
	GenInfo(&geners, 1);
	GenInfo(&geners, 2);
	GenInfo(&geners, 3);
	GenInfo(&geners, 4);
}

void PerfomancesAction(int i, char* str)
{
    struct PerfList* perf;
	PerfCr(&perf);
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
    free(str);
}

void AlbumsAction(struct AlbList** list, struct User** user, char* str, int i)
{
        struct AlbList* search = NULL;
	printf("Please write the name of performer.");
	search = SearchByPerformer(list, str);
	AlbInfo(search->head);
	printf("\nDo you want to buy such album? (Yes/1, No/0)\n");
	if (i == 1)
	{
		search->head->bought++;
		(*user)->totalSum += search->head->price;
	}
	AlbInfo(search->head->next);
	printf("\nDo you want to buy such album? (Yes/1, No/0)\n");
	if (i == 1)
    	{
        	search->head->next->bought++;
        	(*user)->totalSum += search->head->next->price;
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
