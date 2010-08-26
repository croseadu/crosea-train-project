#include "../include/my.h"
#include "../include/util.h"


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
}



int main()
{
	LP_TREE_NODE pRootNode = NULL;
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
	
	putchar('\n');
	preOrderTraverse(pRootNode, visit);	
	
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

void postOrderTraverse(LP_TREE_NODE pTreeNode, void (*pFn)(LP_TREE_NODE))
{
	if (pTreeNode->pLeftChild)
		postOrderTraverse(pTreeNode->pLeftChild, pFn);
	if (pTreeNode->pRightChild)
		postOrderTraverse(pTreeNode->pRightChild, pFn);	
	pFn(pTreeNode);
}
