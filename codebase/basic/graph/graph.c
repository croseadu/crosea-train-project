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
	R_NOTCOMPLETED = 2,
	R_SUCCESS = 3,
};
LP_NODE createNode(LP_NODE *ppStartNode, char data);
LP_EDGE createEdge(LP_EDGE *ppStartEdge, NODE *pFrom, NODE *pTo);
void printGraph(LP_NODE pStartNode);
NODE * findNode(LP_NODE pStartNode, char data);
enum RESULT getNextEdge(char *buf, int *pCurIndex, char *from, char *to);

int main()
{
	FILE *fp;
	char buf[1024];
	char from, to;
	int readCount;
	int curIndex;
	int offset = 0;

	LP_NODE pStartNode = NULL, pFromNode, pToNode, pIterNode;
	LP_EDGE pStartEdge = NULL, pNewEdge, pIterEdge;
	enum RESULT status;

	if ((fp = fopen("F:\\temp.txt", "rt+")) == NULL)
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
		return ERROR;


	if(isalpha(buf[index] ))
		index++;
	else if (buf[index] == '\0')
		return R_NOTCOMPLETED;
	else
		return ERROR;

	if(buf[index] == ',')
		index++;
	else if (buf[index] == '\0')
		return R_NOTCOMPLETED;
	else
		return ERROR;

	if(isalpha(buf[index]))
		index++;
	else if (buf[index] == '\0')
		return R_NOTCOMPLETED;
	else
		return ERROR;

	
	if(buf[index] == ')')
		index++;
	else if (buf[index] == '\0')
		return R_NOTCOMPLETED;
	else
		return ERROR;

	*to = buf[index-2];
	*from = buf[index-4];
	*pCurIndex = index;

	return R_SUCCESS; 
} 



