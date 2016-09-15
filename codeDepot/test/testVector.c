

#include "vector.h"
#include "utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>


BOOL
mod3(const void *data)
{
	int val = *(int *)data;
	return ( val % 3 == 0 ) ? True : False;
}

int main()
{
	FILE *fp = NULL;
	LPVector pVector = NULL;
	int temp;



	if (NULL == (fp = fopen("input.txt", "r"))) {
		DBG(printf("Failed to open input file\n"));
		goto Fail;
	}
	if (False == createVector(&pVector, sizeof(int), lessInt, printInt)) {
		DBG(printf("Failed to vector!\n"));
		goto Fail;
	}

	
	while (fscanf(fp, "%d", &temp) > 0) {
		pushFrontInVector(pVector, &temp);
		//pushBackInVector(pVector, &temp);

	}

	printf("\nCreated Vector:\n");
	printVector(pVector);


	sortVector(pVector);
	printf("after Sorted:");
	printVector(pVector);

	while(isVectorEmpty(pVector) == False) {
		popFrontInVector(pVector, &temp);
	}
	
Fail:

	if (NULL != fp)
		fclose(fp);

	if (NULL != pVector)
		destroyVector(&pVector);


}
