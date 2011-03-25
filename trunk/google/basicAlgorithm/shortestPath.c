
#include "../include/common.h"
#include "../include/stack.h"
#include "../include/circularQueue.h"
#include "../include/singleList.h"

struct _EDGE;

typedef struct _NODE
{
  char data;
  struct _EDGE *pFirstInEdge;
  struct _EDGE *pFirstOutEdge;
  BOOL bVisited;
  BOOL bInQueue;
}NODE, *LP_NODE;

typedef struct _EDGE
{
  NODE *pFrom;
  NODE *pTo;
  int value;
  struct _EDGE *pNextSameFrom;
  struct _EDGE *pNextSameTo;
}EDGE, *LP_EDGE;

int *pAdjWeight = NULL;
int nodeNum;

#define MAX_WEIGHT 65535
#define EDGE_VALUE(pWeight,i, j) *(pWeight + i * nodeNum + j) 


void depthOrderTraverse(LP_NODE pStartNode, int nodeNum);
void widthOrderTraverse(LP_NODE pStartNode, int nodeNum);

void dijkstra(LP_NODE pStartNode, int nodeNum);
void dynamicProgramming(LP_NODE pStartNode, int nodeNum);
void floydDynamicProgramming(LP_NODE pStartNode, int nodeNum);
void bellmanFordShortestPath(LP_NODE pStartNode, int nodeNum);
void johnsonShortestPath(LP_NODE pStartNode ,int nodeNum);

int main()
{

  char buf[4096];
  unsigned int weight[2048];
  FILE *fp;
  int index, curIndex;
  int line, column;
  int i,j;
  NODE *pStartNode, *pIterNode;
  EDGE *pIterEdge;

  
  if ((fp = fopen("inputDataForShortestPath.txt", "r")) == NULL)
    {
      printf ("Cannot Open File inputData.txt\n");
      exit(-1);
    }

  line = 0;
  column = -1;
  while (fgets(buf, 4095, fp))
    {
      index = 0;
      curIndex = 0;

      while (buf[curIndex] == '\t' || buf[curIndex] == ' ')
	curIndex++;

      while (sscanf(buf+curIndex, "%d", &weight[index]))
	{
	  index++;
	  while (isdigit(buf[curIndex]))
	    curIndex++;
	  while (buf[curIndex] == '\t' || buf[curIndex] == ' ')
	    curIndex++;
	  if (buf[curIndex] == '\n')
	    break;
	}
      if (column != -1 && column != index)
	break;

      column = index;
      if (NULL == pAdjWeight)
	{
	  pAdjWeight = (int *)malloc(sizeof(int)*column*column);
	  if (NULL == pAdjWeight)
	    {
	      printf("Out Of Memory in Line %d, File %s", __LINE__, __FILE__);
	      exit(OVERFLOW);
	    }
	}
      for (index = 0; index < column; index++)
	{
	  *(pAdjWeight + line * column + index) = weight[index];
	}
      line++;
    }


  if (line != column)
    {
      printf("Edge Data Error\n");
      free(pAdjWeight);
      exit(-1);
    }

  nodeNum = line;

  printf("\nInput Graph:\n");
  for (i = 0; i < line; i++)
    {
      printf("[Node V[%d]]:", i);
      for (j = 0; j < column; j++)
	{
	  if (i != j && *(pAdjWeight + i * column + j) != MAX_WEIGHT)
	    printf("(V[%d], V[%d], %d)", i,j,*(pAdjWeight + i * column + j));
	}
      
       putchar('\n');
    }

  printf("Transfer to Noraml Adj Graph:\n");
  pStartNode = (NODE *)malloc(sizeof(NODE) * nodeNum);
  if (NULL == pStartNode)
    {
      printf("Out Of Memory in Line %d, File %s", __LINE__, __FUNCTION__);
      free(pAdjWeight);
      exit(OVERFLOW);
    }

  memset(pStartNode, 0, sizeof(NODE) * nodeNum);

  for (i = 0; i < nodeNum; i++)
    {
      pIterNode = pStartNode + i;
      pIterNode->data = 'a'+i;
      for (j = 0; j < nodeNum; j++)
	{
	  if (EDGE_VALUE(pAdjWeight,i, j) > 0 && EDGE_VALUE(pAdjWeight,i, j) != MAX_WEIGHT)
	    {
	      pIterEdge = (EDGE *)malloc(sizeof(EDGE));
	      if (NULL == pIterEdge)
		{
		  printf("Out Of Memory in Line %d, File %s", __LINE__, __FUNCTION__);
		  exit(OVERFLOW);
		}
	      pIterEdge->pFrom = pStartNode + i;
	      pIterEdge->pTo = pStartNode + j;
	      pIterEdge->value = EDGE_VALUE(pAdjWeight,i, j);

	      pIterEdge->pNextSameFrom = pIterEdge->pFrom->pFirstOutEdge;
	      pIterEdge->pFrom->pFirstOutEdge = pIterEdge;

	      pIterEdge->pNextSameTo = pIterEdge->pTo->pFirstInEdge;
	      pIterEdge->pTo->pFirstInEdge = pIterEdge;
	    }
	}
    }
  
  depthOrderTraverse(pStartNode, nodeNum);
  widthOrderTraverse(pStartNode, nodeNum);
  
  dijkstra(pStartNode, nodeNum);
  dynamicProgramming(pStartNode, nodeNum);
  floydDynamicProgramming(pStartNode, nodeNum);
  bellmanFordShortestPath(pStartNode, nodeNum);
  johnsonShortestPath(pStartNode ,nodeNum);
  putchar('\n');
  free(pAdjWeight);
  return 0;
}

