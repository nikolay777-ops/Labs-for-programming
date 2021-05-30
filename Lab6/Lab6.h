#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct QueueNode
{
	int value;
	struct QueueNode *next;
	struct QueueNode *prev;
}QueueNode;

typedef struct Queue
{
	QueueNode* head;
	QueueNode* tail;
	int size;
}Queue;

typedef struct TreeNode
{
	struct TreeNode* leftChild;
	struct TreeNode* rightChild;
	struct TreeNode* parent;
	int data;
}TreeNode;

Queue* QueueCreate(Queue* q);

void QInit(Queue** q);

void QPush(struct Queue** q, int value);

int QPop(Queue **q);

void QClear(Queue **q);

int QTop(Queue **q);

void TreeInit(struct TreeNode** root);

void CreateNode(TreeNode** root, int value);

void BuildTree(struct TreeNode** root, struct TreeNode** newNode);

void GiveParent(struct TreeNode* node);

void Print(struct TreeNode** root);

void TraversePreorder(struct TreeNode** root);

void TraversePostorder(struct TreeNode** root);

void TClear(struct TreeNode** root);

