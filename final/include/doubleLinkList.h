
#ifndef _MY_DOUBLE_LINK_LIST_H
#define _MY_DOUBLE_LINK_LIST_H

#include "common.h"

typedef struct _DoubleLinkListNode
{
  	void * data;
  	struct _DoubleLinkListNode *pNextNode;
	struct _DoubleLinkListNode *pPrevNode;
}DoubleLinkListNode, *LPDoubleLinkListNode;


typedef LPDoubleLinkListNode * IteratorOfDoubleLinkList;


typedef struct _DoubleLinkList
{
	LPDoubleLinkListNode pHead;

	unsigned int 	elementSize;
	Printer  	printer;
	Less		less;	

}DoubleLinkList, *LPDoubleLinkList;


bool createDoubleLinkList(LPDoubleLinkList *ppList, unsigned int elementSize, Printer printer, Less less);
void destroyDoubleLinkList(LPDoubleLinkList *ppList);


void clearDoubleLinkList(LPDoubleLinkList pList);
bool insertToHeadOfDoubleLinkList(LPDoubleLinkList pList, const void *data);
bool insertToTailOfDoubleLinkList(LPDoubleLinkList pList, const void *data);

bool insertBeforeInDoubleLinkList(LPDoubleLinkList pList, const void *data, IteratorOfDoubleLinkList);
bool insertAfterInDoubleLinkList(LPDoubleLinkList pList, const void *data, IteratorOfDoubleLinkList);

IteratorOfDoubleLinkList findInDoubleLinkList(LPDoubleLinkList pList, const void *data);
IteratorOfDoubleLinkList findIfInDoubleLinkList(LPDoubleLinkList pList, Pred pred);

bool removeInDoubleLinkList(LPDoubleLinkList pList, const void *data);
bool removeIfInDoubleLinkList(LPDoubleLinkList pList, Pred);

bool eraseFromDoubleLinkList(LPDoubleLinkList pList, IteratorOfDoubleLinkList iter);


bool isDoubleLinkListEmpty(const LPDoubleLinkList);

void sortDoubleLinkList(LPDoubleLinkList);
void traverseDoubleLinkList(LPDoubleLinkList, Visitor);



#endif

