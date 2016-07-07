#include "singleLinkList.h"


#include "memory.h"

#include <assert.h>

BOOL createSingleLinkList(LPSingleLinkList *ppList,
			  unsigned int elementSize,
			  Printer printer,
			  Less less)
{
	LPSingleLinkList pList = NULL;


	pList = (LPSingleLinkList)myAlloc(sizeof(SingleLinkList));
	if (NULL == pList) {
		assert(0 && "Out Of Memory");
		return False;
	}
	pList->pHead 		= NULL;
	pList->elementSize 	= elementSize;
	pList->printer 		= printer;
	pList->less 		= less;

	*ppList = pList;
	return True;
}

void clearSingleLinkList(LPSingleLinkList pList)
{
	LPSingleLinkListNode pIterNode, pNextNode;
	assert(pList);

	pIterNode = pList->pHead;
	while (pIterNode != NULL) {
		pNextNode = pIterNode;

		myFree(pIterNode->data);
		myFree(pIterNode);

		pIterNode = pNextNode;
	}

	pList->pHead = NULL;

}

void destroySingleLinkList(LPSingleLinkList *ppList)
{
	LPSingleLinkList pList;

	assert(ppList);
	pList = *ppList;

	clearSingleLinkList(pList);
	myFree(pList);

	*ppList = NULL;
}

void traverseSingleLinkList(LPSingleLinkList pList, Visitor visitor)
{
	LPSingleLinkListNode pIterNode = pList->pHead;

	while (pIterNode != NULL) {
		visitor(pIterNode->data);
		pIterNode = pIterNode->pNextNode;
	}
}

void sortSingleLinkList(LPSingleLinkList pList)
{
	LPSingleLinkListNode pIterNode, pNextNode;
	LPSingleLinkListNode *ppInsertPos;
  	assert(pList);

	if (NULL == pList->pHead ||
	    NULL == pList->pHead->pNext)
		return;


	pIterNode = pList->pHead->pNextNode;
	pList->pHead->pNextNode = NULL;

	while (pIterNode != NULL) {
		pNextNode = pIterNode->pNext;
		ppInsertPos = &pList->pHead;
		while (*ppInsertPos != NULL && 
		       pList->less((*ppInsertPos)->data, pIterNode->data) == True)
			ppInsertPos = &(*ppInsertPos)->pNext;
		pIterNode->pNext = *ppInsertPos;
		*ppInsertPos = pIterNode;
		
		pIterNode = pNextNode;
	}


}


void printSingleLinkList(const LPSingleLinkList pList)
{
	unsigned int count = 0;
#define MAX_ITEM_PER_LINE 5
	LPSingleLinkListNode pIterNode = pList->pHead;
	while (pIterNode != NULL) {
		pList->printer(pIterNode->data);
		++count;
		if (count % MAX_ITEM_PER_LINE == 0)
			putchar('\n');
	}
	
	if (count % 5 != 0)
		putchar('\n');
#undef MAX_ITER_PER_LINE	
}


LPSingleLinkListNode *findInSingleLinkList(LPSingleLinkList pList, const void *ref)
{
	LPSingleLinkListNode *ppIterNode = &pList->pHead;
	while (*ppIterNode != NULL && 
		pList->less(ref, (*ppIterNode)->data) == False &&
		pList->less((*ppIterNode)->data, ref) == False)
		ppIterNode = &(*ppIterNode)->pNext;
	return ppIterNode;
}

LPSingleLinkListNode *findIfInSingleLinkList(LPSingleLinkList, Pred pred)
{
	LPSingleLinkListNode *ppIterNode = &pList->pHead;
	while (*ppIterNode != NULL && 
		pList->pred((*ppIterNode)->data) == False)
		ppIterNode = &(*ppIterNode)->pNext;
	return ppIterNode;
}
}

