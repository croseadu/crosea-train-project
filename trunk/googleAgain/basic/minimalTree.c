#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/mytype.h"
#include "../include/binaryHeap.h"

typedef char ElementType;
typedef struct _Tok
{
  ElementType first;
  ElementType second;
  unsigned int weight;
}Tok, *LPTok;

#define INIT_SET_SIZE 5

#define INCRE_SET_SIZE 5
typedef struct _Node
{
  int parent;
  ElementType data;
}SetNode, *LPSetNode;

typedef struct _Set
{
  LPSetNode pNode;
  unsigned int capacity;
  unsigned int count;
}Set, *LPSet;

void skipSpace(const char **pp)
{
  while(**pp == ' ')
    ++*pp;
}

void initSet(LPSet *ppSet)
{
  LPSet pSet = (LPSet)malloc(sizeof(Set));
  *ppSet = NULL;
  if (NULL == pSet) {
    printf("Out Of Memory in %s", __func__);
    return;
  }
  
  pSet->pNode = (LPSetNode)malloc(sizeof(SetNode) * INIT_SET_SIZE);
  if (NULL == pSet->pNode) {
    printf ("Out Of Memory in %s", __func__);
    free(pSet);
    return;
  }

  pSet->capacity = INIT_SET_SIZE;
  pSet->count = 0;
  *ppSet = pSet;
}

void destroySet(LPSet *ppSet) 
{
  free((*ppSet)->pNode);
  free(*ppSet);
  *ppSet = NULL;
}

void unionNode(LPSet pSet, int lhs, int rhs)
{
  int i,j;
  
  i = findRoot(pSet, lhs);
  j = findRoot(pSet, rhs);
  if (pSet->pNode[i].parent > pSet->pNode[j].parent 
      || (pSet->pNode[i].parent == pSet->pNode[j].parent
	  && i > j)) {
    pSet->pNode[j].parent += pSet->pNode[i].parent;
    pSet->pNode[i].parent = j;
  }
  else {
    pSet->pNode[i].parent += pSet->pNode[j].parent;
    pSet->pNode[j].parent = i;
  }
}

int findRoot(LPSet pSet, int i)
{
  int k, j;
  k = i;
  while (pSet->pNode[k].parent >= 0)
    k = pSet->pNode[k].parent;

  while (i != k) {
    j = pSet->pNode[i].parent;
    pSet->pNode[i].parent = k;
    i = j;
  }
  return k;
}

int findNode(LPSet pSet, ElementType data)
{
  int i;
  for (i = 0; i < pSet->count; ++i) {
    if (pSet->pNode[i].data == data)
      return i;
  }
  
  return -1;
}