void depthOrderTraverse(LP_NODE pStartNode, int nodeNum)
{
  LP_STACK pStack;
  LP_NODE pIterNode;
  LP_EDGE pIterEdge;
  int i;

  printf("\n==Start Depth Order Traverse==:");

  for (i = 0; i < nodeNum; i++)
    (pStartNode + i)->bVisited = FALSE;
  
  createStack(&pStack, sizeof (LP_NODE));

  for (i = 0; i < nodeNum; i++)
    {
      pIterNode = pStartNode + i;
      if (pIterNode->bVisited == FALSE)
	{
	  pIterNode->bVisited = TRUE;
	  push(pStack, &pIterNode);
	  
	  while (!isStackEmpty(pStack))
	    {
	      pop (pStack, &pIterNode);
	      printf("V[%d]:%c ",pIterNode->data - 'a', pIterNode->data);
	      pIterEdge = pIterNode->pFirstOutEdge;
	      while (pIterEdge)
		{
		  if (pIterEdge->pTo->bVisited == FALSE)
		    {
		      pIterEdge->pTo->bVisited = TRUE;
		      push (pStack, &pIterEdge->pTo);
		    }
		  pIterEdge = pIterEdge->pNextSameFrom;
		}
	    }
	}

    }
  
  destroyStack (pStack);
}

