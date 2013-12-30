//normal algorithm.
//gabow algorithm


#include "../include/mytype.h"
#include "../include/set.h"
#include "../include/stack.h"
#include "../include/queue.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define ElementType char
#define NodeType LPVertex


typedef struct _Tok
{
  ElementType first;
  ElementType second;
  unsigned int weight;
}Tok, *LPTok;

// For Graph
struct _Edge;
typedef struct _Vertex
{
  ElementType data;
  int vertexId;
  struct _Edge *pFirstEdge;

  // This is not real graph node member, only used
  // to keep all vertex linked together.
  struct _Vertex *pNextVertex;
}Vertex, *LPVertex;
typedef struct _Edge
{
  // in undirected Graph, no from or to.
  LPVertex pFrom;
  LPVertex pTo;
  unsigned int weight;
  
  struct _Edge *pNextFrom;
  struct _Edge *pNextTo;


  // This is not real graph edge member, only used
  // to keep all vertex linked together.
  struct _Edge *pNextEdge;
}Edge, *LPEdge;

typedef struct _Graph
{
  LPVertex pVertexSet;
  LPEdge pEdgeSet;
  unsigned int count;
}Graph, *LPGraph;


void vertexPrint(void *key)
{
  LPVertex pNode;

  pNode = *(LPVertex *)key;
  printf(" V[%c] ", pNode->data);
}

bool vertexEq(void * lhs, void *rhs)
{
  LPVertex pLeft, pRight;
  pLeft = *(LPVertex *)lhs;
  pRight = *(LPVertex *)rhs;
  return pLeft == pRight;
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
  skipSpace(pp);
  if (**pp != ',')
    return false;
  ++*pp;
  skipSpace(pp);
  pTok->second = **pp;
  ++*pp;
  skipSpace(pp);

  /*
  if (**pp != ',')
    return false;
  ++*pp;
  skipSpace(pp);

  sscanf(*pp, "%d", &pTok->weight);
  while(isdigit(**pp))
    ++*pp;
  skipSpace(pp);
  */
  if (**pp != ')')
    return false;
  ++*pp;
  return true;
}


bool initGraph(LPGraph *ppGraph)
{
  LPGraph pGraph;

  pGraph = (LPGraph)malloc(sizeof(Graph));
  if (NULL == pGraph) {
    printf ("Out Of Memory in %s", __func__);
    return false;
  }
  pGraph->pVertexSet = NULL;
  pGraph->pEdgeSet = NULL;
  pGraph->count = 0;
  *ppGraph = pGraph;
  return true;
}

LPVertex getOrInsertVertex(LPGraph pGraph, ElementType key)
{
  LPVertex *ppIter, pVertex;
  ppIter = &pGraph->pVertexSet;
  while(*ppIter && (*ppIter)->data != key)
    ppIter = &(*ppIter)->pNextVertex;
  if (NULL != *ppIter)
    return *ppIter;
  
  pVertex = (LPVertex)malloc(sizeof(Vertex));
  if (NULL == pVertex) {
    printf ("Out Of Memory in %s", __func__);
    return NULL;
  }

  pVertex->data = key;
  pVertex->pFirstEdge = NULL;
  pVertex->pNextVertex = NULL;
  pVertex->vertexId = pGraph->count;

  *ppIter = pVertex;
  ++pGraph->count;
  return pVertex;
}

bool addEdgeToGraph(LPGraph pGraph, LPVertex pFrom, LPVertex pTo, unsigned int weight)
{
  LPEdge pEdge, pIterEdge;
  
  pEdge = (LPEdge)malloc(sizeof(Edge));
  if (NULL == pEdge) {
    printf ("OUt Of Memory in %s", __func__);
    return false;
  }

  pEdge->pFrom = pFrom;
  pEdge->pTo = pTo;
  pEdge->pNextFrom = pFrom->pFirstEdge;
  pFrom->pFirstEdge = pEdge;

  pEdge->pNextTo = pTo->pFirstEdge;
  pTo->pFirstEdge = pEdge;
  pEdge->pNextEdge = NULL;
  pEdge->weight = weight;

  if (pGraph->pEdgeSet == NULL)
    pGraph->pEdgeSet = pEdge;
  else {
    pIterEdge = pGraph->pEdgeSet;
    while (pIterEdge->pNextEdge)
      pIterEdge = pIterEdge->pNextEdge;
    pIterEdge->pNextEdge = pEdge;
  }
  return true;
}

void createGraph(LPGraph pGraph, const char *p)
{
  const char *p2 = p;
  LPVertex pLhs, pRhs;
  Tok token;

  while(getNextToken(&token, &p2)) {
    pLhs = getOrInsertVertex(pGraph, token.first);
    pRhs = getOrInsertVertex(pGraph, token.second);
    addEdgeToGraph(pGraph, pLhs, pRhs, 0);
  }
}

void destroyGraph(LPGraph *ppGraph)
{
  LPVertex pIterVertex, pNextVertex;
  LPEdge pIterEdge, pNextEdge;

  pIterVertex = (*ppGraph)->pVertexSet;
  while (pIterVertex) {
    pNextVertex = pIterVertex->pNextVertex;
    free (pIterVertex);
    pIterVertex = pNextVertex;
  }

  pIterEdge = (*ppGraph)->pEdgeSet;
  while (pIterEdge) {
    pNextEdge = pIterEdge->pNextEdge;
    free (pIterEdge);
    pIterEdge = pNextEdge;
  }
  free (*ppGraph);
  *ppGraph = NULL;
}


void findArticul(LPGraph pGraph);

