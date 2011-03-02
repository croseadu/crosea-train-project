#include "../include/listQueue.h"
#include "../include/singleList.h"

static unsigned int  queueElementSize;

STATUS createListQueue(LP_LIST_QUEUE *ppQueue, unsigned int elementSize)
{
  LP_LIST_QUEUE pQueue;
  STATUS status;
  
  pQueue = (LP_LIST_QUEUE)malloc(sizeof(LIST_QUEUE));
  if (NULL == pQueue)
    {
      printf ("Out Of Memory in Line %d, Function %s", __LINE__, __FUNCTION__);
      return OVERFLOW;
    }

  status = createSingleList(&pQueue->pListHead, elementSize);
  if (status != OK)
    {
      free(pQueue);
      return status;
    }

  queueElementSize = elementSize;
  *ppQueue = pQueue;
  return OK;
}

void destroyListQueue(LP_LIST_QUEUE pQueue)
{
  assert(pQueue && pQueue->pListHead);
  destroySingleList(pQueue->pListHead);
  free(pQueue);
}

BOOL isQueueEmpty(const LP_LIST_QUEUE pQueue)
{
  return isListEmpty(pQueue->pListHead);
}

S_RESULT compare_node(void *pFirst, void *pSecond)
{
  if (!memcmp(pFirst, pSecond, queueElementSize))
    return R_EQ;
  else
    return R_LT;
}

void getFromQueueHead(LP_LIST_QUEUE pQueue, void *pOut)
{
  getListBegin(pQueue->pListHead, pOut);
  deleteItemFromList(pQueue->pListHead, pOut,compare_node);
}

STATUS insertToQueueTail(LP_LIST_QUEUE pQueue, void *pIn)
{
  return insertToTail(pQueue->pListHead, pIn);
}
