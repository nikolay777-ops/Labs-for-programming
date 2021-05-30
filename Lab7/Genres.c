#include "Genres.h"

long curPos = 0;

bool GenExists(GenersList* list, char* str)
{
	GenersNode* temp;
	for (temp = list->head; temp != NULL; temp = temp->next)
	{
		if (temp->ID == str)
			return true;
	}
	return false;
}

GenersNode* GenSearch(GenersList* list, char* str)
{
	GenersNode* temp;
	for (temp = list->head; temp != list->tail; temp = temp->next)
	{
		if (temp->ID == str)
		{
			return temp;
		}
	}
	return NULL;
}

GenersNode* GenCr(GenersNode* node)
{
	int i;
	node = (GenersNode*)malloc(sizeof(GenersNode));
	node->next = NULL;
	node->article = (char**)malloc(sizeof(char*) * 4);
	for (i = 0; i < 4; i++)
	{
		node->article[i] = (char*)malloc(sizeof(char) * 72);
	}
	return node;
}

void SetArticle(GenersNode* node, long* curPos)
{   
	FILE *pp;
    int i;
    if (!(pp = fopen("Article.txt", "r")))
    {
        printf("lox");
        exit(1);
    }
    else
    {
        fseek(pp, *curPos, 0);
        for (i = 0; i < 4; i++)
        {
			fgets(node->article[i], 71, pp);
			fflush(stdin);
        }
        *curPos = ftell(pp);
        fclose(pp);   
    }
}

void GenPush(GenersList** list, char* str)
{
	char* temp;
	int i;
	i = 0;
	if(!(*list))
	{
		*list = (GenersList*)malloc(sizeof(GenersList));
		(*list)->head = GenCr((*list)->head);
		(*list)->head->ID = str;
		SetArticle((*list)->head, &curPos);
		(*list)->tail = (*list)->head;
		(*list)->size++;
	}
	else
	{
		GenersNode* buf = NULL;
		GenersNode* help = (*list)->head;
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

GenersList* ListCr()
{
	FILE *fp;
	GenersList* geners;
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

void GenInfo(GenersList** geners, int num)
{
	GenersNode* temp;
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

void ClearAll(GenersList** list)
{
	int i, j;
	GenersNode* temp;
	i = 0; j = 0;
	temp = NULL;
	do
	{
		if (j >= 1)
			break;
		temp = (*list)->tail;
		for (i = 0; i < 4; i++)
		{
			free(temp->article[i]);
		}
		free(temp->article);
		free(temp->ID);
		(*list)->tail = (*list)->tail->prev;
		j++;
	}while(true);
	free(*list);
	*list = NULL;
}

int main()
{
   	GenersList* geners;
	geners = ListCr();
	GenInfo(&geners, 1);
	GenInfo(&geners, 2);
	GenInfo(&geners, 3);
	GenInfo(&geners, 4);
	ClearAll(&geners);
	return 0;
}
