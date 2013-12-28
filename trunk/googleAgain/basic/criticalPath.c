#include <stdio.h>
#include <stdlib.h>
#include "../include/set.h"
#include "../include/map.h"
#include "../include/stack.h"
#include "../include/queue.h"
#include "../include/mytype.h"

typedef char ElementType;

struct _EDGE;

typedef struct _NODE
{
  ElementType data;
  struct _EDGE *pFirstInEdge;
  struct _EDGE *pFirstOutEdge;

  struct _NODE *pNextNode;
}Node, *LPNode;

typedef struct _EDGE
{
  LPNode pFrom;
  LPNode pTo;
  unsigned int weight;
  struct _EDGE *pNextSameFrom;
  struct _EDGE *pNextSameTo;
  
  struct _EDGE *pNextEdge;
}Edge, *LPEdge;

typedef struct _DGraph
{
  LPNode pFirstNode;
  LPEdge pFirstEdge;

}DGraph, *LPDGraph;

typedef struct _Tok
{
  ElementType first;
  ElementType second;
  int weight;
}Tok, *LPTok;

bool keyEq(void * lhs, void *rhs)
{
  LPNode pLeft, pRight;
  pLeft = *(LPNode *)lhs;
  pRight = *(LPNode *)rhs;
  return pLeft == pRight;
}

void keyPrint(void *key)
{
  LPNode pNode;

  pNode = *(LPNode *)key;
  printf(" V[%c] ", pNode->data);
}

void valPrint(void *val)
{
  int degree;
  degree = *(int *)val;
  printf(" %d ", degree);
}

bool initGraph(LPDGraph *ppGraph)
{
  LPDGraph pGraph;

  pGraph = (LPDGraph)malloc(sizeof(DGraph));
  if (NULL == pGraph) {
    printf ("Out Of Memory in %s", __func__);
    return false;
  }

  pGraph->pFirstNode = NULL;
  pGraph->pFirstEdge = NULL;
  *ppGraph = pGraph;
  return true;
}

void skipSpace(const char **pp)
{
  while(**pp == ' ')
    ++*pp;
}

bool getNextToken(LPTok pTok, const char **pp)
{
  skipSpace(pp);
  if (**pp == '\0')
    return false;
  if (**pp != '(')
    return false;
  ++*pp;
  skipSpace(pp);
  pTok->first = **pp;
  ++*pp;
  if (**pp != ',')
    return false;
  ++*pp;
  pTok->second = **pp;
  ++*pp;
  skipSpace(pp);

  
  if (**pp != ',')
    return false;
  ++*pp;
  skipSpace(pp);
  
  sscanf(*pp, "%d", &pTok->weight);
  while(isdigit(**pp))
    ++*pp;
  skipSpace(pp);
  

  if (**pp != ')')
    return false;
  ++*pp;
  return true;
}

LPNode getOrInsertNode(LPDGraph pGraph, ElementType key)
{
  LPNode *ppNode = &pGraph->pFirstNode;
  LPNode pNewNode;
  while (*ppNode != NULL) {
    if ((*ppNode)->data == key)
      return *ppNode;
    ppNode = &(*ppNode)->pNextNode;
  }
  
  pNewNode = (LPNode)malloc(sizeof(Node));
  if (NULL == pNewNode) {
    printf ("Out Of Memory in %s", __func__);
    return NULL;
  }
  
  pNewNode->data = key;
  pNewNode->pFirstInEdge = NULL;
  pNewNode->pFirstOutEdge = NULL;
  pNewNode->pNextNode = NULL;
  *ppNode = pNewNode;
  return pNewNode;
}

bool addEdge(LPDGraph pGraph, LPNode from, LPNode to, unsigned int weight)
{
  LPEdge pNewEdge;

  pNewEdge = (LPEdge)malloc(sizeof(Edge));
  if (NULL == pNewEdge) {
    printf ("Out Of Memory in %s", __func__);
    return false;
  }
  
  pNewEdge->pFrom = from;
  pNewEdge->pTo = to;
  pNewEdge->pNextSameFrom = from->pFirstOutEdge;
  from->pFirstOutEdge = pNewEdge;
  pNewEdge->pNextSameTo = to->pFirstInEdge;
  to->pFirstInEdge = pNewEdge;
  pNewEdge->weight = weight;

  pNewEdge->pNextEdge = pGraph->pFirstEdge;
  pGraph->pFirstEdge = pNewEdge;
  return true;
}

void createGraph(LPDGraph pGraph, const char *p)
{
  const char *p2 = p;
  Tok token;
  LPNode pFrom, pTo;

  while (getNextToken(&token, &p2)) {
    pFrom = getOrInsertNode (pGraph, token.first);
    pTo = getOrInsertNode (pGraph, token.second);
    addEdge(pGraph, pFrom, pTo, token.weight);
  }
}

void destroyGraph(LPDGraph *ppGraph)
{
  LPDGraph pGraph;
  LPNode pIterNode, pNextNode;
  LPEdge pIterEdge, pNextEdge;

  if (NULL == ppGraph || NULL == *ppGraph)
    return;
  
  pGraph = *ppGraph;
  pIterNode = pGraph->pFirstNode;
  while (pIterNode) {
    pNextNode = pIterNode->pNextNode;
    free(pIterNode);
    pIterNode = pNextNode;
  }
  pIterEdge = pGraph->pFirstEdge;
  while (pIterEdge) {
    pNextEdge = pIterEdge->pNextEdge;
    free (pIterEdge);
    pIterEdge = pIterEdge->pNextEdge;
  }
  *ppGraph = NULL;
}


