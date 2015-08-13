#include "singleLinkList.h"
#include <assert.h>
#include "common.h"

typedef struct _PolyNode
{
	float coef;
	unsigned int exp;
}PolyNode, *LPPolyNode;


void printer(const void *data)
{
	LPPolyNode pNode = (LPPolyNode)data;
	printf(" %f ", pNode->coef);
	if (pNode->exp != 0)
		printf("* X^^%d",pNode->exp);

}

enum BOOL 
less(const void *lhs, const void *rhs)
{
	LPPolyNode pLhs, pRhs;


	pLhs = (LPPolyNode)lhs;
	pRhs = (LPPolyNode)rhs;
	return pLhs->exp < pRhs->exp;

}

enum BOOL
createSingleLinkListFromFile(LPSingleLinkList pList, const char *fileName)
{
	FILE *fp = NULL;
	char *buf = NULL;
	char *pCur;
	LPPolyNode pLeft, pRight;
	int size = 0;
	int i;	
	PolyNode tempNode;


	LPSingleLinkListNode pIterLeft, pIterRight;	

	if (NULL == (fp = fopen(fileName, "r"))) {
		printf("Can't Open input.txt!");
		return False;
	}
	fseek(fp, 0, SEEK_END);
	size = ftell(fp);
	rewind(fp);
	printf("size of file is : %d", size);
	buf = (char *)myAlloc(size+1);
	
	if (NULL == buf) {
		printf("Out Of memory\n");
		return False;
	}
	buf[size] = EOF;
	printf("Start reading\n");
	fread(buf, 1, size, fp);
	printf("end of reading\n");
	fclose(fp);

	i = 0;
	printf("Input buffer is :\n");
	while (buf[i] != EOF && i < size) {
		putchar(buf[i]);
		++i;
	}
	putchar('\n');
	pCur = buf;
	while (1) {
		skipSpace(&pCur);
		if (match(*pCur, '(') == True) {
			++pCur;
			skipSpace(&pCur);
			sscanf(pCur, "%f", &tempNode.coef);
			advanceTill(&pCur, ',');
			++pCur;
			skipSpace(&pCur);
			sscanf(pCur, "%d", &tempNode.exp);
			advanceTill(&pCur, ')');
			++pCur;
			printf("\nGot a new item: %f %d", tempNode.coef, tempNode.exp);
			insertToTailOfSingleLinkList(pList, &tempNode);

		} else if (match(*pCur, '\n') == True) {
			++pCur;
		} else if (isEOF(*pCur) == True) {
			break;
		}
	}
	printf("Constructed Poly is :\n");
	printSingleLinkList(pList);
	sortSingleLinkList(pList);
	printf("After Sorting, Poly is :\n");
	printSingleLinkList(pList);

	myFree(buf);
	return True;

}

int main()
{

	LPSingleLinkList pLhsList = NULL, pRhsList = NULL, pMergeList = NULL;
	int i;
	
	LPPolyNode pLeftPoly, pRightPoly;
	LPSingleLinkListNode pIterLeft, pIterRight, pNextNode;	
	LPSingleLinkListNode *ppMergeInsertPos;


	if (False == createSingleLinkList(&pLhsList,
					  sizeof(PolyNode),
					  printer,
				          less)) {
		printf("Failed to Create Single Link List!");
		goto cleanup;

	}


	if (False == createSingleLinkList(&pRhsList,
					  sizeof(PolyNode),
					  printer,
				          less)) {
		printf("Failed to Create Single Link List!");
		goto cleanup;

	}

	if (False == createSingleLinkList(&pMergeList,
					  sizeof(PolyNode),
					  printer,
				          less)) {
		printf("Failed to Create Single Link List!");
		goto cleanup;

	}

	if (False == createSingleLinkListFromFile(pLhsList, "input.txt")) {
		goto cleanup;
	}
	if (False == createSingleLinkListFromFile(pRhsList, "input2.txt")) {
		goto cleanup;
	}



	pIterLeft = pLhsList->pHead;
	pIterRight = pRhsList->pHead;
	i = 0;
	ppMergeInsertPos = &pMergeList->pHead;
	while (pIterLeft != NULL && pIterRight != NULL) {
		pLeftPoly = (LPPolyNode)pIterLeft->data;
		pRightPoly = (LPPolyNode)pIterRight->data;			
		if (pLeftPoly->exp < pRightPoly->exp) {
			printf("\nMerge Step :%d: pick left", i);
			*ppMergeInsertPos = pIterLeft;
			ppMergeInsertPos = &pIterLeft->pNextNode;
			pIterLeft = pIterLeft->pNextNode;
			
		} else if (pLeftPoly->exp > pRightPoly->exp) {
			printf("\nMerge Step :%d: pick right", i);
			*ppMergeInsertPos = pIterRight;
			ppMergeInsertPos = &pIterRight->pNextNode;
			pIterRight = pIterRight->pNextNode;
		} else {
			if (pLeftPoly->coef + pRightPoly->coef == 0.0) {
				printf("\nMerge Step :%d: sum zero, no new node", i);
				pNextNode = pIterLeft->pNextNode;
				myFree(pIterLeft->data);
				myFree(pIterLeft);
				pIterLeft = pNextNode;

				pNextNode = pIterRight->pNextNode;
				myFree(pIterRight->data);
				myFree(pIterRight);
				pIterRight = pNextNode;
				
			} else {
				pLeftPoly->coef = pLeftPoly->coef + pRightPoly->coef;
				printf("\nMerge Step :%d: combine left and right", i);
				*ppMergeInsertPos = pIterLeft;
				ppMergeInsertPos = &pIterLeft->pNextNode;
				pIterLeft = pIterLeft->pNextNode;
				pNextNode = pIterRight->pNextNode;
				myFree(pIterRight->data);
				myFree(pIterRight);
				pIterRight = pNextNode;

			} 
			
		}	
		++i;

	}

	*ppMergeInsertPos = (pIterLeft != NULL)?pIterLeft:pIterRight;
	pLhsList->pHead = pRhsList->pHead = NULL;
	printf("\nMerge List :");
	printSingleLinkList(pMergeList);
cleanup:
	if (pLhsList != NULL) 
		destroySingleLinkList(&pLhsList);
	if (pRhsList != NULL)
		destroySingleLinkList(&pRhsList);
	if (pMergeList != NULL)
		destroySingleLinkList(&pMergeList);

	return 0;



}

