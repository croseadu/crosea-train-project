
#include "../include/common.h"
#include "../include/stack.h"
#include "../include/circularQueue.h"
#include "../include/singleList.h"

#define INIT_SIZE 10
#define INCRE_SIZE 5

#define MAX_TIME 65535
struct _EDGE;

typedef struct _NODE
{
  char *pData;
  struct _EDGE *pFirstInEdge;
  struct _EDGE *pFirstOutEdge;
  struct _NODE *pNextNode;
  BOOL bVisited;
  BOOL bInStack;
  BOOL bFoundSCC;
  int dfsVisitIndex;
  int reachLowIndex;
}NODE, *LP_NODE;

typedef struct _EDGE
{
  NODE *pFrom;
  NODE *pTo;
  int value;
  struct _EDGE *pNextSameFrom;
  struct _EDGE *pNextSameTo;
}EDGE, *LP_EDGE;

LP_NODE findNode(LP_NODE pStartNode, void *pKeyData, COMPARE_FUNC compare);

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

STATUS createNode(LP_NODE *ppNode, void *pData, unsigned int sizeOfData);
STATUS createEdge(LP_NODE pFrom, LP_NODE pTo);
void destroyGraph(LP_NODE pStartNode);
#define VALID_NODE_DATA(c) (c != EOF && c != ',' && c != ')' && c != '(')
#define VALID_EDGE_START(c) (c == '(')
#define VALID_EDGE_SEPARATOR(c) (c == ',')
#define VALID_EDGE_END(c) (c == ')')


void depthOrderTraverse(LP_NODE pStartNode, VISIT_FUNC visit);
void widthOrderTraverse(LP_NODE pStartNode, VISIT_FUNC visit);
void findSCC(LP_NODE pStartNode);
void tarjanFindSCC(LP_NODE pStartNode);
void tarjanDFS(LP_NODE);

