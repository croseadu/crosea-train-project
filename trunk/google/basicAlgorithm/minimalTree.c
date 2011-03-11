
#include "../include/common.h"
#include "../include/stack.h"
#include "../include/circularQueue.h"
#include "../include/singleList.h"




#define MAX_WEIGHT 65535



typedef struct _NODE
{
  char data;
  BOOL bVisited;
}NODE, *LP_NODE;


int nodeNum;

#define EDGE_VALUE(pWeight,i, j) *(pWeight + i * nodeNum + j) 
void depthOrderTraverse(LP_NODE pStartNode, int *pAdjWeight, int nodeNum);
void widthOrderTraverse(LP_NODE pStartNode, int *pAdjWeight, int nodeNum);

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
