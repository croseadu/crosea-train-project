// get a forest for all spanning tree
//7.3

#include "../include/mytype.h"
#include "../include/set.h"
#include "../include/stack.h"
#include "../include/queue.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define ElementType char
#define NodeType LPVertex


typedef struct _Tok
{
  ElementType first;
  ElementType second;
  unsigned int weight;
}Tok, *LPTok;

// For Graph
struct _Edge;
typedef struct _Vertex
{
  ElementType data;
  struct _Edge *pFirstEdge;

  // This is not real graph node member, only used
  // to keep all vertex linked together.
  struct _Vertex *pNextVertex;
}Vertex, *LPVertex;
typedef struct _Edge
{
  // in undirected Graph, no from or to.
  LPVertex pFrom;
  LPVertex pTo;
  unsigned int weight;
  
  struct _Edge *pNextFrom;
  struct _Edge *pNextTo;


  // This is not real graph edge member, only used
  // to keep all vertex linked together.
  struct _Edge *pNextEdge;
}Edge, *LPEdge;

typedef struct _Graph
{
  LPVertex pVertexSet;
  LPEdge pEdgeSet;
  unsigned int count;
}Graph, *LPGraph;

// For Spanning Tree

typedef struct _Node
{
  NodeType data;
  struct _Node *pFirstChild;
  struct _Node *pNextSibling;
}Node, *LPNode;


void vertexPrint(void *key)
{
  LPVertex pNode;

  pNode = *(LPVertex *)key;
  printf(" V[%c] ", pNode->data);
}

bool vertexEq(void * lhs, void *rhs)
{
  LPVertex pLeft, pRight;
  pLeft = *(LPVertex *)lhs;
  pRight = *(LPVertex *)rhs;
  return pLeft == pRight;
}

void skipSpace(const char **pp)
{
  while(**pp == ' ')
    ++*pp;
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

  if (**pp != ',')
    return false;
  ++*pp;
  skipSpace(pp);

  sscanf(*pp, "%d", &pTok->weight);
  while(isdigit(**pp))
    ++*pp;
  skipSpace(pp);

  if (**pp != ')')
    return false;
  ++*pp;
  return true;
}

LPNode DFSForest(LPGraph pGraph);
void DFSTree(LPGraph pGraph, LPSet , LPVertex , LPNode );

LPNode BFSForest(LPGraph pGraph);


bool initGraph(LPGraph *ppGraph)
{
  LPGraph pGraph;

  pGraph = (LPGraph)malloc(sizeof(Graph));
  if (NULL == pGraph) {
    printf ("Out Of Memory in %s", __func__);
    return false;
  }
  pGraph->pVertexSet = NULL;
  pGraph->pEdgeSet = NULL;
  pGraph->count = 0;
  *ppGraph = pGraph;
  return true;
}

LPVertex getOrInsertVertex(LPGraph pGraph, ElementType key)
{
  LPVertex *ppIter, pVertex;
  ppIter = &pGraph->pVertexSet;
  while(*ppIter && (*ppIter)->data != key)
    ppIter = &(*ppIter)->pNextVertex;
  if (NULL != *ppIter)
    return *ppIter;
  
  pVertex = (LPVertex)malloc(sizeof(Vertex));
  if (NULL == pVertex) {
    printf ("Out Of Memory in %s", __func__);
    return NULL;
  }

  pVertex->data = key;
  pVertex->pFirstEdge = NULL;
  pVertex->pNextVertex = NULL;

  *ppIter = pVertex;
  ++pGraph->count;
  return pVertex;
}

bool addEdgeToGraph(LPGraph pGraph, LPVertex pFrom, LPVertex pTo, unsigned int weight)
{
  LPEdge pEdge, pIterEdge;
  
  pEdge = (LPEdge)malloc(sizeof(Edge));
  if (NULL == pEdge) {
    printf ("OUt Of Memory in %s", __func__);
    return false;
  }

  pEdge->pFrom = pFrom;
  pEdge->pTo = pTo;
  pEdge->pNextFrom = pFrom->pFirstEdge;
  pFrom->pFirstEdge = pEdge;

  pEdge->pNextTo = pTo->pFirstEdge;
  pTo->pFirstEdge = pEdge;
  pEdge->pNextEdge = NULL;
  pEdge->weight = weight;

  if (pGraph->pEdgeSet == NULL)
    pGraph->pEdgeSet = pEdge;
  else {
    pIterEdge = pGraph->pEdgeSet;
    while (pIterEdge->pNextEdge)
      pIterEdge = pIterEdge->pNextEdge;
    pIterEdge->pNextEdge = pEdge;
  }
  return true;
}