void gabowFindSCC(LP_NODE pStartNode);
void gabowDFS(LP_NODE);
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

  /*
  printf ("\nDFS Forest:");
  DFSforest(pStartNode, &pDFStree);
  preOrderTraverseForest(pDFStree);
  freeDFStree(pDFStree);
  */

  findSCC(pStartNode);

  printf("\n Use Tarjan Algorithm:\n");
  tarjanFindSCC(pStartNode);

  printf("\b Use Gabow Algorithm:\n");
  gabowFindSCC(pStartNode);

  /*
  printf("\nTopo Order Traverse:");
  topoOrderTraverse(pStartNode, visit);

  printf("\nCritical Path:");
  criticalPath(pStartNode);

  printf("\nShortest Path:");
  shortestPath(pStartNode);
  */

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
	  while (!isQueueEmpty(pQueue))
	    {
	      getFromQueueHead(pQueue, &pIterNode);
	      if (pIterNode->bVisited)
		continue;
	      visit(pIterNode);
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


static LP_NODE *pOrderNodeArray;
static int curOrder;

void dfsForSCC(LP_NODE pRoot)
{
  LP_EDGE pIterEdge;
  LP_NODE pIterNode;

  pRoot->bVisited = TRUE;
  
  pIterEdge = pRoot->pFirstOutEdge;
  while (pIterEdge)
    {
      pIterNode = pIterEdge->pTo;
      if (pIterNode->bVisited == FALSE)
	dfsForSCC(pIterNode);
      pIterEdge = pIterEdge->pNextSameFrom;
    }
  
  pOrderNodeArray[curOrder++] = pRoot;
}

void revertDFS(LP_NODE pRoot)
{
  LP_EDGE pIterEdge;
  LP_NODE pIterNode;

  pRoot->bVisited = TRUE;
  printf("%c", *(char *)pRoot->pData);

  pIterEdge = pRoot->pFirstInEdge;
  while (pIterEdge)
    {
      pIterNode = pIterEdge->pFrom;
      if (pIterNode->bVisited == FALSE)
	revertDFS(pIterNode);
      pIterEdge = pIterEdge->pNextSameTo;
    }
}

void findSCC(LP_NODE pStartNode)
{
  LP_NODE pIterNode;
  int i;
  int nodeNum = 0, sccNum = 0;

  pIterNode = pStartNode;
  while (pIterNode)
    {
      nodeNum++;
      pIterNode->bVisited = FALSE;
      pIterNode = pIterNode->pNextNode;
    }
  
  curOrder = 0;
  pOrderNodeArray = (LP_NODE *)malloc(sizeof(LP_NODE)*nodeNum);
  if (NULL == pOrderNodeArray)
    {
      printf("Out Of Memory in Line %d, Function %s", __LINE__, __FUNCTION__);
      exit(OVERFLOW);
    }
  
  memset(pOrderNodeArray, 0, sizeof(LP_NODE)*nodeNum);

  pIterNode = pStartNode;
  while (pIterNode)
    {
      if (pIterNode->bVisited == FALSE)
	dfsForSCC(pIterNode);
      pIterNode = pIterNode->pNextNode;
    }
  printf("\nFinished DFS Order is :");
  for (i = 0; i < curOrder; i++)
    {
      printf("%c", *(char *)pOrderNodeArray[i]->pData);
      pOrderNodeArray[i]->bVisited = FALSE;
    }
  putchar('\n');

  //Start To Calculate SCC
  curOrder--;
  sccNum = 0;
  while (curOrder >= 0)
    {
      printf("The %d SCC is :", sccNum);
      sccNum++;
      revertDFS(pOrderNodeArray[curOrder]);
      putchar('\n');
      while (curOrder >= 0 && pOrderNodeArray[curOrder]->bVisited == TRUE)
	curOrder--;
    }
  putchar('\n');
  free(pOrderNodeArray);
}

LP_STACK pStack;
int visitIndex = 0;

void tarjanFindSCC(LP_NODE pStartNode)
{
  LP_NODE pIterNode;
  LP_EDGE pIterEdge;
  int nodeNum;
  
  createStack(&pStack, sizeof(LP_NODE));

  nodeNum++;
  pIterNode = pStartNode;
  while (pIterNode)
    {
      pIterNode->bVisited = FALSE;
      pIterNode->bInStack = FALSE;
      pIterNode = pIterNode->pNextNode;
      nodeNum++;
    }

  pIterNode = pStartNode;
  while (pIterNode)
    {
      if (pIterNode->bVisited)
	{
	  pIterNode = pIterNode->pNextNode;
	  continue;
	}
      
      tarjanDFS(pIterNode);

      pIterNode = pIterNode->pNextNode;
    }

  destroyStack(pStack);

}

void tarjanDFS(LP_NODE pRoot)
{
  LP_NODE pIterNode;
  LP_EDGE pIterEdge;

  pRoot->bVisited = TRUE;
  pRoot->dfsVisitIndex = visitIndex;
  pRoot->reachLowIndex = visitIndex;
  push(pStack, &pRoot);
  pRoot->bInStack = TRUE;

  visitIndex++;
  pIterEdge = pRoot->pFirstOutEdge;
  while (pIterEdge)
    {
      if (pIterEdge->pTo->bVisited == FALSE)
	{
	  tarjanDFS(pIterEdge->pTo);
	  if (pIterEdge->pTo->reachLowIndex < pRoot->reachLowIndex)
	    pRoot->reachLowIndex = pIterEdge->pTo->reachLowIndex;
	}
      else if (pIterEdge->pTo->bInStack 
	       && pIterEdge->pTo->dfsVisitIndex < pRoot->reachLowIndex)
	{
	  pRoot->reachLowIndex = pIterEdge->pTo->dfsVisitIndex;
	}

      pIterEdge = pIterEdge->pNextSameFrom;
    }

  if (pRoot->dfsVisitIndex == pRoot->reachLowIndex)
    {
      printf("\nNew SCC:");
      do 
	{
	  pop(pStack, &pIterNode);
	  pIterNode->bInStack = FALSE;
	  printf("%c", *(char *)pIterNode->pData);
	}while (pIterNode != pRoot);
    }
}

LP_STACK pStack1, pStack2;

void gabowFindSCC(LP_NODE pStartNode)
{
  LP_NODE pIterNode;
  LP_EDGE pIterEdge;
  
  createStack(&pStack1, sizeof(LP_NODE));
  createStack(&pStack2, sizeof(LP_NODE));
  
  visitIndex = 0;
  pIterNode = pStartNode;
  while (pIterNode)
    {
      pIterNode->bVisited = FALSE;
      pIterNode->bFoundSCC = FALSE;
      pIterNode = pIterNode->pNextNode;
    }

  pIterNode = pStartNode;
  while (pIterNode)
    {
      if (pIterNode->bVisited)
	{
	  pIterNode = pIterNode->pNextNode;
	  continue;
	}
      
      gabowDFS(pIterNode);

      pIterNode = pIterNode->pNextNode;
    }

  destroyStack(pStack1);
  destroyStack(pStack2);
}

void gabowDFS(LP_NODE pRoot)
{
  LP_NODE pIterNode;
  LP_EDGE pIterEdge;

  pRoot->bVisited = TRUE;
  pRoot->dfsVisitIndex = visitIndex;
  push(pStack1, &pRoot);
  push(pStack2, &pRoot);

  visitIndex++;
  pIterEdge = pRoot->pFirstOutEdge;
  while (pIterEdge)
    {
      if (pIterEdge->pTo->bVisited == FALSE)
	{
	  gabowDFS(pIterEdge->pTo);
	}
      else if (!pIterEdge->pTo->bFoundSCC)
	{
	  getTop(pStack2, &pIterNode);
	  while (pIterNode->dfsVisitIndex > pIterEdge->pTo->dfsVisitIndex)
	    {
	      pop(pStack2, &pIterNode);
	      getTop(pStack2, &pIterNode);
	    }
	}

      pIterEdge = pIterEdge->pNextSameFrom;
    }

  getTop(pStack2, &pIterNode);
  if (pIterNode == pRoot)
    {
      printf("\nNew SCC:");
      do 
	{
	  pop(pStack1, &pIterNode);
	  pIterNode->bFoundSCC = TRUE;
	  printf("%c", *(char *)pIterNode->pData);
	}while (pIterNode != pRoot);
      pop(pStack2, &pIterNode);
    }
}
