#include "../../../include/common.h"
#include "../../../include/stack.h"
#include "../../../include/circularQueue.h"
#include "../../../include/singleList.h"


struct _EDGE;

typedef struct _NODE
{
  char *pData;
  struct _EDGE *pFirstInEdge;
  struct _EDGE *pFirstOutEdge;
  struct _NODE *pNextNode;
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

#define VALUE_EDGE
int findShortestPath(LP_NODE pStartNode, char from, char to);
void depthOrderTraverse(LP_NODE pStartNode, VISIT_FUNC visit);
void widthOrderTraverse(LP_NODE pStartNode, VISIT_FUNC visit);
STATUS createNode(LP_NODE *ppNode, void *pData, unsigned int sizeOfData);
STATUS createEdge(LP_NODE pFrom, LP_NODE pTo);
STATUS createValueEdge(LP_NODE pFrom, LP_NODE pTo, int value);
void destroyGraph(LP_NODE pStartNode);
#define VALID_NODE_DATA(c) (c != EOF && c != ',' && c != ')' && c != '(')
#define VALID_EDGE_START(c) (c == '(')
#define VALID_EDGE_SEPARATOR(c) (c == ',')
#define VALID_EDGE_END(c) (c == ')')

LP_NODE findNode(LP_NODE pStartNode, void *pKeyData, COMPARE_FUNC compare);

void printChar(char c)
{
  printf ("%c",c);
}

void getNext(FILE *fp, char *pC)
{
  while (!feof(fp))
      {
	*pC = fgetc(fp); 
	if (*pC != ' ' && *pC != '\t' && *pC != '\n' && *pC != '\r')
	  break;
      }
}

S_RESULT compareKey(void *pFirst, void *pSecond)
{
  if (*(char *)pFirst == *(char *)pSecond)
    return R_EQ;
  return R_LT;
}

void visit (void *pData)
{
  LP_NODE pNode = (LP_NODE)pData;
  printf("%c", *(char *)pNode->pData);
}

LP_NODE findNode(LP_NODE pStartNode, void *pKeyData, COMPARE_FUNC compare)
{
  LP_NODE pIterNode = pStartNode;
  while (pIterNode && compare(pIterNode->pData, pKeyData) != R_EQ)
    pIterNode = pIterNode->pNextNode;
  
  return pIterNode; 
}
STATUS createNode(LP_NODE *ppNode, void *pData, unsigned int sizeOfData)
{
  LP_NODE pNode;
  pNode = (LP_NODE)malloc(sizeof(NODE));
  if (NULL == pNode)
    {
      printf("Out Of Memory in Line %d, Function %s", __LINE__, __FUNCTION__);
      return OVERFLOW;
    }
  memset(pNode, 0, sizeof(NODE));
  pNode->pData = (char *)malloc(sizeOfData);
  if (NULL == pNode->pData)
    {
      printf("Out Of Memory in Line %d, Function %s", __LINE__, __FUNCTION__);
      return OVERFLOW;
    }

  memcpy(pNode->pData, (char *)pData, sizeOfData);
  *ppNode = pNode;
  return OK;
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
STATUS createValueEdge(LP_NODE pFrom, LP_NODE pTo, int value)
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
  pEdge->value = value;

  pEdge->pNextSameFrom = pFrom->pFirstOutEdge;
  pEdge->pNextSameTo = pTo->pFirstInEdge;

  pFrom->pFirstOutEdge = pEdge;
  pTo->pFirstInEdge = pEdge;

  return OK;
}


void destroyGraph(LP_NODE pStartNode);

int main()
{
  FILE *fp;
  char c;
  STATUS status;
  NODE *pFrom, *pTo, *pStartNode, *pIterNode, *pNextNode;
  EDGE *pEdge;
  int value;
  
  pStartNode = NULL;


  if ((fp = fopen("inputData.txt", "r")) == NULL)
    {
      printf ("Cannot Open File inputData.txt\n");
      exit(-1);
    }

  getNext(fp, &c);
  while (!feof(fp))
    {
       if (!VALID_EDGE_START(c))
	{
	  status = ERROR;
	  break;
	}
      getNext(fp, &c);
      if (!VALID_NODE_DATA(c))
	{
	  status = ERROR;
	  break;
	}
      if ((pFrom = findNode(pStartNode, &c, compareKey)) == NULL)
	{
	  status = createNode(&pFrom, &c, sizeof(char));
	  if (status != OK)
	    break;
	  pFrom->pNextNode = pStartNode;
	  pStartNode = pFrom;
	}
      getNext(fp, &c);
      if (!VALID_EDGE_SEPARATOR(c))
	{
	  status = ERROR;
	  break;
	}

#ifdef VALUE_EDGE
      if (fscanf(fp, "%d", &value))
	{
	  if (value < 0)
	    {
	      printf("Invalid Edge Value\n");
	      status = ERROR; 
	      break;
	    }
	}
      else
	{
	  printf("Invalid Input for Edge\n");
	  status = ERROR;
	  break;
	}
      getNext(fp, &c);
      if (!VALID_EDGE_SEPARATOR(c))
	{
	  status = ERROR;
	  break;
	}
#endif

      getNext(fp, &c);
      if (!VALID_NODE_DATA(c))
	{
	  status = ERROR;
	}
      if ((pTo = findNode(pStartNode, &c, compareKey)) == NULL)
	{
	  status = createNode(&pTo, &c, sizeof(char));
	  if (status != OK)
	    break;
	  pTo->pNextNode = pStartNode;
	  pStartNode = pTo;
	}
#ifdef VALUE_EDGE
      status = createValueEdge(pFrom, pTo, value);
#else
      status = createEdge(pFrom, pTo);
#endif
      if (status != OK)
	break;
      getNext(fp, &c);
      if (!VALID_EDGE_END(c))
	{
	  status = ERROR;
	  break;
	}
      getNext(fp, &c);
    }
  if (status == ERROR)
    {
      fclose(fp);
      exit(-1);
    }

  // Reverse the Node List 
  pIterNode = pStartNode->pNextNode;
  pStartNode->pNextNode = NULL;
  while (pIterNode)
    {
      pNextNode = pIterNode->pNextNode;
      pIterNode->pNextNode = pStartNode;
      pStartNode = pIterNode;
      pIterNode = pNextNode;
    }
  printf("\nOriginal Node List is :");
  pIterNode = pStartNode;
  while (pIterNode)
    {
      printf ("%c", *(char *)pIterNode->pData);
      pIterNode = pIterNode->pNextNode;
    }


  printf("\nDepth First Order Traverse:");
  depthOrderTraverse(pStartNode, visit);
  printf("\nWidth First Order Traverse:");
  widthOrderTraverse(pStartNode, visit);
  putchar('\n');

  findShortestPath(pStartNode,'s', 't');

  destroyGraph(pStartNode);
  fclose(fp);

  return 0;

}
int maxNum = 0;
LP_NODE *array = NULL;
int *next = NULL; 

int findShortestPath(LP_NODE pStartNode, char from, char to)
{
  LP_NODE pFrom, pTo;
  LP_NODE pIterNode;
  STATUS status;
  int i;
  int *dist = NULL;
  LP_CIRCULAR_QUEUE pQueue;
  LP_EDGE pIterEdge;

  pFrom = findNode(pStartNode, &from, compareKey);
  pTo = findNode(pStartNode, &to, compareKey);
  assert(pFrom && pTo);

  pIterNode = pStartNode;
  while(pIterNode)
    {
      pIterNode->bVisited = FALSE;
      pIterNode = pIterNode->pNextNode;
      maxNum++;
    }

  array = (LP_NODE *)malloc(sizeof(LP_NODE)*maxNum);
  if (NULL == array)
    {
      printf ("Out Of Memory in Line %d, Function %s", __LINE__, __FUNCTION__);
      exit(OVERFLOW);
    }
  memset(array, 0, sizeof(LP_NODE)*maxNum);

  next = (int *)malloc(sizeof(int)*maxNum);
  if (NULL == next)
    {
      printf ("Out Of Memory in Line %d, Function %s", __LINE__, __FUNCTION__);
      exit(OVERFLOW);
    }
  memset(next, 0, sizeof(int)*maxNum);

  dist = (int *)malloc(sizeof(int)*maxNum);
  if (NULL == dist)
    {
      printf ("Out Of Memory in Line %d, Function %s", __LINE__, __FUNCTION__);
      exit(OVERFLOW);
    }
  memset(dist, 0xFF, sizeof(int)*maxNum);

  status = createCircularQueue(&pQueue, maxNum, sizeof(LP_NODE));
  if (status != OK)
    {
      printf ("Create Circular Queue Failed in Function %s", __FUNCTION__);
      exit(-1);
    }

  i = 0;
  pFrom->bVisited = TRUE;
  insertToQueueTail(pQueue, &pFrom);
  while(!isQueueEmpty(pQueue))
    {
      getFromQueueHead(pQueue, &pIterNode);
      array[i++] = pIterNode;
      pIterEdge = pIterNode->pFirstOutEdge;
      while (pIterEdge)
	{
	  if (pIterEdge->pTo->bVisited == FALSE)
	    {
	      insertToQueueTail(pQueue, &pIterEdge->pTo);
	      pIterEdge->pTo->bVisited = TRUE;
	    }
	  pIterEdge = pIterEdge->pNextSameFrom;
	}
    }

  assert(i == maxNum && array[0] == pFrom && array[i-1] == pTo);
  dist[maxNum-1] = 0;
  i = maxNum-2;
  while(i>=0)
    {
      int minDist = 65535;

      pIterNode = array[i];
      pIterEdge = pIterNode->pFirstOutEdge;
      while (pIterEdge)
	{
	  int j;
	  for (j = i+1; i < maxNum; j++)
	    if (array[j] == pIterEdge->pTo)
	      break;
	  assert(j < maxNum);
	  assert(dist[j] != -1);
	  if (minDist > dist[j] + pIterEdge->value)
	    {
	      minDist = dist[j] + pIterEdge->value;
	      next[i] = j;
	    }
	  dist[i] = minDist;
	  pIterEdge = pIterEdge->pNextSameFrom;
	}
      i--;
    }

  printf("\nFrom %c to %c shortest path = %d", 
	 *(char *)pFrom->pData, 
	 *(char *)pTo->pData, 
	 dist[0]);
  putchar('\n');
  printf("Path:%c", *(char *)array[0]->pData);
  i = next[0];
  while(i != maxNum - 1)
    {
      printf("-%c", *(char *)array[i]->pData);
      i = next[i];
    }
  printf("-%c\n", *(char *)array[i]->pData);

  free(dist);
  free(array);
  free(next);

  destroyCircularQueue(pQueue);
}


void destroyGraph(LP_NODE pStartNode)
{
  LP_NODE pIterNode, pNextNode;
  LP_EDGE pIterEdge, pNextEdge;

  
  pIterNode = pStartNode;

  while (pIterNode)
    {
      pNextNode = pIterNode->pNextNode;
      pIterEdge = pIterNode->pFirstOutEdge;
      while (pIterEdge)
	{
	  pNextEdge = pIterEdge->pNextSameFrom;
	  free(pIterEdge);
	  pIterEdge = pNextEdge;
	}
      pIterNode = pNextNode;
    }
}
void depthOrderTraverse(LP_NODE pStartNode, VISIT_FUNC visit)
{
  LP_NODE pIterNode;
  LP_EDGE pIterEdge;
  LP_STACK pStack;
  STATUS status;

  status = createStack(&pStack, sizeof(LP_NODE));
  if (status != OK)
    {
      printf("Create Stack Failed in Function %s", __FUNCTION__);
      exit(-1);
    }

  pIterNode = pStartNode;
  while (pIterNode)
    {
      pIterNode->bVisited = FALSE;
      pIterNode = pIterNode->pNextNode;
    }

  pIterNode = pStartNode;
  while (pIterNode)
    {
      if (pIterNode->bVisited == FALSE)
	{
	  push (pStack, &pIterNode);
	  while (!isStackEmpty(pStack))
	    {     
	      pop (pStack, &pIterNode);
	      if (pIterNode->bVisited == FALSE)
		{
		  visit(pIterNode);
		  pIterNode->bVisited = TRUE;
		  pIterEdge = pIterNode->pFirstOutEdge;
		  while (pIterEdge)
		    {
		      if (pIterEdge->pTo->bVisited == FALSE)
			{
			  push (pStack, &pIterEdge->pTo);
			}
		      pIterEdge = pIterEdge->pNextSameFrom;
		    }
		}
	    }
	}
      pIterNode = pIterNode->pNextNode;
    }
  destroyStack(pStack);
}

void widthOrderTraverse(LP_NODE pStartNode, VISIT_FUNC visit)
{
  LP_NODE pIterNode;
  LP_CIRCULAR_QUEUE pQueue;
  STATUS status;
  unsigned int maxNum = 0;
  LP_EDGE pIterEdge;

  pIterNode = pStartNode;
  while(pIterNode)
    {
      pIterNode->bVisited = FALSE;
      pIterNode = pIterNode->pNextNode;
      maxNum++;
    }
  status = createCircularQueue(&pQueue, maxNum, sizeof(LP_NODE));
  if (status != OK)
    {
      printf ("Create Circular Queue Failed in Function %s", __FUNCTION__);
      exit(-1);
    }

  pIterNode = pStartNode;
  while (pIterNode)
    {
      if (pIterNode->bVisited == FALSE)
	{
	  insertToQueueTail(pQueue, &pIterNode);
	  pIterNode->bVisited = TRUE;
	  while (!isQueueEmpty(pQueue))
	    {
	      getFromQueueHead(pQueue, &pIterNode);
	      visit(pIterNode);
	      pIterEdge = pIterNode->pFirstOutEdge;
	      while (pIterEdge)
		{
		  if (pIterEdge->pTo->bVisited == FALSE)
		    {
		      insertToQueueTail(pQueue, &pIterEdge->pTo);
		      pIterEdge->pTo->bVisited = TRUE;
		    }
		  pIterEdge = pIterEdge->pNextSameFrom;
		}
	    }
	}
      pIterNode = pIterNode->pNextNode;
    }

  destroyCircularQueue(pQueue);
}
