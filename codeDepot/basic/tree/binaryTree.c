


typedef struct _Tree
{
	char data;
	struct _Tree *leftChild;
	struct _Tree *rightChild;
}Tree, *LPTree;





void
preOrder(LPTree, Visitor visitor);
void
inOrder(LPTree, Visitor visitor);
void
postOrder(LPTree, Visitor visitor);



void
preOrderNoRecursive(LPTree, Visitor);
void
inOrderNoRecursiveV1(LPTree, Visitor);
void
inOrderNoRecursiveV2(LPTree, Visitor);
void
postOrderNoRecursive(LPTree, Visitor);



LPTree
createTree(const char *, int *pIdx);

int main()
{


	



	return 0;
}


static
LPTree
createTreeNode(char data)
{
	LPTree pNode;
	
	pNode = myAlloc(sizeof(Tree));
	if (NULL == pNode) {
		assert(0);
		return NULL;	
	}

	pNode->data = data;
	pNode->leftChild = NULL;
	pNode->rightChild = NULL;
	return pNode;
}


LPTree
createTree(const char *ptr, int *pIdx)
{
	LPTree pNode;

	if (ptr[*pIdx]== '#') {
		++*pIdx;
		return NULL;
	}

	pNode = createTreeNode(ptr[*pIdx]);
	++*pIdx;
	pNode->leftChild = createTree(ptr, pIdx);
	pNode->rightChild = createTree(ptr, pIdx);


	return pNode;	
}

void
preOrder(LPTree pRoot, Visitor visitor)
{
	if (pRoot == NULL)
		return;
	
	visitor(pRoot->data);

	preOrder(pRoot->leftChild, visitor);
	preOrder(pRoot->rightChild, visitor);
	
}

void
inOrder(LPTree pRoot, Visitor visitor)
{
	if (NULL == pRoot)
		return;
	inOrder(pRoot->leftChild, visitor);
	visitor(pRoot->data);
	inOrder(pRoot->rightChild, visitor);
}

void
postOrder(LPTree pRoot, Visitor visitor)
{
	if (NULL == pRoot)
		return;

	postOrder(pRoot->leftChild, visitor);
	postOrder(pRoot->rightChild, visitor);
	visitor(pRoot->data);

}


void
preOrderNoRecursive(LPTree pRoot, Visitor visitor)
{
	LPStack pStack = NULL;


	if (False == createStack(&pStack, sizeof(LPTree))) {
		goto cleanup;
	}

	if (pRoot)
		pushToStack(pStack, &pRoot);

	while (isStackEmpty(pStack) == False) {
		getTopOfStack(pStack, &pCurNode);
		popFromStack(pStack);

		visitor(pCurNode->data);
		if (pCurNode->rightChild)
			pushToStack(pStack, pCurNode->rightChild);
		if (pCurNode->leftChild)
			pushToStack(pStack, pCurNode->leftChild);
	}


cleanup:
	if (pStack)
		destroyStack(&pStack);

}

void
inOrderNoRecursiveV1(LPTree pRoot, Visitor visitor)
{

	LPTree pCur = pRoot;
	LPStack pStack = NULL;

	if (False == createStack(pStack, sizeof(LPTree))) {
		goto cleanup;
	}
	

	while (pCur || isStackEmpty(pStack) == False) {
		if (pCur) {
			do {
				pushToStack(pStack, &pCur);
				pCur = pCur->leftChild;
			} while (pCur);
		} 
		getTopOfStack(pStack, &pCur);
		popFromStack(pStack);
		
		
		visitor(pCur->data);
		pCur = pCur->rightChild;
	}


cleanup:
	if (pStack)
		destroyStack(&pStack);

}

void
inOrderNoRecursiveV2(LPTree pRoot, Visitor visitor)
{

	LPTree pCur = pRoot;
	LPStack pStack = NULL;

	if (False == createStack(pStack, sizeof(LPTree))) {
		goto cleanup;
	}
	



cleanup:
	if (pStack)
		destroyStack(&pStack);





}

void
postOrderNoRecursive(LPTree, Visitor);









