
#include "doubleLinkList.h"


#include "utils.h"
#include "memory.h"

#include <stdio.h>
#include <string.h>
#include <assert.h>


static 
LPDoubleLinkListNode
createDoubleLinkListNode(const LPDoubleLinkList pList, const void *data)
{
	LPDoubleLinkListNode pNode = NULL;

	pNode = (LPDoubleLinkListNode)myAlloc(sizeof(DoubleLinkListNode));
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
	pNode->pPrev = NULL;

	return pNode;
}

BOOL
createDoubleLinkList(LPDoubleLinkList *ppList,
	             unsigned int elementSize,
		     Less less,
		     Printer printer)
{
	LPDoubleLinkList pList = NULL;

	pList = (LPDoubleLinkList)myAlloc(sizeof(DoubleLinkList));
	if (NULL == pList) {
		DBG(printf("Out Of Memory in %s %d", __FILE__, __line__));
		return False;
	}

	pList->pHead = (LPDoubleLinkListNode)myAlloc(sizeof(DoubleLinkListNode));
	if (NULL == pList->pHead) {
		DBG(printf("Out Of Memory in %s %d", __FILE__, __line__));
		myFree(pList);
		return False;
	}
	pList->data = NULL;
	pList->pHead->pNext = pList->pHead;
	pList->pHead->pPrev = pList->pHead;

	pList->elementSize = elementSize;
	pList->less = less;
	pList->printer = printer;

	

	*ppList = pList;

	return True;
}

void
destroyDoubleLinkList(LPDoubleLinkList *ppList)
{
	LPDoubleLinkList pList = *ppList;
	LPDoubleLinkListNode pIter, pNext;
	
	if (NULL == pList)
		return;

	pIter = pList->pHead->pNext;
	while (pList->pHead != pIter) {
		pNext = pIter->pNext;
		
		myFree(pIter->data);
		myFree(pIter);

		pIter = pNext;	
	}
	myFree(pList->pHead);
	pList->pHead = NULL;
	myFree(pList);
	
	*ppList = NULL;
}


BOOL
insertToHeadOfDoubleLinkList(LPDoubleLinkList pList, const void *data)
{
	LPDoubleLinkListNode pNode = NULL;

	pNode = createDoubleLinkListNode(pList, data);
	if (NULL == pNode)
		return False;	

	pNode->pNext = pList->pHead->pNext;
	pNode->pPrev = pList->pHead;

	pNode->pNext->pPrev = pNode;
	pNode->pPrev->pNext = pNode;

	return True;
}

BOOL
insertToTailOfDoubleLinkList(LPDoubleLinkList pList, const void *data)
{
	LPDoubleLinkListNode pNode = NULL, pIter;

	pNode = createDoubleLinkListNode(pList, data);
	if (NULL == pNode)
		return False;	

	pNode->pNext = pList->pHead;
	pNode->pPrev = pList->pHead->pPrev;

	pNode->pNext->pPrev = pNode;
	pNode->pPrev->pNext = pNode;

	return True;
}

BOOL
insertAfterInDoubleLinkList(LPDoubleLinkList pList, DoubleLinkListIter pos, const void *data)
{
	LPDoubleLinkListNode pNode;

	assert(pos != NULL);

	pNode = createDoubleLinkListNode(pList, data);
	if (NULL == pNode) 
		return False;

	pNode->pNext = (*pos)->pNext;
	pNode->pPrev = *pos;

	pNode->pNext->pPrev = pNode;
	pNode->pPrev->pNext = pNode;


	return True;
}

BOOL
insertBeforeInDoubleLinkList(LPDoubleLinkList pList, DoubleLinkListIter pos, const void *data)
{
	LPDoubleLinkListNode pNode;

	assert(pos != NULL);

	pNode = createDoubleLinkListNode(pList, data);
	if (NULL == pNode) 
		return False;

	pNode->pNext = (*pos);
	pNode->pPrev = (*pos)->pPrev;

	pNode->pNext->pPrev = pNode;
	pNode->pPrev->pNext = pNode;



	return True;
}


