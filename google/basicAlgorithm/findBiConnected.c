

#include "../include/common.h"
#include "../include/stack.h"
#include "../include/circularQueue.h"
#include "../include/singleList.h"

#define INIT_SIZE 10
#define INCRE_SIZE 5


#define MAX_WEIGHT 65535


struct _EDGE;

typedef struct _NODE
{
  char data;
  BOOL bVisited;
  int index;
  int lowPt;
  struct _EDGE *pFirstOutEdge;
  struct _EDGE *pFirstInEdge;
}NODE, *LP_NODE;

typedef struct _EDGE
{
  NODE *pFrom;
  NODE *pTo;
  struct _EDGE *pNextSameFrom;
  struct _EDGE *pNextSameTo;
}EDGE, *LP_EDGE;

int nodeNum;

#define EDGE_VALUE(pWeight,i, j) *(pWeight + i * nodeNum + j) 
void depthOrderTraverse(LP_NODE pStartNode, int *pAdjWeight, int nodeNum);
void widthOrderTraverse(LP_NODE pStartNode, int *pAdjWeight, int nodeNum);
STATUS createEdge(LP_NODE pFrom, LP_NODE pTo);
void dfsFindBCC(LP_NODE pNode, LP_NODE pFather);
void findBiConnectedComponent(LP_NODE pStartNode, int *pAdjWeight, int nodeNum);

int main()
{
  FILE *fp;
  char buf[4096];
  unsigned int weight[2048];
  int line, column;
  int curIndex, index;
  int *pAdjWeight;
  int i,j;
  LP_NODE pStartNode, pIterNode;


  if ((fp = fopen("inputDataForMinimalTree.txt", "r")) == NULL)
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
	  if (i == j && *(pAdjWeight + i * column + j) != 0)
	    printf ("Edge Data Error\n");
	  if (i != j 
	      && *(pAdjWeight + i * column + j) !=  *(pAdjWeight + j * column + i))
	    printf ("Edge Data Error for a undirected graph\n");

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
    }

  depthOrderTraverse(pStartNode, pAdjWeight, nodeNum);
  widthOrderTraverse(pStartNode, pAdjWeight, nodeNum);
  findBiConnectedComponent(pStartNode, pAdjWeight, nodeNum);

  putchar('\n');
  return 0;
}

void depthOrderTraverse(LP_NODE pStartNode, int *pAdjWeight, int nodeNum)
{
  int i;
  int j;
  int cur;
  LP_NODE pIterNode;
  LP_STACK pStack;

  printf("\n==Start Undirected Graph DFS :");

  createStack(&pStack, sizeof(LP_NODE));

  for (i = 0; i < nodeNum; i++)
    (pStartNode + i)->bVisited = FALSE;

  for (i = 0; i < nodeNum; i++)
    {
      if ((pStartNode + i)->bVisited)
	continue;
      pIterNode = pStartNode + i;

      pIterNode->bVisited = TRUE;
      push (pStack, &pIterNode);
      while (!isStackEmpty(pStack))
	{
	  pop(pStack, &pIterNode);
	  putchar(pIterNode->data);
	  cur = pIterNode - pStartNode;
	  for (j = 0; j < nodeNum; j++)
	    {
	      if (j == cur 
		  || EDGE_VALUE(pAdjWeight, cur ,j) == MAX_WEIGHT)
		continue;
	      if ((pStartNode+j)->bVisited == FALSE)
		{
		  (pStartNode+j)->bVisited = TRUE;
		  pIterNode = pStartNode + j;
		  push (pStack, &pIterNode);
		}
	    }

	}
      
    }
  putchar('\n');
  destroyStack(pStack);

}
void widthOrderTraverse(LP_NODE pStartNode, int *pAdjWeight, int nodeNum)
{
  LP_CIRCULAR_QUEUE pQueue;
  int i, j, cur;
  LP_NODE pIterNode;

  printf("\n==Start Undirected Graph BFS :");
  
  createCircularQueue(&pQueue, nodeNum, sizeof(LP_NODE));

  for (i = 0; i < nodeNum; i++)
    (pStartNode + i)->bVisited = FALSE;

  for (i = 0; i < nodeNum; i++)
    {
      if((pStartNode+i)->bVisited)
	continue;

      pIterNode = pStartNode + i;
      pIterNode->bVisited = TRUE;
      insertToQueueTail(pQueue, &pIterNode);
      while (!isQueueEmpty(pQueue))
	{
	  getFromQueueHead(pQueue, &pIterNode);
	  putchar(pIterNode->data);
	  
	  cur = pIterNode - pStartNode;

	  for (j = 0; j < nodeNum ;j++)
	    {
	      if (j == cur 
		  || EDGE_VALUE(pAdjWeight, cur ,j) == MAX_WEIGHT)
		continue;
	      if ((pStartNode+j)->bVisited == FALSE)
		{
		  (pStartNode+j)->bVisited = TRUE;
		  pIterNode = pStartNode + j;
		  insertToQueueTail(pQueue, &pIterNode);
		}
	    }
	}
    }



  putchar('\n');
  destroyCircularQueue(pQueue);
}
LP_STACK pStack;
int visitIndex = 0;

