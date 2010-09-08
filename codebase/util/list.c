#include "../include/my.h"
#include "../include/util.h"
#include "../include/list.h"

STATUS initList(LP_DOUBLE_LINK_LIST *ppList, unsigned int elementSize)
{
	*ppList = (LP_DOUBLE_LINK_LIST)malloc(sizeof(DOUBLE_LINK_LIST));
	if (NULL == *ppList)
	{
		Print(("Out Of Memory when allocate list head\n")) ;
		return ERROR;
	}
	
	(*ppList)->pStartNode = (LP_LIST_NODE)malloc(sizeof(LIST_NODE));
	if (NULL == (*ppList)->pStartNode)
	{
		Print(("Out Of Memory when allocate list pStartNode\n")) ;
		return ERROR;
	}

	(*ppList)->pStartNode->pNextNode = (*ppList)->pStartNode;
	(*ppList)->pStartNode->pPrevNode = (*ppList)->pStartNode;
	(*ppList)->pStartNode->pData = NULL;
	
	(*ppList)->elementSize = elementSize;
	
	return OK;
}	

void visitList(LP_DOUBLE_LINK_LIST *ppList, void (*fn)(void *pData))
{


}


void destoryList(LP_DOUBLE_LINK_LIST pListHead)
{

}

STATUS insertAfterNode(LP_LIST_NODE pInsertPos, void *pData)
{


}
STATUS insertBeforeNode(LP_LIST_NODE pInsertPos, void *pData)
{
}
void deleteNode(LP_LIST_NODE pDeleteNode)
{
	
}

