#include <stdio.h>
#include <stdlib.h>
#include "../include/set.h"
#include "../include/map.h"
#include "../include/stack.h"
#include "../include/queue.h"
#include "../include/mytype.h"

typedef char ElementType;

struct _EDGE;

typedef struct _NODE
{
  ElementType data;
  struct _EDGE *firstIn;
  struct _EDGE *firstOut;

  struct _NODE *pNextNode;
}Node, *LPNode;

typedef struct _EDGE
{
  LPNode from;
  LPNode to;
  unsigned int weight;
  struct _EDGE *pNextSameFrom;
  struct _EDGE *pNextSameTo;
  
  struct _EDGE *pNextEdge;
}Edge, *LPEdge;

typedef struct _DGraph
{
  LPNode pFirstNode;
  LPEdge pFirstEdge;

}DGraph, *LPDGraph;


bool initGraph(LPDGraph *ppGraph)
{
  LPDGraph pGraph;

  pGraph = (LPDGraph)malloc(sizeof(DGraph));
  if (NULL == pGraph) {
    printf ("Out Of Memory in %s", __func__);
    return false;
  }

  pGraph->pFirstNode = NULL;
  pGraph->pFirstEdge = NULL;
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

  /*
  if (**pp != ',')
    return false;
  ++*pp;
  skipSpace(pp);
  
  sscanf(*pp, "%d", &pTok->weight);
  while(isdigit(**pp))
    ++*pp;
  skipSpace(pp);
  */

  if (**pp != ')')
    return false;
  ++*pp;
  return true;
}

void createGraph(LPDGraph pGraph, const char *p)
{
  const char *p2 = p;
  Tok token;
  LPNode pFrom, pTo;

  while (getNextToken(&token, &p2)) {
    pFrom = getOrInsertNode (pGraph, token.first);
    pTo = getOrInsertNode (pGraph, token.second, 0);
    addEdgeToGraph(pGraph, pFrom, pTo);
  }
}

void destroyGraph(LPDGraph *ppGraph)
{
  LPDGraph pGraph;
  LPNode pIterNode, pNextNode;
  LPEdge pIterEdge, pNextEdge

  if (NULL == ppGraph || NULL == *ppGraph)
    return;
  
  pGraph = *ppGraph;
  pIterNode = pGraph->pFirstNode;
  while (pIterNode) {
    pNextNode = pIterNode->pNextNode;
    free(pIterNode);
    pIterNode = pNextNode;
  }
  pIterEdge = pGraph->pFirstEdge;
  while (pIterEdge) {
    pNextEdge = pIterEdge->pNextEdge;
    free (pIterEdge);
    pIterEdge = pNextEdge;
  }
  *ppGraph = NULL;
}

LPNode getOrInsertNode(LPDGraph pGraph, ElementType key)
{
  LPNode *ppNode = &pGraph->pFirstNode;
  LPNode pNewNode;
  while (*ppNode != NULL) {
    if ((*ppNode)->data == key)
      return *ppNode;
    ppNode = &(*ppNode)->pNextNode;
  }
  
  pNewNode = (LPNode)malloc(sizeof(Node));
  if (NULL == pNewNode) {
    printf ("Out Of Memory in %s", __func__);
    return NULL;
  }
  
  pNewNode->data = key;
  pNewNode->pFirstInEdge = NULL;
  pNewNode->pFirstOutEdge = NULL;
  pNewNode->pNextNode = NULL;
  *ppNode = pNewNode;
  return pNewNode;
}

bool addEdge(LPDGraph pGraph, LPNode from, LPNode to, unsigned int weight)
{
  LPEdge pNewEdge;

  pNewEdge = (LPEdge)malloc(sizeof(Edge));
  if (NULL == pEdge) {
    printf ("Out Of Memory in %s", __func__);
    return false;
  }
  
  pNewEdge->from = from;
  pNewEdge->to = to;
  pNewEdge->pNextSameFrom = from->pFirstOutEdge;
  from->pFirstOutEdge = pNewEdge;
  pNewEdge->pNextSameTo = to->pFirstInEdge;
  to->pFirstInEdge = pNewEdge;

  pNewEdge->pNextEdge = pGraph->pFirstEdge;
  pGraph->pFirstEdge = pNewEdge;
  return true;
}

