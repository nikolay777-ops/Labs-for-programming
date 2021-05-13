#include <stdio.h>
#include <stdlib.h>
#include "Lab6.h"
#include <assert.h>

void FirstTest()
{
	Queue *queueForTree;
	TreeNode *root;
	queueForTree = NULL;
	root = NULL;
	QPush(&queueForTree, 15);
	QPush(&queueForTree, 11);
	QPush(&queueForTree, 9);
	QPush(&queueForTree, 13);
	QPush(&queueForTree, 20);
	QPush(&queueForTree, 18);
	QPush(&queueForTree, 22);
	while(queueForTree->size != 0)
	{
		TreeNode *temp = CreateNode(QTop(&queueForTree));
		BuildTree(&root, &temp);
		QPop(queueForTree);
	}
	TraversePreorder(&root);
	TraversePostorder(&root);
	TraversePreorder(&root);
	QClear(queueForTree);
	TClear(&root);
	assert(queueForTree->head == NULL);
	assert(queueForTree->tail == NULL);
	assert(root == NULL);
}

void SecondTest()
{
	TreeNode *root, *temp;
	root = NULL;
	temp = NULL;
	temp = (TreeNode*)malloc(sizeof(TreeNode));
	temp->data = 10;
	BuildTree(&root, &temp);
	temp = (TreeNode*)malloc(sizeof(TreeNode));
	temp->data = 18;
	BuildTree(&root, &temp);
	temp = (TreeNode*)malloc(sizeof(TreeNode));
	temp->data = 8;
	BuildTree(&root, &temp);
	temp = (TreeNode*)malloc(sizeof(TreeNode));
	temp->data = 3;
	BuildTree(&root, &temp);
	temp = (TreeNode*)malloc(sizeof(TreeNode));
	temp->data = 9;
	BuildTree(&root, &temp);
	temp = (TreeNode*)malloc(sizeof(TreeNode));
	temp->data = 26;
	BuildTree(&root, &temp);
	temp = (TreeNode*)malloc(sizeof(TreeNode));
	temp->data = 15;
	BuildTree(&root, &temp);
	temp = NULL;
	TraversePreorder(&root);
	TraversePostorder(&root);
	printf("\n");
	TraversePreorder(&root);
	TClear(&root);
	assert(temp == NULL);
	assert(root == NULL);
}

int main()
{
	FirstTest();
	SecondTest();
	printf("Tests are done!");
	return 0;
}