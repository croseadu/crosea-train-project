typedef struct _LIST_NODE
{
	struct _LIST_NODE *pNextNode;
	struct _LIST_NODE *pPrevNode;
	char 		pData[1];
}LIST_NODE, *LP_LIST_NODE;

typedef struct _DOUBLE_LINK_LIST
{
	LIST_NODE *pStartNode;
	unsigned int elementSize;
}DOUBLE_LINK_LIST, *LP_DOUBLE_LINK_LIST;

STATUS initList(LP_DOUBLE_LINK_LIST *, unsigned int);
void destoryList(LP_DOUBLE_LINK_LIST);
STATUS insertToListTail(LP_DOUBLE_LINK_LIST, void *);
STATUS insertToListHead(LP_DOUBLE_LINK_LIST, void *);
STATUS insertBeforeNode(LP_DOUBLE_LINK_LIST, LP_LIST_NODE , void *);
STATUS insertAfterNode(LP_DOUBLE_LINK_LIST, LP_LIST_NODE , void *);
void visitList(LP_DOUBLE_LINK_LIST pList, void (*fn)(void *pData, void *pArg), void *pArg);
LP_LIST_NODE findNodeInList(LP_DOUBLE_LINK_LIST pList, void *pKeyData, BOOL (*cmp)(void *, void *));

