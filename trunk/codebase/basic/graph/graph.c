#include "../../include/my.h"
#include "../../include/util.h"
#include "../../include/queue.h"
#include "../../include/stack.h"
#include "../../include/list.h"

struct _EDGE;
typedef struct _NODE
{
	char data;
	struct _EDGE *pFirstEdgeIn;
	struct _EDGE *pFirstEdgeOut;

	/************link all node**************/
	struct _NODE *pNextNode;
	BOOL bVisited;
}NODE, *LP_NODE;

typedef struct _EDGE
{
	NODE *pFrom;
	NODE *pTo;
	struct _EDGE *pNextSameFrom;
	struct _EDGE *pNextSameTo;

	/************link all edge**************/
	struct _EDGE *pNextEdge;
}EDGE, *LP_EDGE;

enum RESULT
{
	R_END = 0,
	R_ERROR = 1,
	R_NOTCOMPLETED = 2,
	R_SUCCESS = 3,
};

typedef struct _DEGREE
{
	LP_NODE pGraphNode;
	int degree;	
}DEGREE, *LP_DEGREE;

void visit(LP_NODE pVisitNode, int *pIndex);
LP_NODE createNode(LP_NODE *ppStartNode, char data);
LP_EDGE createEdge(LP_EDGE *ppStartEdge, NODE *pFrom, NODE *pTo);
void printGraph(LP_NODE pStartNode);
NODE * findNode(LP_NODE pStartNode, char data);
enum RESULT getNextEdge(char *buf, int *pCurIndex, char *from, char *to);
void widthTraverse(LP_NODE pStartNode, void (*fn)(LP_NODE, int *), int *pCurIndex, LP_QUEUE pQueue);
void depthTraverse(LP_NODE pStartNode, void (*fn)(LP_NODE, int *), int *pCurIndex, LP_STACK pStack);
void findZeroDegreeNode(void *pData, void *pArg);
void topologySortGraph(LP_NODE pStartNode);
int main()
{
	FILE *fp;
	char buf[1024];
	char from, to;
	int readCount;
	int curIndex, numOfNodes;
	int offset = 0;
	
	LP_QUEUE pQueue = NULL;
	LP_STACK pStack = NULL;
	LP_NODE pStartNode = NULL, pFromNode, pToNode, pIterNode;
	LP_EDGE pStartEdge = NULL, pNewEdge, pIterEdge;
	enum RESULT status;

	if ((fp = fopen("f:\\temp.txt", "rt+")) == NULL)
	{
		Print(("Failed when open file\n"));
		exit(-1);
	}

	if (fp < 0)
		return -1;

	memset(buf, 0 ,1024);

	while (!feof(fp))
	{
		if(NULL == fgets(buf+offset, 100, fp))
			break;
		printf("\nInput is %s\n", buf);

		curIndex = 0;
		while (buf[curIndex] == '\t' 
			   || buf[curIndex] == ' ')
			   curIndex++;
	
		if (buf[curIndex] == 0)
		{
			if (offset)
				Print(("impossible"));
			memset(buf, 0, curIndex);
			continue;

		}
		while((status = getNextEdge(buf, &curIndex, &from, & to)) == R_SUCCESS)
		{
			if (NULL == (pFromNode = findNode(pStartNode, from)))
			{
				pFromNode = createNode(&pStartNode, from);
			}
			if (NULL ==(pToNode =findNode(pStartNode, to)))
			{
				pToNode = createNode(&pStartNode, to);
			}

			if (!pFromNode || !pToNode)
			{
				Print(("Out of memory when create new node\n"));
			}

			pIterEdge = pFromNode->pFirstEdgeOut;
			while(pIterEdge)
			{
				if (pIterEdge->pTo == pToNode)
					break;
				pIterEdge = pIterEdge->pNextSameFrom;
			}
			
			if(pIterEdge)
				pNewEdge = pIterEdge;
			else
				pNewEdge = createEdge(&pStartEdge, pFromNode, pToNode);

			if (!pNewEdge)
			{
				Print(("Out of memory when create new edge\n"));	
			}
		}

		if (status == R_ERROR)
		{
			Print(("Error in Input\n"));
		}
		else if (status == R_END)
		{
			memset(buf, 0, 1024);
			offset = 0;
		}
		else 
		{
			Print(("a normal edge have been splitted\n"));
		}
	

	}

	fclose(fp);


	printf("Graph is:\n");
	printGraph(pStartNode);

	numOfNodes = 0;
	pIterNode = pStartNode;
	while(pIterNode)
	{
		numOfNodes++;
		pIterNode->bVisited = FALSE;
		pIterNode = pIterNode->pNextNode;
	}

	createQueue(&pQueue, sizeof(LP_NODE), numOfNodes+1);
	curIndex = 0;
	printf("\nwidthTraverse : ");
	widthTraverse(pStartNode, visit, &curIndex, pQueue);
	destoryQueue(pQueue);

	pIterNode = pStartNode;
	while(pIterNode)
	{
		pIterNode->bVisited = FALSE;
		pIterNode = pIterNode->pNextNode;
	}
	createStack(&pStack, sizeof(LP_NODE));
	curIndex = 0;
	printf("\ndepthTraverse :");
	depthTraverse(pStartNode, visit, &curIndex, pStack);
	destoryStack(pStack);


	printf("\nTopo Order :");
	topologySortGraph(pStartNode);

	while(pStartNode)
	{
		pFromNode = pStartNode->pNextNode;
		free(pStartNode);
		pStartNode = pFromNode;
	}
	while(pStartEdge)
	{
		pNewEdge = pStartEdge->pNextEdge;
		free(pStartEdge);
		pStartEdge = pNewEdge;
	}


	
	return 0;



}

