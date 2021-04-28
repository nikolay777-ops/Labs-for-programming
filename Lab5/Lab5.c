#include "Lab5.h"

static int timeToWork;
static int MaxWait;
static int MaxBuyers;

void Init(struct Queue* q)
{
	q->head= NULL;
	q->tail = NULL;
	q->size = 0;
}

void Push(struct Queue *q, int value, int timeToCashBox, int timeToService)
{
	if (q->head == NULL)
	{
		struct Node* current = (struct Node*)malloc(sizeof(struct Node));
		current->value = value;
		current->timeToCashBox = timeToCashBox;
		current->timeToService = timeToService;
		q->head = current;
		q->size++;
		return;
	}
	else
	{
		struct Node* temp = q->head;
		struct Node* current = (struct Node*)malloc(sizeof(struct Node));
		while(temp->next != NULL)
		temp = temp->next;
		temp->next = current;
		current->prev = temp;
		current->value = value;
		current->timeToCashBox = timeToCashBox
		+ current->prev->timeToCashBox + current->prev->timeToService;
		current->timeToService = timeToService;
		current->next = NULL;
		q->tail = current;
		q->size++;
	}
}

void Pop(struct Queue *q)
{
	struct Node* temp;
	if(q->head == NULL) return;
	temp = q->head;
	q->head = q->head->next;
	if(q->head == NULL)
	{
        q->tail = NULL;
	}
	free(temp);
	q->size--;
}

void Clear(struct Queue *q)
{		
	while(q->head != NULL && q->tail != NULL)
	{
		Pop(q);
	}	
}
int Top(struct Queue *q)
{
	return q->head->value;
}

void Info(struct Queue *q)
{
	int comparator = 0;
	while(q->head != NULL && q->tail != NULL)
	{
		comparator += q->head->timeToCashBox + q->head->timeToService;
		if(comparator >= timeToWork) break;
		if(q->head->timeToCashBox + q->head->timeToService > MaxWait)
		{
			MaxWait = q->head->timeToCashBox + q->head->timeToService;
		}
		printf("*********************************************************\n");
		printf(" | %d | Time to cashbox: %d, time to service: %d\n", Top(q), q->head->timeToCashBox, q->head->timeToService);
		printf("*********************************************************\n");
		MaxBuyers++;
		Pop(q);
	}
	if (comparator <= timeToWork)
	{
		printf("All buyers were serviced!\n");
	}
	else if(q->size > 0)
	{
		printf("That quality of buyers weren't serviced: %d\n", q->size);
	}
	Clear(q);
}

#ifndef TESTING

int main()
{
	int i;
	int qualityOfBuyers;
	struct Queue* buyers;
	srand(time(NULL));
	qualityOfBuyers = rand() % 20;
	buyers = (struct Queue*)malloc(sizeof(struct Queue));
	if (!buyers)
	{
		printf("Smth errors with memory.");
		exit(1);
	}
	Init(buyers);
	timeToWork = rand() % 300;
	for (i = 0; i < qualityOfBuyers; i++)
	{
		if(buyers->head == NULL && buyers->tail == NULL)
		{
			Push(buyers, i+1, 0, rand() % 10 + 5);
		}
		else
		{
			Push(buyers, i+1, rand() % 10 + 5, rand() % 10 + 5);
		}
	}
	Info(buyers);
	printf("Total: %d", qualityOfBuyers);
	printf("Time to work: %d\n", timeToWork);
	printf("Max Wait: %d\n", MaxWait);
	printf("Max Buyers: %d\n", MaxBuyers);
	free(buyers);
	return 0;
}

#endif