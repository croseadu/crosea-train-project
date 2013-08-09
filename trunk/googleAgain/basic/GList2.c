#include "../include/mytype.h"

typedef char ElementType;
#include <stdio.h>
#include <stdlib.h>

typedef struct _GNode
{
  bool isAtom;
  union {
    ElementType value;
    struct { struct _GNode *hp, *tp; } ptr;
  };
}GNode , * LPGNode;

void skipSpace(const char **pp)
{
  while(**pp && **pp == ' ')
    ++*pp;
}

void dumpGList(LPGNode pList)
{
  LPGNode pIter;
  if (NULL == pList) {
    printf("()");
    return;
  }
  if (pList->isAtom) {
    putchar(pList->value);
    return;
  }
  putchar('(');
  pIter = pList;
  while(pIter) {
    dumpGList(pIter->ptr.hp);
    pIter = pIter->ptr.tp;
    if (pIter)
      putchar(',');
  }
  putchar(')');
}

LPGNode createGList(const char **pp)
{
  LPGNode pNode, pNode2;
  LPGNode *pInsert;
  skipSpace(pp);
  if (**pp == '\0')
    return NULL;
  if(**pp == '(') {
    ++*pp;
    if (*(*pp) ==')') {
      ++*pp;
      return NULL;
    }
    pNode = (LPGNode)malloc(sizeof(GNode));
    pNode->isAtom = false;
    pNode->ptr.hp = createGList(pp);
    pInsert = &pNode->ptr.tp;
    while(**pp != ')') {
      pNode2 = (LPGNode)malloc(sizeof(GNode));
      *pInsert = pNode2;
      ++*pp; // skip ,
      pNode2->isAtom = false;
      (*pInsert)->ptr.hp = createGList(pp);
      pInsert = &(*pInsert)->ptr.tp;
    }
    *pInsert = NULL;
    ++*pp;
  }
  else {
    pNode = (LPGNode)malloc(sizeof(GNode));
    pNode->isAtom = true;
    pNode->value = **pp;
    ++*pp;
  }
  return pNode;
}


int main()
{

  LPGNode pNode;
  //const char pp[] = "(a,(b),(e,(c,())))";
  const char pp[] = "((a,(),(e,f)),(b,(c,d,(g,h,(k,i))),e),())";
  const char *p = pp;

  pNode = createGList(&p);
  putchar('\n');
  dumpGList(pNode);
  putchar('\n');
  printf("%s\n",pp);
  return 0;
}