LP_NODE createNode(LP_NODE *ppStartNode, char data)
{
	LP_NODE pIterNode;
	LP_NODE pNewNode;
	
	pNewNode = (NODE *)malloc(sizeof(NODE));
	if (NULL == pNewNode)
	{
		Print(("Out of memory in createNode\n"));
		return NULL;
	}

	memset(pNewNode, 0, sizeof(NODE));
	pNewNode->data = data;

	if (*ppStartNode)
	{
		pIterNode = *ppStartNode;
		while(pIterNode->pNextNode)
			pIterNode = pIterNode->pNextNode;

		pIterNode->pNextNode = pNewNode;
	}
	else
	{
		*ppStartNode = pNewNode;
	}

	return pNewNode;

}

LP_EDGE createEdge(LP_EDGE *ppStartEdge, NODE *pFrom, NODE *pTo)
{
	LP_EDGE pIterEdge, pNewEdge;

	pNewEdge = (EDGE *)malloc(sizeof(EDGE));
	if (NULL == pNewEdge)
	{
		Print(("Out of memory in createEdge\n"));
		return NULL;
	}	

	pNewEdge->pFrom = pFrom;
	pNewEdge->pTo = pTo;

	pNewEdge->pNextSameFrom = pFrom->pFirstEdgeOut;
	pFrom->pFirstEdgeOut = pNewEdge;

	pNewEdge->pNextSameTo = pTo->pFirstEdgeIn;
	pTo->pFirstEdgeIn = pNewEdge;

	pNewEdge->pNextEdge = NULL;

	if (*ppStartEdge)
	{
		pIterEdge = *ppStartEdge;
		while(pIterEdge->pNextEdge)
			pIterEdge = pIterEdge->pNextEdge;

		pIterEdge->pNextEdge = pNewEdge;
	}
	else
	{
		*ppStartEdge = pNewEdge;
	}

	return pNewEdge;
}


void printGraph(LP_NODE pStartNode)
{
	LP_NODE pIterNode = pStartNode;
	LP_EDGE pIterEdge;

	while (pIterNode)
	{
		printf("\nNode [%c]->{", pIterNode->data);
		pIterEdge = pIterNode->pFirstEdgeOut;		
		
		if (pIterEdge)
		{
			while(pIterEdge)
			{
				putchar(pIterEdge->pTo->data);
				pIterEdge = pIterEdge->pNextSameFrom;
				if (pIterEdge)
					putchar(',');
			}	
		}
		else
		{
			printf("NULL");
		}

		putchar('}');		

		pIterNode = pIterNode->pNextNode;
	}
}

NODE * findNode(LP_NODE pStartNode, char data)
{
	LP_NODE pIterNode = pStartNode;
	while(pIterNode)
	{
		if (pIterNode->data == data)
			break;

		pIterNode = pIterNode->pNextNode;
	}
	
	return pIterNode;
}


enum RESULT getNextEdge(char *buf, int *pCurIndex, char *from, char *to)
{
	int index = *pCurIndex;

	while(buf[index] == ' ' 
		  || buf[index] == '\t')
		index++;

	if (buf[index] == '\0')
		return R_END;

	if(buf[index] == '(')
		index++;
	else if (buf[index] == '\0')
		return R_NOTCOMPLETED;
	else
		return R_ERROR;


	if(isalpha(buf[index] ))
		index++;
	else if (buf[index] == '\0')
		return R_NOTCOMPLETED;
	else
		return R_ERROR;

	if(buf[index] == ',')
		index++;
	else if (buf[index] == '\0')
		return R_NOTCOMPLETED;
	else
		return R_ERROR;

	if(isalpha(buf[index]))
		index++;
	else if (buf[index] == '\0')
		return R_NOTCOMPLETED;
	else
		return R_ERROR;

	
	if(buf[index] == ')')
		index++;
	else if (buf[index] == '\0')
		return R_NOTCOMPLETED;
	else
		return R_ERROR;

	*to = buf[index-2];
	*from = buf[index-4];
	*pCurIndex = index;

	return R_SUCCESS; 
} 

void visit(LP_NODE pVisitNode, int *pIndex)
{
	printf("%3c[%2d]",  pVisitNode->data,*pIndex);
	(*pIndex)++;	
}