void uniqueSingleLinkList(LPSingleLinkList pList)
{
	LPSingleLinkListNode pIterNode;
	LPSingleLinkListNode pNode;

	if (NULL == pList->pHead ||
	    NULL == pList->pHead->pNext)
		return;

	pIterNode = pList->pHead;
	while (pIterNode->pNext != NULL) {
		if (pList->less(pIterNode->pNext->data, pIterNode->data) == False &&
		    pList->less((pIterNode->data, pIterNode->pNext->data) == False) {
			pNode = pIterNode->pNextNode;
			pIterNode->pNextNode = pNode->pNext;
			myFree(pNode->data);
			myFree(pNode);
		} else {
			pIterNode = pIterNode->pNextNode;
		}
	}
}

BOOL removeInSingleLinkList(LPSingleLinkList pList, const void *ref)
{
	LPSingleLinkListNode *ppIterNode = NULL;
	LPSingleLinkListNode pNode;

	while (*ppIterNode != NULL) {
		if (pList->less(ref, (*ppIterNode)->data) == False &&
		    pList->less((*ppIterNode)->data, ref) == False) {
			pNode = *ppIterNode;
			*ppIterNode = pNode->pNext;
			myFree(pNode->data);
			myFree(pNode);

		} else {
			ppIterNode = &(*ppIterNode)->pNext;
		}
			
	}


}

BOOL removeIfInSingleLinkList(LPSingleLinkList pList, Pred pred)
{
	LPSingleLinkListNode *ppIterNode = NULL;
	LPSingleLinkListNode pNode;

	while (*ppIterNode != NULL) {
		if (pList->pred((*ppIterNode)->data) == True) {
			pNode = *ppIterNode;
			*ppIterNode = pNode->pNext;
			myFree(pNode->data);
			myFree(pNode);

		} else {
			ppIterNode = &(*ppIterNode)->pNext;
		}
			
	}

}

static
LPSingleLinkListNode createNewSingleLinkListNode(LPSingleLinkList pList, const void *data)
{
	LPSingleLinkListNode pNewNode = NULL;
		
	pNewNode = (LPSingleLinkListNode)myAlloc(sizeof(SingleLinkListNode));
	if (NULL == pNewNode) {
		assert(0 && "Out Of memory!");
		return NULL;
	}

	pNewNode->data = (char *)myAlloc(pList->elementSize);
	if (NULL == pNewNode->data) {
		myFree(pNewNode);
		assert(0 &&"Out Of Memory!");
		return NULL;
	}

	memcpy(pNewNode->data, data, pList->elementSize);
	pNewNode->pNext = NULL;
	return pNewNode;
}


BOOL insertToHeadOfSingleLinkList(LPSingleLinkList pList, const void *data)
{
	LPSingleLinkListNode pNewNode;

	pNewNode = createNewSingleLinkListNode(pList, data);
	if (NULL == pNewNode)
		return False;
	pNewNode->pNext = pList->pHead;
	pList->pHead = pNewNode;

	return True;

}

BOOL insertToTailOfSingleLinkList(LPSingleLinkList pList, const void *data)
{
	LPSingleLinkListNode pNewNode = NULL;
	LPSingleLinkListNode *ppInsertPos = NULL;
	
	pNewNode = createNewSingleLinkListNode(pList, data);
	if (NULL == pNewNode)
		return False;
	
	ppInsertPos = &pList->pHead;
	while ( *ppInsertPos != NULL)
		ppInsertPos = &(*ppInsertPos)->pNext;

	*ppInsertPos = pNewNode;
	

	return True;


}
BOOL insertAfterInSingleLinkList(LPSingleLinkList pList, LPSingleLinkListNode *ppInsertPos, const void *data)
{
	LPSingleLinkListNode pNewNode;

	pNewNode = createNewSingleLinkListNode(pList, data);
	if (NULL == pNewNode)
		return False;

	pNewNode->pNext = (*ppInsertPos)->pNext;
	(*ppInsertPos)->pNext = pNewNode;

	return True;
}

BOOL insertBeforeInSingleLinkList(LPSingleLinkList, LPSingleLinkListNode *ppInsertPos, const void *)
{
	LPSingleLinkListNode pNewNode;

	pNewNode = createNewSingleLinkListNode(pList, data);
	if (NULL == pNewNode)
		return False;

	pNewNode->pNext = (*ppInsertPos);
	(*ppInsertPos) = pNewNode;

	return True;

}



