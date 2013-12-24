#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "../include/queue.h"
#include "../include/priorityQueue.h"
#include "../include/stack.h"
#include "../include/set.h"

#define INIT_GRAPH_NODE 5
#define INCRE_GRAPH_NODE 5

#define M 15
int path[M][M][M];

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
  unsigned int i = 0;

  while (i < pGraph->count) {
    if ((pGraph->pFirstNode+i)->data == key)
      break;
    ++i;
  }
  if (i < pGraph->count)
    return i;
  
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
  pNewEdge->weight = weight;
  pNewEdge->pNextEdge = pGraph->pFirstEdge;
  pGraph->pFirstEdge = pNewEdge;
  return true;
}

void createGraph(LPDGraph pGraph, const char *p)
{
  const char *p2 = p;
  Tok token;
  int fromIdx, toIdx;

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
void DijkstraWithHeap(LPDGraph);
void naiveDynamicProgramming(LPDGraph);
void BellmanFord(LPDGraph);
void FloydWarShall(LPDGraph);
void Johnson(LPDGraph);

int main()
{

  LPDGraph pGraph = NULL;
  char in[] = "(A,C,10) (A,E,30) (A,F,100) (B,C,5) (C,D,50) (E,D,20) (D,F,10) (E,F,60)";
  const char *p = in;

  initGraph(&pGraph);
  createGraph(pGraph, p);
  
  Dijkstra(pGraph);
  DijkstraWithHeap(pGraph);
  naiveDynamicProgramming(pGraph);
  BellmanFord(pGraph);
  FloydWarShall(pGraph);
  //Johnson();

  destroyGraph(&pGraph);


  return 0;
}
#define MAX_LENGTH 0x7FFFFFFF

int findNoVisitedMin(int *dist, int *flag, int n)
{
  int i;
  int minIdx;

  i = 0;
  while (flag[i] || dist[i] == MAX_LENGTH)
    ++i;
  minIdx = i;
  ++i;
  
  while (i < n) {
    if (flag[i] ||
	dist[i] == MAX_LENGTH ||
	dist[i] > dist[minIdx]) {
      ++i;
      continue;
    }
    minIdx = i;
    ++i;
  }
  return minIdx;
}

//Non-Negative Weight
void Dijkstra(LPDGraph pGraph)
{
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
  initStack(&pStack, sizeof(int));

  printf("\nDijstra :");
  for (i = 0; i < nodeNum; ++i) {
    cur = findNoVisitedMin(dist, visited, nodeNum);
    if (cur >= nodeNum) {
      break;
    }
    visited[cur] = true;
    printf ("\nFind Min %c", (pGraph->pFirstNode+cur)->data);
    pIterEdge = (pGraph->pFirstNode+cur)->pFirstOutEdge;
    while (pIterEdge) {
      if (dist[cur] + pIterEdge->weight < dist[pIterEdge->toIdx]) {
	printf("\nUpdate To, V[%c] ", (pGraph->pFirstNode+pIterEdge->toIdx)->data);
	assert (visited[pIterEdge->toIdx] == false);
	dist[pIterEdge->toIdx] = dist[cur] + pIterEdge->weight;
	prev[pIterEdge->toIdx] = cur;
      }
      pIterEdge = pIterEdge->pNextSameFrom;
    }
  }
  printf("\nDump Path:");
  for (i = 1; i < nodeNum; ++i) {
    if (dist[i] == MAX_LENGTH) {
      printf ("\nNo Path between V[%c] to V[%c]",pGraph->pFirstNode->data, (pGraph->pFirstNode+i)->data);
      continue;
    }
    prevNode = prev[i];
    while(1) {
      push(pStack, &prevNode);
      if (prevNode == 0)
	break;
      prevNode = prev[prevNode];
    }
    printf("\nFrom V[%c] to V[%c] dist = %d: ", pGraph->pFirstNode->data, (pGraph->pFirstNode+i)->data, dist[i]);
    while (!isStackEmpty(pStack)) {
      pop(pStack, &path);
      printf ("V[%c]->",  (pGraph->pFirstNode+path)->data);
    }
    printf("V[%c]\n", (pGraph->pFirstNode+i)->data);
  }

  destroyStack(&pStack);
  free(visited);
  free(prev);
  free(dist);
}

typedef struct _DistInfo 
{
  int *pDist;
  unsigned int idx;
}DistInfo, *LPDistInfo;

bool lessDist(void *lhs, void *rhs)
{
  LPDistInfo pLhs, pRhs;
  int *dist;

  pLhs = (LPDistInfo)lhs;
  pRhs = (LPDistInfo)rhs;
  dist = pLhs->pDist;

  return dist[pLhs->idx] < dist[pRhs->idx];
}

bool sameNode(void *lhs, void *rhs)
{
  LPDistInfo pLhs, pRhs;

  pLhs = (LPDistInfo)lhs;
  pRhs = (LPDistInfo)rhs;

  return pLhs->idx == pRhs->idx;
}

void DijkstraWithHeap(LPDGraph pGraph)
{
  int i, nodeNum, newDist;
  int *dist;
  int *prev;
  LPPriorityQueue pQueue; 
  LPStack pStack;
  DistInfo t, t2;
  LPEdge pIterEdge;
  int trail, prevNode;

  dist = (int *)malloc(sizeof(int)*pGraph->count);
  prev = (int *)malloc(sizeof(int)*pGraph->count);
  if (NULL == dist || NULL == prev) {
    if (dist)
      free(dist);
    if (prev)
      free(prev);
    return;
  }

  initStack(&pStack, sizeof(LPNode));
  initPriorityQueue(&pQueue, sizeof(DistInfo), lessDist, sameNode);
  nodeNum = pGraph->count;

  dist[0] = 0;
  t.pDist = dist;
  t.idx = 0;
  t2.pDist = dist;
  insertToPriorityQueue(pQueue, &t);
  for (i = 1; i < nodeNum; ++i) {
    dist[i] = MAX_LENGTH;
    prev[i] = -1;
    t.idx = i;
    insertToPriorityQueue(pQueue, &t);
  }
  printf("\n Dijstra with Heap: ");
  while (!isPriorityQueueEmpty(pQueue)) {
    deleteMin(pQueue, &t);
    if (dist[t.idx] == MAX_LENGTH)
      break;
    printf ("\nFind Min V[%c]", (pGraph->pFirstNode+t.idx)->data);
    pIterEdge = (pGraph->pFirstNode+t.idx)->pFirstOutEdge;
    while (pIterEdge) {
      newDist = dist[t.idx] + pIterEdge->weight;
      if (newDist < dist[pIterEdge->toIdx]) {
	dist[pIterEdge->toIdx] = newDist;
	prev[pIterEdge->toIdx] = t.idx;
	t2.idx = pIterEdge->toIdx;
	boostPriority(pQueue, &t2, &t2);
      }
      pIterEdge = pIterEdge->pNextSameFrom;
    }
  }

  printf("\nDump Path: ");
  for (i = 1; i < nodeNum; ++i) {
    if (dist[i] == MAX_LENGTH) {
      printf ("\nNo Path between V[%c] to V[%c]",pGraph->pFirstNode->data, (pGraph->pFirstNode+i)->data);
      continue;
    }

    prevNode = prev[i];
    while(1) {
      push(pStack, &prevNode);
      if (prevNode == 0)
	break;
      prevNode = prev[prevNode];
    }
    printf ("\nFrom between V[%c] to V[%c] dist = %d :",pGraph->pFirstNode->data, (pGraph->pFirstNode+i)->data, dist[i]);
    while (!isStackEmpty(pStack)) {
      pop(pStack, &trail);
      printf ("V[%c]->", (pGraph->pFirstNode+trail)->data);
    }
    printf("V[%c]\n", (pGraph->pFirstNode+i)->data);
  }

  destroyPriorityQueue(&pQueue);
  destroyStack(&pStack);
  free(dist);
  free(prev);
}


#define GET(mem, i, j, n)			\
  *(mem+i*n+j)

void extendShortestPath(int *dPrev, int *dCur, int *adjMatrix, int n)
{
  int i, j, k, m;
  memcpy(dCur, dPrev, sizeof(int)*n*n);
  for (i = 0; i < n; ++i)
    for (j = 0; j < n; ++j)
      for(k = 0; k < n; ++k)
	if (GET(adjMatrix,k,j,n) != MAX_LENGTH 
	    &&  GET(dPrev,i,k,n) != MAX_LENGTH
	    && GET(dPrev,i,k,n)+ GET(adjMatrix,k,j,n) < GET(dCur,i,j,n)) {
          GET(dCur,i,j,n) = GET(dPrev,i,k,n)+ GET(adjMatrix,k,j,n);
	  for (m = 0; m < n; ++m)
	    path[i][j][m] = path[i][k][m] | path[k][j][m];
	}

}

void naiveDynamicProgramming(LPDGraph pGraph)
{
  int nodeNum = pGraph->count;
  int i, j,k,m,n;
  int *adjMatrix; 
  int *dPrev;
  int *dCur;
  int *t;
  LPEdge pIterEdge;

  printf("\nNaive DynamicProgramming:");
  adjMatrix = (int *)malloc(nodeNum*nodeNum*sizeof(int));
  dPrev = (int *)malloc(nodeNum*nodeNum*sizeof(int));
  dCur = (int *)malloc(nodeNum*nodeNum*sizeof(int));

  if (NULL == adjMatrix
      || NULL == dPrev
      || NULL == dCur) {
    if (adjMatrix)
      free(adjMatrix);
    if (dPrev)
      free(dPrev);
    if (dCur)
      free(dCur);
    printf ("Out of Memory in %s\n", __func__);
    return;
  }

  // Create adjMatrix from adj List
  for (i = 0; i < nodeNum; ++i) {
    for (j = 0; j < nodeNum; ++j)
      *(adjMatrix+i*nodeNum+j) = MAX_LENGTH;
    //*(adjMatrix+i*nodeNum+i) = 0;
    pIterEdge = (pGraph->pFirstNode+i)->pFirstOutEdge;
    while (pIterEdge) {
      *(adjMatrix+i*nodeNum+pIterEdge->toIdx) = pIterEdge->weight;
      pIterEdge = pIterEdge->pNextSameFrom;
    }
  }

  //Init D(1)
  memcpy(dPrev, adjMatrix, nodeNum*nodeNum*sizeof(int));
  n = nodeNum;
  for (i = 0; i < n; ++i)
    for (j = 0; j < n; ++j)
      for (k = 0; k < n; ++k)
	if (i == k || j == k)
	  path[i][j][k] = 1;
	else 
	  path[i][j][k] = 0;

  for (m=2; m < n; ++m) {
    extendShortestPath(dPrev, dCur, adjMatrix, n);
    //swap pointer, we don't have n D, just use two to used as D(k) and D(k-1)
    t = dPrev;
    dPrev = dCur;
    dCur = t;
  }
    
  // dPrev hold final result
  for (i = 0; i < n; ++i)
    for (j = 0; j < n; ++j) {
      if (*(dPrev+i*n+j) != MAX_LENGTH) {
	//There is a path
	printf("\n ShortestPath between V[%c] and V[%c] dist = %d", 
	       (pGraph->pFirstNode+i)->data, (pGraph->pFirstNode+j)->data,
	       *(dPrev+i*n+j));
	
	printf("V[%c]", (pGraph->pFirstNode+i)->data);
	m = i;
	while(m != j) {
	  for (k = 0; k < n; ++k)
	    if (path[m][j][k] && 
		*(adjMatrix+m*n+k)!= MAX_LENGTH 
		&& *(adjMatrix+m*n+k) == *(dPrev+m*n+k)
		&&  k != m)
	      break;
	  printf("->V[%c]",(pGraph->pFirstNode+k)->data);
	  m = k;
	}
	
	
      }

    }

  free(adjMatrix);
  free(dPrev);
  free(dCur);

}
// Can handle negative edge
void BellmanFord(LPDGraph pGraph)
{
  int i, n;
  int *dist;
  int *prev;
  LPEdge pIterEdge;
  LPStack pStack;
  int prevNode, trail;

  n = pGraph->count;
  dist = (int *)malloc(sizeof(int)*n);
  if (NULL == dist)
    return;
  prev = (int *)malloc(sizeof(int)*n);
  if (NULL == prev) {
    free(dist);
    return;
  }
  
  printf ("\n BellmanFord :");
  for (i = 0; i < n; ++i) {
    dist[i] = MAX_LENGTH;
    prev[i] = -1;
  }
  dist[0] = 0;

  for (i = 0; i < n-1; ++i) {
    pIterEdge = pGraph->pFirstEdge;
    while (pIterEdge) {
      if (dist[pIterEdge->fromIdx] != MAX_LENGTH &&
	  dist[pIterEdge->toIdx] > dist[pIterEdge->fromIdx] + pIterEdge->weight) {
	dist[pIterEdge->toIdx] = dist[pIterEdge->fromIdx] + pIterEdge->weight;
	prev[pIterEdge->toIdx] = pIterEdge->fromIdx;
      }
      pIterEdge = pIterEdge->pNextEdge;
    }
  }

  pIterEdge = pGraph->pFirstEdge;
  while (pIterEdge) {
    if (dist[pIterEdge->toIdx] > dist[pIterEdge->fromIdx] + pIterEdge->weight) {
	// found a negative cycle
      printf ("Found negative cycle\n");
      goto cleanup;
    }
    pIterEdge = pIterEdge->pNextEdge;
  }

     
  printf("\nDump Path:");
  initStack(&pStack, sizeof(int));
  for (i = 1; i < n; ++i) {
    if (dist[i] == MAX_LENGTH) {
      printf ("\nNo Path between V[%c] to V[%c]",pGraph->pFirstNode->data, (pGraph->pFirstNode+i)->data);
      continue;
    }
    prevNode = prev[i];
    while(1) {
      push(pStack, &prevNode);
      if (prevNode == 0)
	break;
      prevNode = prev[prevNode];
    }
    printf("\nFrom V[%c] to V[%c] dist = %d: ", pGraph->pFirstNode->data, (pGraph->pFirstNode+i)->data, dist[i]);
    while (!isStackEmpty(pStack)) {
      pop(pStack, &trail);
      printf ("V[%c]->",  (pGraph->pFirstNode+trail)->data);
    }
    printf("V[%c]\n", (pGraph->pFirstNode+i)->data);
  }
  destroyStack(&pStack);
 cleanup:
  free(dist);
  free(prev);
}

void FloydWarShall(LPDGraph pGraph)
{
  int i, j, k,m,n;
  int *adjMatrix; 
  int *dist;
  int alt;
  LPEdge pIterEdge;

  n = pGraph->count;
  adjMatrix = (int *)malloc(n*n*sizeof(int));
  dist = (int *)malloc(n*n*sizeof(int));

  if (NULL == adjMatrix
      || NULL == dist) {
    if (adjMatrix)
      free(adjMatrix);
    if (dist)  
      free(dist);
    printf ("Out of Memory in %s\n", __func__);
    return;
  }

  printf ("\n FloydwarShall :");

  // Create adjMatrix from adj List
  for (i = 0; i < n; ++i) {
    for (j = 0; j < n; ++j)
      *(adjMatrix+i*n+j) = MAX_LENGTH;
    pIterEdge = (pGraph->pFirstNode+i)->pFirstOutEdge;
    while (pIterEdge) {
      *(adjMatrix+i*n+pIterEdge->toIdx) = pIterEdge->weight;
      pIterEdge = pIterEdge->pNextSameFrom;
    }
  }

  //Init D(-1)
  memcpy(dist, adjMatrix, n*n*sizeof(int));
  for (i = 0; i < n; ++i)
    for (j = 0; j < n; ++j)
      for (k = 0; k < n; ++k)
	if (k != i && k != j)
	  path[i][j][k] = 0;
        else 
          path[i][j][k] = 1;

  for (k = 0; k < n; ++k)
    for (i = 0; i < n; ++i)
      for (j = 0; j < n; ++j) {
	if (*(dist+i*n+k) == MAX_LENGTH ||
	    *(dist+k*n+j) == MAX_LENGTH)
	  continue;
	alt = *(dist+i*n+k) + *(dist+k*n+j);
	if (*(dist+i*n+j) > alt) {
	  *(dist+i*n+j) = alt;
	  for (m = 0; m < n; ++m) //This should be implement as a bitset to avoid extra o(n)
	    path[i][j][m] = path[i][k][m] | path[k][j][m];
	}
      }

  //
  // for path, there are two other different approach to calculate
  // one is a predecessor matrix
  //  init p(i,j)  if (i == j || (i,j) is not an edge ) assign NIL otherwise assign i
  //    p(i,j) = p (k,j)
  // other is a intermediate matrix
  //   next(i,j) = k
  //   reconstruct path like path(i,j) = path(i,k) + k + path(k,j)

  // dist hold final result
  for (i = 0; i < n; ++i)
    for (j = 0; j < n; ++j) {
      if (*(dist+i*n+j) != MAX_LENGTH) {
	//There is a path
	printf("\n ShortestPath between V[%c] and V[%c] dist = %d:\n", 
	       (pGraph->pFirstNode+i)->data, (pGraph->pFirstNode+j)->data,
	       *(dist+i*n+j));
	printf("V[%c]", (pGraph->pFirstNode+i)->data);

	m = i;
	while(m != j) {
	  for (k = 0; k < n; ++k)
	    if (path[m][j][k] && 
		*(adjMatrix+m*n+k)!= MAX_LENGTH 
		&& *(adjMatrix+m*n+k) == *(dist+m*n+k)
		&&  k != m)
	      break;
	  printf("->V[%c]",(pGraph->pFirstNode+k)->data);
	  m = k;
	}
      }

    }

  free(adjMatrix);
  free(dist);
}
// 1. Add fake node with all edge = 0
// 2. run bellman-ford to check have negative-cycle
// 3. reweight graph
// 4. run dijstra
// 5. reweight
void Johnson(LPDGraph pGraph)
{

}

typedef struct _priorItem
{
  unsigned int idx;
  unsigned int *pToF;
}PriorItem, *LPPriorItem;

bool lessF(void *lhs, void *rhs)
{
  LPPriorItem pLhs, pRhs;
  int *fValue;

  pLhs = (LPPriorItem)lhs;
  pRhs = (LPPriorItem)rhs;
  fValue = pLhs->pToF;

  return fValue[pLhs->idx] < fValue[pRhs->idx];
}

bool equalNode(void *lhs, void *rhs)
{
  LPPriorItem pLhs, pRhs;

  pLhs = (LPPriorItem)lhs;
  pRhs = (LPPriorItem)rhs;

  return pLhs->idx == pRhs->idx;
}

// Single pair shortest path
void AStarPathFinding(LPDGraph pGraph)
{

  /*
  LPNode pStart, pEnd;
  LPPriorityQueue pOpenList;
  LPBitSet pCloseSet, pOpenSet;
  PriorItem tempItem;

  int *h;
  int *f;
  int *g;
  int *path;

  int n = pGraph->count;

  int *tempBuffer;
  tempBuffer = (int *)malloc(sizeof(int)*n*4);
  if (NULL == tempBuffer) {
    printf ("Out Of Memory in %s", __func__);
    return;
  }
  h = tempBuffer;
  f = h+n;
  g = f+n;
  path = g+n;
  

  pStart = pGraph->pFirstNode;
  pEnd = pGraph->pFirstNode+n-1;

  initHeuristic(pGraph, h);

  g[0] = 0;
  path[0] = -1;
  f[0] = h[0] + g[0];

  initPriorityQueue(&pOpenList, sizeof(PriorItem), lessF, equalNode);
  initBitSet(&pCloseSet, n);
  initBitSet(&pOpenSet, n);

  tempItem.pToF = f;
  tempItem.idx = 0;
  insertToPriorityQueue(pQueue, &tempItem);
  setInBitSet(pOpenSet, tempItem.idx);
  while (!isPriorityQueueEmpty(pOpenList)) {
    deleteMin(pQueue, &tempItem);
    if (tempItem.idx == pEnd->idx)
      break;
    
    current = tempItem.idx;

    resetInBitSet(pOpenSet, current)
    setInBitSet(pCloseSet, current);
    pIterEdge = (pGraph->pFirstNode+current)->pFirstOutEdge;
    while (pIterEdge) {
      temp_g = g[tempItem.idx]+pIterEdge->weight;
      temp_f = temp_g + h[pIterEdge->toIdx];

      if (testInBitSet(pCloseSet, pIterEdge->toIdx) &&
	  temp_f >= f[pIterEdge->toIdx]) {
	pIterEdge = pIterEdge->pNextSameFrom;
	continue;
      }
      if (!testInBitSet(pOpenSet, pIterEdge->toIdx) ||
	  temp_f < f[pIterEdge->toIdx]) {
	path[pIterEdge->toIdx] = current;
	g[pIterEdge->toIdx] = temp_g;
	f[pIterEdge->toIdx] = temp_f;
	tempItem.idx = pIterEdge->toIdx;

	if (!testInBitSet(pOpenSet, pIterEdge->toIdx)) {
	  setInBitSet(pOpenSet, pIterEdge->toIdx);
	  insertToPriorityQueue(pOpenList, &tempItem);
	} else {
	  bootPriority(pOpenList, &tempItem, &tempItem)
	}
	
      }
      pIterEdge = pIterEdge->pNextSameFrom;
    }
  }
  
  // Output Path
  initStack(&pStack, sizeof(int));
  prev = pEnd->idx;
  push(pStack, &prev);
  while(path[prev] != pStart->idx) {
    prev = path[prev];
    push(pStack, &prev);
  }
  printf("\n path from start v[%d] to end v[%d]:\n", pStart->idx, pEnd->idx);
  printf("V[%d]", pStart->idx)
  while (!isStackEmpty(pStack)) {
    pop(pStack, &prev)
    printf("->V[%d]", prev)
  }
  putchar('\n');
  destroyStack(&pStack);

  destroyBitSet(&pCloseSet);
  destroyBitSet(&pOpenSet);

  destroyPriorityQueue(&pOpenList);
  */
}