void widthTraverse(LP_NODE pStartNode, void (*fn)(LP_NODE, int *), int *pCurIndex, LP_QUEUE pQueue)
{
	LP_NODE pIterNode;	
	LP_EDGE pIterEdge;

	pIterNode = pStartNode;
	while (pIterNode)
	{
		if (pIterNode->bVisited == FALSE)
		{
			insertToTail(pQueue, &pIterNode);
			pIterNode->bVisited = TRUE;

			while (!isQueueEmpty(pQueue))
			{
				getFromHead(pQueue, &pIterNode);
				fn(pIterNode, pCurIndex);
			
				pIterEdge = pIterNode->pFirstEdgeOut;
				while (pIterEdge)
				{
					if (pIterEdge->pTo->bVisited == FALSE)
					{
						insertToTail(pQueue, &pIterEdge->pTo);
						pIterEdge->pTo->bVisited  = TRUE;
					}
					pIterEdge = pIterEdge->pNextSameFrom;
				}
			}
		}
		pIterNode = pIterNode->pNextNode;
	}

}

void depthTraverse(LP_NODE pStartNode, void (*fn)(LP_NODE, int *), int *pCurIndex, LP_STACK pStack)
{
	LP_NODE pIterNode;
	LP_EDGE pIterEdge;
	LP_STACK pEdgeStack = NULL;
	int index = 0;

	createStack(&pEdgeStack, sizeof(LP_EDGE));
	
	pIterNode = pStartNode;
	while (pIterNode)
	{
		if (pIterNode->bVisited == FALSE)
		{	
	
			push(pStack, &pIterNode);
			pIterNode->bVisited = TRUE;

			while (!isStackEmpty(pStack))
			{
				pop(pStack, &pIterNode);
				fn(pIterNode, &index);
	
				pIterEdge = pIterNode->pFirstEdgeOut;
				while (pIterEdge)
				{
					push(pEdgeStack, &pIterEdge);
					pIterEdge = pIterEdge->pNextSameFrom;
				} 		
				while (!isStackEmpty(pEdgeStack))
				{
					pop(pEdgeStack, &pIterEdge);
					if (pIterEdge->pTo->bVisited == FALSE)
					{
						push(pStack, &pIterEdge->pTo);
						pIterEdge->pTo->bVisited = TRUE;
					}
				}
			}
		}
		pIterNode = pIterNode->pNextNode;
	}

	destoryStack(pEdgeStack);
}

void findZeroDegreeNode(void *pData, void *pArg)
{
	DEGREE *pDegreeNode;
	LP_STACK pNodeStack;

	pDegreeNode = (DEGREE *)pData;
	pNodeStack = (LP_STACK)pArg;

	if (!pDegreeNode->degree)
		push(pNodeStack, &pDegreeNode->pGraphNode);
}
void dumpDegree(void *pData, void *pArg)
{
	DEGREE *pDegreeNode;
	pDegreeNode = (DEGREE *)pData;

	printf("[%c,d%d]",pDegreeNode->pGraphNode->data, pDegreeNode->degree);
}

BOOL cmp(void *pData, void *pKey)
{
	DEGREE	*pDegreeNode;
	LP_NODE pNode = (NODE *)pKey;

	pDegreeNode = (DEGREE *)pData;
	//printf("\nCmp %c %c", pDegreeNode->pGraphNode->data, pNode->data);
	return (pDegreeNode->pGraphNode == pNode);	

}
void topologySortGraph(LP_NODE pStartNode)
{
	LP_EDGE pIterEdge;	
	LP_NODE pIterNode;
	LP_DOUBLE_LINK_LIST pDegreeList;
	LP_LIST_NODE pListNode;
	DEGREE	degreeNode, *pDegreeNode;
	LP_STACK pNodeStack;
	int degrees;
	int index = 0, numOfNode = 0;

	createStack(&pNodeStack, sizeof(LP_NODE));
	initList(&pDegreeList, sizeof(DEGREE));

	pIterNode = pStartNode;
	while (pIterNode)
	{
		degrees = 0;
		numOfNode++;
		pIterEdge = pIterNode->pFirstEdgeIn;
		while (pIterEdge)
		{
			degrees++;
			pIterEdge = pIterEdge->pNextSameTo;			
		}
		
		degreeNode.pGraphNode = pIterNode;
		degreeNode.degree = degrees;
		insertToListTail(pDegreeList, &degreeNode);

		pIterNode = pIterNode->pNextNode;
	}

	visitList(pDegreeList, findZeroDegreeNode, pNodeStack);
	//visitList(pDegreeList, dumpDegree, NULL);
	while (!isStackEmpty(pNodeStack))
	{
		pop(pNodeStack, &pIterNode);
		printf("[%d]%c", index, pIterNode->data);
		index++;		

		pIterEdge = pIterNode->pFirstEdgeOut;
		while (pIterEdge)
		{
			pDegreeNode = findNodeInList(pDegreeList, pIterEdge->pTo, cmp);
			pDegreeNode->degree--;
			if (!pDegreeNode->degree)
				push(pNodeStack, &pIterEdge->pTo);

			pIterEdge = pIterEdge->pNextSameFrom;
		}			
	}

	if (index < numOfNode)
		printf("\nCylce in Graph\n");
	
	destoryList(pDegreeList);
	destoryStack(pNodeStack);

}