void findBiConnectedComponent(LP_NODE pStartNode, int *pAdjWeight, int nodeNum)
{
  int i, j;  
  LP_EDGE pIterEdge;
  LP_NODE pIterNode;

  for (i = 0; i < nodeNum; i++)
    for (j = 0; j < i; j++)
      {
	if (EDGE_VALUE(pAdjWeight, i,j) == MAX_WEIGHT)
	  continue;
	createEdge(pStartNode+i, pStartNode+j);
	createEdge(pStartNode+j, pStartNode+i);
      }

  for (i = 0; i < nodeNum; i++)
    (pStartNode+i)->bVisited = FALSE;

  createStack(&pStack, sizeof(EDGE));

  dfsFindBCC(pStartNode, NULL);
  destroyStack(pStack);
}

void dfsFindBCC(LP_NODE pNode, LP_NODE pFather)
{
  EDGE tempEdge;
  LP_EDGE pIterEdge;

  pNode->bVisited = TRUE;
  pNode->index = visitIndex;
  pNode->lowPt = visitIndex;
  visitIndex++;

  pIterEdge = pNode->pFirstOutEdge;
  while (pIterEdge)
    {
      if (!pIterEdge->pTo->bVisited)
	{
	  tempEdge.pFrom = pNode;
	  tempEdge.pTo = pIterEdge->pTo;
	  push(pStack, &tempEdge);
	  dfsFindBCC(pIterEdge->pTo, pNode);
	  if (pNode->lowPt > pIterEdge->pTo->lowPt)
	    pNode->lowPt = pIterEdge->pTo->lowPt;
	  
	  if (pNode->index <= pIterEdge->pTo->lowPt)
	    {
	      //Found a new BCC
	      printf("\nNew BCC :");
	      getTop(pStack, &tempEdge);
	      while (tempEdge.pFrom->index >= pIterEdge->pTo->index)
		{
		  pop(pStack, &tempEdge);
		  getTop(pStack, &tempEdge);
		  printf(" (%c, %c)", tempEdge.pFrom->data, tempEdge.pTo->data);
		}
	      pop(pStack, &tempEdge);
	      assert(tempEdge.pFrom == pNode);
	      assert(tempEdge.pTo == pIterEdge->pTo);
	      //printf(" (%c, %c)", tempEdge.pFrom->data, tempEdge.pTo->data);
	    }

	}
      else if (pIterEdge->pTo->index < pNode->index && pIterEdge->pTo != pFather)
	{
	  tempEdge.pFrom = pNode;
	  tempEdge.pTo = pIterEdge->pTo;
	  push(pStack, &tempEdge);
	  pNode->lowPt = (pNode->lowPt > pIterEdge->pTo->index)?pIterEdge->pTo->index:pNode->lowPt;
	}


      pIterEdge = pIterEdge->pNextSameFrom;
    }
  

}

STATUS createEdge(LP_NODE pFrom, LP_NODE pTo)
{
  EDGE *pIterEdge, *pEdge;
#if 1
  pIterEdge = pFrom->pFirstOutEdge;
  while (pIterEdge && pIterEdge->pTo != pTo)
    pIterEdge = pIterEdge->pNextSameFrom;
  assert(pIterEdge == NULL);
#endif

  pEdge = (LP_EDGE)malloc(sizeof(EDGE));
  if (NULL == pEdge)
    {
      printf("Out Of Memory in Line %d, FUnction %s", __LINE__, __FUNCTION__);
      return OVERFLOW;
    }
  
  pEdge->pFrom = pFrom;
  pEdge->pTo = pTo;

  pEdge->pNextSameFrom = pFrom->pFirstOutEdge;
  pEdge->pNextSameTo = pTo->pFirstInEdge;

  pFrom->pFirstOutEdge = pEdge;
  pTo->pFirstInEdge = pEdge;

  return OK;
}
