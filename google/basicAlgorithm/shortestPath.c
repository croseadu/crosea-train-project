
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
#define EDGE_VALUE(i, j) (*(pAdjWeight + i * nodeNum + j)) 


void depthOrderTraverse(LP_NODE pStartNode, int nodeNum);
void widthOrderTraverse(LP_NODE pStartNode, int nodeNum);

void dijkstra(LP_NODE pStartNode, int nodeNum);
void dynamicProgramming(LP_NODE pStartNode, int nodeNum);
void floydDynamicProgramming(LP_NODE pStartNode, int nodeNum);

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

  
  if ((fp = fopen("inputData.txt", "r")) == NULL)
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
	  if (EDGE_VALUE(i, j) > 0 && EDGE_VALUE(i, j) != MAX_WEIGHT)
	    {
	      pIterEdge = (EDGE *)malloc(sizeof(EDGE));
	      if (NULL == pIterEdge)
		{
		  printf("Out Of Memory in Line %d, File %s", __LINE__, __FUNCTION__);
		  exit(OVERFLOW);
		}
	      pIterEdge->pFrom = pStartNode + i;
	      pIterEdge->pTo = pStartNode + j;
	      pIterEdge->value = EDGE_VALUE(i, j);

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

  printf("\nStart Shortest path calculate, Use dijkstra\n");
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
  //free(dist);
  //free(pPrevPathNode);
}


void dynamicProgramming(LP_NODE pStartNode ,int nodeNum)
{
  

}
void floydDynamicProgramming(LP_NODE pStartNode ,int nodeNum)
{
  

}
