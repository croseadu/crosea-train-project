
#include "common.h"
#include "utils.h"
#include "memory.h"
#include "singleLinkList.h"
#include "set.h"
#include "stack.h"
#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


typedef char ElementType;
typedef int WeightType;

struct _Vertex;
struct _Edge;

typedef struct _Vertex
{
	ElementType data;
	struct _Edge *pFirstInEdge;
	struct _Edge *pFirstOutEdge;

}Vertex, *LPVertex;

typedef struct _Edge
{
	LPVertex pStartVertex;
	LPVertex pEndVertex;
	
	struct _Edge *pNextSameStartEdge;
	struct _Edge *pNextSameEndEdge;
	WeightType weight;

}Edge, *LPEdge;

typedef struct _Graph
{
	LPSingleLinkList pListOfVertices;	
	LPSingleLinkList pListOfEdges;
	
}Graph, *LPGraph;

BOOL
compareVertex(const void *lhs, const void *rhs)
{
	const LPVertex *pLeft = (LPVertex*)lhs;
	const LPVertex *pRight = (LPVertex*)rhs;

	return (*pLeft)->data < (*pRight)->data ? True : False;
}

BOOL
compareEdge(const void *lhs, const void *rhs)
{
	const LPEdge *pLeft = (const LPEdge *)lhs;
	const LPEdge *pRight = (const LPEdge *)rhs;

	
	if ((*pLeft)->pStartVertex->data != (*pRight)->pStartVertex->data)
		return (*pLeft)->pStartVertex->data < (*pRight)->pStartVertex->data ? True : False;
	return (*pLeft)->pEndVertex->data < (*pRight)->pEndVertex->data ? True : False;
}


LPVertex
getOrInsertVertex(LPGraph pGraph,
		  ElementType data)
{
	SingleLinkListIter it;
	LPVertex pVertex;

	pVertex = (LPVertex)myAlloc(sizeof(Vertex));
	assert(pVertex != NULL);

	pVertex->data = data;
	pVertex->pFirstInEdge = NULL;
	pVertex->pFirstOutEdge = NULL;

	it = findInSingleLinkList(pGraph->pListOfVertices, &pVertex);
	if (*it != NULL) {
		myFree(pVertex);
		pVertex = (LPVertex)(*it)->data;
		return pVertex;
	}

	insertToTailOfSingleLinkList(pGraph->pListOfVertices, &pVertex);

	return pVertex;
}



LPEdge
getOrInsertEdge(LPGraph pGraph,LPVertex pStart,LPVertex pEnd, WeightType weight)
{
	SingleLinkListIter it;
	LPEdge pNewEdge;

	pNewEdge = (LPEdge)myAlloc(sizeof(Edge));
	assert(pNewEdge != NULL);

	pNewEdge->pStartVertex = pStart;
	pNewEdge->pEndVertex = pEnd;
	pNewEdge->weight = weight;

	pNewEdge->pNextSameStartEdge = pStart->pFirstOutEdge;
	pNewEdge->pNextSameEndEdge = pEnd->pFirstInEdge;
	pStart->pFirstOutEdge = pNewEdge;
	pEnd->pFirstInEdge = pNewEdge;


	it = findInSingleLinkList(pGraph->pListOfEdges, &pNewEdge);
	if (*it != NULL) {
		myFree(pNewEdge);
		pNewEdge = (LPEdge)(*it)->data;
		return  pNewEdge;
	}
	insertToTailOfSingleLinkList(pGraph->pListOfEdges, &pNewEdge);

	return pNewEdge;
}

void depthFirstTraverse(LPGraph pGraph, Visitor visitor)
{
	LPStack pStack = NULL;
	LPSet pVisitedSet = NULL;

	LPSingleLinkListNode pIter = NULL;
	LPVertex pVertex = NULL;
	LPEdge pIterEdge = NULL;

	if (createStack(&pStack, 
			sizeof(LPVertex), 
			defaultPrinter) == False)
		goto lexit;



	pIter = pGraph->pListOfVertices->pHead;
	while (pIter != NULL) {
		pVertex = (LPVertex)pIter->data;
		pushToStack(pStack, pVertex);
		while (isStackEmpty(pStack) == False) {
			getTopFromStack(pStack, &pVertex);
			popFromStack(pStack);
			if (insertToSet(pVisitedSet, &pVertex)) {
				visitor(pVertex);
				pIterEdge = pVertex->pFirstOutEdge;
				while (pIterEdge) {
					pushToStack(pStack, pIterEdge->pEndVertex);
				}
			}
		
		}
		pIter = pIter->pNext;
	}
		
lexit:
	if (pStack != NULL)
		destroyStack(&pStack);
	if (pVisitedSet != NULL)
		destroySet(&pVisitedSet);
}
void breathFirstTraverse(LPGraph pGraph, Visitor visitor)
{
	LPQueue pQueue = NULL;

	LPSet pVisitedSet = NULL;
	LPSingleLinkListNode pIter = NULL;
	LPVertex pVertex = NULL;
	LPEdge pIterEdge = NULL;

	pIter = pGraph->pListOfVertices->pHead;
	while (pIter != NULL) {
		pVertex = (LPVertex)pIter->data;
		enQueue(pQueue, &pVertex);

		while (isQueueEmpty(pQueue) == False) {
			deQueue(pQueue, &pVertex);
			if (insertToSet(pVisitedSet, &pVertex)) {
				visitor(pVertex);
				pIterEdge = pVertex->pFirstOutEdge;
				while (pIterEdge) {
					enQueue(pQueue, &pIterEdge->pEndVertex);
				}
			}

		}
		pIter = pIter->pNext;
	}

lexit:
	if (pQueue != NULL)
		destroyQueue(&pQueue);
	if (pVisitedSet != NULL)
		destroySet(&pVisitedSet);
	
}


