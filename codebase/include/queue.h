

typedef struct _QUEUE
{
	char *pData;
	int head;
	int tail;
	int maxElements;
	int elementSize;
}QUEUE, *LP_QUEUE;


STATUS createQueue(LP_QUEUE *ppQueue, unsigned int elementSize, unsigned int maxElements);
void destoryQueue(LP_QUEUE pQueue);
BOOL isQueueEmpty(LP_QUEUE pQueue);
STATUS getFromHead(LP_QUEUE pQueue, char *data);
STATUS insertToTail(LP_QUEUE pQueue, char *data);
