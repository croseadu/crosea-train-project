


typedef struct _Tree
{
	char data;
	struct _Tree *leftChild;
	struct _Tree *rightChild;
}Tree, *LPTree;





void
preOrder(LPTree);
void
inOrder(LPTree);
void
postOrder(LPTree);



void
preOrderNoRecursive(LPTree);
void
inOrderNoRecursiveV1(LPTree);
void
inOrderNoRecursiveV2(LPTree);
void
postOrderNoRecursive(LPTree);



LPTree
createTree(const char *);

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
		
	}
}

