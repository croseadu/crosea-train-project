#ifndef _MY_LINK_LIST_H
#define _MY_LINK_LIST_H

#include "mytype.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct _NODE
{
  char *pData;
  struct _NODE *pNext;
};
typedef struct _NODE Node;
typedef struct _NODE *LPNode;

typedef struct _LIST
{
  Node *pHead;
  unsigned int elementSize;
  PrintFunc printer;
  CompareFunc equal;
  CompareFunc less;
} LinkList;

typedef LinkList * LPLinkList;

bool initLinkList(LPLinkList *ppList, unsigned int elementSize, PrintFunc printer, CompareFunc eq, CompareFunc less);
bool insertToLinkListHead(LPLinkList pList, void * pVal);
bool insertToLinkListTail(LPLinkList pList, void *pVal);
bool insertToLinkList(LPLinkList pList, void *pVal, Node *pInsertPos);
void deleteNodeInLinkList(LPLinkList pList, Node *pDelete);
unsigned int deleteValInLinkList(LPLinkList pList, void *val);
unsigned int deleteIfInLinkList(LPLinkList pList, PredFunc pred);
void visitLinkList(LPLinkList pList, VisitFunc visitor);
void printLinkList(LPLinkList pList);
void clearLinkList(LPLinkList pList);
void sortLinkList(LPLinkList pList);
void reverseLinkList(LPLinkList pList);
void destroyLinkList(LPLinkList *ppList);
#endif
