#include "../../include/my.h"
#include "polyList.h"
#include "../../include/util.h"

int main()
{
	STATUS status;
	SINGLE_LIST *pResultList, *pMulList;
	int n;
	unsigned int k;

	printf("Input a data which you want to calculate factorial\n");
	scanf("%d", &n);

	if (n <= 0)
	{
		Print(("Input data is less than 1\n"));
		
	}

	initList(&pResultList);	


	insertToPolyList(pResultList, 1, 0);
	k = 2;
	while(k <= n)
	{
		if (setMulList(pMulList, k))
		{
			Print(("OutOfMemory when set mulList ,here k is %d", k));
			exit(-1);
		}	
		MulSelfList(pResultList, pMulList);

		cleanList(pMulList);
		k++;
	}

	printf("\nx = 10, %d! = ");
	printList(pResultList);	

	destoryList(pResultList);
	destoryList(pMulList);
	return 0;
}

STATUS initList(LP_SINGLE_LIST *ppListHead)
{
	*ppListHead = (LP_SINGLE_LIST)malloc(sizeof(SINGLE_LIST));
	if (NULL == *ppListHead)
	{
		Print(("Out Of Memory when allocate list head\n")) ;
		return ERROR;
	}
	
	(*ppListHead)->data = -1;
	(*ppListHead)->pNextNode = NULL;
	return OK;
}	

void printPolyList(const LP_SINGLE_LIST pListHead)
{
	LP_SINGLE_LIST pIterNode = pListHead->pNextNode;


}
void cleanList(LP_SINGLE_LIST pListHead)
{
	LP_SINGLE_LIST pNextNode, pIterNode = pListHead->pNextNode;

	pListHead->pNextNode = NULL;

	while (pIterNode)
	{
		pNextNode = pIterNode->pNextNode;
		free(pIterNode);
		pIterNode = pNextNode;
	}
		
}
void destoryList(LP_SINGLE_LIST pListHead)
{
	LP_SINGLE_LIST pNextNode, pIterNode = pListHead;
	while (pIterNode)
	{
		pNextNode = pIterNode->pNextNode;
		free(pIterNode);
		pIterNode = pNextNode;
	}
	
}

STATUS setMulList(LP_SINGLE_LIST pListHead, unsigned int k)
{
	unsigned int temp, index = 0;
	char c;
	LP_SINGLE_LIST pInsertNode = NULL;
	
	while(k%10)
	{
		temp = k%10;
		pInsertNode = (LP_SINGLE_LIST)malloc(sizeof(SINGLE_LIST));
		if (NULL == pInsertNode)
		{
			Print(("OutOfMemory when add node in mul list\n"));
			return -2;
		}

		pInsertNode->factor = temp;
		pInsertNode->nIndex = index;
		pInsertNode->pNextNode = pListHead->pNextNode;
		pListHead->pNextNode = pInsertNode;
		
		index++;
		k = k/10;		
	}

	return OK;
}

