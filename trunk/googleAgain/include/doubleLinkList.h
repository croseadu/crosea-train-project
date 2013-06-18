#ifndef _MY_DOUBLE_LINK_LIST_H
#define _MY_DOUBLE_LINK_LIST_H
#include "mytype.h"

typedef struct _DoubleLinkListNode
{
  char *pData;
  struct _DoubleLinkListNode *pNext;
  struct _DoubleLinkListNode *pPrev;
}DoubleLinkListNode, *LPDoubleLinkListNode;

typedef struct _DoubleLinkList
{
  LPDoubleLinkListNode pHead;
  unsigned int elementSize;
  PrintFunc printer;
  CompareFunc equal;
  CompareFunc less;
}DoubleLinkList, *LPDoubleLinkList;

bool initDoubleLinkList(LPDoubleLinkList *ppList, unsigned int elementSize, PrintFunc printer, CompareFunc eq, CompareFunc less);
bool insertToDoubleLinkListHead(LPDoubleLinkList pList, void * pVal);
bool insertToDoubleLinkListTail(LPDoubleLinkList pList, void *pVal);
bool insertToDoubleLinkList(LPDoubleLinkList pList, void *pVal, DoubleLinkListNode *pInsertPos);
void deleteNodeInDoubleLinkList(LPDoubleLinkList pList, DoubleLinkListNode *pDelete);
unsigned int deleteValInDoubleLinkList(LPDoubleLinkList pList, void *val);
unsigned int deleteIfInDoubleLinkList(LPDoubleLinkList pList, PredFunc pred);
void visitDoubleLinkList(LPDoubleLinkList pList, VisitFunc visitor);
void printDoubleLinkList(LPDoubleLinkList pList);
void clearDoubleLinkList(LPDoubleLinkList pList);
void sortDoubleLinkList(LPDoubleLinkList pList);
void reverseDoubleLinkList(LPDoubleLinkList pList);
void destroyDoubleLinkList(LPDoubleLinkList *ppList);
#endif
