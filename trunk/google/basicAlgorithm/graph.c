#include "../include/common.h"
#include "../include/stack.h"
#include "../include/circularQueue.h"
#include "../include/singleList.h"

#define INIT_SIZE 10
#define INCRE_SIZE 5

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
  struct _EDGE *pNextSameFrom;
  struct _EDGE *pNextSameTo;
}EDGE, *LP_EDGE;

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
  printf("%c", *(char *)pData);
}

STATUS createNode(LP_NODE *ppNode, void *pData, unsigned int sizeOfData);
STATUS createEdge(LP_NODE pFrom, LP_NODE pTo);
void destroyGraph(LP_NODE pStartNode);
#define VALID_NODE_DATA(c) (c != EOF && c != ',' && c != ')' && c != '(')
#define VALID_EDGE_START(c) (c == '(')
#define VALID_EDGE_SEPARATOR(c) (c == ',')
#define VALID_EDGE_END(c) (c == ')')


void depthOrderTraverse(LP_NODE pStartNode, VISIT_FUNC visit);
void widthOrderTraverse(LP_NODE pStartNode, VISIT_FUNC visit);
void topoOrderTraverse(LP_NODE pStartNode, VISIT_FUNC visit);

int main()
{
  FILE *fp;
  char c;
  STATUS status = OK;
  NODE *pStartNode = NULL, *pTo, *pFrom;
  LP_NODE pIterNode, pNextNode;
  EDGE *pEdge;

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
      status = createEdge(pFrom, pTo);
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

  printf("\nTopo Order Traverse:");
  topoOrderTraverse(pStartNode, visit);



  putchar('\n');
  destroyGraph(pStartNode);
  fclose(fp);
  return 0;
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
		  visit(pIterNode->pData);
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
	  while (!isQueueEmpty(pQueue))
	    {
	      getFromQueueHead(pQueue, &pIterNode);
	      if (pIterNode->bVisited)
		continue;
	      visit(pIterNode->pData);
	      pIterNode->bVisited = TRUE;
	      pIterEdge = pIterNode->pFirstOutEdge;
	      while (pIterEdge)
		{
		  if (pIterEdge->pTo->bVisited == FALSE)
		    {
		      insertToQueueTail(pQueue, &pIterEdge->pTo);
		    }
		  pIterEdge = pIterEdge->pNextSameFrom;
		}
	    }
	}
      pIterNode = pIterNode->pNextNode;
    }

  destroyCircularQueue(pQueue);
}

typedef struct _DEGREE
{
  LP_NODE pNode;
  unsigned int degree;
}DEGREE, *LP_DEGREE;

S_RESULT compareNode(void *pFirst, void *pSecond)
{
  if (!memcmp(pFirst, pSecond, sizeof(LP_NODE)))
    return R_EQ;
  else
    return R_GT;
}

void topoOrderTraverse(LP_NODE pStartNode, VISIT_FUNC visit)
{
  LP_NODE pIterNode;
  LP_EDGE pIterEdge;
  LP_STACK pStack;
  LP_SINGLE_LIST_NODE pListHead;
  unsigned int nodeNum = 0;
  unsigned int visitNum = 0;
  STATUS status;
  DEGREE tempDegree;

  status = createStack (&pStack, sizeof (pIterNode));
  if (status != OK)
    {
      printf("Create Stack Failed in Function %s", __FUNCTION__);
      exit(-1);
    }


  status = createSingleList(&pListHead, sizeof(DEGREE));
    if (status != OK)
    {
      printf("Create Single List Failed in Function %s", __FUNCTION__);
      exit(-1);
    }
    
  pIterNode = pStartNode;
  while (pIterNode)
    {
      pIterNode->bVisited = FALSE;
      nodeNum++;

      memset(&tempDegree, 0, sizeof(DEGREE));
      tempDegree.pNode = pIterNode;
      pIterEdge = pIterNode->pFirstInEdge;
      while (pIterEdge)
	{
	  tempDegree.degree++;
	  pIterEdge = pIterEdge->pNextSameTo;
	}
      if (tempDegree.degree)
	insertToHead(pListHead, &tempDegree);
      else
	push (pStack, &pIterNode);

      pIterNode = pIterNode->pNextNode;
    }

  while (!isStackEmpty(pStack))
    {
      pop (pStack, &pIterNode);
      visit (pIterNode->pData);
      pIterNode->bVisited = TRUE;
      visitNum++;

      pIterEdge = pIterNode->pFirstOutEdge;
      while (pIterEdge)
	{
	  LP_NODE pTo;
	  pTo = pIterEdge->pTo;

	  findItemInList(pListHead, &pTo, &tempDegree, compareNode);
	  deleteItemFromList(pListHead, &pTo, compareNode);
	  tempDegree.degree--;
	  if (tempDegree.degree == 0)
	    push (pStack, &pTo);
	  else
	    insertToHead(pListHead, &tempDegree);

	  pIterEdge = pIterEdge->pNextSameFrom;
	}
    }
  
  if (nodeNum > visitNum)
    {
      printf("\n Cycle in Graph, total Node is %d, node in Cyle is %d\n",nodeNum, nodeNum - visitNum);
    }
  else
    {
      printf (":No Cycle in Graph, total Node %d\n", nodeNum);
    }

  destroySingleList(pListHead);
  destroyStack(pStack);
}