void nodePrint(void *key)
{
  LPNode pNode;

  pNode = *(LPNode *)key;
  printf(" V[%c] ", pNode->data);
}

bool nodeEq(void * lhs, void *rhs)
{
  LPNode pLeft, pRight;
  pLeft = *(LPNode *)lhs;
  pRight = *(LPNode *)rhs;
  return pLeft == pRight;
}

void DFS(LPDGraph pGraph)
{
  LPSet pSet;
  LPNode pIterNode;

  initSet(&pSet, sizeof(LPNode), nodePrint,  nodeEq);
  pIterNode = pGraph->pFirstNode;
  while (pIterNode) {
    if (countInSet(pSet, &pIterNode)) {
      pIterNode = pIterNode->pNextNode;
      continue;
    }
 
    DFSTraverse(pNode, nodePrint, pSet);
    pIterNode = pIterNode->pNextNode;
  }

  destroySet(&pSet);
}

void DFSTraverse(LPNode pNode, VisitFunc visitor, LPSet pVisitedFlag)
{
  LPEdge pEdge;

  visitor(&pNode->data);
  insertToSet(pVisitedFlag, &pNode);

  pEdge = pNode->pFirstOutEdge;
  while (pEdge) {
    if (!countInSet(pVisitedFlag, &pEdge->to))
      DFSTraverse(pEdge->to, visitor, pVisitedFlag);
    pEdge = pEdge->pNextSameFrom;
  }
}

void BFS(LPDGraph pGraph)
{
  LPNode pNode, pVisitNode;
  LPEdge pEdge;
  LPQueue pQueue;

  pNode = pGraph->pFirstNode;
  initQueue(&pQueue, sizeof(LPNode));
  initSet(&pSet, sizeof(LPNode), nodePrint,  nodeEq);

  while (!isQueueEmpty(pQueue) || pNode) {
    if (!isQueueEmpty(pQueue)) { 
      deQueue(pQueue, &pVisitNode);
      nodePrint(&pVisitNode);
      pEdge = pVisitNode->pFirstOutEdge;
      while (pEdge) {
	if (!countInSet(pSet, &pEdge->pTo)) {
	  enQueue(pQueue, &pEdge->pTo);
	  insertToSet(pSet, &pEdge->pTo);
	}
	pEdge = pEdge->pNextSameFrom;
      }
    }
    else {
      if (!countInSet(pNode)) {
	enQueue(pQueue, &pNode);
	insertToSet(pSet, &pNode);
      }
      pNode = pNode->pNextNode;
    }
  }

  destroySet(&pSet);
  destroyQueue(&pQueue);
} 

void DFSTraverse_SCC(LPNode pNode, 
		     VisitFunc visitor, 
		     LPSet pVisitedFlag,
		     LPStack pQuitOrder)
{
  LPEdge pEdge;

  visitor(&pNode->data);
  insertToSet(pVisitedFlag, &pNode);

  pEdge = pNode->pFirstOutEdge;
  while (pEdge) {
    if (!countInSet(pVisitedFlag, &pEdge->to))
      DFSTraverse(pEdge->to, visitor, pVisitedFlag);
    pEdge = pEdge->pNextSameFrom;
  }
  push(pQuitOrder, &pNode);
}
void nullFunc(void *)
{
}

void DFS_SCC(LPDGraph pGraph, LPStack pStack)
{
  LPSet pSet;
  LPNode pIterNode;

  initSet(&pSet, sizeof(LPNode), nodePrint,  nodeEq);
  pIterNode = pGraph->pFirstNode;
  while (pIterNode) {
    if (countInSet(pSet, &pIterNode)) {
      pIterNode = pIterNode->pNextNode;
      continue;
    }
 
    DFSTraverse_SCC(pNode, nullFunc, pSet, pStack);
    pIterNode = pIterNode->pNextNode;
  }

  destroySet(&pSet);
}

void DFSReverseTraverse_SCC(LPNode pNode, 
		     VisitFunc visitor, 
		     LPSet pVisitedFlag,
		     LPStack pQuitOrder)
{
  LPEdge pEdge;

  visitor(&pNode->data);
  insertToSet(pVisitedFlag, &pNode);

  pEdge = pNode->pFirstOutEdge;
  while (pEdge) {
    if (!countInSet(pVisitedFlag, &pEdge->to))
      DFSTraverse(pEdge->to, visitor, pVisitedFlag);
    pEdge = pEdge->pNextSameFrom;
  }
  push(pQuitOrder, &pNode);
}


