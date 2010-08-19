#include "../../include/my.h"
#include "polyList.h"


int main()
{
	STATUS status;
	DOUBLE_LIST *pResultList, *pMulList;
	LP_DOUBLE_LIST pInsertNode;
	int n;
	int k;

	printf("Input a data which you want to calculate factorial\n");
	n = 10;//scanf("%d", &n);

	if (n <= 0)
	{
		Print(("Input data is less than 1\n"));
		exit(-1);
	}

	initList(&pResultList);	
		
	pInsertNode = (LP_DOUBLE_LIST)malloc(sizeof(DOUBLE_LIST));
	if (NULL == pInsertNode)
	{
		Print(("OutOfMemory when copyList\n"));
		return -2;
	}
	pInsertNode->factor = 1;
	pInsertNode->nIndex = 0;
	pResultList->pNextNode = pInsertNode;
	pInsertNode->pNextNode = pResultList;

	k = 2;
	initList(&pMulList);
	while(k <= n)
	{

		if (setMulList(pMulList, k) != 0)
		{
			Print(("OutOfMemory when set mulList ,here k is %d\n", k));
			exit(-1);
		}	
		mulSelfList(pResultList, pMulList);

		cleanList(pMulList);
		k++;
	}

	printf("\n %d! = ", n);
	printPolyList(pResultList);	
	putchar('\n');

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
	(*ppListHead)->pPrevNode = *ppListHead;
	return OK;
}	

