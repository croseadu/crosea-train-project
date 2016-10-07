


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
preOrderNoRecursive(LPTree);
void
inOrderNoRecursiveV1(LPTree);
void
inOrderNoRecursiveV2(LPTree);
void
postOrderNoRecursive(LPTree);



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








