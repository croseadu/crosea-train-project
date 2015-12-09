#ifndef _SINGLE_LINK_LIST_H
#define _SINGLE_LINK_LIST_H

#include "common.h"

typedef struct _DoubleLinkListNode {
  void *data;
  struct _DoubleLinkListNode *pNextNode;
  struct _DoubleLinkListNode *pPrevNode;
}DoubleLinkListNode, *LPDoubleLinkListNode;

typedef LPDoubleLinkListNode DoubleLinkListIter;

typedef struct _DoubleLinkList {
  LPDoubleLinkListNode pHead;
  unsigned int elementSize;
  Printer printer;
  Less less;
}DoubleLinkList, *LPDoubleLinkList;


BOOL createDoubleLinkList(LPDoubleLinkList *, unsigned int, Printer, Less);
void clearDoubleLinkList(LPDoubleLinkList);
void destroyDoubleLinkList(LPDoubleLinkList *);

BOOL insertToHeadOfDoubleLinkList(LPDoubleLinkList, const void *data);
BOOL insertToTailOfDoubleLinkList(LPDoubleLinkList, const void *data);
BOOL insertAfterInDoubleLinkList(LPDoubleLinkList, const void *data, DoubleLinkListIter);
BOOL insertBeforeInDoubleLinkList(LPDoubleLinkList, const void *data, DoubleLinkListIter);

DoubleLinkListIter findInDoubleLinkList(LPDoubleLinkList, Predicate);
void removeFromDoubleLinkList(LPDoubleLinkList, DoubleLinkListIter);
void removeIfInDoubleLinkList(LPDoubleLinkList, Predicate pred);

void sortDoubleLinkList(LPDoubleLinkList);

BOOL isDoubleLinkListEmpty(const LPDoubleLinkList);
unsigned int sizeOfDoubleLinkList(const LPDoubleLinkList);

void TraverseDoubleLinkList(LPDoubleLinkList, Visitor visitor);

#endif

