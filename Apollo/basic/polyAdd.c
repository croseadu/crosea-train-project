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
	int exp = 0;
	int i = *pI;
	if (buf[i] == '\0' || buf[i] == '\n')
		return False;
	printf("\n%s\n", buf+i);
	assert(buf[i] == '(');
	++i;
	sscanf(buf+i, "%f", &coeff);
	while(buf[i] == '-' || isdigit(buf[i]) || buf[i] == '.' || buf[i] == 'f')
		++i;
	assert(buf[i] == ',');
	++i;
	sscanf(buf+i, "%d", &exp);
	while(buf[i] == '-' || isdigit(buf[i]))
		++i;
	assert(buf[i] == ')');
	++i;

	*pI = i;
	pPoly->coefficient = coeff;
	pPoly->exponent = exp;

	return True;	
}


void
addPoly(
	LPSingleLinkList pLeftList,
	LPSingleLinkList pRightList,
	LPSingleLinkList pResultList)

{
	LPSingleLinkListNode pLeftNode, pRightNode, pDeleteNode;

	LPSingleLinkListNode *ppPos = &pResultList->pHead;


	LPPolyItem pLeftPoly, pRightPoly;

	float newCoeff;

	pLeftNode = pLeftList->pHead;
	pRightNode = pRightList->pHead;
	pLeftList->pHead = NULL;
	pRightList->pHead = NULL;

	while (pLeftNode && pRightNode) {
		
		if (pLeftList->less(pLeftNode->data, pRightNode->data) == True) {
			*ppPos = pLeftNode;
			ppPos = &pLeftNode->pNext;

			pLeftNode = pLeftNode->pNext;
		} else if (pRightList->less(pRightNode->data, pLeftNode->data) == True) {
			*ppPos = pRightNode;
			ppPos = &pRightNode->pNext;

			pRightNode = pRightNode->pNext;

		} else {
			pLeftPoly = (LPPolyItem)pLeftNode->data;
			pRightPoly = (LPPolyItem)pRightNode->data;

			newCoeff = pLeftPoly->coefficient + pRightPoly->coefficient;
			if (newCoeff != 0) {
				pLeftPoly->coefficient = newCoeff;
				*ppPos = pLeftNode;
				ppPos = &pLeftNode->pNext;
				pLeftNode = pLeftNode->pNext;

				pDeleteNode = pRightNode;
				pRightNode = pRightNode->pNext;
				myFree(pDeleteNode->data);
				myFree(pDeleteNode);
			} else {
				pDeleteNode = pLeftNode;
				pLeftNode = pLeftNode->pNext;			
				myFree(pDeleteNode->data);
				myFree(pDeleteNode);

				pDeleteNode = pRightNode;
				pRightNode = pRightNode->pNext;
				myFree(pDeleteNode->data);
				myFree(pDeleteNode);
			}		
		}
	}
	
	*ppPos = pLeftNode != NULL ? pLeftNode : pRightNode;
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
	printf("\nAfter Merge:\n");
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