void printPolyList(const LP_DOUBLE_LIST pListHead)
{
	LP_DOUBLE_LIST pIterNode = pListHead->pPrevNode;
	int curIndex = -1;

	while(pIterNode != pListHead)
	{
		if (curIndex > 0 && curIndex - 1 > pIterNode->nIndex)
		{
			while (--curIndex > pIterNode->nIndex)
				putchar('0');
		}
		curIndex = pIterNode->nIndex;
		putchar(('0'+pIterNode->factor));
		pIterNode = pIterNode->pPrevNode;
	}
	while(curIndex > 0 && curIndex--)
	{
		putchar('0');
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

void insertNodeAfter(LP_DOUBLE_LIST pInsertPos, LP_DOUBLE_LIST pInsertNode)
{
	pInsertNode->pNextNode = pInsertPos->pNextNode;
	pInsertNode->pPrevNode = pInsertPos;
	pInsertNode->pNextNode->pPrevNode = pInsertNode;
	pInsertPos->pNextNode = pInsertNode;

}
void deleteNode(LP_DOUBLE_LIST pDeleteNode)
{
	LP_DOUBLE_LIST pPrevNode, pNextNode;

	if (pDeleteNode->pNextNode == pDeleteNode)
	{
		Print(("Error when delete a node\n"));
		exit(-1);
	}

	pPrevNode = pDeleteNode->pPrevNode;
	pNextNode = pDeleteNode->pNextNode;
	
	free(pDeleteNode);
	pPrevNode->pNextNode = pNextNode;
	pNextNode->pPrevNode = pPrevNode;	
}
STATUS setMulList(LP_DOUBLE_LIST pListHead, unsigned int k)
{
	unsigned int temp, index = 0;
	char c;
	LP_DOUBLE_LIST pInsertNode = NULL;
	LP_DOUBLE_LIST pInsertPos = pListHead;
	
	while(k)
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
		pInsertNode->pPrevNode = pInsertPos;
		pInsertPos->pNextNode = pInsertNode;
		pInsertPos = pInsertNode;		
		index++;
		k = k/10;		
	}

	pInsertNode->pNextNode = pListHead;
	pListHead->pPrevNode = pInsertNode;
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
			Print(("OutOfMemory when copyList\n"));
			return -2;
		}
		pInsertNode->factor = pIterNode->factor;
		pInsertNode->nIndex = pIterNode->nIndex;
		pInsertNode->pPrevNode = pInsertNodePrev;
		pInsertNodePrev->pNextNode = pInsertNode;
		pInsertNodePrev = pInsertNode;
		pIterNode = pIterNode->pNextNode;
	}
	pInsertNodePrev->pNextNode = pDst;
	pDst->pPrevNode = pInsertNodePrev;
	return OK;

}
STATUS mulOneNode(LP_DOUBLE_LIST pDst, LP_DOUBLE_LIST pSrc, LP_DOUBLE_LIST pNode)
{
	LP_DOUBLE_LIST pIterNode, pInsertNode, pInsertPos;
	BOOL bHaveAcc = FALSE;
	int accIndex = 0, accFactor = 0;
	
	pInsertPos = pDst;
	if (pNode->factor)
	{
		pIterNode = pSrc->pNextNode;
		while (pIterNode != pSrc)
		{

			pInsertNode = (LP_DOUBLE_LIST)malloc(sizeof(DOUBLE_LIST));
			if (NULL == pInsertNode)
			{
				Print(("OutOfMemory when mulOneNode\n"));
				return -2;
			}

			pInsertNode->factor = pIterNode->factor*pNode->factor;
			pInsertNode->nIndex = pIterNode->nIndex+pNode->nIndex;
			
			if (bHaveAcc)
			{
				LP_DOUBLE_LIST pInsertAccNode;
				bHaveAcc = FALSE;
				
				if (accIndex == pInsertNode->nIndex)
				{
					pInsertNode->factor += accFactor;
				}
				else
				{
					pInsertAccNode = (LP_DOUBLE_LIST)malloc(sizeof(DOUBLE_LIST));
					if (NULL == pInsertAccNode)
					{
						Print(("OutOfMemory when mulOneNode\n"));
						return -2;
					}
					
					pInsertAccNode->factor = accFactor;
					pInsertAccNode->nIndex = accIndex;
					insertNodeAfter(pInsertPos, pInsertAccNode);
					pInsertPos = pInsertAccNode;
				}
			}	

			if (pInsertNode->factor >= 10)
			{
				bHaveAcc = TRUE;
				accIndex = pInsertNode->nIndex + 1;
				accFactor = pInsertNode->factor/10;
				pInsertNode->factor %= 10;
			}		

			if (pInsertNode->factor == 0)
			{
				free(pInsertNode);
			}
			else
			{
				insertNodeAfter(pInsertPos, pInsertNode);
				pInsertPos = pInsertNode;
			}

			pIterNode = pIterNode->pNextNode;
		}
		
		if (bHaveAcc)
		{
			LP_DOUBLE_LIST pInsertAccNode;
			bHaveAcc = FALSE;
				
			pInsertAccNode = (LP_DOUBLE_LIST)malloc(sizeof(DOUBLE_LIST));
			if (NULL == pInsertAccNode)
			{
				Print(("OutOfMemory when mulOneNode\n"));
				return -2;
			}
					
			pInsertAccNode->factor = accFactor;
			pInsertAccNode->nIndex = accIndex;
			insertNodeAfter(pInsertPos, pInsertAccNode);
			pInsertPos = pInsertAccNode;
		}
	}

	return OK;
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
			if (pInsertPos->pNextNode->factor >= 10)
			{
				if (pInsertPos->pNextNode->pNextNode != pResultList &&
				    pInsertPos->pNextNode->pNextNode->nIndex == pIterNode->nIndex + 1)
				{
					pInsertPos->pNextNode->pNextNode->factor += 1;
				}
				else
				{
					LP_DOUBLE_LIST pInsertAccNode = (LP_DOUBLE_LIST)malloc(sizeof(DOUBLE_LIST));
					if (NULL == pInsertAccNode)
					{
						Print(("OutOfMemory in addToList\n"));
						return -2;
					}
					pInsertAccNode->factor = 1;
					pInsertAccNode->nIndex = pIterNode->nIndex+1;
					insertNodeAfter(pInsertPos->pNextNode, pInsertAccNode);
				}
				pInsertPos->pNextNode->factor %= 10;

				if (pInsertPos->pNextNode->factor == 0)
				{
					deleteNode(pInsertPos->pNextNode);	
				}
			}
				
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
			insertNodeAfter(pInsertPos, pInsertNode);
			pInsertPos = pInsertNode;
			
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
		cleanList(pTempResultList);
		pIterNode = pIterNode->pNextNode;
	}

	destoryList(pOriList);
	destoryList(pTempResultList);
	return OK;
}
