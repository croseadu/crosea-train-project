#ifndef _MY_LIST_H
#define _MY_LIST_H

#include <stdlib.h>
#include <string.h>
#include "mytype.h"

#define LIST_INIT_SIZE 10
#define LIST_INCRE_SIZE 5



struct _LIST
{
  char *data;
  unsigned int elementSize;
  unsigned int capacity;
  unsigned int size;
  PrintFunc printer;
  CompareFunc equal;
  CompareFunc less;
};
typedef struct _LIST List;
typedef struct _LIST * LPList;

bool initList(LPList *ppList, unsigned elementSize, 
	      PrintFunc printer, CompareFunc eq, CompareFunc less);
bool insertToListTail(LPList pList, void *val);
bool insertToList(LPList pList, void *val, int insertPos);
bool insertToListHead(LPList pList, void *val);
bool deleteListItem(LPList pList, int idx);
unsigned int deleteValInList(LPList pList, void *val);
unsigned int deleteIfInList(LPList pList, PredFunc pred);
void visitList(LPList pList, VisitFunc visitor);
void printList(LPList pList);
bool getItem(LPList pList, int idx, void *outVal);
int locateItem(LPList pList, PredFunc pred);
void sortList(LPList pList);
void clearList(LPList pList);
void destroyList(LPList *ppList);
#endif
