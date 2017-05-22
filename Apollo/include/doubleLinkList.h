
#ifndef _MY_DOUBLE_LINK_LIST_H
#define _MY_DOUBLE_LINK_LIST_H

#include "common.h"

typedef struct _DoubleLinkListNode
{
	void *data;
	struct _DoubleLinkListNode *pNext;
	struct _DoubleLinkLIstNode *pPrev;
}DoubleLinkListNode, *LPDoubleLinkListNode;


typedef struct _DoubleLinkList
{
	LPDoubleLinkList pHead;
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


typedef LPDoubleLinkListNode IterOfDoubleLinkList;


DoubleLinkListIter
findInDoubleLinkList(
	LPDoubleLinkList pList,
	const void *data);

DoubleLinkListIter
findInDoubleLinkList(
	LPDoubleLinkList pList,
	Pred pred);


void
removeFromDoubleLinkList(
	LPDoubleLinkList pList,
	IterOfDoubleLinkList it);

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




#endif