int insertNode(LPSet pSet, ElementType data)
{
  if (pSet->count >= pSet->capacity) {
    pSet->pNode = realloc(pSet->pNode, sizeof(SetNode) * 
			  (pSet->count + INCRE_SET_SIZE));
    if (NULL == pSet->pNode) {
      printf("Out Of Memory in %s", __func__);
      exit(-1);
    }
    pSet->capacity = pSet->count + INCRE_SET_SIZE;
  }

  (pSet->pNode+pSet->count)->parent = -1;
  (pSet->pNode+pSet->count)->data = data;
  
  ++pSet->count;
  return pSet->count-1;
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


bool less(void *lhs, void *rhs)
{
  int op0, op1;
  op0 = *(int *)lhs;
  op1 = *(int *)rhs;
  return op0 < op1;
}

void print(void *data)
{
  printf("%-5d", *(int*)data);
}

// DataStruct from prim algorithm.
typedef struct _GVertex
{
  ElementType data;
  unsigned int vertexIdx; //Index Edge in AdjMatrix

  // This is not real graph node member, only used
  // to keep all vertex linked together.
  struct _GVertex *pNextVertex;
}Vertex_P, *LPVertex_P;

typedef struct _Graph
{
  LPVertex_P pVertexSet;
  unsigned int count;
  int *adjMatrix;
}Graph_P, *LPGraph_P;


// DataStruct from Kruskal Algorithm.

struct _Edge;
typedef struct _GVertex2
{
  ElementType data;
  struct _Edge *pFirstEdge;

  // This is not real graph node member, only used
  // to keep all vertex linked together.
  struct _GVertex2 *pNextVertex;
}Vertex_K, *LPVertex_K;
typedef struct _Edge
{
  // in undirected Graph, no from or to.
  LPVertex_K pFrom;
  LPVertex_K pTo;
  unsigned int weight;
  
  struct _Edge *pNextFrom;
  struct _Edge *pNextTo;


  // This is not real graph edge member, only used
  // to keep all vertex linked together.
  struct _Edge *pNextEdge;
}Edge_K, *LPEdge_K;

typedef struct _Graph2
{
  LPVertex_K pVertexSet;
  LPEdge_K pEdgeSet;
  unsigned int count;
}Graph_K, *LPGraph_K;


void minimalTree_Prim(const char *p);
void minimalTree_Kruskal(const char *p);

int main()
{
  int i;
  char buf[] = "(1,2,6) (1,3,1) (1,4,5) (2,3,5) (3,4,5) (2,5,3) (3,5,6) (3,6,3) (4,6,2) (5,6,6)";
  char *p = buf;

  minimalTree_Prim(p);
  minimalTree_Kruskal(p);

  return 0;
}

bool initGraph_P(LPGraph_P *ppGraph)
{
  LPGraph_P pGraph = (LPGraph_P)malloc(sizeof(Graph_P));
  if (NULL == pGraph) {
    printf ("Out Of Memory in %s", __func__);
    return false;
  }
  pGraph->pVertexSet = NULL;
  pGraph->count = 0;
  pGraph->adjMatrix = NULL;

  *ppGraph = pGraph;
  return true;
}
void destroyGraph_P(LPGraph_P * ppGraph)
{
  LPVertex_P pIter, pNext;
  pIter = (*ppGraph)->pVertexSet;
  while(pIter) {
    pNext = pIter->pNextVertex;
    free(pIter);
    pIter = pNext;
  }
  free((*ppGraph)->adjMatrix);
  free(*ppGraph);
  *ppGraph = NULL;
}

LPVertex_P getOrInsertVertex_P(LPGraph_P pGraph, ElementType key)
{
  LPVertex_P pFind = pGraph->pVertexSet;
  LPVertex_P pIter;
  while(pFind && pFind->data != key)
    pFind = pFind->pNextVertex;
  if (pFind)
    return pFind;
  
  pFind = (LPVertex_P)malloc(sizeof(Vertex_P));
  if (NULL == pFind) {
    printf ("Out Of Memory in %s", __func__);
    return NULL;
  }
  pFind->data = key;
  pFind->pNextVertex = NULL;
  pFind->vertexIdx = pGraph->count;
  ++pGraph->count;
  
  if (pGraph->pVertexSet == NULL)
    pGraph->pVertexSet = pFind;
  else {
    pIter = pGraph->pVertexSet;
    while(pIter->pNextVertex)
      pIter = pIter->pNextVertex;
    pIter->pNextVertex = pFind;
  }

  return pFind;
}

LPVertex_P getVertexFromIdx(LPGraph_P pGraph, unsigned int idx)
{
  LPVertex_P pIter = pGraph->pVertexSet;

  while (pIter && pIter->vertexIdx != idx)
    pIter = pIter->pNextVertex;
  return pIter;
}

void createGraph_P(LPGraph_P pGraph, const char *p)
{
  Tok token;
  LPVertex_P pLhs, pRhs;
  const char *p2 = p;
  int i;

  while(getNextToken(&token, &p2)) {
    pLhs = getOrInsertVertex_P(pGraph, token.first);
    pRhs = getOrInsertVertex_P(pGraph, token.second);
  }
  pGraph->adjMatrix = (int*)malloc(sizeof(int)*pGraph->count*pGraph->count);

  for (i = 0; i < pGraph->count*pGraph->count; ++i) {  
    pGraph->adjMatrix[i] = -1;
  }
  for (i = 0; i < pGraph->count; ++i) {
    pGraph->adjMatrix[i*pGraph->count+i] = 0;
  }
    

  p2 = p;
  while(getNextToken(&token, &p2)) {
    pLhs = getOrInsertVertex_P(pGraph, token.first);
    pRhs = getOrInsertVertex_P(pGraph, token.second);
    
    *(pGraph->adjMatrix+pLhs->vertexIdx*pGraph->count + pRhs->vertexIdx)
      = token.weight;
    *(pGraph->adjMatrix+pRhs->vertexIdx*pGraph->count + pLhs->vertexIdx)
      = token.weight;
  }
}

void dumpGraph_P(LPGraph_P pGraph)
{
  int i, j;
  LPVertex_P pIter = pGraph->pVertexSet;
  putchar('\n');
  while (pIter) {
    printf("V[%d] = %c\n", pIter->vertexIdx, pIter->data);
    pIter = pIter->pNextVertex;
  }

  for (i = 0; i < pGraph->count; ++i) {
    for (j = 0; j < pGraph->count; ++j)
      printf("%4d", *(pGraph->adjMatrix + i*pGraph->count+j));
    putchar('\n');
  }
}

typedef struct _CloseEdge
{
  unsigned int adjVertexIdx;
  unsigned int cost;
  unsigned int vertexIdx;
}CloseEdge, *LPCloseEdge;

LPCloseEdge getMinEdge(LPCloseEdge pEdgeList, unsigned vertexNum)
{
  int i, minIdx;
  minIdx = -1;
  for (i = 0; i < vertexNum; ++i)
    if (pEdgeList[i].cost) {
      if (minIdx == -1)
	minIdx = i;
      else if (pEdgeList[i].cost < pEdgeList[minIdx].cost)
	minIdx = i;
    }
  return pEdgeList+minIdx;
}
void minimalTree_Prim(const char *p)
{
  LPGraph_P pGraph;
  LPCloseEdge pCloseEdge, pMinEdge;
  int i, j, k;
  int startIdx;
  LPVertex_P pStartVertex;

  initGraph_P(&pGraph);
  createGraph_P(pGraph, p);
  dumpGraph_P(pGraph);

  pCloseEdge = (LPCloseEdge)malloc(sizeof(CloseEdge) * pGraph->count);
  if (NULL == pCloseEdge) {
    printf ("Out Of Memory in %s", __func__);
    goto fail;
  }
  
  startIdx = 0;
  pStartVertex = getVertexFromIdx(pGraph, startIdx);
  for (i = 0; i < pGraph->count; ++i) {
    if (i != startIdx) {
      pCloseEdge[i].adjVertexIdx = startIdx;
      pCloseEdge[i].cost = (unsigned int)pGraph->adjMatrix[i*pGraph->count+startIdx];
      pCloseEdge[i].vertexIdx = i;
    }
  }
  pCloseEdge[startIdx].adjVertexIdx = startIdx;
  pCloseEdge[startIdx].cost = 0;
  pCloseEdge[startIdx].vertexIdx = startIdx;

  for (i = 0; i < pGraph->count -1; ++i) {
    pMinEdge = getMinEdge(pCloseEdge, pGraph->count);
    pMinEdge->cost = 0;
    printf("\nSelect Edge between [%d]V%c and [%d]V%c", 
	   pMinEdge->adjVertexIdx, getVertexFromIdx(pGraph, pMinEdge->adjVertexIdx)->data,
	   pMinEdge->vertexIdx, getVertexFromIdx(pGraph, pMinEdge->vertexIdx)->data);
    //pMinEdge->adjVertexIdx = pMinEdge->vertexIdx;
    for (j = 0; j < pGraph->count; ++j) {
      if (pCloseEdge[j].cost > 0 
	  && pGraph->adjMatrix[j*pGraph->count+pMinEdge->vertexIdx] != -1) {
	if (pGraph->adjMatrix[j*pGraph->count+pMinEdge->vertexIdx] < pCloseEdge[j].cost) {
	  pCloseEdge[j].cost = pGraph->adjMatrix[j*pGraph->count+pMinEdge->vertexIdx];
	  pCloseEdge[j].adjVertexIdx = pMinEdge->vertexIdx;
	}
      }
    }
  } 
  putchar('\n');  
 fail:
  if (pCloseEdge)
    free(pCloseEdge);
  destroyGraph_P(&pGraph);
}

bool initGraph_K(LPGraph_K *ppGraph)
{
  LPGraph_K pGraph;

  pGraph = (LPGraph_K)malloc(sizeof(Graph_K));
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

LPVertex_K getOrInsertVertex_K(LPGraph_K pGraph, ElementType key)
{
  LPVertex_K *ppIter, pVertex;
  ppIter = &pGraph->pVertexSet;
  while(*ppIter && (*ppIter)->data != key)
    ppIter = &(*ppIter)->pNextVertex;
  if (NULL != *ppIter)
    return *ppIter;
  
  pVertex = (LPVertex_K)malloc(sizeof(Vertex_K));
  if (NULL == pVertex) {
    printf ("Out Of Memory in %s", __func__);
    return NULL;
  }

  pVertex->data = key;
  pVertex->pFirstEdge = NULL;
  pVertex->pNextVertex = NULL;

  *ppIter = pVertex;
  ++pGraph->count;
  return pVertex;
}

bool addEdgeToGraph_K(LPGraph_K pGraph, LPVertex_K pFrom, LPVertex_K pTo, unsigned int weight)
{
  LPEdge_K pEdge, pIterEdge;
  
  pEdge = (LPEdge_K)malloc(sizeof(Edge_K));
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

void createGraph_K(LPGraph_K pGraph, const char *p)
{
  const char *p2 = p;
  LPVertex_K pLhs, pRhs;
  Tok token;

  while(getNextToken(&token, &p2)) {
    pLhs = getOrInsertVertex_K(pGraph, token.first);
    pRhs = getOrInsertVertex_K(pGraph, token.second);
    addEdgeToGraph_K(pGraph, pLhs, pRhs, token.weight);
  }
}

void destroyGraph_K(LPGraph_K *ppGraph)
{
  LPVertex_K pIterVertex, pNextVertex;
  LPEdge_K pIterEdge, pNextEdge;

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

bool lessEdge(void *lhs, void *rhs)
{
  LPEdge_K pLeftEdge, pRightEdge;

  pLeftEdge = *(LPEdge_K *)lhs;
  pRightEdge = *(LPEdge_K *)rhs;
  
  return pLeftEdge->weight < pRightEdge->weight;
}

bool equalEdge(void *lhs, void *rhs)
{
  LPEdge_K pLeftEdge, pRightEdge;

  pLeftEdge = *(LPEdge_K *)lhs;
  pRightEdge = *(LPEdge_K *)rhs;
  
  return pLeftEdge == pRightEdge;
}
void minimalTree_Kruskal(const char *p)
{
  LPGraph_K pGraph;
  LPBinaryHeap pHeap;
  LPEdge_K pIterEdge;
  LPVertex_K pIterVertex;
  LPSet pSet;
  int i;
  int leftIdx, rightIdx;


  initGraph_K(&pGraph);
  
  createGraph_K(pGraph, p);
  
  initBinaryHeap(&pHeap, sizeof(LPEdge_K), lessEdge, equalEdge);
  pIterEdge = pGraph->pEdgeSet;
  while (pIterEdge) {
    insertKeyToBinaryHeap(pHeap, &pIterEdge);
    pIterEdge = pIterEdge->pNextEdge;
  }
  
  initSet(&pSet);
  pIterVertex = pGraph->pVertexSet;
  while (pIterVertex) {
    insertNode(pSet, pIterVertex->data);
    pIterVertex = pIterVertex->pNextVertex;
  }
  
  for (i = 0; i < pGraph->count-1; ++i) {
    do {
      peekBinaryHeap(pHeap, &pIterEdge);
      removeRootFromBinaryHeap(pHeap);
      leftIdx = findNode(pSet, pIterEdge->pFrom->data);
      rightIdx = findNode(pSet, pIterEdge->pTo->data);
    } while(findRoot(pSet, leftIdx) == findRoot(pSet, rightIdx));
    unionNode(pSet, leftIdx, rightIdx);
    printf("\nSelect Edge between v[%c] and v[%c]", pIterEdge->pFrom->data, pIterEdge->pTo->data);
  }
  putchar('\n');

  destroySet(&pSet);
  destroyBinaryHeap(&pHeap);
  destroyGraph_K(&pGraph);
}
