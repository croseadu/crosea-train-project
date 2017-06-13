
#include "vector.h"
#include "utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>




BOOL mod3(const void *data)
{
	int val = *(const int *)data;
	return val % 3 == 0 ? True : False;
}

BOOL mod4(const void *data)
{
	int val = *(const int *)data;
	return val % 4 == 0 ? True : False;
}

int main()
{

	LPVector pVector = NULL;
	FILE *fp;
	int temp;
	VectorIter it;	

	if (False == createVector(&pVector,
					  sizeof(int),
					  intPrinter,
					  intLess)) {
		exit(-1);
	}

	
	if ( NULL == ( fp = fopen("input.txt", "r") )) {
		goto lexit;
	}
	

	while(fscanf(fp, "%d", &temp) != EOF) {
		printf("\nInsert %d to Vector:", temp);
		pushBackInVector(pVector, &temp);

	}

	fclose(fp);
	
	printf("\nVector:");
	dumpVector(pVector," ", 5);


	sortVector(pVector);
	printf ("\nVector after sorting");
	dumpVector(pVector, " ", 5);

	removeIfInVector(pVector, mod3);
	printf ("\nVector after remove mod3");
	dumpVector(pVector, " ", 5);

	temp = 5;
	it = findInVector(pVector, &temp);
	eraseFromVector(pVector, it);
	printf ("\nVector after remove one 5");
	dumpVector(pVector, " ", 5);


	it = findIfInVector(pVector, mod4);
	eraseFromVector(pVector, it);
	printf ("\nVector after remove one mod4");
	dumpVector(pVector, " ", 5);

	temp = 1;
	removeValFromVector(pVector, &temp);
	printf ("\nVector after remove all 1");
	dumpVector(pVector, " ", 5);


lexit:

	destroyVector(&pVector);

	return 0;
}