void widthOrderTraverse(LP_NODE pStartNode, int nodeNum)
{
  LP_CIRCULAR_QUEUE pQueue;
  LP_NODE pIterNode;
  LP_EDGE pIterEdge;
  int i;

  printf("\n==Start Width Order Traverse==:");

  for (i = 0; i < nodeNum; i++)
    (pStartNode + i)->bVisited = FALSE;

  createCircularQueue(&pQueue, nodeNum, sizeof(LP_NODE));

  for (i = 0; i < nodeNum; i++)
    {
      pIterNode = pStartNode + i;
      if (pIterNode->bVisited == FALSE)
	{
	  pIterNode->bVisited = TRUE;
	  insertToQueueTail(pQueue, &pIterNode);
	  
	  while (!isQueueEmpty(pQueue))
	    {
	      getFromQueueHead(pQueue, &pIterNode);
	      printf("V[%d]:%c ",pIterNode->data - 'a', pIterNode->data);
	      pIterEdge = pIterNode->pFirstOutEdge;
	      while (pIterEdge)
		{
		  if (pIterEdge->pTo->bVisited == FALSE)
		    {
		      pIterEdge->pTo->bVisited = TRUE;
		      insertToQueueTail(pQueue, &pIterEdge->pTo);
		    }
		  pIterEdge = pIterEdge->pNextSameFrom;
		}
	    }
	}

    }
  
  destroyCircularQueue (pQueue);
}
void dijkstra(LP_NODE pStartNode ,int nodeNum)
{
  LP_NODE pSource, pIterNode, *pPrevPathNode;
  LP_EDGE pIterEdge;
  int index = 0;
  int *dist = NULL;
  int i, j;
  LP_STACK pStack;

  printf("\nStart SSSP Shortest path calculate, Use dijkstra\n");
  createStack(&pStack, sizeof(LP_NODE));

  dist = (int *)malloc(sizeof(int) * (nodeNum));
  if (NULL == dist)
    {
      printf ("Out of Memory in line %d, function %s", __LINE__, __FUNCTION__);
      exit(OVERFLOW);
    }
  pPrevPathNode = (LP_NODE *)malloc(sizeof(LP_NODE) * (nodeNum));
  if (NULL == pPrevPathNode)
    {
      printf ("Out of Memory in line %d, function %s", __LINE__, __FUNCTION__);
      exit(OVERFLOW);
    }

  for (index = 0; index < nodeNum; index++)
    {
      pSource = pStartNode + index;
      
      for (i = 0; i < nodeNum; i++)
	{
	  if (i == index)
	    dist[i] = 0;
	  else 
	    dist[i] = MAX_WEIGHT;
	  (pStartNode + i)->bVisited = FALSE;
	  *(pPrevPathNode+i) = NULL;
	}

      for (i = 0; i < nodeNum; i++)
	{
	  int minDist, minIndex;
	  minDist = MAX_WEIGHT;
	  for (j = 0; j < nodeNum; j++)
	    {
	      if ((pStartNode + j)->bVisited == FALSE)
		{
		  if (dist[j] < minDist)
		    {
		      minDist = dist[j];
		      minIndex = j;
		    }
		}
	    }

	  if (minDist == MAX_WEIGHT)
	    break;

	  // Find Next Smallest Path, Mark this Node
	  (pStartNode+minIndex)->bVisited = TRUE;
	  pIterEdge = (pStartNode + minIndex)->pFirstOutEdge;
	  while (pIterEdge)
	    {
	      pIterNode = pIterEdge->pTo;
	      if (minDist + pIterEdge->value < dist[pIterNode - pStartNode])
		{
		  pPrevPathNode[pIterNode - pStartNode] = pIterEdge->pFrom;
		  dist[pIterNode - pStartNode] = minDist + pIterEdge->value;
		}
	      pIterEdge = pIterEdge->pNextSameFrom;
	    }
	}
      
      if (i < nodeNum)
	{
	  printf("From Source Node V[%d]:%c , some Node is unreachable", 
index, 'a'+index); 
	  //break;
	}
      
      
	{
	  printf("\n==Start Node V[%d]:%c:\n", index, 'a'+index);
	  for (i = 0; i < nodeNum; i++)
	    {
	      LP_NODE pPathNode = pStartNode + i;
	      if (pPathNode->bVisited == FALSE)
		continue;
	      printf("To Node V[%d]:%c:Short path length %d", i, 'a'+i, dist[i]);
	      printf(" path:[");
	      push(pStack, &pPathNode);
	      while (pPrevPathNode[pPathNode-pStartNode])
		{
		  pPathNode = pPrevPathNode[pPathNode-pStartNode];
		  push(pStack, &pPathNode);
		}
	      while (!isStackEmpty(pStack))
		{
		  pop(pStack, &pPathNode);
		  putchar(pPathNode->data);
		}
	      putchar(']');
	      putchar('\n');
	    }
	}

    }

  destroyStack(pStack);
  free(dist);
  free(pPrevPathNode);
}


