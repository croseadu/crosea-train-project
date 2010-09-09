#include "../include/my.h"
#include "../include/util.h"
#include "../include/stack.h"
#include "../include/queue.h"

typedef struct _TREE_NODE
{
	char data;
	struct _TREE_NODE *pLeftChild;
	struct _TREE_NODE *pRightChild;
}TREE_NODE, *LP_TREE_NODE;


void visit(LP_TREE_NODE pTreeNode)
{
	if (pTreeNode)
	{
		putchar(pTreeNode->data);
	}
}

void destory(LP_TREE_NODE pTreeNode)
{
	if (pTreeNode)
	{
		free(pTreeNode);
	}
}

void preOrderTraverse(LP_TREE_NODE pTreeNode, void (*pFn)(LP_TREE_NODE));
void postOrderTraverse(LP_TREE_NODE pTreeNode, void (*pFn)(LP_TREE_NODE));
void inOrderTraverse(LP_TREE_NODE pTreeNode, void (*pFn)(LP_TREE_NODE));

void preOrderUseStack(LP_TREE_NODE pTreeNode, void (*pFn)(LP_TREE_NODE), LP_STACK pStack);
void inOrderUseStack(LP_TREE_NODE pTreeNode, void (*pFn)(LP_TREE_NODE), LP_STACK pStack);
void hierarchyTraverse(LP_TREE_NODE pRootNode,void (*pFn)(LP_TREE_NODE), LP_QUEUE pQueue);
void buildTree(LP_TREE_NODE *ppTreeNode, char *inputBuffer, int *pIndex)
{
	LP_TREE_NODE pTempNode = NULL;

	if (inputBuffer[*pIndex] == '#')
	{
		*ppTreeNode = NULL;
		(*pIndex)++;
		return;
	}

	pTempNode = (LP_TREE_NODE)malloc(sizeof(TREE_NODE));
	if (NULL == pTempNode)
	{
		Print(("Out Of Memory when allocate temp tree node in buildTree\n"));
		exit(-1);
	}

	pTempNode->data = inputBuffer[(*pIndex)++];
	buildTree(&pTempNode->pLeftChild, inputBuffer, pIndex);
	buildTree(&pTempNode->pRightChild, inputBuffer, pIndex);
	*ppTreeNode = pTempNode;
}



int main()
{
	LP_TREE_NODE pRootNode = NULL;
	LP_STACK pStack = NULL;
	LP_QUEUE pQueue = NULL;
	int curIndex, maxElements;
	char *inputBuffer, c;

	inputBuffer = (char *)malloc(sizeof(char) * INIT_BUFFER_SIZE);
	if (NULL == inputBuffer)
	{
		Print(("Out of Memory when allocate inputBuffer"));
		exit(-1);
	}	
	maxElements = INIT_BUFFER_SIZE;

	c = getchar();
	curIndex = 0;
	while (c != '\n')
	{
		inputBuffer[curIndex++] = c;
		c = getchar();

		if (curIndex >= maxElements - 1)
		{
			maxElements += INCRE_BUFFER_SIZE;
			inputBuffer = (char *)realloc(inputBuffer, sizeof(char) * maxElements);
			if (inputBuffer == NULL)
			{
				Print(("Out of Memory when enlarge input buffer"));
				exit(-1);
			}
		}
	}
	inputBuffer[curIndex] = '\0';

	curIndex = 0;
	buildTree(&pRootNode, inputBuffer, &curIndex);
	
	printf("\npreOrder :");
	preOrderTraverse(pRootNode, visit);	
	printf("\nInOrder :");
	inOrderTraverse(pRootNode, visit);	
	printf("\npostOrder :");
	postOrderTraverse(pRootNode, visit);

	/******************************************/
	createStack(&pStack, sizeof(LP_TREE_NODE));
	printf("\npreOrderUseStack :");
	preOrderUseStack(pRootNode, visit, pStack);
	printf("\ninOrderUseStack :");
	inOrderUseStack(pRootNode, visit, pStack);

	destoryStack(pStack);
	/******************************************/

	/******************************************/
	createQueue(&pQueue, sizeof(LP_TREE_NODE), curIndex);

	printf("\nhierarchyTraverse :");
	hierarchyTraverse(pRootNode, visit, pQueue);
	destoryQueue(pQueue);
	/******************************************/

	// destory Tree
	postOrderTraverse(pRootNode, destory);
	free(inputBuffer);
	
}



