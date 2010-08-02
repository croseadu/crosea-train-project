typedef struct _SingleList
{
	int data;
	struct _SingleList *pNextNode;
}SINGLE_LIST, *LP_SINGLE_LIST;


STATUS initList(LP_SINGLE_LIST *);
void destoryList(LP_SINGLE_LIST);
STATUS insertToListHead(LP_SINGLE_LIST, int);
STATUS insertToListTail(LP_SINGLE_LIST, int);
void bubbleSortList(LP_SINGLE_LIST);
void insertSortList(LP_SINGLE_LIST);
void selectSortList(LP_SINGLE_LIST);
void quickSortList(LP_SINGLE_LIST);
void reverseList(LP_SINGLE_LIST);
void printList(const LP_SINGLE_LIST);