static LP_EDGE edgeExist(LP_NODE pStartNode ,int from, int to)
{
  LP_NODE pFrom, pTo;
  LP_EDGE pIterEdge;

  pFrom = pStartNode + from;
  pTo = pStartNode + to;

  pIterEdge = pFrom->pFirstOutEdge;
  while (pIterEdge && pIterEdge->pTo != pTo)
    pIterEdge = pIterEdge->pNextSameFrom;

  return pIterEdge;
}

void dynamicProgramming(LP_NODE pStartNode ,int nodeNum)
{
  int *pPrevMinimalDist, *pCurMinimalDist, *pTemp;
  LP_NODE *pPrevPathNode;
  LP_EDGE pIterEdge;
  LP_NODE pIterNode;
  int i, j, w;
  int m, u, v;
  LP_STACK pStack;
  int minDist;

  printf("\n==Start All Pairs Shorest Path use dynamic programming==\n");

  pPrevMinimalDist = (int *)malloc(sizeof(int)*nodeNum*nodeNum);
  if (NULL == pPrevMinimalDist)
    {
      printf("Out Of Memory in Line %d, Function %s", __LINE__, __FUNCTION__);
      exit(OVERFLOW);
    }

  pCurMinimalDist = (int *)malloc(sizeof(int)*nodeNum*nodeNum);
  if (NULL == pCurMinimalDist)
    {
      printf("Out Of Memory in Line %d, Function %s", __LINE__, __FUNCTION__);
      exit(OVERFLOW);
    }
  pPrevPathNode = (LP_NODE *)malloc(sizeof(LP_NODE)*nodeNum*nodeNum);
  if (NULL == pPrevPathNode)
    {
      printf("Out Of Memory in Line %d, Function %s", __LINE__, __FUNCTION__);
      exit(OVERFLOW);
    }

  memset(pCurMinimalDist, 0 , sizeof(int) * nodeNum * nodeNum);
  memset(pPrevMinimalDist, 0 , sizeof(int) * nodeNum * nodeNum);
  memset(pPrevPathNode, 0 , sizeof(LP_NODE) * nodeNum * nodeNum);

  createStack(&pStack, sizeof(LP_NODE));

  for (i = 0; i < nodeNum; i++)
    for (j = 0; j < nodeNum; j++)
      {
	if (i == j)
	  {
	    EDGE_VALUE(pCurMinimalDist, i, j) = 0;
	  }
	else
	  {
	    EDGE_VALUE(pCurMinimalDist, i, j) = MAX_WEIGHT;
	  }
      }
#if 1
  putchar('\n');
  for (i = 0; i < nodeNum; i++)
    {
    for (j = 0; j < nodeNum; j++)
      {
	printf("%7d", EDGE_VALUE(pCurMinimalDist, i, j));
      }
    putchar('\n');
    }
#endif


  for (m = 1; m <= nodeNum - 1; m++)
    {
      pTemp = pPrevMinimalDist;
      pPrevMinimalDist = pCurMinimalDist;
      pCurMinimalDist = pTemp;

      for (u = 0; u < nodeNum; u++)
	for (v = 0; v < nodeNum; v++)
	  {
	
	    minDist = EDGE_VALUE(pPrevMinimalDist, u ,v);
	    pIterEdge = (pStartNode + v)->pFirstInEdge;
	    while (pIterEdge)
	      {
		w = pIterEdge->pFrom - pStartNode;

		if (minDist > EDGE_VALUE(pPrevMinimalDist,u, w) + pIterEdge->value)
		  {
		    minDist = EDGE_VALUE(pPrevMinimalDist,u, w) + pIterEdge->value;
		    *(pPrevPathNode + u * nodeNum + v) = pStartNode + w;
		    printf("\nFind New Way[cost:%d] from V%d to V%d through V%d",minDist, u, v ,w);
		  }

		pIterEdge = pIterEdge->pNextSameTo;
	      }
	    EDGE_VALUE(pCurMinimalDist, u ,v) = minDist;
	  }
    }

  for (u = 0; u < nodeNum; u++)
	{
	  printf("\n==Start Node V[%d]:%c:\n", u, 'a'+u);
	  for (v = 0; v < nodeNum; v++)
	    {
	      if (EDGE_VALUE(pCurMinimalDist, u ,v) != MAX_WEIGHT)
		{
		  LP_NODE pPathNode;
		  int pathIndex;
		  printf("To Node V[%d]:%c:Short path length %d", v, 'a'+v, EDGE_VALUE(pCurMinimalDist, u ,v));
		  printf(" path:[");
		  pPathNode = pStartNode + v;
		  push(pStack, &pPathNode);
		  pathIndex = v;
		  while (*(pPrevPathNode + u * nodeNum + pathIndex))
		    {
		      pPathNode = 
			*(pPrevPathNode + u * nodeNum + pathIndex);
		      pathIndex = pPathNode - pStartNode;
		      push(pStack, &pPathNode);
		    }
		  while (!isStackEmpty(pStack))
		    {
		      pop(pStack, &pPathNode);
		      putchar(pPathNode->data);
		    }
		  putchar(']');
		  putchar('\n');
		}
	    }
	}


  destroyStack(pStack);
  free(pPrevMinimalDist);
  free(pCurMinimalDist);
  free(pPrevPathNode);

}
void floydDynamicProgramming(LP_NODE pStartNode ,int nodeNum)
{
  int u, v;
  int k;
  int maxEdge = nodeNum - 1;
  int *pPrevMinimalDist, *pCurMinimalDist, *temp;
  LP_NODE *pPrevPathNode;
  int minDist, from, to;
  LP_NODE pIterNode, pPathNode, pFrom, pTo;
  LP_EDGE pIterEdge;
  LP_STACK pStack;


  createStack(&pStack, sizeof(LP_NODE));
  printf("\n==Start All Pairs Shorest Path use Floyd dynamic programming==\n");

  pPrevMinimalDist = (int *)malloc(sizeof(int)*nodeNum*nodeNum);
  if (NULL == pPrevMinimalDist)
    {
      printf("Out Of Memory in Line %d, Function %s", __LINE__, __FUNCTION__);
      exit(OVERFLOW);
    }

  pCurMinimalDist = (int *)malloc(sizeof(int)*nodeNum*nodeNum);
  if (NULL == pCurMinimalDist)
    {
      printf("Out Of Memory in Line %d, Function %s", __LINE__, __FUNCTION__);
      exit(OVERFLOW);
    }
  pPrevPathNode = (LP_NODE *)malloc(sizeof(LP_NODE)*nodeNum*nodeNum);
  if (NULL == pPrevPathNode)
    {
      printf("Out Of Memory in Line %d, Function %s", __LINE__, __FUNCTION__);
      exit(OVERFLOW);
    }

  memset(pCurMinimalDist, 0 , sizeof(int) * nodeNum * nodeNum);
  memset(pPrevMinimalDist, 0 , sizeof(int) * nodeNum * nodeNum);
  memset(pPrevPathNode, 0 , sizeof(LP_NODE) * nodeNum * nodeNum);

 for (u = 0; u < nodeNum; u++)
    for (v = 0; v < nodeNum; v++)
      {
	if (pIterEdge = edgeExist(pStartNode, u, v))
	  {
	    EDGE_VALUE(pCurMinimalDist, u, v) = pIterEdge->value;
	    *(pPrevPathNode + u * nodeNum + v) = pStartNode + u;
	  }
	else
	  {
	    EDGE_VALUE(pCurMinimalDist, u, v) = MAX_WEIGHT;
	  }
      }


  for (k = 0; k < nodeNum; k++)
    {
      temp = pPrevMinimalDist;
      pPrevMinimalDist = pCurMinimalDist;
      pCurMinimalDist = temp;
      
      for (u = 0; u < nodeNum; u++)
	for (v = 0; v < nodeNum; v++)
	  {
	    int newDist;
	    minDist = EDGE_VALUE(pPrevMinimalDist, u ,v);
	    newDist = EDGE_VALUE(pPrevMinimalDist, u ,k) + 
	      EDGE_VALUE(pPrevMinimalDist,k,v);

	    if (minDist > newDist)
	      {
		minDist = newDist;
		*(pPrevPathNode + u * nodeNum + v) = * (pPrevPathNode + k * nodeNum + v);
	      }
	    EDGE_VALUE(pCurMinimalDist, u, v) = minDist;
	  }

    }
  
  for (u = 0; u < nodeNum; u++)
	{
	  printf("\n==Start Node V[%d]:%c:\n", u, 'a'+u);
	  for (v = 0; v < nodeNum; v++)
	    {
	      if (EDGE_VALUE(pCurMinimalDist, u ,v) != MAX_WEIGHT)
		{
		  LP_NODE pPathNode;
		  int pathIndex;
		  printf("To Node V[%d]:%c:Short path length %d", v, 'a'+v, EDGE_VALUE(pCurMinimalDist, u ,v));
		  printf(" path:[");
		  pPathNode = pStartNode + v;
		  push(pStack, &pPathNode);
		  pathIndex = v;
		  while (*(pPrevPathNode + u * nodeNum + pathIndex))
		    {
		      pPathNode = 
			*(pPrevPathNode + u * nodeNum + pathIndex);
		      pathIndex = pPathNode - pStartNode;
		      push(pStack, &pPathNode);
		    }
		  while (!isStackEmpty(pStack))
		    {
		      pop(pStack, &pPathNode);
		      putchar(pPathNode->data);
		    }
		  putchar(']');
		  putchar('\n');
		}
	    }
	}


  destroyStack(pStack);
  free(pPrevMinimalDist);
  free(pCurMinimalDist);
  free(pPrevPathNode);

}


