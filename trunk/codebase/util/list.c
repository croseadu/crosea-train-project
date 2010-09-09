#include "../include/my.h"
#include "../include/util.h"
#include "../include/list.h"

STATUS initList(LP_DOUBLE_LINK_LIST *ppList, unsigned int elementSize)
{
	*ppList = (LP_DOUBLE_LINK_LIST)malloc(sizeof(DOUBLE_LINK_LIST));
	if (NULL == *ppList)
	{
		Print(("Out Of Memory when allocate list head\n")) ;
		return ERROR;
	}
	
	(*ppList)->pStartNode = (LP_LIST_NODE)malloc(sizeof(LIST_NODE)+elementSize-1);
	if (NULL == (*ppList)->pStartNode)
	{
		Print(("Out Of Memory when allocate list pStartNode\n")) ;
		return ERROR;
	}

	(*ppList)->pStartNode->pNextNode = (*ppList)->pStartNode;
	(*ppList)->pStartNode->pPrevNode = (*ppList)->pStartNode;
	
	(*ppList)->elementSize = elementSize;
	
	return OK;
}	

void visitList(LP_DOUBLE_LINK_LIST pList, void (*fn)(void *pData))
{
	LP_LIST_NODE pIterNode;
	
	pIterNode = pList->pStartNode;
	while (pIterNode)
	{
		fn((void *)pIterNode->pData);
		
		pIterNode = pIterNode->pNextNode;	
	}

}


void destoryList(LP_DOUBLE_LINK_LIST pListHead)
{
	LP_NODE pIterNode = pListHead->pStartNode->pNextNode;
	LP_NODE pNextNode;
	
	while (pIterNode != pListHead->pStartNode)
	{
			pNextNode = pIterNode->pNextNode;
			free(pIterNode);
			pIterNode = pNextNode;
	}
	free(pIterNode);
	free(pListHead);
}

STATUS insertAfterNode(LP_DOUBLE_LINK_LIST pListHead,LP_LP_LIST_NODE pInsertPos, void *pData)
{
	LP_NODE pInsertNode;
	
	pInsertNode = (LP_LIST_NODE)malloc(sizeof(LIST_NODE)+elementSize-1);
	if (NULL == pInsertNode)
	{
		Print(("Out Of Memory when insert node to list\n")) ;
		return ERROR;
	}
	
	memcpy(pInsertNode->pData, pdata, pListHead->elementSize);
	
	pInsertNode->pNextNode = pInsertPos->pNextNode;
	pInsertNode->pPrevNode = pInsertPos;
	
	pInsertPos->pPrevNode->pNextNode = pInsertNode;
	pInsertNode->pNextNode->pPrevNode = pInsertNode;

	return OK;
}
STATUS insertBeforeNode(LP_DOUBLE_LINK_LIST pListHead,LP_LIST_NODE pInsertPos, void *pData)
{
	LP_NODE pInsertNode;
	
	pInsertNode = (LP_LIST_NODE)malloc(sizeof(LIST_NODE)+elementSize-1);
	if (NULL == pInsertNode)
	{
		Print(("Out Of Memory when insert node to list\n")) ;
		return ERROR;
	}
	
	memcpy(pInsertNode->pData, pdata, pListHead->elementSize);
	
	pInsertNode->pNextNode = pInsertPos;
	pInsertNode->pPrevNode = pInsertPos->pPrevNode;
	
	pInsertPos->pPrevNode->pNextNode = pInsertNode;
	pInsertNode->pNextNode->pPrevNode = pInsertNode;

	return OK;
}

STATUS insertToHead(LP_DOUBLE_LINK_LIST pListHead, void *pData)
{
	return insertAfterNode(pListHead, pListHead->pStartNode, pData);	
}

STATUS insertToTail(LP_DOUBLE_LINK_LIST pListHead, void *pData)
{
	return insertAfterNode(pListHead, pListHead->pStartNode->pPrevNode, pData);	
}

void deleteNode(LP_LIST_NODE pDeleteNode)
{
	pDeleteNode->pPrevNode->pNextNode = pDeleteNode->pNextNode;
	pDeleteNode->pNextNode->pPrevNode = pDeleteNode->pPrevNode;
	free(pDeleteNode);
}

