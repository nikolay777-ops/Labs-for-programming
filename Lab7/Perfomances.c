#include "Perfomances.h"

struct PerfNode* NodeInit(struct PerfNode* node)
{
    node = (struct PerfNode*)malloc(sizeof(struct PerfNode));
    node->name = (char*)malloc(sizeof(char) * 21);
    node->year = (char*)malloc(sizeof(char) * 4);
    node->next = NULL;
    return node;
}

void AddInfo(struct PerfNode* node, char* ID, long *curPos)
{
    FILE *fp;
    char* temp;
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
        ((*list)->head) = NodeInit((*list)->head);
        (*list)->curPos = 0;
        AddInfo((*list)->head, ID, &((*list)->curPos));
        (*list)->size++;
    }
    else
    {
        struct PerfNode *temp, *buf;
        temp = (*list)->head;
        buf = NodeInit(buf);
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

struct PerfList* PerfCr(struct PerfList** list)
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

void PerfClear(struct PerfList** list)
{
    struct PerfNode* node = (*list)->head;
    while (node != NULL)
    {
        free(node->genID); node->genID = NULL;
        free(node->name); node->name = NULL;
        free(node->year); node->year = NULL;
        node = node->next;
    }
    free(*list); *list = NULL;
}
/*
int main()
{
    PerfList* list;
    char* gen;
    gen = (char*)malloc(sizeof(char) * 20);
    gen = "Kanye\0";
    list = PerfCr(&list);
    SearchID(&list, "-HHP");
    SearchName(&list, gen);
    PerfClear(&list);	
    free(gen);
    return 0;
}*/
