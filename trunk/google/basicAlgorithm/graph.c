#include "../include/common.h"
#include "../include/stack.h"
#include "../include/circularQueue.h"
#include "../include/singleList.h"

#define INIT_SIZE 10
#define INCRE_SIZE 5

//#define VALUE_EDGE

#define MAX_TIME 65535
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


typedef struct _DFS_TREE
{
  LP_NODE pNode;
  struct _DFS_TREE *pFirstChild;
  struct _DFS_TREE *pNextSibling;
}DFS_TREE, *LP_DFS_TREE;


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

STATUS createNode(LP_NODE *ppNode, void *pData, unsigned int sizeOfData);
STATUS createEdge(LP_NODE pFrom, LP_NODE pTo);
STATUS createValueEdge(LP_NODE pFrom, LP_NODE pTo, int value);
void destroyGraph(LP_NODE pStartNode);
#define VALID_NODE_DATA(c) (c != EOF && c != ',' && c != ')' && c != '(')
#define VALID_EDGE_START(c) (c == '(')
#define VALID_EDGE_SEPARATOR(c) (c == ',')
#define VALID_EDGE_END(c) (c == ')')


void depthOrderTraverse(LP_NODE pStartNode, VISIT_FUNC visit);
void widthOrderTraverse(LP_NODE pStartNode, VISIT_FUNC visit);
BOOL topoOrderTraverse(LP_NODE pStartNode, VISIT_FUNC visit);
void criticalPath(LP_NODE pStartNode);
void shortestPath(LP_NODE pStartNode);
static void DFStree(LP_DFS_TREE pRoot);
void DFSforest(LP_NODE pStartNode, LP_DFS_TREE *ppDfsTreeRoot);
static void preOrderTraverseForest(LP_DFS_TREE pStartRoot);

void freeDFStree(LP_DFS_TREE pStartRooot);
void findSCC(LP_NODE pStartNode);
int main()
{
  FILE *fp;
  char c;
  STATUS status = OK;
  NODE *pStartNode = NULL, *pTo, *pFrom;
  LP_NODE pIterNode, pNextNode;
  EDGE *pEdge;
  int value;
  LP_DFS_TREE pDFStree;

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

  /*
  printf ("\nDFS Forest:");
  DFSforest(pStartNode, &pDFStree);
  preOrderTraverseForest(pDFStree);
  freeDFStree(pDFStree);
  */

  findSCC(pStartNode);
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

BOOL topoOrderTraverse(LP_NODE pStartNode, VISIT_FUNC visit)
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
      visit (pIterNode);
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
  return (nodeNum == visitNum)?TRUE:FALSE;
}

static LP_SINGLE_LIST_NODE pReverseTopoOrderList;
static LP_SINGLE_LIST_NODE pEarlyTimeList;
static LP_SINGLE_LIST_NODE pLateTimeList;

typedef struct _EARLY_TIME
{
  LP_NODE pNode;
  unsigned int time;
}TIME, *LP_TIME;

static void calculateEarlyAndRecordOrder(void *pData)
{
  LP_NODE pNode = (LP_NODE)pData;
  LP_EDGE pIterEdge;
  TIME earlyTime;
  unsigned int maxTime = 0;
  BOOL bFind;

  insertToHead(pReverseTopoOrderList, &pNode);
  pIterEdge = pNode->pFirstInEdge;
  if (pIterEdge)
    {
      while (pIterEdge)
	{
	  bFind = findItemInList(pEarlyTimeList, &pIterEdge->pFrom, &earlyTime, compareNode);
	  assert(bFind);
	  if (earlyTime.time + pIterEdge->value > maxTime)
	    maxTime = earlyTime.time + pIterEdge->value;
	  pIterEdge = pIterEdge->pNextSameTo;
	}
    }
  earlyTime.time = maxTime;
  earlyTime.pNode = pNode;

  insertToHead(pEarlyTimeList, &earlyTime);
}

