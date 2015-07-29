#ifndef _MY_SINGLE_LINK_LIST_H
#define _MY_SINGLE_LINK_LIST_H

#include "common.h"

typedef struct _SingleLinkListNode
{
  void *data;
  struct _SingleLinkListNode *pNextNode;
}SingleLinkListNode, *LPSingleLinkListNode;

typedef LPSingleLinkListNode * SingleLinkListIter;

typedef struct _SingleLinkList
{
  LPSingleLinkListNode pHead;
  unsigned int elementSize;
  Printer printer;
  Less less;
}SingleLinkList, * LPSingleLinkList;

enum BOOL createSingleLinkList(LPSingleLinkList *,
			  unsigned int ,
			  Printer ,
			  Less);
void destorySingleLinkList(LPSingleLinkList *);

enum BOOL insertToHeadOfSingleLinkList(LPSingleLinkList, const void *);
enum BOOL insertToTailOfSingleLinkList(LPSingleLinkList, const void *);

enum BOOL insertAfterInSingleLinkList(LPSingleLinkList, const void *, SingleLinkListIter);

SingleLinkListIter findInSingleLinkList(LPSingleLinkList, const void *);
SingleLinkListIter findIfInSingleLinkList(LPSingleLinkList, Pred);

enum BOOL removeInSingleLinkList(LPSingleLinkList, const void *);
enum BOOL removeIfInSingleLinkList(LPSingleLinkList, Pred);

void traverseSingleLinkList(LPSingleLinkList, Visitor);
void sortSingleLinkList(LPSingleLinkList);

void printSingleLinkList(const LPSingleLinkList);

#endif
