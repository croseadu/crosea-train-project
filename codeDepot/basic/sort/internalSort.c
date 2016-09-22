#include "memory.h"
#include "utils.h"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>


void
printArray(int arr[], int size)
{
#define MAX_PER_LINE 5
	int count = 0;
	int i;
	for (i = 0; i < size; ++i) {
		++count;
		printf("%5d", arr[i]);
		if (count % MAX_PER_LINE == 0)
			putchar('\n');
	}
	if (count % MAX_PER_LINE)
		putchar('\n');
#undef MAX_PER_LINE 
}



void
bubbleSort(int arr[], int size);
void
insertionSort(int arr[], int size);
void
selectionSort(int arr[], int size);
void
mergeSort(int arr[], int size);
void
quickSort(int arr[], int size);
void
shellSort(int arr[], int size);
void
heapSort(int arr[], int size);


int dst[4096];


int main()
{


	FILE *fp = NULL;
	int array[4096];
	int size = 0;
	int num;

	if (NULL == (fp = fopen("input.txt", "r"))) {
		goto cleanup;
	}


	while (fscanf(fp, "%d", &num) > 0) {
		array[size++] = num;
	}

	printf("\nInput Array:\n");
	printArray(array, size);
	

	selectionSort(array, size);


	printf("\nAfter Sorted:\n");
	printArray(array, size);
	



cleanup:
	if (fp)
		fclose(fp);


	return 0;
}


void
bubbleSort(int arr[], int size)
{
	BOOL changed = False;
	int i;
	int j;
	int temp;

	i = size -1;
	for(;i > 0; --i)
	{
		changed = False;
		for(j = 0; j < i; ++j) {
			if (arr[j] > arr[j+1]) {
				temp = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = temp;
				changed = True;
			}
		
		}

		if (changed == False)
			break;
	}

}

void
insertionSort(int arr[], int size)
{
	int i, j, cur;

	for (i = 1; i < size; ++i) {
		j = i - 1;
		if (arr[i] < arr[j]) {
			cur = arr[i];

			while(j >= 0 && arr[j] > cur) {
				arr[j+1] = arr[j];
				--j;
			}
			arr[j+1] = cur;

		}

	}

}

int 
selectMin(int arr[], int start, int end)
{
	int minIdx, minVal;

	minIdx = start;
	minVal = arr[start];

	++start;
	while(start < end) {
		if (arr[start] < minVal) {
			minVal = arr[start];
			minIdx = start;
		}
		++start;

	}

	return minIdx;
}

void
selectionSort(int arr[], int size)
{
	int i, j, minIdx;
	int temp;

	for (i = 0; i < size - 1; ++i) {
		minIdx = selectMin(arr, i, size);
		if (minIdx != i) {
			temp = arr[i];
			arr[i] = arr[minIdx];
			arr[minIdx] = temp;
		}

	}

}

int
partition(int arr[], int start, int end)
{
	int low, high;
	int val = arr[start];

	low = start;
	high = end -1;
	while (low < high) {
		while(high > low && arr[high] >= val)
			--high;
		arr[low] = arr[high];
		while(low < high && arr[low] <= val)
			++low;
		arr[high] = arr[low];

	}
	
	arr[low] = val;

	return low;
}



void
quickSortImpl(int arr[], int start, int end)
{
	int pivot;
	if (start + 1 >= end)
		return;

	pivot = partition(arr, start, end);
	quickSortImpl(arr, start, pivot);
	quickSortImpl(arr, pivot + 1, end);
}



void
quickSort(int arr[], int size)
{
	quickSortImpl(arr, 0, size);

}


void
shellSort(int arr[], int size)
{
	int delta[] = {5, 3 ,1};
	int step;
	int i, j;
	int d;
	int cur;

	for (d = 0; d < 3; ++d) {
		step = delta[d];
		for(i = step; i < size; ++i) {
			j = i - step;
			if (arr[i] < arr[j]) {
				cur = arr[i];
				while (j >= 0 && arr[j] > cur) {
					arr[j+step] = arr[j];
					j -= step;
				}
				arr[j+step] = cur;

			}
		}

	}
}

void heapAdjust(int arr[], int start, int size)
{
	int i, j;
	int cur  = arr[start];
	
	for(i = start, j = 2 * start; j < size; ) {
		j = 2 * i;
		if (j+1 < size && arr[j+1] > arr[j])
			++j;
		if (arr[j] <= cur)
			break;

		arr[i] = arr[j];
		i = j;
		j = 2 * i;

	}

	arr[i] = cur;
}

void
heapSort(int arr[], int size)
{
	int i;
	int temp;

	if (size <= 1)
		return;


	for (i = size / 2; i >= 0; --i) {
		heapAdjust(arr, i, size);
	}
	
	
	for (i = size -1 ; i > 0; --i) {
		temp = arr[i];
		arr[i] = arr[0];
		arr[0] = temp;
		heapAdjust(arr, 0, i);
	
	}

}

void
merge(int arr[], int firstBegin, int firstEnd, int secondBegin, int secondEnd, int dst[])
{

	int i = firstBegin;
	int j = secondBegin;
	int idx = firstBegin;

	while (i < firstEnd && j < secondEnd) {
		if (arr[i] <= arr[j]) {
			dst[idx++] = arr[i++];

		} else {
			dst[idx++] = arr[j++];
		}
	}
	
	while (i < firstEnd) {
		dst[idx++] = arr[i++];
	}
	while (j < secondEnd) {
		dst[idx++] = arr[j++];
	}
}

void
mergeSortImpl(int arr[], int begin, int end)
{
	int medium;
	int i;

	if (begin + 1 >= end)
		return;

	
	medium = (begin + end) / 2;
	mergeSortImpl(arr, begin, medium);
	mergeSortImpl(arr, medium, end);

	merge(arr, begin, medium, medium, end, dst);
	for (i = begin; i < end; ++i)
		arr[i] = dst[i];
	
}


void
mergeSort(int arr[], int size)
{
	mergeSortImpl(arr, 0, size);

}

