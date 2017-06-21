#include "singleLinkList.h"
#include "common.h"


#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>


void 
format(
	char buf[])
{
	int i = 0;
	int j = 0;

	while (buf[i] != '\0') {
		if (buf[i] == ' ' || buf[i] == '\n') {
			++i;
			continue;
		}
		if (i != j) {
			buf[j] = buf[i];
		}
		++j;
		++i;
	}
	buf[j] = '\0';
}


typedef struct _PolyItem
{
	float coefficient;
	int exponent;
}PolyItem, *LPPolyItem;

void
polyPrinter(
	const void *data)
{
	LPPolyItem pPoly = (LPPolyItem)data;

	printf(" %f", pPoly->coefficient);
	if (pPoly->exponent != 0) {
		printf("*X^^%d ", pPoly->exponent);
	}
}

BOOL
polyLess(
	const void *left,
	const void *right)
{
	LPPolyItem pLeft = (LPPolyItem)left;
	LPPolyItem pRight = (LPPolyItem)right;

	return (pLeft->exponent < pRight->exponent) ? True : False;
}


BOOL
getPoly(
	char *buf,
	LPPolyItem pPoly,
	int *pI)
{
	float coeff = 0.0;
	int i = *pI;
	if (buf[i] == '\0' || buf[i] == '\n')
		return False;

	assert(buf[i] == '(');
	sscanf(buf+i, "%f", &coeff);
	while(buf[i] == '-' || isdigit(buf[i]))
		++i;
	assert(buf[i] == ',');
	++i;
	sscanf(buf+i, "%f", &coeff);
	while(buf[i] == '-' || isdigit(buf[i]))
		++i;
	assert(buf[i] == ')');
	++i;

	*pI = i;
	return True;	
}


void
addPoly(
	LPSingleLinkList pLeftList,
	LPSingleLinkList pRightList,
	LPSingleLinkList pResultList)

{
	LPSingleLinkListNode pLeftNode, pRightNode;
	LPSingleLinkListNode *ppLeft = &pLeftList->pHead;
	LPSingleLinkListNode *ppRight = &pRightList->pHead;

	LPSingleLinkListNode *ppPos = &pResultList->pHead;

	LPPolyItem pLeftPoly, pRightPoly;
	float newCoeff;

	while (*ppLeft && *ppRight) {
		pLeftNode = *ppLeft;
		pRightNode = *ppRight;
		
		if (pLeftList->less(pLeftNode->data, pRightNode->data) == True) {
			*ppPos = pLeftNode;
			ppPos = &pLeftNode->pNext;

			*ppLeft = NULL;
			ppLeft = &pLeftNode->pNext;
		} else if (pRightList->less(pRightNode->data, pLeftNode->data) == True) {
			*ppPos = pRightNode;
			ppPos = &pRightNode->pNext;

			*ppRight = NULL;
			ppRight = &pRightNode->pNext;

		} else {
			pLeftPoly = (LPPolyItem)pLeftNode->data;
			pRightPoly = (LPPolyItem)pRightNode->data;

			newCoeff = pLeftPoly->coefficient + pRightPoly->coefficient;
			if (newCoeff != 0) {
				pLeftPoly->coefficient = newCoeff;
				*ppPos = pLeftNode;
				ppPos = &pLeftNode->pNext;

				*ppLeft = NULL;
				*ppRight = NULL;
				ppLeft = &pLeftNode->pNext;
				ppRight = &pRightNode->pNext;

				myFree(pRightNode->data);
				myFree(pRightNode);
			} else {
				*ppLeft = NULL;
				*ppRight = NULL;
				ppLeft = &pLeftNode->pNext;
				ppRight = &pRightNode->pNext;
				myFree(pLeftNode->data);
				myFree(pLeftNode);
				myFree(pRightNode->data);
				myFree(pRightNode);
			}		
		}
	}
	
	*ppPos = *ppLeft != NULL ? *ppLeft : *ppRight;
	*ppLeft = NULL;
	*ppRight = NULL;
}

int main()
{
	
	LPSingleLinkList pLeftList = NULL;
	LPSingleLinkList pRightList = NULL;
	LPSingleLinkList pResultList = NULL;
	char buf[128+1] = {'\0'};
	int i;
	PolyItem poly;
	FILE *fp = NULL;
	

	if (False == createSingleLinkList(&pLeftList,
					  sizeof(PolyItem),
					  polyPrinter,
					  polyLess)) {
		goto lexit;

	}	


	if (False == createSingleLinkList(&pRightList,
					  sizeof(PolyItem),
					  polyPrinter,
					  polyLess)) {
		goto lexit;

	}	

	if (False == createSingleLinkList(&pResultList,
					  sizeof(PolyItem),
					  polyPrinter,
					  polyLess)) {
		goto lexit;

	}	


	
	fp = fopen("poly.txt", "r");
	if (NULL == fp) {
		goto lexit;
	}

	
	fgets(buf, 128, fp);
	format(buf);
	i = 0;
	while (getPoly(buf, &poly, &i) == True)
	{
		insertToTailOfSingleLinkList(pLeftList, &poly);
	}

	memset(buf, '\0', sizeof(buf));

	fgets(buf, 128, fp);
	format(buf);
	i = 0;
	while (getPoly(buf, &poly, &i) == True)
	{
		insertToTailOfSingleLinkList(pRightList, &poly);
	}

	dumpSingleLinkList(pLeftList, " + ", 100);
	dumpSingleLinkList(pRightList, " + ", 100);

	sortSingleLinkList(pLeftList);
	sortSingleLinkList(pRightList);

	printf("\nAfter Sorting:\n");
	dumpSingleLinkList(pLeftList, " + ", 100);
	dumpSingleLinkList(pRightList, " + ", 100);

	addPoly(pLeftList, pRightList, pResultList);
	printf("\nAfter Merget\n");
	assert(isSingleLinkListEmpty(pLeftList) == True);
	assert(isSingleLinkListEmpty(pRightList) == True);	
	dumpSingleLinkList(pResultList, " + ", 100);


lexit:
	if (pLeftList != NULL) {
		destroySingleLinkList(&pLeftList);
	}
	if (pRightList != NULL) {
		destroySingleLinkList(&pRightList);
	}
	if (pResultList != NULL) {
		destroySingleLinkList(&pResultList);
	}

	return 0;
}
