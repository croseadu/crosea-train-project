#include "../include/singleList.h"


STATUS createSingleList(LP_SINGLE_LIST_NODE *ppListHead, unsigned int elementSize)
{
	LP_SINGLE_LIST_NODE pListHead = NULL;

	pListHead = (LP_SINGLE_LIST_NODE)malloc(sizeof(SINGLE_LIST_NODE));
	if (NULL == pListHead)
        {
		printf("Out of Memory in line %d Function %s File %s", __LINE__, __FUNCTION__, __FILE__);
		return OVERFLOW;
	}

	pListHead->pData = (char *)elementSize;
	pListHead->pNext = NULL;

	*ppListHead = pListHead;
	return OK;
}

void destroySingleList(LP_SINGLE_LIST_NODE pListHead)
{
	LP_SINGLE_LIST_NODE pNextNode, pIterNode;
	
	assert(pListHead != NULL);
	pIterNode = pListHead->pNext;
	free(pListHead);

	while(pIterNode)
	{
		pNextNode = pIterNode->pNext;
		free(pIterNode->pData);
		free(pIterNode);

		pIterNode = pNextNode;
	}		

}

STATUS insertToHead(LP_SINGLE_LIST_NODE pListHead, void * pData)
{
	int elementSize;
	LP_SINGLE_LIST_NODE pNode = NULL;

	assert(pListHead != NULL);

	elementSize = (unsigned int)pListHead->pData;
	pNode = (LP_SINGLE_LIST_NODE)malloc(sizeof(SINGLE_LIST_NODE));
	if (NULL == pNode)
	{
		printf("Out of Memory in line %d Function %s File %s", __LINE__, __FUNCTION__, __FILE__);
		return OVERFLOW;
	}

	pNode->pData = (char *)malloc(elementSize);
	if (NULL == pNode->pData)
	{
		free(pNode);
		printf("Out of Memory in line %d Function %s File %s", __LINE__, __FUNCTION__, __FILE__);
		return OVERFLOW;
	}

	memcpy(pNode->pData, (char *)pData, elementSize);
	pNode->pNext = pListHead->pNext;
	pListHead->pNext = pNode;

	return OK;
}

STATUS insertToTail(LP_SINGLE_LIST_NODE pListHead, void * pData)
{
	int elementSize;
	LP_SINGLE_LIST_NODE pNode = NULL, pInsertPos = NULL;

	assert(pListHead != NULL);

	elementSize = (unsigned int)pListHead->pData;
	pNode = (LP_SINGLE_LIST_NODE)malloc(sizeof(SINGLE_LIST_NODE));
	if (NULL == pNode)
	{
		printf("Out of Memory in line %d Function %s File %s", __LINE__, __FUNCTION__, __FILE__);
		return OVERFLOW;
	}

	pNode->pData = (char *)malloc(elementSize);
	if (NULL == pNode->pData)
	{
		free(pNode);
		printf("Out of Memory in line %d Function %s File %s", __LINE__, __FUNCTION__, __FILE__);
		return OVERFLOW;
	}

	memcpy(pNode->pData, (char *)pData, elementSize);
	
	pInsertPos = pListHead;
	while(pInsertPos->pNext != NULL)
		pInsertPos = pInsertPos->pNext;

	pInsertPos->pNext = pNode;

	return OK;
}


STATUS insertToList(LP_SINGLE_LIST_NODE pListHead, void * pData, LP_SINGLE_LIST_NODE pInsertPos, BOOL bIsBefore)
{
	int elementSize;
	LP_SINGLE_LIST_NODE pNode = NULL, pInsertPrev = NULL;

	assert(pListHead != NULL);

	elementSize = (unsigned int)pListHead->pData;
	pNode = (LP_SINGLE_LIST_NODE)malloc(sizeof(SINGLE_LIST_NODE));
	if (NULL == pNode)
	{
		printf("Out of Memory in line %d Function %s File %s", __LINE__, __FUNCTION__, __FILE__);
		return OVERFLOW;
	}

	pNode->pData = (char *)malloc(elementSize);
	if (NULL == pNode->pData)
	{
		free(pNode);
		printf("Out of Memory in line %d Function %s File %s", __LINE__, __FUNCTION__, __FILE__);
		return OVERFLOW;
	}

	memcpy(pNode->pData, (char *)pData, elementSize);

	if (bIsBefore)
	{
		pInsertPrev = pListHead;
		while(pInsertPrev && pInsertPrev->pNext != pInsertPos)
			pInsertPrev = pInsertPrev->pNext;

		assert(pInsertPrev);
	}
	else
	{
		pInsertPrev = pInsertPos;
	}

	pNode->pNext = pInsertPrev->pNext;
	pInsertPrev->pNext = pNode;
		
	return OK;
}


BOOL findItemInList(const LP_SINGLE_LIST_NODE pListHead, void *pKeyData, void *pGetData, COMPARE_FUNC pFunc)
{
	LP_SINGLE_LIST_NODE pIterNode;

	assert(pListHead != NULL);
	pIterNode = pListHead->pNext;

	while (pIterNode && pFunc(pIterNode->pData, pKeyData)!= R_EQ)
		pIterNode = pIterNode->pNext;

	if (NULL == pIterNode)
		return FALSE;
	
	memcpy(pGetData, pIterNode->pData, (unsigned int)pListHead->pData);
	
	return TRUE;	

}
void deleteItemFromList(LP_SINGLE_LIST_NODE pListHead, void *pKeyData, COMPARE_FUNC pFunc)
{
	LP_SINGLE_LIST_NODE pIterNodePrev, pDeleteNode;

	assert(pListHead != NULL);
	pIterNodePrev = pListHead;

	while (pIterNodePrev->pNext && pFunc(pIterNodePrev->pNext->pData, pKeyData)!= R_EQ)
		pIterNodePrev = pIterNodePrev->pNext;

	assert(pIterNodePrev->pNext != NULL);
	pDeleteNode = pIterNodePrev->pNext;

	pIterNodePrev->pNext = pDeleteNode->pNext;
	free(pDeleteNode->pData);
	free(pDeleteNode);		
}

void listTraverse(LP_SINGLE_LIST_NODE pListHead, VISIT_FUNC visit)
{
	LP_SINGLE_LIST_NODE pIterNode;

	assert(pListHead != NULL);
	
	pIterNode = pListHead->pNext;
	while(pIterNode)
	{
		visit(pIterNode->pData);
		pIterNode = pIterNode->pNext;
	}
}