void findScc(LPGraph pGraph)
{
  LPSet pVisitSet, pSCCSet;
  LPNode pIterNode, pSCCNode;
  LPStack pSCCStack, pQuitStack;

  initSet(&pVisitSet, sizeof(LPNode), nodePrint,  nodeEq);
  initSet(&pSCCSet, sizeof(LPNode), nodePrint,  nodeEq);
  initStack(&pSCCStack, sizeof(LPNode));
  initStack(&pQuitStack, sizeof(LPNode));

  DFS_SCC(pGraph, pQuitStack);

  while (!isStackEmpty(pQuitStack)) {
    pop(pQuitStack, &pIterNode);
    if (countInSet(pSCCSet, &pIterNode)) {
      continue;
    }

    clearSet(pVisitSet);
    DFSReverseTraverse_SCC(pNode, nullFunc, pVisitSet, pSCCStack);


    printf ("\nFind a New SCC:");
    clearSet(pSCCSet);
    while (!isStackEmpty(pSCCStack)) {
      pop(pStack, &pSCCNode);
      nodePrint(&pSCCNode);
      insertToSet(pSCCSet, &pSCCNode);
    }
    putchar('\n');

  }

  destroyStack(&pSCCStack);
  destroyStack(&pQuitStack);
  destroySet(&pVisitSet);
  destroySet(&pSCCSet);
}


void strongConnectedComponent(LPNode pNode, LPStack pStack, LPMap pIndexMap,
			      LPMap pLowLinkMap, int *pIndex)
{
  int index = *pIndex;
  int lowLink = index;
  LPEdge pIterEdge;
  LPNode pToNode, pSCCNode;
  int toIndex;
  int toLowLink;

  ++*pIndex;

  insertEntry(pIndexMap, &pNode, &index);
  insertEntry(pLowLinkMap, &pNode, &lowLink);
  push(pStack, &pNode);

  pIterEdge = pNode->pFirstOutEdge;
  while (pIterEdge) {
    pToNode = pIterEdge->pTo;
    
    if (false == findValueViaKey(pIndexMap, &pToNode, &toIndex)) {
      strongConnectedComponent(pToNode, pStack, pIndexMap, pLowLinkMap, pIndex);
      findValueViaKey(pLowLinkMap, &pToNode, &toLowLink);
      if (lowLink > toLowLink) {
	lowLink = toLowLink;
	insertOrModifyEntry(pLowLinkMap, &pNode, &lowLink);
      }
    }
    else {
      if (lowLink > toIndex) {
	lowLink = toIndex;
	insertOrModifyEntry(pLowLinkMap, &pNode, &lowLink);
      }
    }
    pIterEdge = pIterEdge->pNextSameFrom;
  }

  if (index == lowLink) {
    // Start a new SCC.
    printf ("Find a new SCC\n");
    do {
      pop(pStack, &pSCCNode);
      nodePrint(&pSCCNode);
    } while (pSCCNode != pNode)
  }
}

//Tarjan's Algorithm
void findSccV2(LPDGraph pGraph)
{
  int index, curIndex;
  LPStack pStack;
  LPNode pIterNode;
  LPMap pIndexMap, pLowLinkMap;

  initStack(&pStack, sizeof(LPNode));
  initMap(&pIndexMap, sizeof(LPNode), sizeof(int),
	  keyEq, keyPrint, valPrint);
  initMap(&pLowLinkMap, sizeof(LPNode), sizeof(int),
	  keyEq, keyPrint, valPrint);

  index = 0;
  pIterNode = pGraph->pFirstNode;
  while (pIterNode) {
    
    if (false == findValueViaKey(pIndexMap, &pIterNode, &curIndex)) {
      strongConnectedComponent(pIterNode, pStack, pIndexMap, 
			       pLowLinkMap, &index);
    }
    pIterNode = pIterNode->pNextNode;
  }
  


  destroyMap(&pIndexMap);
  destroyMap(&pLowLinkMap);
  destroyStack(&pStack);
}

