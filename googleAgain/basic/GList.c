#include "../include/mytype.h"
#include <stdio.h>
#include <stdlib.h>

typedef char ElementType;

typedef struct _GNode
{
  bool isAtom;
  union {
    ElementType value;
    struct _GNode *pNode;
  };
  struct _GNode *pNext;
}GNode, *LPGNode;


void dumpGList(LPGNode pList)
{
  LPGNode pIter = NULL;
  if (pList == NULL)
    return;

  pIter = pList;
  while (pIter != NULL) {
    if (pIter->isAtom)
      putchar(pIter->value);
    else {
      putchar('(');
      dumpGList(pIter->pNode);
      putchar(')');
    }
    pIter = pIter->pNext;
    if (pIter)
      putchar(',');
  }
}

void skipSpace(const char **ppStr)
{
  const char *p = *ppStr;
  while (*p !='\0' && *p == ' ')
    ++p;
  *ppStr = p;
}

LPGNode createGList(const char **ppStr)
{
  LPGNode pNode;
  LPGNode *ppInsert;
  skipSpace(ppStr);
  
  if (**ppStr == '(') {
    ++*ppStr;
    skipSpace(ppStr);
    pNode = malloc(sizeof(GNode));
    pNode->isAtom = false;
    pNode->pNode = NULL;
    pNode->pNext = NULL;

    ppInsert = &pNode->pNode;
    while(**ppStr != ')') {
      *ppInsert = createGList(ppStr);
      skipSpace(ppStr);
      if (**ppStr == ',')
	++*ppStr;
      ppInsert = &(*ppInsert)->pNext;
    }
    *ppInsert = NULL;
    ++*ppStr;
  }
  else{
    pNode = (LPGNode)malloc(sizeof(GNode));
    pNode->isAtom = true;
    pNode->value = **ppStr;
    pNode->pNext = NULL;
    ++*ppStr;
  }

  return pNode;
}

int main()
{
  LPGNode pNode;
  const char *p = "(a,(b),(e,(c,())))";
  //const char *p = "((a,(),(e,f)),(b,(c,d,(g,h,(k,i))),e),())";
  pNode = createGList(&p);
  putchar('\n');
  dumpGList(pNode);
  putchar('\n');
  return 0;
}
