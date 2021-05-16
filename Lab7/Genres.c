#include "Genres.h"

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
	node = (GenersNode*)malloc(sizeof(GenersNode));
	node->article = (char**)malloc(sizeof(char*) * 4);
	return node;
}

void SetArticle(GenersNode** node)
{
	FILE *pf;
	char* temp;
	char* help;
	int i;
	temp = NULL;
	i = 0;
	if (!(pf = fopen("Article.txt", "r")))
	{
		printf("Error with opening Article.txt\n");
	}
	else
	{
		help = (char*)malloc(sizeof(char) * 72);
		fgets(help, 72, pf);
		while(strncmp(help, (*node)->ID, 3) != 0)
		{
			fflush(stdin);
			fgets(help, 72, pf);
		}
		do
		{
			if (i == 4)
				break;
			fflush(stdin);
			temp = (char*)malloc(sizeof(char) * 71);
			fgets(temp, 71, pf);
			(*node)->article[i] = temp;
			i++;
		}while(temp[0] != '-');
	}
	free(help);
	help = "";
	fclose(pf);
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
		SetArticle(&((*list)->head));
		(*list)->tail = (*list)->head;
		(*list)->size++;
	}
	else
	{
		if (!(GenExists(*list, str)))
		{
			GenersNode* buf = GenCr(buf);
			GenersNode* temp = (*list)->head;
			buf->ID = str;
			SetArticle(&buf);
			while(temp->next != NULL)
			{
				temp = temp->next;
			}
			temp->next = buf;
			buf->prev = temp;
			(*list)->tail = buf;
			(*list)->size++;
		}
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
		do
		{
			i++;
			if (i > 4)
				break;
			str = (char*)malloc(sizeof(char) * 7);
			fgets(str, 7, fp);
			GenPush(&geners, str);
			fflush(stdin);
		} while (StrSize(str) != 0);
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
		if (j >= 4)
			break;
		temp = (*list)->tail;
		for (i = 0; i < 4; i++)
		{
			free(temp->article[i]);
			temp->article[i] = NULL;
		}
		free(temp->ID);
		temp->ID = NULL;
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
	GenInfo(&geners,1);
	GenInfo(&geners,2);
	GenInfo(&geners,3);
	GenInfo(&geners,4);
	ClearAll(&geners);
	return 0;
}