static void updateLateTime(void *pData)
{
  LP_TIME pTime = (LP_TIME)pData;
  LP_NODE pNode;
  LP_EDGE pIterEdge;
  int minTime;
  BOOL bFind;
  TIME lateTime;

  pNode = pTime->pNode;
  pIterEdge = pNode->pFirstOutEdge;

  if (pIterEdge)
    {
      minTime = MAX_TIME;
      while (pIterEdge)
	{
	  bFind = findItemInList(pLateTimeList, &pIterEdge->pTo, &lateTime, compareNode);
	  assert(bFind);
	  if (minTime > lateTime.time - pIterEdge->value)
	    minTime = lateTime.time - pIterEdge->value;
	  pIterEdge = pIterEdge->pNextSameFrom;
	}
    }
  else
    {
      minTime = pTime->time;
    }
  
  pTime->time = minTime;
}

static void printTime(void *pData)
{
  LP_TIME pTime = (LP_TIME)pData;

  printf("[%c, S %d] ", *(char *)pTime->pNode->pData, pTime->time);
}

static void copyToLate(void *pData)
{
  LP_TIME pTime = (LP_TIME)pData;
  
  insertToTail(pLateTimeList, pTime);
}

void criticalPath(LP_NODE pStartNode)
{
  LP_NODE pIterNode;
  unsigned int nodeNum;
  BOOL bNoCycle;
  LP_NODE pSource = NULL, pSink = NULL;

  nodeNum = 0;
  pIterNode = pStartNode;
  while (pIterNode)
    {
      nodeNum++;
      if (pIterNode->pFirstInEdge == NULL)
	{
	  if (pSource)
	    {
	      printf("Two Leader Node in Graph, cannot calculate Critical Path\n");
	      return;
	    }
	  else
	    {
	      pSource = pIterNode;
	    }
	}
      if (pIterNode->pFirstOutEdge == NULL)
	{
	  if (pSink)
	    {
	      printf("Two end Node in Graph, cannot calculate Critical Path\n");
	      return;
	    }
	  else
	    {
	      pSink = pIterNode;
	    }
	}

      pIterNode = pIterNode->pNextNode;
    }



  createSingleList(&pReverseTopoOrderList, sizeof(LP_NODE));
  createSingleList(&pEarlyTimeList, sizeof(TIME));
  createSingleList(&pLateTimeList, sizeof(TIME));
  
  bNoCycle = topoOrderTraverse(pStartNode, calculateEarlyAndRecordOrder);
  if (!bNoCycle)
    {
      printf("Cycle in Graph, Cannot calculate Critical path");
      destroySingleList(pLateTimeList);
      destroySingleList(pEarlyTimeList);
      destroySingleList(pReverseTopoOrderList);
      return;
    }

  printf("\nEarly Time:");
  listTraverse(pEarlyTimeList, printTime);
  // Init Late time as Early Time
  listTraverse(pEarlyTimeList, copyToLate);
  printf("\nInit Late Time:");
  listTraverse(pLateTimeList, printTime);
  
  listTraverse(pLateTimeList, updateLateTime);
  printf("\nFinal Late Time");
  listTraverse(pLateTimeList, printTime);

  destroySingleList(pLateTimeList);
  destroySingleList(pEarlyTimeList);
  destroySingleList(pReverseTopoOrderList);
}

typedef struct _DIST
{
  LP_NODE pNode;
  unsigned int distance;
}DIST, *LP_DIST;

typedef struct _PREV_NODE
{
  LP_NODE pNode;
  LP_NODE pPathPrevNode;
}PREV_NODE ,*LP_PREV_NODE;
void visitList(void *pData)
{
  LP_NODE pNode;
  memcpy(&pNode, pData, sizeof(LP_NODE));
  printf("%c", *(char *)pNode->pData);
}

