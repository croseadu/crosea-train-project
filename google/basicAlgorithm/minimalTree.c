
#include "../include/common.h"
#include "../include/stack.h"
#include "../include/circularQueue.h"
#include "../include/singleList.h"

#define INIT_SIZE 10
#define INCRE_SIZE 5


#define MAX_WEIGHT 65535



typedef struct _NODE
{
  char data;
  BOOL bVisited;
  int index;
  int parent; // Use for MFset, which used to build minimal Tree for Krusal
}NODE, *LP_NODE;

typedef struct _EDGE
{
  int from;
  int to;
  int value;
}EDGE, *LP_EDGE;

int nodeNum;

#define EDGE_VALUE(pWeight,i, j) *(pWeight + i * nodeNum + j) 
void depthOrderTraverse(LP_NODE pStartNode, int *pAdjWeight, int nodeNum);
void widthOrderTraverse(LP_NODE pStartNode, int *pAdjWeight, int nodeNum);
void primMinimalTree(LP_NODE pStartNode, int *pAdjWeight, int nodeNum);
void krusalMinimalTree(LP_NODE pStartNode, int *pAdjWeight, int nodeNum);

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
  primMinimalTree(pStartNode, pAdjWeight, nodeNum);
  krusalMinimalTree(pStartNode, pAdjWeight,  nodeNum);
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

typedef struct _MINIMAL_EDGE
{
  int from;
  int to;
  int value;
}MINIMAL_EDGE, *LP_MINIMAL_EDGE;

static int selectNonzeronMinimalEdge(LP_MINIMAL_EDGE minimalEdge, int nodeNum)
{
  int i;
  int minimal = -1;
  int minimalWeight = MAX_WEIGHT;
  for (i = 0; i < nodeNum; i++)
    {
      if (minimalEdge[i].value == 0)
	continue;
      
      if (minimalEdge[i].value < minimalWeight)
	{
	  minimal = i;
	  minimalWeight = minimalEdge[i].value;
	}
      
    }

  return minimal;
}

void primMinimalTree(LP_NODE pStartNode, int *pAdjWeight, int nodeNum)
{
  MINIMAL_EDGE *minimalEdge = NULL;
  int minimal, i,j;
  int newNode;

  printf("\n==Start Prim Minimal Tree==\n");
  minimalEdge = (MINIMAL_EDGE *)malloc(sizeof(MINIMAL_EDGE)*nodeNum);
  if (NULL == minimalEdge)
    {
      printf("Out Of Memory in Line %d, Function %s", __LINE__, __FUNCTION__);
      exit(OVERFLOW);
    }

  // Init minimal Edge based on edge graph
  for (i = 0; i < nodeNum; i++)
    {
      minimalEdge[i].from = i;
      minimalEdge[i].to = 0;
      minimalEdge[i].value = EDGE_VALUE(pAdjWeight, 0, i);
    }

  for (i = 1; i < nodeNum; i++)
    {
      minimal = selectNonzeronMinimalEdge(minimalEdge, nodeNum);
      if (minimal == -1)
	break;

      printf ("\nEdge in Minimal Tree [V%d, V%d, %d]", minimalEdge[minimal].from, 
	      minimalEdge[minimal].to, minimalEdge[minimal].value);

      minimalEdge[minimal].value = 0;
      newNode = minimalEdge[minimal].from;
      // Update minimal Edge information from U, {V-U}
      for (j = 0; j < nodeNum; j++)
	{
	  if (minimalEdge[j].value != 0 
	      && minimalEdge[j].value > EDGE_VALUE(pAdjWeight, newNode, j))
	    {
	      minimalEdge[j].to = newNode;
	      minimalEdge[j].value = EDGE_VALUE(pAdjWeight, newNode, j);
	    }
	}
      
    }
  if (i < nodeNum)
    {
      printf("The Graph isn't full connected\n");
    }

  putchar('\n');
  free(minimalEdge);

}

typedef struct _EDGE_HEAP
{
  LP_EDGE pEdge;
  int maxEdge;
  int maxSize;
}EDGE_HEAP, *LP_EDGE_HEAP;

static void createEdgeHeap(LP_EDGE_HEAP *ppHeap)
{
  LP_EDGE_HEAP pHeap;
  pHeap = (LP_EDGE_HEAP)malloc(sizeof(EDGE_HEAP));
  if (NULL == pHeap)
    {
      printf("Out Of Memory in Line %d, Function %s", __LINE__, __FUNCTION__);
      exit(OVERFLOW);
    }

  pHeap->pEdge = (LP_EDGE)malloc(sizeof(EDGE) * INIT_SIZE);
  if (NULL == pHeap->pEdge)
    {
      printf("Out Of Memory in Line %d, Function %s", __LINE__, __FUNCTION__);
      exit(OVERFLOW);
    }
  
  pHeap->maxEdge = 0;
  pHeap->maxSize = INIT_SIZE;

  *ppHeap = pHeap;
}

static void destroyEdgeHeap(LP_EDGE_HEAP pHeap)
{
  free(pHeap->pEdge);
  free(pHeap);
}

static void insertToEdgeHeap(LP_EDGE_HEAP pHeap, LP_EDGE pEdge)
{
  if (pHeap->maxEdge >= pHeap->maxSize-1)
    {
      pHeap->pEdge = (LP_EDGE)realloc(pHeap->pEdge, 
				      (pHeap->maxSize + INCRE_SIZE) * sizeof (EDGE));
      if (NULL == pHeap->pEdge)
	{
	  printf("Out Of Memory in Line %d, Function %s", __LINE__, __FUNCTION__);
	  exit(OVERFLOW);
	}
      pHeap->maxSize += INCRE_SIZE;
    }
  pHeap->maxEdge++;
  memcpy((char *)(pHeap->pEdge + pHeap->maxEdge), (char *)pEdge, sizeof(EDGE));
}