//BellmanFord
void bellmanFordShortestPath(LP_NODE pStartNode, int nodeNum)
{
  int *dist;
  LP_NODE *pPrevPathNode;
  LP_NODE pIterNode;
  LP_EDGE pIterEdge;
  int i, nodeIndex;
  LP_STACK pStack;

  printf("\bStart SSSP use BellmanFord:\n");

  dist = (int *)malloc(sizeof(int) * (nodeNum));
  if (NULL == dist)
    {
      printf ("Out of Memory in line %d, function %s", __LINE__, __FUNCTION__);
      exit(OVERFLOW);
    }
  pPrevPathNode = (LP_NODE *)malloc(sizeof(LP_NODE) * (nodeNum));
  if (NULL == pPrevPathNode)
    {
      printf ("Out of Memory in line %d, function %s", __LINE__, __FUNCTION__);
      exit(OVERFLOW);
    }

  dist[0] = 0;
  pPrevPathNode[0] = NULL;
  for (i = 1; i < nodeNum; i++)
    {
      pIterNode = pStartNode + i;
      pIterNode->bVisited = FALSE;
      dist[i] = MAX_WEIGHT;
      pPrevPathNode[i] = NULL;
    }

  for (i = 1; i < nodeNum; i++)
    {
      for (nodeIndex = 0; nodeIndex < nodeNum; nodeIndex++)
	{
	  pIterNode = pStartNode + nodeIndex;
	  pIterEdge = pIterNode->pFirstOutEdge;
	  while (pIterEdge)
	    {
	      int u, v;
	      u = pIterEdge->pFrom - pStartNode;
	      v = pIterEdge->pTo - pStartNode;
	      if (dist[v] > dist[u] + pIterEdge->value)
		{
		  dist[v] = dist[u] + pIterEdge->value;
		  pPrevPathNode[v] = pStartNode + u;
		}

	      pIterEdge = pIterEdge->pNextSameFrom;
	    }
	}

    }

  createStack(&pStack, sizeof(LP_NODE));
  {
    printf("\n==Start Node V[%d]:%c:\n", 0, 'a');
    for (i = 0; i < nodeNum; i++)
      {
	LP_NODE pPathNode = pStartNode + i;
	if (dist[i] >= MAX_WEIGHT || i == 0)
	  continue;
	printf("To Node V[%d]:%c:Short path length %d", i, 'a'+i, dist[i]);
	printf(" path:[");
	push(pStack, &pPathNode);
	while (pPrevPathNode[pPathNode-pStartNode])
	  {
	    pPathNode = pPrevPathNode[pPathNode-pStartNode];
	    push(pStack, &pPathNode);
	  }
	while (!isStackEmpty(pStack))
	  {
	    pop(pStack, &pPathNode);
	    putchar(pPathNode->data);
	  }
	putchar(']');
	putchar('\n');
      }
  }
       
	destroyStack(pStack);

  free(dist);
  free(pPrevPathNode);

}
//Johnson
// Only Implement the prior Queue, left arc partion 
void johnsonShortestPath(LP_NODE pStartNode ,int nodeNum)
{
  int i;
  LP_CIRCULAR_QUEUE pQueue;
  LP_NODE pIterNode;
  LP_EDGE pIterEdge;
  int *dist;
  LP_NODE *pPrevPathNode;
  LP_STACK pStack;

  printf("\bStart SSSP use johnson:\n");

  dist = (int *)malloc(sizeof(int) * (nodeNum));
  if (NULL == dist)
    {
      printf ("Out of Memory in line %d, function %s", __LINE__, __FUNCTION__);
      exit(OVERFLOW);
    }
  pPrevPathNode = (LP_NODE *)malloc(sizeof(LP_NODE) * (nodeNum));
  if (NULL == pPrevPathNode)
    {
      printf ("Out of Memory in line %d, function %s", __LINE__, __FUNCTION__);
      exit(OVERFLOW);
    }

  dist[0] = 0;
  pPrevPathNode[0] = NULL;

  for (i = 1; i < nodeNum; i++)
    {
      (pStartNode+i)->bInQueue = FALSE;
      (pStartNode+i)->bVisited = FALSE;
      dist[i] = MAX_WEIGHT;
      pPrevPathNode[i] = NULL;
    }

  createCircularQueue(&pQueue, nodeNum, sizeof(LP_NODE));

  pStartNode->bInQueue = TRUE;
  insertToQueueTail(pQueue, &pStartNode);
  while (!isQueueEmpty(pQueue))
    {
      getFromQueueHead(pQueue, &pIterNode);
      pIterNode->bInQueue = FALSE;
      pIterEdge = pIterNode->pFirstOutEdge;
      
      while (pIterEdge)
	{
	  int u, v;
	  u = pIterEdge->pFrom - pStartNode;
	  v = pIterEdge->pTo - pStartNode;
	  if (dist[v] > dist[u] + pIterEdge->value)
	    {
	      dist[v] = dist[u] + pIterEdge->value;
	      pPrevPathNode[v] = pIterEdge->pFrom;
	      if (!pIterEdge->pTo->bInQueue)
		{
		  pIterEdge->pTo->bInQueue = TRUE;
		  insertToQueueTail(pQueue, &pIterEdge->pTo);
		}
	    }

	  pIterEdge = pIterEdge->pNextSameFrom;
	}
    }

  createStack(&pStack, sizeof(LP_NODE));
  {
    printf("\n==Start Node V[%d]:%c:\n", 0, 'a');
    for (i = 0; i < nodeNum; i++)
      {
	LP_NODE pPathNode = pStartNode + i;
	if (dist[i] >= MAX_WEIGHT || i == 0)
	  continue;
	printf("To Node V[%d]:%c:Short path length %d", i, 'a'+i, dist[i]);
	printf(" path:[");
	push(pStack, &pPathNode);
	while (pPrevPathNode[pPathNode-pStartNode])
	  {
	    pPathNode = pPrevPathNode[pPathNode-pStartNode];
	    push(pStack, &pPathNode);
	  }
	while (!isStackEmpty(pStack))
	  {
	    pop(pStack, &pPathNode);
	    putchar(pPathNode->data);
	  }
	putchar(']');
	putchar('\n');
      }
  }
  destroyStack(pStack);

  destroyCircularQueue(pQueue);
  free(dist);
  free(pPrevPathNode);
}
