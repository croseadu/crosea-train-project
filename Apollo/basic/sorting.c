#include "vector.h"
#include "memory.h"

#include "utils.h"


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

void insertSorting(int *array, int n);
void selectionSorting(int *array, int n);

void quickSorting(int *array, int n);
void shellSorting(int *array, int n);
void heapSorting(int *array, int n);
void radixSorting(int *array, int n);

void mergeSorting(int *array, int n);

int main()
{
	LPVector pVector = NULL;
	FILE *fp;
	int temp;
	int *array = NULL;
	int n = 0;


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
	
	printf("\nInput Array:");
	dumpVector(pVector," ", 5);

	array = (int *)getDataFromVector(pVector);
	n = getSizeOfVector(pVector);

	printf("After Sorting:");

	//insertSorting(array,n);
	//selectionSorting(array, n);
	//quickSorting(array, n);
	//heapSorting(array, n);
	//shellSorting(array, n);
	mergeSorting(array, n);
	dumpVector(pVector, " ", 5);

lexit:
	destroyVector(&pVector);


	return 0;

}


void insertSorting(int *array, int n)
{
	int i, j, temp;

	if (n <= 1)
		return;


	for (i = 1; i < n; ++i) {
		if (array[i] >= array[i-1])
			continue;

		temp = array[i];
		for (j = i -1; j >= 0 && array[j] > temp; --j) {
			array[j+1] = array[j];
		}
		array[j+1] = temp;
	}

}

static int
selectMin(int *array, int start, int end)
{
	int minIdx = start;
	int i;
	int minVal = array[minIdx];
	for (i = start + 1; i < end; ++i) {
		if (array[i] < minVal) {
			minIdx = i;
			minVal = array[i];
		}
	}
	

	return minIdx;
}

void selectionSorting(int *array, int n)
{
	int i;
	int minIdx;
	int temp;

	for (i = 0; i < n -1; ++i) {
		minIdx = selectMin(array, i, n);
		if (minIdx != i) {
			temp = array[i];
			array[i] = array[minIdx];
			array[minIdx] = temp;
		}
	}	

}

static int
partition(int *array, int start, int end)
{
	int low = start;
	int high = end;
	int key = array[start];

	while (low < high) {
		while (high > low && array[high] >= key)
			--high;
		array[low] = array[high];

		while (low < high && array[low] <= key)
			++low;
		array[high] = array[low];
	}

	array[low] = key;

	return low;
}


static void
quickSort(int *array, int start, int end)
{
	if (start >= end)
		return;

	int pivot = partition(array, start, end);
	quickSort(array, start, pivot - 1);
	quickSort(array, pivot + 1, end);
}

void quickSorting(int *array, int n)
{

	quickSort(array, 0, n - 1);

}

void shellSorting(int *array, int n)
{
	int delta[] = {5, 3, 1};
	int d;
	int i, j;
	int step, key;

	for (d = 0; d < sizeof(delta)/sizeof(delta[0]); ++d) {
		step = delta[d];

		for (i = 1; i < n; ++i) {
			if (i - step < 0 || array[i - step] <= array[i]) {
				continue;
			}
			key = array[i];

			for (j = i - step; j >= 0 && array[j] > key; j -= step) {
				array[j + step] = array[j];
			}
			array[j + step] = key;
		}
	}
}


void
heapAdjust(int *array, int start, int end)
{
	int key = array[start];
	
	int i;
	int j;


	for (i = start, j = i * 2; j <= end;) {
		if (j + 1 <= end && array[j+1] > array[j]) {
			++j;
		}

		if (array[j] <= key)
			break; 

		array[i] = array[j];
		i = j;
		j = i << 1;
	}

	array[i] = key;
	
}

void heapSorting(int *array, int n)
{
	int i;
	int temp;
	
	for (i = (n - 1)/2; i >= 0; --i) {
		heapAdjust(array, i, n - 1);
	}

	for (i = n - 1; i > 0; --i) {
		temp = array[i];
		array[i] = array[0];
		array[0] = temp;
		heapAdjust(array, 0, i - 1);
	}

}

void merge(int *dst, int *src, int start, int end)
{
	int m;
	int i, j;
	int idx = start;
	

	m = (start + end) / 2;

	i = start;
	j = m + 1;

	while (i <= m && j <= end) {
		if (src[i] <= src[j]) {
			dst[idx++] = src[i++];
			
		} else {
			dst[idx++] = src[j++];
		}
	}
	while (i <= m) {
		dst[idx++] = src[i++];
	}
	while (j <= end) {
		dst[idx++] = src[j++];
	}

}

void mergeSort(int *array, int *temp, int start, int end)
{


	int m = (start + end)/2;
	if (start >= end)
		return;

	mergeSort(array, temp, start, m);
	mergeSort(array, temp,m+1, end);

	merge(temp, array, start, end);
	memcpy(array + start, temp + start,  (end - start + 1) * sizeof(int));
}


void mergeSorting(int *array, int n)
{
	int * temp;

	temp = myAlloc(n * sizeof(int));
	if (NULL == temp) {
		return;
	}
	mergeSort(array, temp, 0, n-1);
	myFree(temp);
}


void radixSorting(int *array, int n)
{

}