void shortestPath(LP_NODE pStartNode)
{
  LP_NODE pIterNode;
  LP_NODE pSource;
  LP_EDGE pIterEdge;
  LP_SINGLE_LIST_NODE pDistList, pWorkList, pPrevNodeList, pIterListNode;
  DIST tempDist, minDist;
  PREV_NODE prevNode;
  BOOL bFind;
  LP_STACK pStack;

  
  createSingleList(&pDistList, sizeof(DIST));
  createSingleList(&pPrevNodeList, sizeof(PREV_NODE));
  createSingleList(&pWorkList, sizeof(LP_NODE));  

  pSource = pStartNode;
  pIterNode = pStartNode;
  while (pIterNode)
    {
      tempDist.pNode = pIterNode;
      tempDist.distance = (pIterNode == pSource)?0:MAX_TIME;
      insertToTail(pDistList, &tempDist);
      prevNode.pNode = pIterNode;
      prevNode.pPathPrevNode = NULL;
      insertToTail(pPrevNodeList, &prevNode);
     
      insertToTail(pWorkList, &pIterNode);
      pIterNode = pIterNode->pNextNode;
    }

  printf("\nWorkList is :");
  listTraverse(pWorkList, visitList);

  while (!isListEmpty(pWorkList))
    {
      // Find Node whose distance is minimal
      minDist.distance = MAX_TIME;
      minDist.pNode = NULL;

      pIterListNode = pWorkList->pNext;
      while (pIterListNode != NULL)
	{
	  memcpy(&pIterNode, pIterListNode->pData, sizeof(LP_NODE));
	  bFind = findItemInList(pDistList, &pIterNode, &tempDist, compareNode);
	  assert(bFind);
	  if (tempDist.distance < minDist.distance)
	    {
	      minDist.distance = tempDist.distance;
	      minDist.pNode = tempDist.pNode;
	    }
	  pIterListNode = pIterListNode->pNext;
	}
     
      if (minDist.pNode == NULL)
	{
	  printf ("some Node is unreachable in Graph\n");
	  break;
	}

      deleteItemFromList(pWorkList, &minDist.pNode, compareNode);
      pIterEdge = minDist.pNode->pFirstOutEdge;
      while (pIterEdge)
	{
	  bFind = findItemInList(pDistList, &pIterEdge->pTo, &tempDist, compareNode);
	  assert(bFind);
	  if (tempDist.distance > minDist.distance + pIterEdge->value)
	    {
	      tempDist.distance = minDist.distance + pIterEdge->value;
	      deleteItemFromList(pDistList, &pIterEdge->pTo, compareNode);
	      deleteItemFromList(pPrevNodeList, &pIterEdge->pTo, compareNode);
	      insertToHead(pDistList, &tempDist);
	      prevNode.pNode = pIterEdge->pTo;
	      prevNode.pPathPrevNode = minDist.pNode;
	      insertToHead(pPrevNodeList, &prevNode);
	    }

	  pIterEdge = pIterEdge->pNextSameFrom;
	}
    }

  if (isListEmpty(pWorkList))
    {
      // Calculate All path, print it out
      printf ("\nSucess\n");
      createStack(&pStack, sizeof(LP_NODE));
      pIterNode = pStartNode;
      while (pIterNode)
	{
	  printf("[NODE %c]:", *(char *)pIterNode->pData);

	  bFind = findItemInList(pDistList, &pIterNode, &tempDist, compareNode);
	  assert(bFind);
	  printf("shortest path length %d", tempDist.distance);
	  if (tempDist.distance)
	    {
	      LP_NODE pPathNode = pIterNode;
	      printf(" Path:[");
	      push(pStack, &pPathNode);
	      while (findItemInList(pPrevNodeList, &pPathNode, &prevNode, compareNode) && prevNode.pPathPrevNode)
		{
		  push(pStack, &prevNode.pPathPrevNode);
		  pPathNode = prevNode.pPathPrevNode;
		}
	      while (!isStackEmpty(pStack))
		{
		  pop(pStack, &pPathNode);
		  printf("%c", *(char *)pPathNode->pData);
		}
	      putchar(']');
	    }
	  putchar('\n');
	  pIterNode = pIterNode->pNextNode;
	}

      destroyStack(pStack);
    }


  destroySingleList(pPrevNodeList);
  destroySingleList(pWorkList);
  destroySingleList(pDistList);

}


