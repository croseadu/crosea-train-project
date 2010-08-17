#include "../../include/my.h"
#include "polyList.h"


int main()
{
	STATUS status;
	DOUBLE_LIST *pResultList, *pMulList;
	int n;
	int k;

	printf("Input a data which you want to calculate factorial\n");
	scanf("%d", &n);

	if (n <= 0)
	{
		Print(("Input data is less than 1\n"));
		
	}

	initList(&pResultList);	

	if (1)
	{		
		LP_DOUBLE_LIST pInsertNode = (LP_DOUBLE_LIST)malloc(sizeof(DOUBLE_LIST));
		if (NULL == pInsertNode)
		{
			Print(("OutOfMemory when copyList"));
			return -2;
		}
		pInsertNode->factor = 1;
		pInsertNode->nIndex = 0;
		pResultList->pNextNode = pInsertNode;
		pInsertNode->pNextNode = pResultList;
	}
	//insertToPolyList(pResultList, 1, 0);
	k = 2;
	initList(&pMulList);
	while(k <= n)
	{

		if (setMulList(pMulList, k) != 0)
		{
			Print(("OutOfMemory when set mulList ,here k is %d", k));
			exit(-1);
		}	
		mulSelfList(pResultList, pMulList);

		cleanList(pMulList);
		k++;
	}

	printf("\nx = 10, %d! = ", n);
	printPolyList(pResultList);	

	destoryList(pResultList);
	destoryList(pMulList);
	return 0;
}

STATUS initList(LP_DOUBLE_LIST *ppListHead)
{
	*ppListHead = (LP_DOUBLE_LIST)malloc(sizeof(DOUBLE_LIST));
	if (NULL == *ppListHead)
	{
		Print(("Out Of Memory when allocate list head\n")) ;
		return ERROR;
	}
	
	(*ppListHead)->nIndex = -1;
	(*ppListHead)->pNextNode = *ppListHead;
	return OK;
}	

void printPolyList(const LP_DOUBLE_LIST pListHead)
{
	LP_DOUBLE_LIST pIterNode = pListHead->pNextNode;
	int curIndex = -1;

	while(pIterNode != pListHead)
	{
		if (curIndex > 0 && curIndex + 1 != pIterNode->nIndex)
		{
			while (++curIndex < pIterNode->nIndex)
				putchar('0');
		}
		curIndex = pIterNode->nIndex;
		putchar(('0'+pIterNode->factor));
		pIterNode = pIterNode->pNextNode;
	}
}

void cleanList(LP_DOUBLE_LIST pListHead)
{
	LP_DOUBLE_LIST pNextNode, pIterNode = pListHead->pNextNode;

	while (pIterNode != pListHead)
	{
		pNextNode = pIterNode->pNextNode;
		free(pIterNode);
		pIterNode = pNextNode;
	}
	pListHead->pNextNode = pListHead;
}
void destoryList(LP_DOUBLE_LIST pListHead)
{
	LP_DOUBLE_LIST pNextNode, pIterNode = pListHead->pNextNode;
	while (pIterNode != pListHead)
	{
		pNextNode = pIterNode->pNextNode;
		free(pIterNode);
		pIterNode = pNextNode;
	}
	free(pListHead);
}

