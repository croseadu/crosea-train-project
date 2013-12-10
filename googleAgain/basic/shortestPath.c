#include <stdio.h>
#include <stdlib.h>

#include "../include/queue.h"
#include "../include/stack.h"
#include "../include/set.h"

#define INIT_GRAPH_NODE 5
#define INCRE_GRAPH_NODE 5

typedef char ElementType;

struct _EDGE;

typedef struct _NODE
{
  ElementType data;
  unsigned int idx;
  struct _EDGE *pFirstInEdge;
  struct _EDGE *pFirstOutEdge;
}Node, *LPNode;

typedef struct _EDGE
{
  unsigned int fromIdx;
  unsigned int toIdx;
  int weight;
  struct _EDGE *pNextSameFrom;
  struct _EDGE *pNextSameTo;
  
  struct _EDGE *pNextEdge;
}Edge, *LPEdge;

typedef struct _DGraph
{
  LPNode pFirstNode;
  LPEdge pFirstEdge;
  unsigned int capacity;
  unsigned int count;
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
  printf(" V[%d]%c ", pNode->idx, pNode->data);
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

  pGraph->pFirstNode = (LPNode)malloc(sizeof(Node)*INIT_GRAPH_NODE);
  if (NULL == pGraph->pFirstNode) {
    free(pGraph);
    return false;
  }
  pGraph->capacity = INIT_GRAPH_NODE;
  pGraph->count = 0;
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

unsigned int  getOrInsertNode(LPDGraph pGraph, ElementType key)
{
  LPNode pNode = pGraph->pFirstNode;
  LPNode pNewNode;
  
  if (pGraph->count >= pGraph->capacity) {
    pGraph->pFirstNode = realloc(pGraph->pFirstNode, (pGraph->capacity+INCRE_GRAPH_NODE)*sizeof(Node));
    pGraph->capacity += INCRE_GRAPH_NODE;
  }
  
  pNewNode = pGraph->pFirstNode+pGraph->count;
  pNewNode->idx = pGraph->count;
  pNewNode->data = key;
  pNewNode->pFirstInEdge = NULL;
  pNewNode->pFirstOutEdge = NULL;


  ++pGraph->count;
 
  return pNewNode->idx;
}

bool addEdge(LPDGraph pGraph, unsigned int fromIdx, unsigned int toIdx, unsigned int weight)
{
  LPEdge pNewEdge;

  pNewEdge = (LPEdge)malloc(sizeof(Edge));
  if (NULL == pNewEdge) {
    printf ("Out Of Memory in %s", __func__);
    return false;
  }
  
  pNewEdge->fromIdx = fromIdx;
  pNewEdge->toIdx = toIdx;
  pNewEdge->pNextSameFrom = (pGraph->pFirstNode+fromIdx)->pFirstOutEdge;
  (pGraph->pFirstNode+fromIdx)->pFirstOutEdge = pNewEdge;
  pNewEdge->pNextSameTo = (pGraph->pFirstNode+toIdx)->pFirstInEdge;
  (pGraph->pFirstNode+toIdx)->pFirstInEdge = pNewEdge;

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
    fromIdx = getOrInsertNode (pGraph, token.first);
    toIdx = getOrInsertNode (pGraph, token.second);
    addEdge(pGraph, fromIdx, toIdx, token.weight);
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
  free(pGraph->pFirstNode);
  pIterEdge = pGraph->pFirstEdge;
  while (pIterEdge) {
    pNextEdge = pIterEdge->pNextEdge;
    free (pIterEdge);
    pIterEdge = pIterEdge->pNextEdge;
  }
  *ppGraph = NULL;
}

void Dijkstra(LPDGraph);
void naiveDynamicProgramming(LPDGraph);
void BellmanFord(LPDGraph);
void FloydWarShall(LPDGraph);
void Johnson(LPDGraph);

int main()
{

  LPDGraph pGraph = NULL;

  initGraph(&pGraph);
  createGraph(pGraph);
  
  Dijkstra();
  naiveDynamicProgramming();
  BellmanFord();
  FloydWarShall();
  Johnson();

  destroyGraph(&pGraph);


  return 0;
}

//Non-Negative Weight
void Dijkstra(LPDGraph pGraph)
{
#define MAX_LENGTH 0x7FFFFFFF
  bool *visited = NULL;
  int *prev = NULL;
  int *dist = NULL;
  int nodeNum = pGraph->count;
  int i, cur, prevNode, path;
  LPQueue pQueue;
  LPStack pStack;
  LPEdge pIterEdge;

  visited = (bool*)malloc(sizeof(bool)*pGraph->count);
  prev = (int *)malloc(sizeof(int)*pGraph->count);
  dist = (int *)malloc(sizeof(int)*pGraph->count);
  if (NULL == visited 
      || NULL == prev
      || NULL == dist) {
    if (visited)
      free(visited);
    if (prev)
      free(prev);
    if (dist)
      free(dist);
    return;
  }

  for (i = 0; i < nodeNum; ++i) {
    visited[i] = false;
    prev[i] = -1;
    dist[i] = MAX_LENGTH;
  }
  dist[0] = 0;
  cur = 0;
  initQueue(&pQueue, sizeof(int));
  initStack(&pStack, sizeof(int));
  enQueue(pQueue, &cur);

  while (!isEmpty(pQueue)) {
    deQueue(pQueue, &cur);
    visited[cur] = true;
    
    pIterEdge = (pGraph->pFirstNode+cur)->pFirstOutEdge;
    while (pIterEdge) {
      if (dist[cur] + pIterEdge->weight < dist[pIterEdge->toIdx]) {
	dist[pIterEdge->toIdx] = dist[cur] + pIterEdge->weight;
	prev[pIterEdge->toIdx] = cur;
	if (visited[pIterEdge->toIdx] == false)
	  enQueue(pQueue,&pIterEdge->toIdx);
      }
      pIterEdge = pIterEdge->pNextSameFrom;
    }
  }

  for (i = 1; i < nodeNum; ++i) {
    prevNode = prev[i];
    while(1) {
      push(pStack, &prevNode);
      if (prevNode == 0)
	break;
      prevNode = prev[prevNode];
    }
    printf("\nFrom V[%d] to V[%d]: \n", 0, i);
    while (!isStackEmpty(pStack)) {
      pop(pStack, &path);
      printf ("V[%d]->", path);
    }
    printf("V[%d]\n", i);
  }

  destroyStack(&pStack);
  destroyQueue(&pQueue)
  free(visited);
  free(prev);
  free(dist);
}

void naiveDynamicProgramming(LPDGraph pGraph){}
void BellmanFord(LPDGraph pGraph){}
void FloydWarShall(LPDGraph pGraph){}
void Johnson(LPDGraph pGraph){}
