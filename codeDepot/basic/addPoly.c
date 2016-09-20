#include "singleLinkList.h"


#include "utils.h"
#include "memory.h"



#include <stdio.h>
#include <stdlib.h>
#include <assert.h>



typedef struct _Item
{
	float coeff;
	unsigned int exp;
}Item, *LPItem;


BOOL
compareItem(const void *lhs, const void *rhs)
{
	LPItem pLhs = (LPItem)lhs;
	LPItem pRhs = (LPItem)rhs;
	
	return pLhs->exp < pRhs->exp ? True : False; 
}

static int counter = 0;
void
printItem(const void *data)
{
	LPItem pItem = (LPItem)data;
	if (counter != 0) {
		printf(" + ");
	}
	printf(" %f * X^^%d ", pItem->coeff, pItem->exp);
	++counter;
}

void
addPoly(const LPSingleLinkList pFirst, const LPSingleLinkList pSecond, LPSingleLinkList pCombined)
{
	LPSingleLinkListNode pFirstIt = pFirst->pHead;
	LPSingleLinkListNode pSecondIt = pSecond->pHead;
	SingleLinkListIter it = (SingleLinkListIter)(&pCombined->pHead);	
	SingleLinkListIter newIt;
	LPItem pFirstItem, pSecondItem;
	Item tempItem;
	float combinedCoeff;	


	while (pFirstIt && pSecondIt) {
		pFirstItem = (LPItem)pFirstIt->data;
		pSecondItem = (LPItem)pSecondIt->data;
	
		if (pFirstItem->exp < pSecondItem->exp) {
			tempItem = *pFirstItem;
			pFirstIt = pFirstIt->pNext;
			
			newIt = insertBeforeInSingleLinkList(pCombined, it, &tempItem);	
			it = &(*newIt)->pNext;		
		} else if (pFirstItem->exp > pSecondItem->exp) {
			tempItem = *pSecondItem;
			pSecondIt = pSecondIt->pNext;
			
			newIt = insertBeforeInSingleLinkList(pCombined, it, &tempItem);			
			it = &(*newIt)->pNext;
		} else {
			combinedCoeff = pFirstItem->coeff + pSecondItem->coeff;
			if (combinedCoeff != 0.0f) {
				tempItem.coeff = combinedCoeff;
				tempItem.exp = pFirstItem->exp;
				newIt = insertBeforeInSingleLinkList(pCombined, it, &tempItem);
				it = &(*newIt)->pNext;
			}
			pFirstIt = pFirstIt->pNext;
			pSecondIt = pSecondIt->pNext;
		}		

	}

	while (pFirstIt) {
		tempItem = *(LPItem)pFirstIt->data;
		newIt = insertBeforeInSingleLinkList(pCombined, it, &tempItem);	
		it = &(*newIt)->pNext;		
		
		pFirstIt = pFirstIt->pNext; 
	}
	while (pSecondIt) {
		tempItem = *(LPItem)pSecondIt->data;
		newIt = insertBeforeInSingleLinkList(pCombined, it, &tempItem);			
		it = &(*newIt)->pNext;
		
		pSecondIt = pSecondIt->pNext;
	}

	*it = NULL;
}

BOOL
constructPoly(LPSingleLinkList pList, FILE *fp)
{
	char *buf = NULL;
	int idx;
	int size;
	Item item;

	float coeff;
	unsigned int exp;

	fseek(fp, 0, SEEK_END);
	size = ftell(fp);
	rewind(fp);

	buf = myAlloc(size+1);
	if (NULL == buf) {
		goto lpexit;
	}

	if (size != fread(buf, 1, size, fp)) {
		goto lpexit;
	}

	buf[size] = '\0';
	idx = 0;
	skipSpace(buf, &idx);
	while (idx < size && buf[idx] != '\0' && buf[idx] != '\n') {
		assert(buf[idx] == '(');
		++idx;
		skipSpace(buf, &idx);
		sscanf(buf+idx, "%f", &coeff);
		while (isdigit(buf[idx]) || buf[idx] == '.')
			++idx;
		skipSpace(buf, &idx);
		assert(buf[idx] == ',');
		++idx;
		skipSpace(buf, &idx);
	
		sscanf(buf+idx, "%d", &exp);
		while(isdigit(buf[idx]))
			++idx;
		skipSpace(buf, &idx);
		assert(buf[idx] == ')');
		++idx;
		skipSpace(buf,&idx);

		
		item.coeff = coeff;
		item.exp = exp;
		insertToTailOfSingleLinkList(pList, &item);
	}



lpexit:
	if (buf)
		myFree(buf);
}

int main()
{
	LPSingleLinkList pFirstList	= NULL;
	LPSingleLinkList pSecondList	= NULL;
	LPSingleLinkList pCombinedList	= NULL;

	FILE *fp1 = NULL;
	FILE *fp2 = NULL;


	if (NULL == (fp1 = fopen("input1.txt", "r"))) {
		goto cleanup;
	}
	if (NULL == (fp2 = fopen("input2.txt", "r")) ) {
		goto cleanup;
	}

	
	if (False == createSingleLinkList(&pFirstList, sizeof(Item), compareItem, printItem)) {
		goto cleanup;
	}
	if (False == createSingleLinkList(&pSecondList, sizeof(Item), compareItem, printItem)) {
		goto cleanup;
	}
	if (False == createSingleLinkList(&pCombinedList, sizeof(Item), compareItem, printItem)) {
		goto cleanup;
	}


	DBG(printf("\nConstruct First List:"));	
	if (False == constructPoly(pFirstList, fp1)) {
		goto cleanup;
	}
	DBG(printf("\nConstruct Second List:"));
	if (False == constructPoly(pSecondList, fp2)) {
		goto cleanup;
	}

	DBG(printf("\nSort First List:"));
	sortSingleLinkList(pFirstList);
	DBG(printf("\nSort Second List:"));
	sortSingleLinkList(pSecondList);

	putchar('\n');
	counter = 0;
	traverseSingleLinkList(pFirstList, printItem);
	putchar('\n');

	counter = 0;
	traverseSingleLinkList(pSecondList, printItem);
	putchar('\n');

	addPoly(pFirstList, pSecondList, pCombinedList);

	counter = 0;
	traverseSingleLinkList(pCombinedList, printItem);
	putchar('\n');


cleanup:
	if (pFirstList)
		destroySingleLinkList(&pFirstList);
	if (pSecondList)
		destroySingleLinkList(&pSecondList);
	if (pCombinedList)
		destroySingleLinkList(&pCombinedList);

	
	if (fp1)
		fclose(fp1);
	if (fp2)
		fclose(fp2);

}