void DFSforest(LP_NODE pStartNode, LP_DFS_TREE *ppDfsTreeRoot)
{

  LP_DFS_TREE pDfsRoot = NULL, pLastDfsRoot = NULL;
  LP_DFS_TREE pRoot, pChild;
  LP_NODE pIterNode;

  pIterNode = pStartNode;
  while (pIterNode)
    {
      pIterNode->bVisited = FALSE;
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
      pIterNode->bVisited = TRUE;
      pRoot = (LP_DFS_TREE)malloc(sizeof(DFS_TREE));
      if (NULL == pRoot)
	{
	  printf("Out Of Memory in Line %d, Function %s", __LINE__, __FUNCTION__);
	  exit(OVERFLOW);
	}

      pRoot->pNode = pIterNode;
      pRoot->pFirstChild = NULL;
      pRoot->pNextSibling = NULL;
      if (pDfsRoot == NULL)
	{
	  pDfsRoot = pLastDfsRoot = pRoot;
	}
      else
	{
	  pLastDfsRoot->pNextSibling = pRoot;
	  pLastDfsRoot = pRoot;
	}
      
      DFStree(pRoot);
      pIterNode = pIterNode->pNextNode;
    }

  *ppDfsTreeRoot = pDfsRoot;
}

static void DFStree(LP_DFS_TREE pRoot)
{
  LP_DFS_TREE pChild;
  LP_EDGE pIterEdge;
 
  pIterEdge = pRoot->pNode->pFirstOutEdge;

  while (pIterEdge)
    {
      if (pIterEdge->pTo->bVisited == FALSE)
	{
	  pChild = (LP_DFS_TREE)malloc(sizeof(DFS_TREE));
	  if (NULL == pChild)
	    {
	      printf("Out Of Memory in Line %d, Function %s", __LINE__, __FUNCTION__);
	      exit(OVERFLOW);
	    }

	  pChild->pNode = pIterEdge->pTo;
	  pChild->pFirstChild = NULL;
	  pChild->pNextSibling = NULL;
	  if (pRoot->pFirstChild == NULL)
	    {
	      pRoot->pFirstChild = pChild;
	    }
	  else
	    {
	      pChild->pNextSibling = pRoot->pFirstChild;
	      pRoot->pFirstChild = pChild;
	    }
	  pIterEdge->pTo->bVisited = TRUE;
	  DFStree(pChild);
	}
      
      pIterEdge = pIterEdge->pNextSameFrom;
    }
  
}

static void preOrderTraverseForest(LP_DFS_TREE pStartRoot)
{
  LP_STACK pStack;
  LP_DFS_TREE pIterTree;

  printf("\nTraverse DFS forest:");
  createStack(&pStack, sizeof(LP_DFS_TREE));
  pIterTree = pStartRoot;
  while (pIterTree)
    {
      push(pStack, &pIterTree);
      pIterTree = pIterTree->pNextSibling;
    }

  while (!isStackEmpty(pStack))
    {
      pop(pStack, &pIterTree);
      printf("%c", *(char *)pIterTree->pNode->pData);
      pIterTree = pIterTree->pFirstChild;
      while (pIterTree)
	{
	  push(pStack, &pIterTree);
	  pIterTree = pIterTree->pNextSibling;
	}
    }
  putchar('\n');
  destroyStack(pStack);

}


void freeDFStree(LP_DFS_TREE pStartRoot)
{
  LP_DFS_TREE pChild, pNext;
  
  pChild = pStartRoot->pFirstChild;

  while (pChild)
    {
      pNext = pChild->pNextSibling;
      freeDFStree(pChild);
      pChild = pNext;
    }
  free(pStartRoot);
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
