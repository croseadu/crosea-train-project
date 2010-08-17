typedef struct _SingleList
{
// 1+2x+3x*x+6x*x*x ----(1, 0), (2, 1), (3,2), (6,3)
	int factor;
	unsigned int nIndex;
	struct _SingleList *pNextNode;
}SINGLE_LIST, *LP_SINGLE_LIST;


STATUS initList(LP_SINGLE_LIST *);
void destoryList(LP_SINGLE_LIST);
STATUS insertToPolyList(LP_SINGLE_LIST, int, int);
void printPolyList(const LP_SINGLE_LIST);

