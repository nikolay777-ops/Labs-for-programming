#include "Lab6.h"

Queue* QueueCreate(Queue* q)
{
	q = (Queue*)malloc(sizeof(Queue));
	return q;
}

void QInit(Queue** q)
{
	(*q)->head = NULL;
	(*q)->tail = NULL;
	(*q)->size = 0;
}

void QPush(struct Queue **q, int value)
{
	QueueNode* current = (struct QueueNode*)malloc(sizeof(struct QueueNode));
	if (*q == NULL)
	{
		*q = (Queue*)malloc(sizeof(Queue));
		current->value = value;
		(*q)->head = current;
		(*q)->tail = current;
		(*q)->size++;
	}
	else
	{
		QueueNode* temp = (*q)->head;
		while(temp->next != NULL)
		temp = temp->next;
		temp->next = current;
		current->prev = temp;
		current->value = value;
		current->next = NULL;
		(*q)->tail = current;
		(*q)->size++;
	}
}

void QPop(Queue *q)
{
	struct QueueNode* temp;
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

void QClear(Queue *q)
{
	while(q->head != NULL)
	QPop(q);
}
int QTop(Queue **q)
{
	return (*q)->head->value;
}

void TreeInit(struct TreeNode** root)
{
	(*root)->leftChild = NULL;
	(*root)->rightChild = NULL;
	(*root)->parent = NULL;
	(*root)->data = 0;
}

TreeNode* CreateNode(int value)
{
	TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
	node->leftChild = node->rightChild = NULL;
	node->data = value;
	return node;
}

void BuildTree(TreeNode** root, TreeNode** newNode)
{
	if (*root == NULL)
	{
		*root = *newNode;
		return;
	}
	if ((*root)->data > (*newNode)->data)
	{
		if (!(*root)->leftChild)
		{
			(*root)->leftChild = *newNode;
			(*root)->leftChild->parent = *root;
		}
		else
		{
			BuildTree(&(*root)->leftChild, &(*newNode));
		}
	}
	else
	{
		if ((*root)->data < (*newNode)->data)
		{
			if (!(*root)->rightChild)
			{
				(*root)->rightChild = *newNode;
				(*root)->rightChild->parent = *root;
			}
			else
			{
				BuildTree(&(*root)->rightChild, &(*newNode));
			}
		}
	}
}

void GiveParent(TreeNode* node)
{
	if(node->leftChild != NULL)
	node->leftChild->parent = node;
	if(node->rightChild != NULL)
	node->rightChild->parent = node;
}

void Print(TreeNode** root)
{
	if (*(root) == NULL)
		return;
	else
		printf("%d\n", (*root)->data);
}

void TraversePreorder(TreeNode** root)
{
	if ((*root) == NULL)
		return;
	else
	{
		Print(&(*root));
		TraversePreorder(&(*root)->leftChild);
		TraversePreorder(&(*root)->rightChild);
	}
}

void TraversePostorder(TreeNode** root)
{
	if((*root)->leftChild)
	TraversePostorder(&(*root)->leftChild);
	if((*root)->rightChild)
	TraversePostorder(&(*root)->rightChild);
	if((*root)->rightChild == NULL && (*root)->leftChild == NULL
	&& (((*root)->parent->leftChild && ((*root)->parent->rightChild))))
	{
		free((*root));
		(*root) = NULL;
	}
}

void TClear(TreeNode **root)
{
	if (!(*root))
		return;
	TClear(&(*root)->leftChild);
	TClear(&(*root)->rightChild);
	free((*root));
	*root = NULL;
}

#ifndef TESTING
int main()
{
	Queue *queueForTree;
	struct TreeNode *root;
	root = NULL;
    queueForTree = NULL;
	QPush(&queueForTree, 15);
	QPush(&queueForTree, 11);
	QPush(&queueForTree, 9);
	QPush(&queueForTree, 13);
	QPush(&queueForTree, 20);
	QPush(&queueForTree, 18);
	QPush(&queueForTree, 22);
	while(queueForTree->size != 0)
	{
		struct TreeNode *temp = CreateNode(QTop(&queueForTree));
		BuildTree(&root, &temp);
		QPop(queueForTree);
	}
	TraversePreorder(&root);
	TraversePostorder(&root);
	printf("\n");
	TraversePreorder(&root);
	QClear(queueForTree);
	TClear(&root);
	return 0;
}
#endif