typedef struct _TREE_NODE
{
	char *pData;
	struct _TREE_NODE *pLeftChild;
	struct _TREE_NODE *pRightChild;
}TREE_NODE, *LP_TREE_NODE;

void preOrderTraverse(LP_TREE_NODE pTreeNode, void (*pFn)(LP_TREE_NODE));
void postOrderTraverse(LP_TREE_NODE pTreeNode, void (*pFn)(LP_TREE_NODE));
void inOrderTraverse(LP_TREE_NODE pTreeNode, void (*pFn)(LP_TREE_NODE));

void preOrderUseStack(LP_TREE_NODE pTreeNode, void (*pFn)(LP_TREE_NODE), LP_STACK pStack);
void inOrderUseStack(LP_TREE_NODE pTreeNode, void (*pFn)(LP_TREE_NODE), LP_STACK pStack);
void hierarchyTraverse(LP_TREE_NODE pRootNode,void (*pFn)(LP_TREE_NODE), LP_QUEUE pQueue);
