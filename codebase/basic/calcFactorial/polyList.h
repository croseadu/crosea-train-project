typedef struct _DoubleList
{
// 1+2x+3x*x+6x*x*x ----(1, 0), (2, 1), (3,2), (6,3)
	int factor;
	unsigned int nIndex;
	struct _DoubleList *pNextNode;
	struct _DoubleList *pPrevNode;
}DOUBLE_LIST, *LP_DOUBLE_LIST;


STATUS initList(LP_DOUBLE_LIST *);
void destoryList(LP_DOUBLE_LIST);
void cleanList(LP_DOUBLE_LIST );
STATUS insertToPolyList(LP_DOUBLE_LIST, int, int);
void printPolyList(const LP_DOUBLE_LIST);
STATUS setMulList(LP_DOUBLE_LIST , unsigned int k);
STATUS mulSelfList(LP_DOUBLE_LIST ,LP_DOUBLE_LIST );

