#ifndef _MY_SINGLE_LINK_LIST_H
#define _MY_SINGLE_LINK_LIST_H

#include "common.h"

typedef struct _SingleLinkListNode
{
	void *data;
	struct _SingleLinkListNode *pNext;
}SingleLinkListNode, *LPSingleLinkListNode;


typedef struct _SingleLinkList
{
	LPSingleLinkList pHead;
	unsigned int elementSize;


	Printer printer;
	Less less;
}SingleLinkList, *LPSingleLinkList;



BOOL 
createSingleLinkList(
	LPSingleLinkList 	*ppList,
	unsigned int 		elementSize,
	Printer 		printer,
	Less 			less);


void
clearSingleLinkList(
	LPSingleLinkList pList);
void
destroySingleLinkList(
	LPSingleLinkList *ppList);

BOOL
insertToHeadOfSingleLinkList(
	LPSingleLinkList pList,
	const void *data);

BOOL
insertToTailOfSingleLinkList(
	LPSingleLinkList pList,
	const void *data);


typedef LPSingleLinkListNode * IterOfSingleLinkList;


SingleLinkListIter
findInSingleLinkList(
	LPSingleLinkList pList,
	const void *data);

SingleLinkListIter
findInSingleLinkList(
	LPSingleLinkList pList,
	Pred pred);


void
removeFromSingleLinkList(
	LPSingleLinkList pList,
	SingleLinkListIter it);

BOOL
removeIfInSingleLinkList(
	LPSingleLinkList pList,
	Pred pred);

void
reverseSingleLinkList(
	LPSingleLinkList pList);

void
sortSingleLinkList(
	LPSingleLinkList pList);


BOOL
isSingleLinkListEmpty(
	const LPSingleLinkList pList);

unsigned int
getSizeOfSingleLinkList(
	const LPSingleLinkList pList);


#endif