int main()
{
  char buf[] = "(A, B) (A, C) (A, F) (A, L) (B, C) (B, D) (B, G) (B, H) (B, M) (D, E) (G, I) (G, H) (G, K) (H, K) (J, L) (J, M) (L, M)";
  char *p = buf;

  LPGraph pGraph;
  
  initGraph(&pGraph);
  createGraph(pGraph, p);
  
  findArticul(pGraph);
  
  
  destroyGraph(&pGraph);

}

void DFSArticul(LPGraph pGraph, LPVertex pCurVertex, int *pCount, int *low, bool *visitedFlag, int *visitedOrder, LPStack pStack)
{
  int min;
  LPEdge pIterEdge, pNextEdge;
  LPVertex pIterVertex, pBCCVertex;
  bool isArticul = false;
  int bccCount;

  push(pStack, &pCurVertex);
  visitedFlag[pCurVertex->vertexId] = true;
  min = (*pCount)++;
  visitedOrder[pCurVertex->vertexId] = min;

  pIterEdge = pCurVertex->pFirstEdge;
  while (pIterEdge) {
    if (pIterEdge->pFrom == pCurVertex) {
      pIterVertex = pIterEdge->pTo;
      pNextEdge = pIterEdge->pNextFrom;
    }
    else {
      pIterVertex = pIterEdge->pFrom;
      pNextEdge = pIterEdge->pNextTo;
    }
    if (!visitedFlag[pIterVertex->vertexId]) {
      DFSArticul(pGraph, pIterVertex, pCount, low, visitedFlag, visitedOrder, pStack);
      if (min > low[pIterVertex->vertexId])
	min = low[pIterVertex->vertexId];
      if (low[pIterVertex->vertexId] >= visitedOrder[pCurVertex->vertexId]) {
	isArticul = true;
      }
      if (low[pIterVertex->vertexId] == visitedOrder[pCurVertex->vertexId]) {
	bccCount = 0;
	printf("\nFind BCC:");
	do {
	  ++bccCount;
	  pop(pStack, &pBCCVertex);
	  printf(" V[%c] ", pBCCVertex->data);
	  
	}while (pBCCVertex != pIterVertex);
	if (bccCount > 1)
	  printf("V[%c] \n", pCurVertex->data);
      }
    }
    else {
      if (min > visitedOrder[pIterVertex->vertexId])
	min = visitedOrder[pIterVertex->vertexId];
    }
    pIterEdge = pNextEdge;
  }

  low[pCurVertex->vertexId] = min;
  if (isArticul) {
    printf ("\n Articul V[%c]", pCurVertex->data);
  }
}

void findArticul(LPGraph pGraph)
{
  bool *visitedFlag;
  int *low;
  int *visitedOrder;
  int n = pGraph->count;
  int count;
  LPEdge pIterEdge, pNextEdge;
  LPVertex pRootVertex, pStartVertex, pIterVertex, pBCCVertex;
  LPStack pStack;
  int bccCount;

  visitedFlag = (bool *)malloc(sizeof(bool)*n);
  low = (int *)malloc(sizeof(int)*n);
  visitedOrder = (int *)malloc(sizeof(int)*n);

  if (NULL == visitedFlag ||
      NULL == low ||
      NULL == visitedOrder) {
    printf ("Out Of Memory in %s", __func__);
    goto cleanup;
  }

  initStack(&pStack, sizeof(LPVertex));

  count = 0;
  visitedFlag[0] = true;
  low[0] = 0;
  visitedOrder[0] = count++;
  
  pRootVertex = pGraph->pVertexSet;
  push(pStack, &pRootVertex);
  pIterEdge = pRootVertex->pFirstEdge;
  if (pIterEdge->pFrom == pRootVertex) {
    pStartVertex = pIterEdge->pTo;
    pIterEdge = pIterEdge->pNextFrom;
  }
  else {
    pStartVertex = pIterEdge->pFrom;
    pIterEdge = pIterEdge->pNextTo;
  }
  DFSArticul(pGraph, pStartVertex, &count, low, visitedFlag, visitedOrder, pStack);
  if (low[pStartVertex->vertexId]  == visitedOrder[pRootVertex->vertexId]) {
    bccCount = 0;
    printf("\nFind BCC:");
    do {
      ++bccCount;
      pop(pStack, &pBCCVertex);
      printf(" V[%c] ", pBCCVertex->data);

    }while (pBCCVertex != pStartVertex);
    if (bccCount > 1)
      printf("V[%c] \n", pRootVertex->data);
  }
  if (count < pGraph->count) {
    // Root Vertex is an articul
    printf ("\n Articul V[%c]", pRootVertex->data);
    while (pIterEdge) {
      if (pIterEdge->pFrom == pRootVertex) {
	pIterVertex = pIterEdge->pTo;
	pNextEdge = pIterEdge->pNextFrom;
      }
      else {
	pIterVertex = pIterEdge->pFrom;
	pNextEdge = pIterEdge->pNextTo;
      }
      if (!visitedFlag[pIterVertex->vertexId]) {
	DFSArticul(pGraph, pIterVertex, &count, low, visitedFlag, visitedOrder, pStack);
	if (low[pStartVertex->vertexId]  == visitedOrder[pRootVertex->vertexId]) {
	  printf("\nFind BCC:");
	  bccCount = 0;
	  do {
	    ++bccCount;
	    pop(pStack, &pBCCVertex);
	    printf(" V[%c] ", pBCCVertex->data);
	  
	  }while (pBCCVertex != pIterVertex);
	  if (bccCount > 1)
	    printf("V[%c] \n", pRootVertex->data);
	}
      	      
      }
      
      pIterEdge = pNextEdge;
    }
  }
  putchar('\n');

  destroyStack(&pStack);
 cleanup:
  if (visitedFlag) 
    free(visitedFlag);
  if (low)
    free(low);
  if (visitedOrder)
    free(visitedOrder);
}