STATUS setMulList(LP_DOUBLE_LIST pListHead, unsigned int k)
{
	unsigned int temp, index = 0;
	char c;
	LP_DOUBLE_LIST pInsertNode = NULL;
	LP_DOUBLE_LIST pInsertPos = pListHead;
	
	while(k%10)
	{
		temp = k%10;
		pInsertNode = (LP_DOUBLE_LIST)malloc(sizeof(DOUBLE_LIST));
		if (NULL == pInsertNode)
		{
			Print(("OutOfMemory when add node in mul list\n"));
			return -2;
		}

		pInsertNode->factor = temp;
		pInsertNode->nIndex = index;
		pInsertPos->pNextNode = pInsertNode;
		pInsertPos = pInsertNode;		
		index++;
		k = k/10;		
	}

	pInsertNode->pNextNode = pListHead;
	return OK;
}
STATUS copyList(LP_DOUBLE_LIST pDst, LP_DOUBLE_LIST pSrc)
{
	LP_DOUBLE_LIST pIterNode = pSrc->pNextNode;
	LP_DOUBLE_LIST pInsertNodePrev = pDst;
	LP_DOUBLE_LIST pInsertNode;

	while(pIterNode != pSrc)
	{
		pInsertNode = (LP_DOUBLE_LIST)malloc(sizeof(DOUBLE_LIST));
		if (NULL == pInsertNode)
		{
			Print(("OutOfMemory when copyList"));
			return -2;
		}
		pInsertNode->factor = pIterNode->factor;
		pInsertNode->nIndex = pIterNode->nIndex;
		pInsertNodePrev->pNextNode = pInsertNode;
		pInsertNodePrev = pInsertNode;
		pIterNode = pIterNode->pNextNode;
	}
	pInsertNodePrev->pNextNode = pDst;
	return OK;

}
void mulOneNode(LP_DOUBLE_LIST pDst, LP_DOUBLE_LIST pSrc, LP_DOUBLE_LIST pNode)
{
	LP_DOUBLE_LIST pIterNode;
	
	copyList(pDst, pSrc);

	if (pNode->factor)
	{
		pIterNode = pDst->pNextNode;
		while (pIterNode != pDst)
		{
			pIterNode->factor *= pNode->factor;
			pIterNode->nIndex += pNode->nIndex;
			pIterNode = pIterNode->pNextNode;
		}
	}
}

STATUS addToList(LP_DOUBLE_LIST pResultList, LP_DOUBLE_LIST pAddSrcList)
{
	LP_DOUBLE_LIST pIterNode = pAddSrcList->pNextNode;
	LP_DOUBLE_LIST pInsertPos = pResultList, pInsertNode;
	
	while (pIterNode != pAddSrcList)
	{
	
		while (pInsertPos->pNextNode != pResultList && 
			pInsertPos->pNextNode->nIndex < pIterNode->nIndex)
		{
			pInsertPos = pInsertPos->pNextNode;
		}

		if (pInsertPos->pNextNode != pResultList && pInsertPos->pNextNode->nIndex == pIterNode->nIndex)
		{
			pInsertPos->pNextNode->factor += pIterNode->factor;
			pInsertPos = pInsertPos->pNextNode;
		}
		else
		{
			pInsertNode = (LP_DOUBLE_LIST)malloc(sizeof(DOUBLE_LIST));
			if (NULL == pInsertNode)
			{
				Print(("OutOfMemory in add List\n"));
				return -2;
			}
			pInsertNode->factor = pIterNode->factor;
			pInsertNode->nIndex = pIterNode->nIndex;

			pInsertNode->pNextNode = pInsertPos->pNextNode;
			pInsertPos->pNextNode = pInsertNode;
			pInsertPos = pInsertNode;
		}

		pIterNode = pIterNode->pNextNode;
	}
	return OK;
}

STATUS mulSelfList(LP_DOUBLE_LIST pResultList,LP_DOUBLE_LIST pMulSrcList)
{
	LP_DOUBLE_LIST pOriList, pIterNode;
	LP_DOUBLE_LIST pTempResultList;
	
	initList(&pOriList);
	initList(&pTempResultList);
	copyList(pOriList, pResultList);
	cleanList(pResultList);
	
	pIterNode = pMulSrcList->pNextNode;
	while (pIterNode != pMulSrcList)
	{
		mulOneNode(pTempResultList, pOriList, pIterNode);
		addToList(pResultList, pTempResultList);
		pIterNode = pIterNode->pNextNode;
	}

	destoryList(pOriList);
	destoryList(pTempResultList);
	return OK;
}