BOOL
createGraph(LPGraph *ppGraph)
{
	LPGraph pGraph;

	pGraph = (LPGraph)myAlloc(sizeof(Graph));
	if (NULL == pGraph)
		return False;
	if (False == createSingleLinkList(&pGraph->pListOfVertices,
					  sizeof(LPVertex),
					  defaultPrinter,
					  compareVertex)) {
		myFree(pGraph);
		return False;
	}
	if (False == createSingleLinkList(&pGraph->pListOfEdges,
					  sizeof(LPEdge),
					  defaultPrinter,
				          compareEdge)) {
		destroySingleLinkList(&pGraph->pListOfVertices);
		myFree(pGraph);
		return False;
	}
	
	*ppGraph = pGraph;
	return True;
}

void
printGraph(const LPGraph pGraph)
{
	LPSingleLinkListNode pIter;
	printf("\nGraph:\n");
	LPVertex pVertex;
	LPEdge pIterEdge;
	

	pIter = pGraph->pListOfVertices->pHead;
	while (NULL != pIter) {
		pVertex = *(LPVertex*)pIter->data;
		printf("V[%c]:", pVertex->data);

		pIterEdge = pVertex->pFirstOutEdge;
		while (NULL != pIterEdge) {
			printf(" (->%c) ", pIterEdge->pEndVertex->data);

			pIterEdge = pIterEdge->pNextSameStartEdge;
		}
		putchar('\n');

		pIter = pIter->pNext;
	}

}

void 
vertexPrinter(void *data)
{
	LPVertex pVertex = (LPVertex)data;
	printf(" %c ", pVertex->data);
}

BOOL
getNextEdge(
	char buf[], 
	int *pI, 
	ElementType *pFirstData, 
	ElementType *pSecondData,
	WeightType *pWeight)
{
	int i = *pI;

	if (buf[i] == '\0' || buf[i] == '\n')
		return False;
	if (buf[i] != '(')
		return False;

	++i;
	*pFirstData = buf[i];
	++i;
	if (buf[i] != ',')
		return False;
	
	++i;
	*pSecondData = buf[i];
	++i;
	
	if (buf[i] != ',')
		return False;
	++i;
	
	sscanf(buf+i, "%d", pWeight);
	while (isdigit(buf[i]))
		++i;
	if (buf[i] != ')')
		return False;

	++i;


	*pI = i;
	return True;
}


int main()
{
	LPGraph pGraph = NULL;
	FILE *fp = NULL;
	int i, fillIndex;
	ElementType firstData, secondData;
	WeightType weight;
	char buf[4096+1] = {'\0'};
	LPVertex pStart;
	LPVertex pEnd;
	LPEdge pEdge;


	fp = fopen("graph.txt", "r");
	if (fp == NULL)
		goto lexit;
	
	fgets(buf, 4096, fp);
	fclose(fp);

	fillIndex = 0;
	for (i = 0; i < 4096; ++i)
		if (buf[i] == ' ')
			continue;
		else {
			if (fillIndex != i)
				buf[fillIndex] = buf[i];
			++fillIndex;
		}
	buf[fillIndex] = '\0';

	i = 0;

	if (False == createGraph(&pGraph))
		goto lexit;	

	while (getNextEdge(buf, &i, &firstData, &secondData, &weight) == True) {
		pStart = getOrInsertVertex(pGraph, firstData);
		pEnd = getOrInsertVertex(pGraph, secondData);
		pEdge = getOrInsertEdge(pGraph, pStart, pEnd, weight);	
	}	
	
	printGraph(pGraph);

	printf("\n Depth First: ");
	depthFirstTraverse(pGraph, vertexPrinter);
	printf("\n Breath First: ");
	breathFirstTraverse(pGraph, vertexPrinter);	
lexit:

	return 0;
}
