



int	initCircularQueue(LPCIRCURLARQUEUE *ppCircularQueue)
{
	(*ppCircularQueue) = (LPCIRCULARQUEUE)malloc(sizeof(CIRCULARQUEUE));
	if (!*ppCircularQueue)
	{
		return 0;
	}
	(*ppCircularQueue)->base = NULL;
	(*ppCircularQueue)->base = (int *)malloc(sizeof(int)*INIT_SIZE);
	if (!*ppCircularQueue)
	{
		return 0;
	}
	(*ppCircularQueue)->front = 0;
	(*ppCircularQueue)->end = 0;
	(*ppCircularQueue)->length = INIT_SIZE;
	return 1;
}

int destroyCircularQueue(LPCIRCULARQUEUE pCircularQueue)
{
	if (pCircularQueue)
	{
		if (pCircularQueue->base)
			free(pCircularQueue->base);
		free(pCircularQueue);
	}
	return 1;
}

int getLengthOfCircularQueue(const LPCIRCULARQUEUE pCircularQueue)
{
	if (pCircularQueue)
		return pCircularQueue->end - pCircularQueue->front;
}

int insertCircularQueue(LPCIRCULARQUEUE pCircularQueue, const int data)
{
	if (!pCircularQueue || !pCircularQueue->base)
		return 0;
	if (((end+1) % pCircularQueue->front) == pCircularQueue->front)
		return 0;
	pCircularQueue->base[pCircularQueue->end] = data;
	pCircularQueue->end = (pCircularQueue->end + 1) % pCircularQueue->length;
	return 1;
}

int	deleteCircularQueue(LPCIRCULARQUEUE pCircularQueue, int * pData)
{
	if (!pCircularQueue || pCircularQueue->end == pCircularQueue->front)
		return 0;
	*pData = pCircularQueue->base[pCircularQueue->front];
	pCircularQueue->front = (pCircularQueue->front + 1) % pCircularQueue->length;
	return 1;
}

 