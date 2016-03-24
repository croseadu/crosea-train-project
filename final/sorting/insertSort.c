
#include "common.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "vector.h"
#include "myMemory.h"
#include <string.h>



int main()
{

	FILE *fp = NULL;
	int temp;
	LPVector data = NULL;
	int *base = NULL;
	unsigned int size = 0;
	unsigned int align;
	int i,j;	
	bool Changed;


	if ((fp = fopen("input.txt", "r")) == NULL) {
		printf("unable to open input file.");
		exit(-1);
	}

	if (False == createVector(&data, sizeof(int))) {
		goto cleanup;
	}

	

	while(fscanf(fp, "%d", &temp) > 0) {
		pushBackToVector(data, &temp);
	}
	
	size = sizeOfVector(data);
	base = (int *)myAlloc(size * sizeof(int));
	if (NULL == base) {
		printf("Out Of Memory!");
		goto cleanup;
	}
		
	memcpy(base, dataOfVector(data), size * sizeof(int));

	printf("\nData in file:\n");
	align = 0;
	
	for (i = 0; i < size; ++i) {
		printf("%5d", *(int *)(base + i));
		++align;
		if ((align%5) == 0 ) putchar('\n');
	}
	if (align % 5) putchar('\n');

	for (i = 1; i < size; ++i) {
		if (base[i] >= base[i-1])
			continue;
		temp = base[i];
		for (j = i - 1; j >= 0; --j) {
			if (base[j] <= temp)
				break;
			base[j+1] = base[j];
		}
		base[j+1] = temp;
	
	}


	printf("\nAfter Sort:\n");
	align = 0;
	
	for (i = 0; i < size; ++i) {
		printf("%5d", *(int *)(base + i));
		++align;
		if ((align%5) == 0 ) putchar('\n');
	}
	if (align % 5) putchar('\n');
cleanup:

	if (fp)
		fclose(fp);

	if (data)
		destroyVector(&data);

	return 0;
}