DoubleLinkListIter
findInDoubleLinkList(LPDoubleLinkList pList, const void *ref)
{
	DoubleLinkListIter it = NULL;
	it = &pList->pHead->pNext;
	while ( *it != pList->pHead ) {
		if (pList->less((*it)->data, ref) == False &&
		    pList->less(ref, (*it)->data) == False)
			return it;
		it = &(*it)->pNext;
	}
	return NULL;
}

DoubleLinkListIter
findIfInDoubleLinkList(LPDoubleLinkList pList, Pred pred)
{
	DoubleLinkListIter it = &pList->pHead->pNext;
	
	while (*it != pList->pHead) {
		if (pred((*it)->data) == True)
			return it;
	}
	return NULL;
}

BOOL
removeInDoubleLinkList(LPDoubleLinkList pList, const void *ref)
{
	BOOL bRemoved = False;
	DoubleLinkListIter it = &pList->pHead->pNext;
	LPDoubleLinkListNode pDeleteNode;
	while (*it != pList->pHead) {
		if (pList->less((*it)->data, ref) == False &&
		    pList->less(ref, (*it)->data) == False) {
			pDeleteNode = *it;
			pDeleteNode->pNext->pPrev = pDeleteNode->pPrev;
			pDeleteNode->pPrev->pNext = pDeleteNode->pNext;


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
removeIfInDoubleLinkList(LPDoubleLinkList pList, Pred pred)
{
	BOOL bRemoved = False;
	DoubleLinkListIter it = &pList->pHead;
	LPDoubleLinkListNode pDeleteNode;
	while (*it != NULL) {
		if (pred((*it)->data) == True) {
			pDeleteNode = *it;
			pDeleteNode->pNext->pPrev = pDeleteNode->pPrev;
			pDeleteNode->pPrev->pNext = pDeleteNode->pNext;


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
eraseFromDoubleLinkList(LPDoubleLinkList pList, DoubleLinkListIter it)
{
	LPDoubleLinkListNode pDeleteNode = *it;

	pDeleteNode->pNext->pPrev = pDeleteNode->pPrev;
	pDeleteNode->pPrev->pNext = pDeleteNode->pNext;
	
	myFree(pDeleteNode->data);
	myFree(pDeleteNode);

}


void
sortDoubleLinkList(LPDoubleLinkList pList)
{
	DoubleLinkListIter it;
	LPDoubleLinkListNode pIter, pNext;

	if (pList->pHead->pNext == pList->pHead)
		return;
	
	pIter = pList->pHead->pNext;
	pList->pHead->pNext = pList->pHead;
	pList->pHead->pPrev = pList->pHead;

	while(pList->pHead != pIter) {
		pNext = pIter->pNext;
		it = &pList->pHead->pNext;
		while (*it != pList->pHead &&
		       pList->less((*it)->data, pIter->data) == True)
			it = &(*it)->pNext;
		
		pIter->pNext = *it;
		pIter->pPrev = (*it)->pPrev;

		pIter->pNext->pPrev = pIter;
		pIter->pPrev->pNext = pIter;
		
		pIter = pNext;
	}

}

// Assume list has been sorted.
void
uniqueDoubleLinkList(LPDoubleLinkList pList)
{
	LPDoubleLinkListNode pPrev;

	if (pList->pHead->pNext == pList->pHead)
		return;

	pPrev = pList->pHead;
	while (pPrev->pNext != pList->pHead) {
		if (pList->less(pPrev->data, pPrev->pNext->data) == False &&
		    pList->less(pPrev->pNext->data, pPrev->data) == False) {
			pDeleteNode = pPrev->pNext;
			
			pDeleteNode->pNext->pPrev = pDeleteNode->pPrev;
			pDeleteNode->pPrev->pNext = pDeleteNode->pNext
;

			myFree(pDeleteNode->data);
			myFree(pDeleteNode);		

		} else {
			pPrev = pPrev->pNext;
		}

	}
}

void
traverseDoubleLinkList(LPDoubleLinkList pList, Visitor visitor)
{
	LPDoubleLinkListNode pIter = pList->pHead->pNext;
	while (pIter != pList->pHead) {

		visitor(pIter->data);
		pIter = pIter->pNext;
	}
}

