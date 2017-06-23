

#include "queue.h"
#include "utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>



int main()
{

	LPQueue pQueue = NULL;
	FILE *fp;
	int temp;

	if (False == createQueue(&pQueue,
					  sizeof(int),
					  intPrinter)) {
		exit(-1);
	}

	
	if ( NULL == ( fp = fopen("input.txt", "r") )) {
		goto lexit;
	}
	

	while(fscanf(fp, "%d", &temp) != EOF) {
		enQueue(pQueue, &temp);

	}

	fclose(fp);
	

	while(False == isQueueEmpty(pQueue)) {
		deQueue(pQueue, &temp);
		printf("\nDeque: %d ", temp);
	}

lexit:

	destroyQueue(&pQueue);

	return 0;
}
