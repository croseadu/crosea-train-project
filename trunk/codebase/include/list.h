typedef struct _LIST_NODE
{
	void *pData;
	struct _LIST_NODE *pNextNode;
	struct _LIST_NODE *pPrevNode;
}LIST_NODE, *LP_LIST_NODE;

typedef struct _DOUBLE_LINK_LIST
{
	LIST_NODE *pStartNode;
	unsigned int elementSize;
}DOUBLE_LINK_LIST, *LP_DOUBLE_LINK_LIST;

STATUS initList(LP_DOUBLE_LINK_LIST *);
void destoryList(LP_DOUBLE_LINK_LIST);
BOOL isNodeExist(LP_DOUBLE_LINK_LIST, void *pData);
STATUS insertToTail(LP_DOUBLE_LINK_LIST, void *pData);
STATUS insertToHead(LP_DOUBLE_LINK_LIST, void *pData);
STATUS insertBeforeNode(LP_LIST_NODE pInsertPos, void *pData);
STATUS insertAfterNode(LP_LIST_NODE pInsertPos, void *pData);

