#include "singleLinkList.h"


#include "utils.h"
#include "memory.h"

#include <stdio.h>
#include <string.h>
#include <assert.h>


BOOL
createSingleLinkList(LPSingleLinkList *ppList,
	             unsigned int elementSize,
		     Less less,
		     Printer printer)
{
	LPSingleLinkList pList = NULL;

	pList = (LPSingleLinkList)myAlloc(sizeof(SingleLinkList));
	if (NULL == pList) {
		DBG(printf("Out Of Memory in %s %d", __FILE__, __line__));
		return False;
	}
	pList->pHead = NULL;
	pList->elementSize = elementSize;
	pList->less = less;
	pList->printer = printer;


	*ppList = pList;

	return True;
}

void
destroySingleLinkList(LPSingleLinkList *ppList)
{
	LPSingleLinkList pList = *ppList;
	LPSingleLinkListNode pIter, pNext;
	
	if (NULL == pList)
		return;

	pIter = pList->pHead;
	while (NULL != pIter) {
		pNext = pIter->pNext;
		
		myFree(pIter->data);
		myFree(pIter);

		pIter = pNext;	
	}
	myFree(pList);

	*ppList = NULL;
}

static 
LPSingleLinkListNode
createSingleLinkListNode(const LPSingleLinkList pList, const void *data)
{
	LPSingleLinkListNode pNode = NULL;

	pNode = (LPSingleLinkListNode)myAlloc(sizeof(SingleLinkListNode));
	if (NULL == pNode) {
		DBG(printf("Out Of Memory in %s %d", __FILE__, __line__));
		return NULL;
	}
	pNode->data = myAlloc(pList->elementSize);
	if (NULL == pNode->data) {
		DBG(printf("Out Of Memory in %s %d", __FILE__, __line__));
		myFree(pNode);
		return NULL;
	}
	
	memcpy(pNode->data, data, pList->elementSize);
	pNode->pNext = NULL;

	return pNode;
}

BOOL
insertToHeadOfSingleLinkList(LPSingleLinkList pList, const void *data)
{
	LPSingleLinkListNode pNode = NULL;

	pNode = createSingleLinkListNode(pList, data);
	if (NULL == pNode)
		return False;	

	pNode->pNext = pList->pHead;
	pList->phead = pNode;

	return True;
}

BOOL
insertToTailOfSingleLinkList(LPSingleLinkList pList, const void *data)
{
	LPSingleLinkListNode pNode = NULL, pIter;

	pNode = createSingleLinkListNode(pList, data);
	if (NULL == pNode)
		return False;	

	if (NULL == pList->pHead) {
		pNode->pNext = NULL;
		pList-<oGead = pNode;
	} else {
		pIter = pList->pHead;
		while (pIter->pNext)
			pIter = pIter->pNext;
		pIter->pNext = pNode;
		pNode->pNext = NULL;
	}

	return True;
}

BOOL
insertAfterInSingleLinkList(LPSingleLinkList pList, SingleLinkListIter pos, const void *data)
{
	LPSingleLinkListNode pNode;

	assert(pos != NULL);

	pNode = createSingleLinkListNode(pList, data);
	if (NULL == pNode) 
		return False;

	pNode->pNext = (*pos)->pNext;
	(*pos)->pNext = pNode;

	return True;
}

BOOL
insertBeforeInSingleLinkList(LPSingleLinkList pList, SingleLinkListIter pos, const void *data)
{
	LPSingleLinkListNode pNode;

	assert(pos != NULL);

	pNode = createSingleLinkListNode(pList, data);
	if (NULL == pNode) 
		return False;

	pNode->pNext = (*pos);
	(*pos) = pNode;

	return True;
}


SingleLinkListIter
findInSingleLinkList(LPSingleLinkList pList, const void *ref)
{
	SingleLinkListIter it = NULL;
	it = &pList->pHead;
	while ( *it != NULL ) {
		if (pList->less((*it)->data, ref) == False &&
		    pList->less(ref, (*it)->data) == False)
			return it;
		it = &(*it)->pNext;
	}
	return NULL;
}

SingleLinkListIter
findIfInSingleLinkList(LPSingleLinkList pList, Pred pred)
{
	SingleLinkListIter it = &pList->pHead;
	
	while (*it != NULL) {
		if (pred((*it)->data) == True)
			return it;
	}
	return NULL;
}

BOOL
removeInSingleLinkList(LPSingleLinkList pList, const void *ref)
{
	BOOL bRemoved = False;
	SingleLinkListIter it = &pList->pHead;
	LPSingleLinkListNode pDeleteNode;
	while (*it != NULL) {
		if (pList->less((*it)->data, ref) == False &&
		    pList->less(ref, (*it)->data) == False) {
			pDeleteNode = *it;
			*it = pDeleteNode->pNext;

			myFree(pDeleteNode->data);
			myFree(pDeleteNode);	

			bRemoved = True;		

		} else {
			it = &(*it)->pNext;
		}	

	}	

	return bRemoved;
}

BOOL
removeIfInSingleLinkList(LPSingleLinkList pList, Pred pred)
{
	BOOL bRemoved = False;
	SingleLinkListIter it = &pList->pHead;
	LPSingleLinkListNode pDeleteNode;
	while (*it != NULL) {
		if (pred((*it)->data) == True) {
			pDeleteNode = *it;
			*it = pDeleteNode->pNext;

			myFree(pDeleteNode->data);
			myFree(pDeleteNode);
			
			bRemoved = True;			

		} else {
			it = &(*it)->pNext;
		}	

	}	

	return bRemoved;
}

void
eraseFromSingleLinkList(LPSingleLinkList pList, SingleLinkListIter it)
{
	LPSingleLinkListNode pDeleteNode = *it;

	*it = pDeleteNode->pNext;
	
	myFree(pDeleteNode->data);
	myFree(pDeleteNode);

}


void
sortSingleLinkList(LPSingleLinkList pList)
{
	SingleLinkListIter it;
	LPSingleLinkListNode pIter, pNext;

	if (pList->pHead == NULL)
		return;
	
	pIter = pList->pHead->pNext;
	pList->pHead->pNext = NULL;

	while(NULL != pIter) {
		pNext = pIter->pNext;
		it = &pList->pHead;
		while (*it != NULL &&
		       pList->less((*it)->data, pIter->data) == True)
			it = &(*it)->pNext;
		
		pIter->pNext = *it;
		*it = pIter;

		pIter = pNext;
	}

}

// Assume list has been sorted.
void
uniqueSingleLinkList(LPSingleLinkList pList)
{
	LPSingleLinkListNode pPrev;

	if (pList->pHead == NULL)
		return;

	pPrev = pList->pHead;
	while (pPrev->pNext != NULL) {
		if (pList->less(pPrev->data, pPrev->pNext->data) == False &&
		    pList->less(pPrev->pNext->data, pPrev->data) == False) {
			pDeleteNode = pPrev->pNext;
			pPrev->pNext = pDeleteNode->pNext;

			myFree(pDeleteNode->data);
			myFree(pDeleteNode);		

		} else {
			pPrev = pPrev->pNext;
		}

	}
}

void
traverseSingleLinkList(LPSingleLinkList pList, Visitor visitor)
{
	LPSingleLinkListNode pIter = pList->pHead;
	while (pIter != NULL) {

		visitor(pIter->data);
		pIter = pIter->pNext;
	}
}