void pathBasedSCC(LPNode pNode, LPMap pIndexMap, LPStack pStack_S, 
		  LPStack pStack_P, int *pIndex)
{
  int index = *pIndex, tempIndex;
  LPEdge pIterEdge;
  LPNode pToNode, pTempNode;
  int toIndex;

  ++*pIndex;
  push(pStack_S, &pNode);
  push(pStack_P, &pNode);
  insertEntry(pIndexMap, &pNode, &index);
  
  pIterEdge = pNode->pFirstOutEdge;
  while (pIterEdge) {
    pToNode = pIterEdge->pTo;
    if (false == findValueViaKey(pIndexMap, &pToNode, &toIndex)) {
      pathBasedSCC(pToNode, pIndexMap, pStack_S, pStack_P, pIndex);
    }
    else {
      getTop(pStack_P, &pTempNode);
      findValueViaKey(pIndexMap, &pTempNode, &tempIndex);
      while (tempIndex > toIndex) {
	pop (pStack_P, &pTempNode);
	getTop(pStack_P, &pTempNode);
	findValueViaKey(pIndexMap, &pTempNode, &tempIndex);
      }
    }
    pIterEdge = pIterEdge->pNextSameFrom;
  }  
  
  getTop(pStack_P, &pTempNode);
  if (pTempNode == pNode) {
    pop(pStack_P, &pTempNode);
    printf ("Find a new SCC\n");
    do {
      pop(pStack_S, &pTempNode);
      nodePrint(&pTempNode);
    }while (pTempNode != pNode);
  }
}

void findSccV3(LPDGraph pGraph)
{
  int index = 0, tIndex;
  LPStack pStack_S, pStack_P;
  LPNode pIterNode;
  LPMap pIndexMap;

  initStack(&pStack_S, sizeof(LPNode));
  initStack(&pStack_P, sizeof(LPNode));
  initMap(&pIndexMap, sizeof(LPNode), sizeof(int),
	  keyEq, keyPrint, valPrint);

  pIterNode = pGraph->pFirstNode;
  while (pIterNode) {
    if (false == findValueViaKey(pIndexMap, &pIterNode, &tIndex)) {
      pathBasedSCC(pIterNode, pIndexMap, pStack_S, pStack_P, &index);
    }
    pIterNode = pIterNode->pNextNode;
  }


  destroyMap(&pIndexMap);
  destroyStack(&pStack_P);
  destroyStack(&pStack_S);
}

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
  printf(" V[%c] ", pNode->data);
}

void valPrint(void *val)
{
  int degree;
  degree = *(int *)val;
  printf(" %d ", degree);
}
void topoOrderSort(LPGraph pGraph)
{
  LPStack pStack;
  LPSet pSet;
  LPNode pNode, pSucc;
  LPEdge pEdge;
  int nodeNum;

  initStack(&pStack, sizeof(LPNode));
  initMap(&pMap, sizeof(LPNode),
	  sizeof(int), keyEq,
	  keyPrint, valPrint);

  pNode = pGraph->pFirstNode;
  nodeNum = 0;
  while (pNode) {
    degree = calcDegree(pNode);
    insertEntry(pMap, &pNode &degree);
    if (degree == 0) {
      push(pStack, &pNode);
    }
    ++nodeNum;
    pNode = pNode->pNextNode;
  }

  while (!isStackEmpty(pStack)) {
    pop(pStack, &pNode);
    printf(" V[%c] ", pNode->data);
    --nodeNum;
    pEdge = pNode->pFirstOut;
    while (pEdge) {
      pSucc = pEdge->pTo;
      findValueViaKey(pMap, &pSucc, &degree);
      --degree;
      insertOrModifyEntry(pMap, &pSucc, &degree);
      if (degree == 0)
	push (pStack, &pSucc);
    }
  }

  if (nodeNum > 0) {
    printf ("Topo Order Sort failed because a cycle in Graph\n");
  }
  
  destroyMap(&pMap);
  destroyStack(&pStack);
}

void criticalPath()
{

}

int main()
{
  char buf[] = "";
  LPDGraph pGraph;

  initGraph(&pGraph);
  createGraph(pGraph, buf);
  DFS(pGraph);
  BFS(pGraph);
  topoOrderSort(pGraph);
  findScc(pGraph);
  findSccV2(pGraph);
  findSccV3(pGraph);

  destroyGraph(&pGraph);

  return 0;
}