void nodePrint(void *key)
{
  LPNode pNode;

  pNode = *(LPNode *)key;
  printf(" V[%c] ", pNode->data);
}

bool nodeEq(void * lhs, void *rhs)
{
  LPNode pLeft, pRight;
  pLeft = *(LPNode *)lhs;
  pRight = *(LPNode *)rhs;
  return pLeft == pRight;
}
int calcDegree(LPNode pNode)
{
  LPEdge pIterEdge = pNode->pFirstInEdge;
  int d = 0;
  while (pIterEdge) {
    ++d;
    pIterEdge = pIterEdge->pNextSameTo;
  }
  return d;
}

void topoOrderSort(LPDGraph pGraph, LPStack pReverseOrder, LPMap pEarly)
{
  LPStack pStack;
  LPNode pNode, pSucc, pPred;
  LPEdge pEdge;
  LPMap pMap;
  int nodeNum, degree;
  int earlyStart, predStart;

  initStack(&pStack, sizeof(LPNode));
  initMap(&pMap, sizeof(LPNode),
	  sizeof(int), keyEq,
	  keyPrint, valPrint);

  pNode = pGraph->pFirstNode;
  nodeNum = 0;
  while (pNode) {
    degree = calcDegree(pNode);
    insertEntry(pMap, &pNode, &degree);
    if (degree == 0) {
      push(pStack, &pNode);
    }
    ++nodeNum;
    pNode = pNode->pNextNode;
  }
  printf ("\nCalculate early: \n");
  while (!isStackEmpty(pStack)) {
    pop(pStack, &pNode);
    push(pReverseOrder, &pNode);
    printf("\nV[%c] ", pNode->data);
    --nodeNum;
    
    earlyStart = 0;
    pEdge = pNode->pFirstInEdge;
    while (pEdge) {
      pPred = pEdge->pFrom;
      findValueViaKey(pEarly, &pPred, &predStart);
      if (predStart + pEdge->weight > earlyStart)
	earlyStart = predStart + pEdge->weight;
      pEdge = pEdge->pNextSameTo;
    }
    insertOrModifyEntry(pEarly, &pNode, &earlyStart);
    printf (" e = %d ", earlyStart);
    pEdge = pNode->pFirstOutEdge;
    while (pEdge) {
      pSucc = pEdge->pTo;
      findValueViaKey(pMap, &pSucc, &degree);
      --degree;
      insertOrModifyEntry(pMap, &pSucc, &degree);
      if (degree == 0)
	push (pStack, &pSucc);
      pEdge = pEdge->pNextSameFrom;
    }
  }

  if (nodeNum > 0) {
    printf ("Topo Order Sort failed because of a cycle in Graph\n");
  }
  
  destroyMap(&pMap);
  destroyStack(&pStack);
}


int main()
{
  LPDGraph pGraph;
  LPNode pIterNode, pStartNode, pEndNode;
  LPMap pEarly, pLate;
  LPStack pLateOrder;
  char buf[] = "(1,2, 6) (1,3, 4) (1,4, 5) (2,5, 1) (3,5, 1) (4,6, 2) (5,7, 9) (5,8, 7) (6,8, 4) (7,9, 2) (8,9, 4) ";
  char *p = buf;
  int early;
  int late, minLate, maxLate;
  LPEdge pIterEdge;
  

  initMap(&pEarly, sizeof(LPNode),
	  sizeof(int), keyEq,
	  keyPrint, valPrint);
  initMap(&pLate, sizeof(LPNode),
	  sizeof(int), keyEq,
	  keyPrint, valPrint);
  initStack(&pLateOrder, sizeof(LPNode));

  initGraph(&pGraph);
  createGraph(pGraph, p);
  
  topoOrderSort(pGraph, pLateOrder, pEarly);
  pStartNode = pGraph->pFirstNode;
  pEndNode = pStartNode;
  while (pEndNode->pNextNode)
    pEndNode = pEndNode->pNextNode;

  printf("\ncalculate Late: \n");
  while (!isStackEmpty(pLateOrder)) {
    pop(pLateOrder, &pIterNode);
    if (pIterNode == pEndNode) {
      findValueViaKey(pEarly, &pEndNode, &early);
      insertOrModifyEntry(pLate, &pEndNode, &early);
      maxLate = early;
      continue;
    }
    pIterEdge = pIterNode->pFirstOutEdge;
    minLate = maxLate;
    while (pIterEdge) {
      findValueViaKey(pLate, &pIterEdge->pTo, &late);
      if (late - pIterEdge->weight < minLate)
	minLate = late - pIterEdge->weight;
      pIterEdge = pIterEdge->pNextSameFrom;
    }
    insertOrModifyEntry(pLate, &pIterNode, &minLate);
    printf("\nV[%c] ", pIterNode->data);
    printf(" l = %d", minLate);
  }  
  putchar('\n');

  pIterNode = pGraph->pFirstNode;
  while (pIterNode) {
    printf("\n");
    nodePrint(&pIterNode);
    findValueViaKey(pEarly, &pIterNode, &early);
    pIterEdge = pIterNode->pFirstOutEdge;
    while (pIterEdge) {
      findValueViaKey(pLate, &pIterEdge->pTo, &late);
      if (late - pIterEdge->weight == early) {
	printf("*->");
	nodePrint(&pIterEdge->pTo);
      }
      pIterEdge = pIterEdge->pNextSameFrom;
    }
    pIterNode = pIterNode->pNextNode;
  }
  putchar('\n');

  destroyStack(&pLateOrder);
  destroyGraph(&pGraph);
  destroyMap(&pEarly);
  destroyMap(&pLate);
  return 0;
}
