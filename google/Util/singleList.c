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
void insertSortList(LP_SINGLE_LIST_NODE pListHead, COMPARE_FUNC pFunc)
{
  LP_SINGLE_LIST_NODE pLastNode, pIterNode, pInsertPosPrev, pTempNode;
  
  if (NULL == pListHead->pNext || NULL == pListHead->pNext->pNext)
    return;

  pIterNode = pListHead->pNext->pNext;
  pListHead->pNext->pNext = NULL;
  pLastNode = pListHead->pNext;

  while (pIterNode)
    {
      if (pFunc(pIterNode->pData, pLastNode->pData) < 0)
	{
          pInsertPosPrev = pListHead;
          while(pFunc(pInsertPosPrev->pNext->pData, pIterNode->pData) < 0)
	    {
	      pInsertPosPrev = pInsertPosPrev->pNext;
	    }
	  pTempNode = pIterNode->pNext;

	  pIterNode->pNext = pInsertPosPrev->pNext;
	  pInsertPosPrev->pNext = pIterNode;
	  pIterNode = pTempNode;
	}
      else
	{
	  pLastNode->pNext = pIterNode;
          pIterNode = pIterNode->pNext;
          pLastNode = pLastNode->pNext;
          pLastNode->pNext = NULL;
	}
    }
 


}

void bubbleSortList(LP_SINGLE_LIST_NODE pListHead, COMPARE_FUNC pFunc)
{
  LP_SINGLE_LIST_NODE pLastNodeNext = NULL;
  LP_SINGLE_LIST_NODE pFirstNode = pListHead->pNext;
  LP_SINGLE_LIST_NODE pTempNode1, pTempNode2, pIterNodePrev;
  //int i, j;

  //i = 0;
  while(pListHead->pNext->pNext != pLastNodeNext)
    {
      //printf("\nOut Loop iterations: %d\n", i);
      //i++;

      pIterNodePrev = pListHead;

      //j = 0;
      while (pIterNodePrev->pNext->pNext != pLastNodeNext)
	{
	  //printf("\ninner: %d", j);
	  // j++;
	  if (pFunc(pIterNodePrev->pNext->pData, pIterNodePrev->pNext->pNext->pData) > 0)
	    {
	     
	      pTempNode1 = pIterNodePrev->pNext;
	      pTempNode2 = pTempNode1->pNext;
	      pTempNode1->pNext = pTempNode2->pNext;
	      pTempNode2->pNext = pTempNode1;
	      pIterNodePrev->pNext = pTempNode2;
	      // printf("[swap %d %d]", *(int *)pTempNode1->pData, *(int *)pTempNode2->pData);

	    }
	  pIterNodePrev = pIterNodePrev->pNext;
	}
      pLastNodeNext = pIterNodePrev->pNext;
    }
}

static LP_SINGLE_LIST_NODE selectMinimalNode(LP_SINGLE_LIST_NODE pStartNode, COMPARE_FUNC pFunc)
{
  LP_SINGLE_LIST_NODE pSelectNode = pStartNode;
  LP_SINGLE_LIST_NODE pIterNode = pStartNode->pNext;

  while (pIterNode != NULL)
    {
      if (pFunc(pIterNode->pData, pSelectNode->pData) < 0)
	pSelectNode = pIterNode;
      pIterNode = pIterNode->pNext;
    }
  return pSelectNode;
}


void selectSortList(LP_SINGLE_LIST_NODE pListHead, COMPARE_FUNC pFunc)
{
  LP_SINGLE_LIST_NODE pIterNode, pLastNode, pSelectNode;

  pIterNode = pListHead->pNext;
  pLastNode = pListHead;
  
  printf("\n Start Select Sort List\n");
  while (pIterNode != NULL)
    {
      pSelectNode = selectMinimalNode(pIterNode, pFunc);
      
      if (pSelectNode == pIterNode)
	pIterNode = pIterNode->pNext;
      else
	{
	  LP_SINGLE_LIST_NODE pDeletePrev = pIterNode;
	  while(pDeletePrev->pNext != pSelectNode)
	    pDeletePrev = pDeletePrev->pNext;
	  pDeletePrev->pNext = pSelectNode->pNext;
	}

      pLastNode->pNext = pSelectNode;
      pLastNode = pSelectNode;
    }

  pLastNode->pNext = NULL;
}

static LP_SINGLE_LIST_NODE partion(LP_SINGLE_LIST_NODE pStartNode, LP_SINGLE_LIST_NODE pEndNode, COMPARE_FUNC pFunc)
{
  LP_SINGLE_LIST_NODE pFirstNode, pLastNode, pIterNode, pTempNode;

  // printf("[P]");
  pFirstNode = pStartNode;
  pLastNode = pStartNode;
  pIterNode = pStartNode->pNext;
  pStartNode->pNext = NULL;

  while (pIterNode != pEndNode)
    {
      pTempNode = pIterNode->pNext;
      if (pFunc(pIterNode->pData, pStartNode->pData) < 0)
	{
	  pIterNode->pNext = pFirstNode;
	  pFirstNode = pIterNode;
	}
      else
	{
	  pLastNode->pNext = pIterNode;
	  pLastNode = pIterNode;
	}
      pIterNode = pTempNode;
    }
  pLastNode->pNext = pEndNode;
  return pFirstNode;
}

static LP_SINGLE_LIST_NODE quickSort(LP_SINGLE_LIST_NODE pStartNode, LP_SINGLE_LIST_NODE pEndNode, COMPARE_FUNC pFunc)
{
  LP_SINGLE_LIST_NODE pFirstNode, pSecondFirstNode;

  //printf("[Q]");
  if (pStartNode == pEndNode || pStartNode->pNext == pEndNode)
    return pStartNode;
  
  pFirstNode = partion(pStartNode, pEndNode, pFunc);
  pFirstNode = quickSort(pFirstNode, pStartNode, pFunc);
  pSecondFirstNode = quickSort(pStartNode->pNext, pEndNode, pFunc);

  pStartNode->pNext = pSecondFirstNode;
  return pFirstNode;
}

void quickSortList(LP_SINGLE_LIST_NODE pListHead, COMPARE_FUNC pFunc)
{
  LP_SINGLE_LIST_NODE pFirstNode;
  
  printf("\nStart Quick Sort List:\n");

  pFirstNode = quickSort(pListHead->pNext, NULL, pFunc);
  pListHead->pNext = pFirstNode;

}

void reverseList(LP_SINGLE_LIST_NODE pListHead)
{
  LP_SINGLE_LIST_NODE pIterNode, pTempNode;

  printf("\nStart Reverse List\n");
  pIterNode = pListHead->pNext;
  pListHead->pNext = NULL;

  while (pIterNode != NULL)
    {
      pTempNode = pIterNode->pNext;
      pIterNode->pNext = pListHead->pNext;
      pListHead->pNext = pIterNode;
      pIterNode = pTempNode;
    }

}