void preOrderTraverse(LP_TREE_NODE pTreeNode, void (*pFn)(LP_TREE_NODE))
{
	pFn(pTreeNode);
	if (pTreeNode->pLeftChild)
		preOrderTraverse(pTreeNode->pLeftChild, pFn);
	if (pTreeNode->pRightChild)
        	preOrderTraverse(pTreeNode->pRightChild, pFn);
}

void inOrderTraverse(LP_TREE_NODE pTreeNode, void (*pFn)(LP_TREE_NODE))
{
	if (pTreeNode->pLeftChild)
		inOrderTraverse(pTreeNode->pLeftChild, pFn);
	pFn(pTreeNode);
	if (pTreeNode->pRightChild)
		inOrderTraverse(pTreeNode->pRightChild, pFn);
}
void postOrderTraverse(LP_TREE_NODE pTreeNode, void (*pFn)(LP_TREE_NODE))
{
	if (pTreeNode->pLeftChild)
		postOrderTraverse(pTreeNode->pLeftChild, pFn);
	if (pTreeNode->pRightChild)
		postOrderTraverse(pTreeNode->pRightChild, pFn);	
	pFn(pTreeNode);
}

void preOrderUseStack(LP_TREE_NODE pRootNode, void (*pFn)(LP_TREE_NODE), LP_STACK pStack)
{
	LP_TREE_NODE pTreeNode;

	push(pStack, &pRootNode);
	while (!isStackEmpty(pStack))
	{
		pop(pStack, &pTreeNode);
		visit(pTreeNode);
		if (pTreeNode->pRightChild)
			push(pStack, &pTreeNode->pRightChild);
		if (pTreeNode->pLeftChild)
			push(pStack, &pTreeNode->pLeftChild);
	}
}

void inOrderUseStack(LP_TREE_NODE pRootNode, void (*pFn)(LP_TREE_NODE), LP_STACK pStack)
{
	LP_TREE_NODE pTreeNode = pRootNode;
	while (pTreeNode || !isStackEmpty(pStack))
	{
		if(pTreeNode)
		{
			while(pTreeNode)
			{
				push(pStack, &pTreeNode);
				pTreeNode = pTreeNode->pLeftChild;
			}
		}
		else
		{
			pop(pStack, &pTreeNode);
			visit(pTreeNode);
			pTreeNode = pTreeNode->pRightChild;
		}
	}

}

void postOrderUseStack(LP_TREE_NODE pRootNode, void (*pFn)(LP_TREE_NODE), LP_STACK pStack)
{
	LP_TREE_NODE pIterNode = NULL;

	push(pStack, &pRootNode);
	while (!isStackEmpty(pStack))
	{
	}
}

void hierarchyTraverse(LP_TREE_NODE pRootNode,void (*pFn)(LP_TREE_NODE), LP_QUEUE pQueue)
{
	LP_TREE_NODE pIterNode;

	insertToTail(pQueue,(char *) &pRootNode);

	while(!isQueueEmpty(pQueue))
	{
		getFromHead(pQueue, &pIterNode);
		pFn(pIterNode);
		if (pIterNode->pLeftChild)
			insertToTail(pQueue, (char *)&pIterNode->pLeftChild);
		if (pIterNode->pRightChild)
			insertToTail(pQueue, (char *)&pIterNode->pRightChild);
	}
}



