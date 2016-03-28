

#include "common.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "vector.h"
#include "myMemory.h"
#include <string.h>


int partition(int * base, int start, int end);
void quickSort(int *base, int start, int end);


int partition(int *base, int start, int end)
{
	int val;
	int low, high;

	if (start+1 >= end)
		return start;

	val = base[start];
	
	low = start;
	high = end - 1;
	while (low < high) {
		while (base[high] >= val && high > low)
			--high;
		base[low] = base[high];
		while (base[low] <= val && low < high)
			++low;
		base[high] = base[low];

	}
	base[low] = val;
	return low;
}

void
quickSort(int *base, int start, int end)
{
	
	int pivot;

	if (start+1 >= end)
		return;

	pivot = partition(base, start, end);
	quickSort(base, start, pivot);
	quickSort(base, pivot+1, end);	
}

int main()
{

	FILE *fp = NULL;
	int temp;
	LPVector data = NULL;
	int *base = NULL;
	unsigned int size = 0;
	unsigned int align;
	unsigned int i,j;	
	bool Changed;
	int min, minIdx;


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


	quickSort(base, 0, size);
	
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

