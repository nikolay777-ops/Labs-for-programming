#include <stdio.h>
#include <stdlib.h>
#include "Lab6.h"
#include <assert.h>

void FirstTest()
{
	Queue *queueForTree = NULL;
	TreeNode *root = NULL;
	queueForTree = (Queue*)malloc(sizeof(Queue));
	assert(queueForTree != NULL);
	queueForTree->head = NULL;
	queueForTree->tail = NULL;
	QPush(&queueForTree, 15);
	QPush(&queueForTree, 11);
	QPush(&queueForTree, 9);
	QPush(&queueForTree, 13);
	QPush(&queueForTree, 20);
	QPush(&queueForTree, 18);
	QPush(&queueForTree, 22);
	while(queueForTree->head != NULL)
	{
		TreeNode* temp = NULL;
		CreateNode(&temp, QPop(&queueForTree));
		BuildTree(&root, &temp);
	}
	TraversePostorder(&root);
	QClear(&queueForTree);
	TClear(&root);
	assert(queueForTree->head == NULL);
	assert(queueForTree->tail == NULL);
	assert(root == NULL);
}

void SecondTest()
{
	TreeNode *tree, *temp;
	temp = NULL;
	tree = NULL;
	temp = (TreeNode*)malloc(sizeof(TreeNode));
	temp->data = 10;
	temp->leftChild = NULL;
	temp->rightChild = NULL;
	BuildTree(&tree, &temp);
	temp = (TreeNode*)malloc(sizeof(TreeNode));
	temp->leftChild = NULL;
	temp->rightChild = NULL;
	temp->data = 18;
	BuildTree(&tree, &temp);
	temp = (TreeNode*)malloc(sizeof(TreeNode));
	temp->leftChild = NULL;
	temp->rightChild = NULL;
	temp->data = 8;
	BuildTree(&tree, &temp);
	temp = (TreeNode*)malloc(sizeof(TreeNode));
	temp->leftChild = NULL;
	temp->rightChild = NULL;
	temp->data = 3;
	BuildTree(&tree, &temp);
	temp = (TreeNode*)malloc(sizeof(TreeNode));
	temp->leftChild = NULL;
	temp->rightChild = NULL;
	temp->data = 9;
	BuildTree(&tree, &temp);
	temp = (TreeNode*)malloc(sizeof(TreeNode));
	temp->leftChild = NULL;
	temp->rightChild = NULL;
	temp->data = 26;
	BuildTree(&tree, &temp);
	temp = (TreeNode*)malloc(sizeof(TreeNode));
	temp->leftChild = NULL;
	temp->rightChild = NULL;
	temp->data = 15;
	BuildTree(&tree, &temp);
	TraversePreorder(&tree);
	printf("\n");
	TraversePostorder(&tree);
	TraversePreorder(&tree);
	TClear(&tree);
	temp = NULL;
	assert(temp == NULL);
	assert(tree == NULL);
}

int main()
{
	FirstTest();
	SecondTest();
	printf("Tests are done!");
	return 0;
}