void createGraph(LPGraph pGraph, const char *p)
{
  const char *p2 = p;
  LPVertex pLhs, pRhs;
  Tok token;

  while(getNextToken(&token, &p2)) {
    pLhs = getOrInsertVertex(pGraph, token.first);
    pRhs = getOrInsertVertex(pGraph, token.second);
    addEdgeToGraph(pGraph, pLhs, pRhs, token.weight);
  }
}

void destroyGraph(LPGraph *ppGraph)
{
  LPVertex pIterVertex, pNextVertex;
  LPEdge pIterEdge, pNextEdge;

  pIterVertex = (*ppGraph)->pVertexSet;
  while (pIterVertex) {
    pNextVertex = pIterVertex->pNextVertex;
    free (pIterVertex);
    pIterVertex = pNextVertex;
  }

  pIterEdge = (*ppGraph)->pEdgeSet;
  while (pIterEdge) {
    pNextEdge = pIterEdge->pNextEdge;
    free (pIterEdge);
    pIterEdge = pNextEdge;
  }
  free (*ppGraph);
  *ppGraph = NULL;
}



void destroySpanningTree(LPNode pRoot)
{
  LPStack pStack;
  LPNode pCurNode;

  initStack(&pStack, sizeof(LPNode));
  push(pStack, &pRoot);

  while (!isStackEmpty(pStack)) {
    pop(pStack, &pCurNode);
    if (pCurNode->pNextSibling)
      push(pStack, &pCurNode->pNextSibling);
    if (pCurNode->pFirstChild)
      push(pStack, &pCurNode->pFirstChild);
    free(pCurNode);
  }
  

  destroyStack(&pStack);
}

void preOrder(LPNode pRoot)
{
  vertexPrint(&pRoot->data);
  if (pRoot->pFirstChild)
    preOrder(pRoot->pFirstChild);
  if (pRoot->pNextSibling)
    preOrder(pRoot->pNextSibling);
}

void inOrder(LPNode pRoot)
{
  if (pRoot->pFirstChild)
    inOrder(pRoot->pFirstChild);
  vertexPrint(&pRoot->data);
  if (pRoot->pNextSibling)
    inOrder(pRoot->pNextSibling);
}


int main()
{
  char buf[] = "(1,3, 0) (1,2, 0) (2,5, 0) (2,4, 0) (4,8, 0) (5,8, 0) (3,7, 0) (3,6, 0) (6,7, 0)";
  char *p = buf;

  LPGraph pGraph;
  LPNode pRootNode;

  printf ("Init Graph:\n");
  initGraph(&pGraph);
  printf ("Create Graph: \n");
  createGraph(pGraph, p);
  
  printf("\nDFSForest: ");
  pRootNode = DFSForest(pGraph);
  printf("\nPreOrder: \n");
  preOrder(pRootNode);
  printf("\nPostOrder: \n");
  inOrder(pRootNode);
  printf ("\nDestroySpanning Tree:\n");
  destroySpanningTree(pRootNode);

  printf("\nBFSForest: ");
  pRootNode = BFSForest(pGraph);
  printf("\nPreOrder: \n");
  preOrder(pRootNode);
  printf("\nPostOrder: \n");
  inOrder(pRootNode);
  printf ("\nDestroySpanning Tree:\n");

  printf ("\nDestroy Graph:\n");
  destroyGraph(&pGraph);

  return 0;
}



LPNode DFSForest(LPGraph pGraph)
{
  LPSet pVisitedSet;
  LPVertex pIterVertex = pGraph->pVertexSet;
  LPNode pRoot = NULL, pBrother;
  LPNode pCurNode;

  initSet(&pVisitedSet, sizeof(LPVertex), vertexPrint, vertexEq);
  while (pIterVertex) {
    if (!countInSet(pVisitedSet, &pIterVertex)) {
      insertToSet(pVisitedSet, &pIterVertex);
      pCurNode = (LPNode)malloc(sizeof(Node));
      pCurNode->data = pIterVertex;
      pCurNode->pFirstChild = NULL;
      pCurNode->pNextSibling = NULL;
      if (NULL == pRoot) {
	pRoot = pCurNode;
	pBrother = pCurNode;
      }
      else {
	pBrother->pNextSibling = pCurNode;
	pBrother = pCurNode;
      }
      DFSTree(pGraph, pVisitedSet, pIterVertex, pCurNode);

    }
    pIterVertex = pIterVertex->pNextVertex;
  }
  
  

  destroySet(&pVisitedSet);
  return pRoot;
}

