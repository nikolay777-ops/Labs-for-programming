#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

typedef struct Node
{
	int timeToCashBox;
	int timeToService;
	int value;
	struct Node *next;
	struct Node *prev;
}Node;

typedef struct Queue
{
	struct Node* head;
	struct Node* tail;
	int size;
}Queue;

void Init(struct Queue* q);

void Push(struct Queue *q, int value, int timeToCashBox, int timeToService);

void Pop(struct Queue *q);

void Clear(struct Queue *q);

int Top(struct Queue *q);

void Info(struct Queue *q);