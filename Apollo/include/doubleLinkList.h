
#ifndef _MY_DOUBLE_LINK_LIST_H
#define _MY_DOUBLE_LINK_LIST_H

#include "common.h"

typedef struct _DoubleLinkListNode
{
	void *data;
	struct _DoubleLinkListNode *pNext;
	struct _DoubleLinkListNode *pPrev;
}DoubleLinkListNode, *LPDoubleLinkListNode;


typedef struct _DoubleLinkList
{
	LPDoubleLinkListNode pHead;
	unsigned int elementSize;


	Printer printer;
	Less less;
}DoubleLinkList, *LPDoubleLinkList;



BOOL 
createDoubleLinkList(
	LPDoubleLinkList 	*ppList,
	unsigned int 		elementSize,
	Printer 		printer,
	Less 			less);


void
clearDoubleLinkList(
	LPDoubleLinkList pList);

void
destroyDoubleLinkList(
	LPDoubleLinkList *ppList);


BOOL
insertToHeadOfDoubleLinkList(
	LPDoubleLinkList pList,
	const void *data);

BOOL
insertToTailOfDoubleLinkList(
	LPDoubleLinkList pList,
	const void *data);


void
removeHeadFromDoubleLinkList(
	LPDoubleLinkList);
void
removeTailFromDoubleLinkList(
	LPDoubleLinkList);

typedef LPDoubleLinkListNode * DoubleLinkListIter;


DoubleLinkListIter
findInDoubleLinkList(
	LPDoubleLinkList pList,
	const void *data);

DoubleLinkListIter
findIfInDoubleLinkList(
	LPDoubleLinkList pList,
	Pred pred);


void
removeFromDoubleLinkList(
	LPDoubleLinkList pList,
	DoubleLinkListIter it);

BOOL
removeIfInDoubleLinkList(
	LPDoubleLinkList pList,
	Pred pred);

void
reverseDoubleLinkList(
	LPDoubleLinkList pList);

void
sortDoubleLinkList(
	LPDoubleLinkList pList);

void
getFrontOfDoubleLinkList(
	LPDoubleLinkList pList,
	void *data);

void
getBackOfDoubleLinkList(
	LPDoubleLinkList pList,
	void *data);

void 
dumpDoubleLinkList(
	const LPDoubleLinkList pList,
	const char *separator,
	unsigned int itemsPerLine);


#endif