static BOOL isHeapEmpty(LP_EDGE_HEAP pHeap)
{
  return (pHeap->maxEdge == 0)?TRUE:FALSE;
}

static void heapAdjust(LP_EDGE_HEAP pHeap, int start, int max)
{
  EDGE tempEdge;
  int i = start, j;

  tempEdge.from = (pHeap->pEdge+start)->from;
  tempEdge.to = (pHeap->pEdge+start)->to;
  tempEdge.value = (pHeap->pEdge+start)->value;

  for (j = 2*i; j <= max;)
    {
      if (j+1<=max 
	  && (pHeap->pEdge+j+1)->value < (pHeap->pEdge+j)->value)
	j = j+1;
      if ((pHeap->pEdge+j)->value < tempEdge.value)
	{
	  (pHeap->pEdge+i)->from = (pHeap->pEdge+j)->from;
	  (pHeap->pEdge+i)->to = (pHeap->pEdge+j)->to;
	  (pHeap->pEdge+i)->value = (pHeap->pEdge+j)->value;
	  i = j;
	  j = 2*i;
	}
      else
	break;
    }
  (pHeap->pEdge+i)->value = tempEdge.value;
  (pHeap->pEdge+i)->from = tempEdge.from;
  (pHeap->pEdge+i)->to = tempEdge.to;
}
static void normalizeHeap(LP_EDGE_HEAP pHeap)
{
  int i;
  i = pHeap->maxEdge/2;
  for (;i>0;i--)
    heapAdjust(pHeap, i, pHeap->maxEdge);
}

static getMinimalFromHeap(LP_EDGE_HEAP pHeap, LP_EDGE pEdge)
{
  pEdge->from = (pHeap->pEdge + 1)->from;
  pEdge->to = (pHeap->pEdge+1)->to;
  pEdge->value = (pHeap->pEdge+1)->value;

  (pHeap->pEdge+1)->from = (pHeap->pEdge+pHeap->maxEdge)->from;
  (pHeap->pEdge+1)->to = (pHeap->pEdge+pHeap->maxEdge)->to;
  (pHeap->pEdge+1)->value = (pHeap->pEdge+pHeap->maxEdge)->value;
  pHeap->maxEdge--;
  if (pHeap->maxEdge > 1)
    heapAdjust(pHeap, 1, pHeap->maxEdge);
}

static int findRoot(LP_NODE pStartNode, int child)
{
  int root, k;

  root = child;

  while ((pStartNode+root)->parent > 0)
    root = (pStartNode+root)->parent;

  while (child != root)
    {
      k = (pStartNode + child)->parent;
      (pStartNode + child)->parent = root;
      child = k;
    }
  
  return root;
}

static void merge(LP_NODE pStartNode, int tree1, int tree2)
{
  if ((pStartNode+tree1)->parent > (pStartNode+tree2)->parent)
    {
      (pStartNode + tree2)->parent += (pStartNode + tree1)->parent;
      (pStartNode + tree1)->parent = tree2;
    }
  else
    {
      (pStartNode + tree1)->parent += (pStartNode + tree2)->parent;
      (pStartNode + tree2)->parent = tree1;
    }
}

// Work On Edge, Build a Heap, store Edge in Heap
void krusalMinimalTree(LP_NODE pStartNode, int *pAdjWeight, int nodeNum)
{
  int heapSize = INIT_SIZE;
  int maxEdgeNum = 0;
  LP_EDGE_HEAP pHeap;
  EDGE tempEdge;
  int root1, root2;
  int i, j;
  
  printf("\n==Start Krusal Minimal Tree ==\n");

  createEdgeHeap(&pHeap);

  for (i = 0; i < nodeNum; i++)
    {
      (pStartNode + i)->index = i;
      (pStartNode + i)->parent = 0;
    }

  for (i = 0; i < nodeNum; i++)
    for (j = 0; j < nodeNum; j++)
      {
	if (i < j &&
	    EDGE_VALUE(pAdjWeight, i ,j) < MAX_WEIGHT)
	  {
	    maxEdgeNum++;
	    tempEdge.from = i;
	    tempEdge.to = j;
	    tempEdge.value = EDGE_VALUE(pAdjWeight, i, j);
	    insertToEdgeHeap(pHeap, &tempEdge);
	  }
      }
  normalizeHeap(pHeap);
  printf("\nDump Edge Heap:\n");
  for (i = 1; i <= pHeap->maxEdge; i++)
    {
      printf("[V%d, V%d, %d]", 
	     (pHeap->pEdge+i)->from, (pHeap->pEdge+i)->to,(pHeap->pEdge+i)->value);
    }
  putchar('\n');

  for (i = 1; i < nodeNum; i++)
    {
      root1 = root2 = 0;
	while (!isHeapEmpty(pHeap))
	{
	  getMinimalFromHeap(pHeap, &tempEdge);
	  root1 = findRoot(pStartNode, tempEdge.from);
	  root2 = findRoot(pStartNode ,tempEdge.to);
	  if (root1 != root2)
	    break;
	}
      if (root1 == root2)
	break;
      printf("\nMinimal Tree Edge [V%d, V%d, %d]",
	     tempEdge.from, tempEdge.to, tempEdge.value);
      merge(pStartNode, tempEdge.from, tempEdge.to);

    }

  putchar('\n');
  destroyEdgeHeap(pHeap);
  if (i < nodeNum)
    {
      printf("\nGraph isn't full connected\n");
    }
}
