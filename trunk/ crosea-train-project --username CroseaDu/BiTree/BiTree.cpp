// BiTree.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "my.h"

HRESULT buildTree(const char *,int *pIndex,LPBITREE * ppTreeNode);
HRESULT preOrderTraverseTree(LPBITREE pRootNode);
HRESULT inOrderTraverseTree(LPBITREE pRootNode);
HRESULT postOrderTraverseTree(LPBITREE pRootNode);
HRESULT preOrderTraverseTreeUseStack(LPBITREE pRootNode, LPDATASTACK pDataStack);
HRESULT inOrderTraverseTreeUseStack(LPBITREE pRootNode, LPDATASTACK pDataStack);
HRESULT postOrderTraverseTreeUseStack(LPBITREE pRootNode, LPDATASTACK pDataStack);

int main(int argc, char* argv[])
{
	char inputArray[100] = {0},c;
	int index = 0,i = 0;
	LPBITREE pTreeNode = NULL;
	LPDATASTACK pDataStack = NULL;

	printf("input a tree in preorder string\n");
	c = getchar();
	while(c!= '\n')
	{
		inputArray[i++] = c;
		c =getchar();
	}	
	
	buildTree(inputArray, &index,&pTreeNode);
	preOrderTraverseTree(pTreeNode);
	putchar('\n');
	inOrderTraverseTree(pTreeNode);
	putchar('\n');
	postOrderTraverseTree(pTreeNode);
	putchar('\n');
	initDataStack(&pDataStack);
	preOrderTraverseTreeUseStack(pTreeNode, pDataStack);
	putchar('\n');
	inOrderTraverseTreeUseStack(pTreeNode, pDataStack);
	putchar('\n');
	destroyDataStack(pDataStack);
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
HRESULT preOrderTraverseTree(LPBITREE pRootNode)
{
	if (!pRootNode)
		return S_OK;
	printf("%3c",pRootNode->data);
	preOrderTraverseTree(pRootNode->pLeftChild);
	preOrderTraverseTree(pRootNode->pRightChild);
	return S_OK;
}
HRESULT inOrderTraverseTree(LPBITREE pRootNode)
{
	if (!pRootNode)
		return S_OK;
	inOrderTraverseTree(pRootNode->pLeftChild);
	printf("%3c",pRootNode->data);
	inOrderTraverseTree(pRootNode->pRightChild);
	return S_OK;
}
HRESULT postOrderTraverseTree(LPBITREE pRootNode)
{
	if (!pRootNode)
		return S_OK;

	postOrderTraverseTree(pRootNode->pLeftChild);
	postOrderTraverseTree(pRootNode->pRightChild);
	printf("%3c",pRootNode->data);
	return S_OK;
}

HRESULT preOrderTraverseTreeUseStack(LPBITREE pRootNode, LPDATASTACK pDataStack)
{
	LPBITREE pTempNode = NULL;
	
	pushDataStack(pDataStack,pRootNode);
	while(!isDataStackEmpty(pDataStack))
	{
		popDataStack(pDataStack, &pTempNode);
		printf("%3c",pTempNode->data);
		if (pTempNode->pRightChild)
			pushDataStack(pDataStack,pTempNode->pRightChild);
		if (pTempNode->pLeftChild)
			pushDataStack(pDataStack,pTempNode->pLeftChild);		
	}
	return S_OK;
}
HRESULT inOrderTraverseTreeUseStack(LPBITREE pRootNode, LPDATASTACK pDataStack)
{
	LPBITREE pTempNode = NULL;
	while(pRootNode || !isDataStackEmpty(pDataStack))
	{
		if (pRootNode)
		{
			pushDataStack(pDataStack, pRootNode);
			pRootNode = pRootNode->pLeftChild;	
		}
		else
		{
			popDataStack(pDataStack, &pRootNode);
			printf("%3c",pRootNode->data);
			pRootNode = pRootNode->pRightChild;	
		}
	}
	
	
	
	return S_OK;
}
HRESULT postOrderTraverseTreeUseStack(LPBITREE pRootNode, LPDATASTACK pDataStack)
{
	LPBITREE pTempNode = NULL;
	pTempNode = pRootNode;
	while(pTempNode || !isDataStackEmpty(pDataStack))
	{
		if (pTempNode)
		{
			if (!pTempNode->pLeftChild && !pTempRightChild)
			{
				printf("%3c",pRootNode->data);			
			}
			else if (!pTempNode->pRightChild)
			{
	
			}
			else
			{
			
			}
		}

	}
	
	return S_OK;
}
