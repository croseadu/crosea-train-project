

#include "common.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "vector.h"
#include "myMemory.h"
#include <string.h>




void mergeSort(int *dst, int start, int end, int *shadow);


void
merge(int *dst, int *src, int start, int end)
{
	int middle = (start+end)/2;

	int i = start;
	int j = middle+1;
	int cur = start;
	while (i <= middle && j <= end) {
		if (src[i] <= src[j]) {
			dst[cur] = src[i++];
		} else {
			dst[cur] = src[j++];
		}
		++cur;
	}
	while (i <= middle) {
		dst[cur++] = src[i++];
	}
	while (j <= end) {
		dst[cur++] = src[j++];
	}

}

void mergeSort(int *base, int start, int end, int *shadow)
{
	int middle;

	int i;
	if (start >= end)
		return;


	middle = (start+end)/2;
	mergeSort(base, start, middle,shadow);
	mergeSort(base, middle+1, end, shadow);

	merge(shadow, base, start, end);	
	for (i = start; i <= end; ++i)
		base[i] = shadow[i];
}


/*
void mergeSort2(int *dst, int *src, int start, int end, int *swap);
void merge2(int *dst, int *src, int start, int end);

void
mergeSort2(int *dst, int *src, int start, int end, int *swap)
{
	int middle;
	if (start > end)
		return;
	if (start == end) {{
		dst[start] = src[start];
		return;
	}
	
	middle = (start+end)/2;
	//mergeSort2(swap, src, start, middle, )


}
*/

int main()
{

	FILE *fp = NULL;
	int temp;
	LPVector data = NULL;
	int *base = NULL, *shadow = NULL;
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
		
	shadow = (int *)myAlloc(size * sizeof(int));
	if (NULL == shadow) {
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

	mergeSort(base, 0, size-1, shadow);

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

	if (base)
		myFree(base);
	if (shadow)
		myFree(shadow);

	return 0;
}

