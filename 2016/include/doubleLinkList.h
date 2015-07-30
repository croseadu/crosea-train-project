
#ifndef _MY_DOUBLE_LINK_LIST_H
#define _M_DOUBLE_LINK_LIST_H

#include "common.h"

typedef struct _DoubleLinkListNode
{
  void *data;
  struct _DoubleLinkListNode *pPrevNode;
  struct _DoubleLinkListNode *pNextNode;
}DoubleLinkListNode, *LPDoubleLinkListNode;

typedef LPDoubleLinkListNode * DoubleLinkListIter;

typedef struct _DoubleLinkList
{
  LPDoubleLinkListNode pHead;
  unsigned int elementSize;
  Printer printer;
  Less less;
}DoubleLinkList, * LPDoubleLinkList;

enum BOOL createDoubleLinkList(LPDoubleLinkList *,
			  unsigned int ,
			  Printer ,
			  Less);
void destoryDoubleLinkList(LPDoubleLinkList *);

enum BOOL insertToHeadOfDoubleLinkList(LPDoubleLinkList, const void *);
enum BOOL insertToTailOfDoubleLinkList(LPDoubleLinkList, const void *);

enum BOOL insertAfterInDoubleLinkList(LPDoubleLinkList, const void *, DoubleLinkListIter);

DoubleLinkListIter findInDoubleLinkList(LPDoubleLinkList, const void *);
DoubleLinkListIter findIfInDoubleLinkList(LPDoubleLinkList, Pred);

enum BOOL removeInDoubleLinkList(LPDoubleLinkList, const void *);
enum BOOL removeIfInDoubleLinkList(LPDoubleLinkList, Pred);

void traverseDoubleLinkList(LPDoubleLinkList, Visitor);
void sortDoubleLinkList(LPDoubleLinkList);

void printDoubleLinkList(const LPDoubleLinkList);

#endif
