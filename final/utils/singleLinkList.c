#include "singleLinkList.h"

#include "myMemory.h"

#include <stdio.h>
#include <assert.h>



bool
createSingleLinkList(LPSingleLinkList *ppList, 
		     unsigned int elementSize,
		     Printer printer,
		     Less less)
{
	LPSingleLinkList pList = NULL;


	pList = (LPSingleLinkList)myAlloc(sizeof(SingleLinkList));
	if (NULL == pList) {
		assert(0 && "Out Of Memory!");
		return False;
	}

	pList->pHead = NULL;
	pList->elementSize = elementSize;
	pList->printer = printer;
	pList->less = less;
	
	*ppList = pList;
	return True;
}


void
destroySingleLinkList(LPSingleLinkList *ppList)
{
	assert(ppList != NULL && *ppList != NULL);
	clearSingleLinkList(*ppList);

	myFree(*ppList);
	*ppList = NULL;
}


void
clearSingleLinkList(LPSingleLinkList pList)
{
	LPSingleLinkListNode pIterNode = pList->pHead;
	LPSingleLinkListNode pNextNode = NULL;


	while (pIterNode != NULL) {
		pNextNode = pIterNode->pNextNode;
		myFree(pIterNode->data);
		myFree(pIterNode);
		pIterNode = pNextNode;
	} 
}

static LPSingleLinkListNode
createNewSingleLinkListNode(const LPSingleLinkList pList, const void *data)
{
	LPSingleLinkListNode pNewNode = NULL;

	pNewNode = (LPSingleLinkListNode)myAlloc(sizeof(SingleLinkListNode));

	if (NULL == pNewNode) {
		assert (0 && "Out Of Memory!");
		return NULL;
	}
	pNewNode->data = myAlloc(pList->elementSize);
	if (NULL == pNewNode->data) {
		myFree(pNewNode);
		assert(0 && "Out Of Memory");
		return NULL;
	}

	memcpy(pNewNode->data, data, pList->elementSize);
	pNewNode->pNextNode = NULL;
	
	return pNewNode;
}


bool
insertToHeadOfSingleLinkList(LPSingleLinkList pList, const void *data)
{
	LPSingleLinkListNode pNewNode = createNewSingleLinkList(pList, data);

	if (NULL == pNewNode) {
		return False;
	}
	pNewNode->pNextNode = pList->pHead;
	pList->pHead = pNewNode;

	return True;

}


bool insertToTailOfSingleLinkList(LPSingleLinkList pList, const void *data)
{
	
	LPSingleLinkListNode *ppInsertAfter;
	LPSingleLinkListNode pNewNode = createNewSingleLinkList(pList, data);

	if (NULL == pNewNode) {
		return False;
	}
	ppInsertAfter = &pList->pHead;
	while (*ppInsertAfter != NULL) {
		ppInsertAfter = &((*ppInsertAfter)->pNextNode);
	}
	*ppInsertAfter = pNewNode;

	return True;

}



bool insertBeforeInSingleLinkList(LPSingleLinkList pList, const void *data, IterOfSingleLinkList);
bool insertAfterInSingleLinkList(LPSingleLinkList pList, const void *data, IterOfSingleLinkList);

IterOfSingleLinkList findInSingleLinkList(LPSingleLinkList pList, const void *data);
IterOfSingleLinkList findIfInSingleLinkList(LPSingleLinkList pList, Pred pred);

bool removeInSingleLinkList(LPSingleLinkList pList, const void *data);
bool removeIfInSingleLinkList(LPSingleLinkList pList, Pred);

bool eraseFromSingleLinkList(LPSingleLinkList pList, IterOfSingleLinkList iter);


bool isSingleLinkListEmpty(const LPSingleLinkList);

void sortSingleLinkList(LPSingleLinkList);
void traverseSingleLinkList(LPSingleLinkList);





