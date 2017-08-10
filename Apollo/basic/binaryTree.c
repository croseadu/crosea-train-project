#include "common.h"
#include "utils.h"
#include "memory.h"
#include "stack.h"
#include "queue.h"



#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


typedef struct _BinaryTree
{
	char data;
	struct _BinaryTree *pLeft;
	struct _BinaryTree *pRight;
}BinaryTree, *LPBinaryTree;



LPBinaryTree
construct(char *str, int *pI)
{
	LPBinaryTree pTree;
	
	char c = str[*pI];
	assert(c != '\0');	
	++*pI;

	if (c == ' ')
		return NULL;

	pTree = myAlloc(sizeof(BinaryTree));
	if (NULL == pTree) {
		assert(0);
	}	

	pTree->data = c;
	pTree->pLeft = construct(str, pI);
	pTree->pRight = construct(str, pI);


	return pTree;
}	



void
preOrderTraverse(LPBinaryTree);
void
inOrderTraverse(LPBinaryTree);
void
postOrderTraverse(LPBinaryTree);


void
preOrderTraverseNoRecursive(LPBinaryTree);
void
inOrderTraverseNoRecursive1(LPBinaryTree);
void
inOrderTraverseNoRecursive2(LPBinaryTree);
void
postOrderTraverseNoRecursive(LPBinaryTree);


int main()
{
	int idx;
	LPBinaryTree pTree = NULL;
	

	char *str = "ABCD   E  G H  ";


	idx = 0;
	pTree = construct(str, &idx);

	
	printf("\nPreOrder: ");
	preOrderTraverse(pTree);
	putchar('\n');

	printf("\nInOrder:  ");
	inOrderTraverse(pTree);
	putchar('\n');


	printf("\nPostOrder:");
	postOrderTraverse(pTree);
	putchar('\n');


	printf("\nPreOrderNoRecursive:    ");
	preOrderTraverseNoRecursive(pTree);
	putchar('\n');	

	printf("\nInOrderNoRecursive1:    ");
	inOrderTraverseNoRecursive1(pTree);
	putchar('\n');
	
	printf("\nInOrderNoRecursive2:    ");
	inOrderTraverseNoRecursive2(pTree);
	putchar('\n');	

	printf("\nPostOrderNoRecurisve:    ");
	postOrderTraverseNoRecursive(pTree);
	putchar('\n');

	return 0;
}




void
preOrderTraverse(LPBinaryTree pTree)
{
	if (pTree == NULL)
		return;
	putchar(pTree->data);
	preOrderTraverse(pTree->pLeft);
	preOrderTraverse(pTree->pRight);
}
void
inOrderTraverse(LPBinaryTree pTree)
{
	if (pTree == NULL)
		return;
	inOrderTraverse(pTree->pLeft);
	putchar(pTree->data);
	inOrderTraverse(pTree->pRight);

}

void
postOrderTraverse(LPBinaryTree pTree)
{
	if (pTree == NULL)
		return;
	postOrderTraverse(pTree->pLeft);
	postOrderTraverse(pTree->pRight);
	putchar(pTree->data);
}




void
preOrderTraverseNoRecursive(LPBinaryTree pTree)
{
	LPStack pStack = NULL;
	if (False == createStack(&pStack, 
				 sizeof(LPBinaryTree),
				 defaultPrinter)) {
		goto lexit;
	}

	
	if (pTree == NULL)
		return;

	pushToStack(pStack, &pTree);
	while (isStackEmpty(pStack) == False) {
		getTopFromStack(pStack, &pTree);
		popFromStack(pStack);

		putchar(pTree->data);
		if (pTree->pRight)
			pushToStack(pStack, &pTree->pRight);
		if (pTree->pLeft)
			pushToStack(pStack, &pTree->pLeft);

	}

lexit:
	if (pStack != NULL)
		destroyStack(&pStack);


	return;	
}

void
inOrderTraverseNoRecursive1(LPBinaryTree pTree)
{
	LPStack pStack = NULL;

	if (False == createStack(&pStack,
				 sizeof(LPBinaryTree),
				 defaultPrinter)) {
		goto lexit;
	}
	
	while (pTree != NULL || isStackEmpty(pStack) == False) {
		if (pTree != NULL) {
			while (pTree->pLeft != NULL) {
				pushToStack(pStack, &pTree);
				pTree = pTree->pLeft;
			}

			putchar(pTree->data);
			pTree = pTree->pRight;
		} else {
			getTopFromStack(pStack, &pTree);
			popFromStack(pStack);

			putchar(pTree->data);
			pTree = pTree->pRight;
		}
	}


lexit:
	if (pStack != NULL)
		destroyStack(&pStack);
	return;
}

void
inOrderTraverseNoRecursive2(LPBinaryTree pTree)
{
	LPStack pStack = NULL;

	if (False == createStack(&pStack, 
				 sizeof(LPBinaryTree),
				 defaultPrinter)) {
		goto lexit;
	}

	pushToStack(pStack, &pTree);

	while (isStackEmpty(pStack) == False) {
		getTopFromStack(pStack, &pTree);
		while (pTree != NULL) {
			pushToStack(pStack, &pTree->pLeft);
			pTree = pTree->pLeft;
		}

		popFromStack(pStack);
		if (isStackEmpty(pStack) == True)
			break;
		getTopFromStack(pStack, &pTree);
		popFromStack(pStack);
		putchar(pTree->data);
		pushToStack(pStack, &pTree->pRight);
	
	}


lexit:
	if (pStack != NULL)
		destroyStack(&pStack);

}

void
postOrderTraverseNoRecursive(LPBinaryTree pTree)
{
	LPStack pStack = NULL;
	LPBinaryTree lastNode = NULL;

	if (False == createStack(&pStack, 
				 sizeof(LPBinaryTree),
				 defaultPrinter)) {
		goto lexit;
	}

	pushToStack(pStack, &pTree);	
	while (isStackEmpty(pStack) == False) {
		getTopFromStack(pStack, &pTree);
			
		if ( (pTree->pLeft == NULL && pTree->pRight == NULL) ||
		     (pTree->pRight && pTree->pRight == lastNode) ||
		     (pTree->pRight == NULL && pTree->pLeft && pTree->pLeft == lastNode) ) {
			popFromStack(pStack);
			lastNode = pTree;
			putchar(pTree->data);
		} else {
			if (pTree->pRight)
				pushToStack(pStack, &pTree->pRight);
			if (pTree->pLeft)
				pushToStack(pStack, &pTree->pLeft);
		}
		
	}

lexit:
	if (pStack != NULL)
		destroyStack(&pStack);

}












