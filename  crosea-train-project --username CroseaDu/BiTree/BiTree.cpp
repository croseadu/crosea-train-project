// BiTree.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#define S_OK 0
#define S_FALSE 1
#define HRESULT int

typedef struct bitree{
	char data;
	struct bitree * pLeftChild;
	struct bitree * pRightChild;
}BITREE,*LPBITREE;

HRESULT buildTree(const char *,int *pIndex,LPBITREE * ppTreeNode);
HRESULT preOrderTraverseTree(LPBITREE pRootNode);
HRESULT preOrderTraverseTree(LPBITREE pRootNode);
HRESULT preOrderTraverseTree(LPBITREE pRootNode);
HRESULT preOrderTraverseTreeUseStack(LPBITREE pRootNode);
HRESULT preOrderTraverseTreeUseStack(LPBITREE pRootNode);
HRESULT preOrderTraverseTreeUseStack(LPBITREE pRootNode);

int main(int argc, char* argv[])
{
	char inputArray[100] = {0};
	int index = 0;
	LPBITREE pTreeNode = NULL;

	printf("input a tree in preorder string\n");
	scanf("%s",inputArray);

	buildTree(inputArray, &index,&pTreeNode);
	preOrderTraverseTree(pTreeNode);
	return 0;
}
HRESULT buildTree(const char * inputArray,int *pIndex,LPBITREE * ppTreeNode)
{
	LPBITREE tempNode = NULL;
	if (inputArray[*pIndex] == ' ')
	{
		(*pIndex)++;
		*ppTreeNode = NULL;
		return S_OK;
	}

	tempNode = (LPBITREE)malloc(sizeof(BITREE));
	if (!tempNode)
	{
		printf("out of memory");
		return S_FALSE;
	}
	tempNode->data = inputArray[*pIndex];
	(*pIndex)++;
	buildTree(inputArray, pIndex,&tempNode->pLeftChild);
	buildTree(inputArray, pIndex,&tempNode->pRightChild);
	*ppTreeNode = tempNode;
	return S_OK;
	
}