void DFSTree(LPGraph pGraph, LPSet pVisitedFlag, LPVertex pCurVertex, LPNode pCurNode)
{
  LPEdge pIterEdge = pCurVertex->pFirstEdge;
  LPEdge pNextEdge;
  LPVertex pAdjVertex;
  LPNode pNewNode, pBrother = NULL;
  
  printf("\nDFSTree: ");
  vertexPrint(&pCurVertex);
  while (pIterEdge) {
    if (pIterEdge->pFrom == pCurVertex) {
      pAdjVertex = pIterEdge->pTo;
      pNextEdge = pIterEdge->pNextFrom;
    }
    else {
      assert (pIterEdge->pTo == pCurVertex);
      pAdjVertex = pIterEdge->pFrom;
      pNextEdge = pIterEdge->pNextTo;
    }

    if (!countInSet(pVisitedFlag, &pAdjVertex)) {
      insertToSet(pVisitedFlag, &pAdjVertex);
      pNewNode = (LPNode)malloc(sizeof(Node));
      if (NULL == pNewNode) {
	printf ("Out Of Memory in %s", __func__);
	return;
      }
      pNewNode->data = pAdjVertex;
      pNewNode->pFirstChild = NULL;
      pNewNode->pNextSibling = NULL;
      if (pCurNode->pFirstChild == NULL) {
	pCurNode->pFirstChild = pNewNode;
	pBrother = pNewNode;
      }
      else {
	pBrother->pNextSibling = pNewNode;
	pBrother = pNewNode;
      }
      DFSTree(pGraph, pVisitedFlag, pAdjVertex, pNewNode);

    }
    pIterEdge = pNextEdge;  
  }

}

LPNode findNode(LPNode pRoot, LPVertex pVertex)
{
  LPStack pStack;
  LPNode pFind;
  LPVertex pIterVertex;
  LPEdge pIterEdge;

  initStack(&pStack, sizeof(LPNode));
  push(pStack, &pRoot);
  while (!isStackEmpty(pStack)) {
    pop(pStack, &pFind);
    if (pFind->data == pVertex)
      return pFind;

    if (pFind->pFirstChild)
      push(pStack, &pFind->pFirstChild);
    if (pFind->pNextSibling)
      push(pStack, &pFind->pNextSibling);
  }

  destroyStack(&pStack);
  return NULL;
}
LPNode getNode(LPVertex pVertex)
{
  LPNode pNew;

  pNew = (LPNode)malloc(sizeof(Node));
  if (NULL == pNew) {
    printf ("Out Of Memory in %s", __func__);
    return NULL;
  }

  pNew->data = pVertex;
  pNew->pFirstChild = NULL;
  pNew->pNextSibling = NULL;
  return pNew;
}
void addTreeEdge(LPNode pFather, LPNode pChild)
{
  LPNode *ppPos;
  if (pFather->pFirstChild == NULL)
    pFather->pFirstChild = pChild;
  else {
    ppPos = &pFather->pFirstChild;
    while (*ppPos != NULL)
      ppPos = &((*ppPos)->pNextSibling);
    *ppPos = pChild;
  }
}

LPNode BFSForest(LPGraph pGraph)
{
  LPNode pRoot, pBrother;
  LPNode pCurNode, pFatherNode, pSubNode;
  LPSet pVisited;
  LPVertex pIterVertex = pGraph->pVertexSet;
  LPVertex pCurVertex;
  LPVertex pSubVertex;
  LPQueue pQueue;
  LPEdge pIterEdge, pNextEdge;

  initSet(&pVisited, sizeof(LPVertex), vertexPrint, vertexEq);
  initQueue(&pQueue, sizeof(LPVertex));

  while (pIterVertex) {
    if (!countInSet(pVisited, &pIterVertex)) {
      insertToSet(pVisited, &pIterVertex);
      enQueue(pQueue, &pIterVertex);
      pCurNode = getNode(pIterVertex);
      if (pRoot == NULL) {
	pRoot = pCurNode;
	pBrother = pCurNode;
      }
      else {
	pBrother->pNextSibling = pCurNode;
	pBrother = pCurNode;
      }

      while (!isQueueEmpty(pQueue)) {
	deQueue(pQueue, &pCurVertex);
	
	pIterEdge = pCurVertex->pFirstEdge;
	while (pIterEdge) {
	  // Link (i, j)
	  pFatherNode = findNode(pRoot, pCurVertex);
	  if (pIterEdge->pFrom == pCurVertex) {
	    pSubVertex = pIterEdge->pTo;
	    pNextEdge = pIterEdge->pNextFrom;
	  }
	  else {
	    assert (pIterEdge->pTo == pCurVertex);
	    pSubVertex = pIterEdge->pFrom;
	    pNextEdge = pIterEdge->pNextTo;
	  }
	  if (!countInSet(pVisited, &pSubVertex)) {
	    insertToSet(pVisited, &pSubVertex);
	    pSubNode = getNode(pSubVertex);
	    addTreeEdge(pFatherNode, pSubNode);
	    enQueue(pQueue, &pSubVertex);
	  }
	  pIterEdge = pNextEdge;
	}
      }

    }

    pIterVertex = pIterVertex->pNextVertex;
  }


  destroyQueue(&pQueue);
  destroySet(&pVisited);
  return pRoot;
}

