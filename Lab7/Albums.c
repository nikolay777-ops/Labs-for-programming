#include "Albums.h"

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
	long pos = 0;
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
		pos = ftell(fp);
		free(temp);
		fclose(fp);
	}
	return pos;
}

void CompPush(struct CompList** list, long* pos)
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
			temp = (char*)malloc(sizeof(char) * 37);
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

void AlbPush(struct AlbList** list, char* str, long* pos)
{
	FILE *fp;
	char* temp;
	struct AlbNode* temporary = NULL;
	int i = 0;
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
			(*list)->head->next = NULL;
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
			temp = (char*)malloc(sizeof(char) * 37);
			do
			{
				temp = (char*)malloc(sizeof(char) * 37);
			}while(StrSize(temp) != 0);
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
	free(temp);
}

void Alb(struct AlbList** list, char* str)
{
	FILE *pf;
	long pos = 0;
	char* temp = (char*)malloc(sizeof(char) * 37);
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
	free(temp);
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

void ClearCompose(struct CompList** list)
{
   	struct CompNode* temp = (*list)->head;
	if (!(*list)) return;
	while(temp != NULL)
	{
		free(temp->name); temp->name = NULL;
		temp = temp->next;
	}
	free(*list); *list = NULL;
}

void ClearAlb(struct AlbList** list)
{
    	struct AlbNode* temp = (*list)->head;
	if (!(*list)) return;
	while (temp != NULL)
	{
		ClearCompose(&(temp->compos));
		free(temp->name); temp->name = NULL;
		free(temp->perfID); temp->perfID = NULL;
		temp = temp->next;
	}
    free(*list); *list = NULL;
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
	int i = 0;
	if (num / 10 == 0)
	{
		str[0] = num + '0';
		return str;
	}
	while(num / 10 != 0)
	{
		str[i] = (num % 10) + '0';
		num /= 10;
		i++;
	}
	return str;
}

/*
int main()
{
	AlbList* albs = NULL;
	AlbList* search = NULL;
	AlbNode* nodeSearch = NULL;
	AlbInit(&search);
	AlbInit(&albs);
	AllAlbums(&albs);
	nodeSearch = SearchByAlbum(&search, "Kamikaze");
	search = SearchByPerformer(&albs, "Louis Armstrong");
	ClearAlb(&albs);
	ClearAlb(&search);
	return 0;
}
*/
