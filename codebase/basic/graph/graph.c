#include "../../include/my.h"
#include "../../include/util.h"

struct _EDGE;
typedef struct _NODE
{
	char data;
	struct _EDGE *pFirstEdgeIn;
	struct _EDGE *pFirstEdgeOut;

	/************link all node**************/
	struct _NODE *pNextNode;
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
	R_NONCOMPLETED = 2,
};
LP_NODE createNode(LP_NODE *ppStartNode, char data);
LP_EDGE createEdge(LP_EDGE *ppStartEdge, NODE *pFrom, NODE *pTo);
void printGraph(LP_NODE pStartNode);

int main()
{
	FILE *fp;
	char buf[1024];
	char from, to;
	int readCount;
	int curIndex;
	int offset = 0;

	LP_NODE pStartNode = NULL, pFromNode, pToNode;
	LP_EDGE pStartEdge = NULL, pNewEdge;
	enum RESULT status;

	if ((fp = fopen("temp", "rt")) == NULL)
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

		
		while (buf[curIndex] == '\t' 
			   || buf[curIndex] == ' ' 
			   || buf[curIndex] != 0)
			   curIndex++;
	
		if (buf[curIndex] == 0)
		{
			if (offset)
				Print(("impossible"));
			memset(buf, 0, curIndex);
			continue;

		}
		while(status = getNextEdge(buf, &curIndex, &from, & to))
		{
			if (!isNodeExist(pStartNode, from))
			{
				pFromNode = createNode(&pStartNode, from);
			}
			if (!isNodeExist(pStartNode, to))
			{
				pToNode = createNode(&pStartNode, to);
			}

			if (!pFromNode || !pToNode)
			{
				Print(("Out of memory when create new node\n"));
			}

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

	pNewEdge = (NODE *)malloc(sizeof(EDGE));
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
		printf("\nNode [%c],{", pIterNode->data);
		pIterEdge = pIterNode->pFirstEdgeOut;		
		while(pIterEdge)
		{
			printf("%c%c", pIterEdge->pTo->data, pIterEdge->pNextEdge?',':'\0');
			pIterEdge = pIterEdge->pNextEdge;
		}

		putchar('}');		

		pIterNode = pIterNode->pNextNode;
	}
}








