#ifndef _SINGLE_LINK_LIST_H
#define _SINGLE_LINK_LIST_H


typedef struct _SingleLinkListNode {
  void *data;
  struct _SingleLinkListNode *pNext;
}SingleLinkListNode, *LPSingleLinkListNode;

typedef LPSingleLinkListNode * SingleLinkListIter;

typedef struct _SingleLinkList {
  LPSingleLinkListNode pHead;
  unsigned int elementSize;
  Printer printer;
  Less less;
}SingleLinkList, *LPSingleLinkList;




BOOL createSingleLinkList(LPSingleLinkList *, unsigned int, Printer, Less);
void clearSingleLinkList(LPSingleLinkList);
void destroySingleLinkList(LPSingleLinkList *);



BOOL insertToHeadOfSingleLinkList(LPSingleLinkList, const void *data);
BOOL insertToTailOfSingleLinkList(LPSingleLinkList, const void *data);
BOOL insertAfterInSingleLinkList(LPSingleLinkList, const void *data, SingleLinkListIter);
BOOL insertBeforeInSingleLinkList(LPSingleLinkList, const void *data, SingleLinkListIter);

SingleLinkListIter findInSingleLinkList(LPSingleLinkList, Predicate);
void removeFromSingleLinkList(LPSingleLinkList, SingleLinkListIter);
void removeIfInSingleLinkList(LPSingleLinkList, Predicate pred);

void sortSingleLinkList(LPSingleLinkList);

BOOL isSingleLinkListEmpty(const LPSingleLinkList);
unsigned int sizeOfSingleLinkList(const LPSingleLinkList);

void TraverseSingleLinkList(LPSingleLinkList, Visitor visitor);
#endif

