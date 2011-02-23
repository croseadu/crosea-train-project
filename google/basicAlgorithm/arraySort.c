#include "../include/common.h"

#define INIT_ARRAY_SIZE 10
#define INCREMENT_ARRAY_SIZE 5

int main()
{
	int data;
	FILE *pInputFile;
	int *array = NULL;
	int curIndex, maxSize;
	
	pInputFile = fopen("inputData.txt", "r");
	if (NULL == pInputFile)
	{
		printf("Cannot Open File : inputData.txt\n");
		exit(-1);
	}

	array = (int *)malloc(INIT_ARRAY_SIZE * sizeof(int));
	if (NULL == array)
	  {
	    printf("Out of Memory in line %d", __LINE__);
	    exit(-1);
	  }
	curIndex = 1;
	maxSize = INIT_ARRAY_SIZE;

	while(fscanf(pInputFile, "%d", &data) != EOF)
	{
	  if (curIndex >= maxSize)
	    {
	      array = (int *) realloc(array, (maxSize+INCREMENT_ARRAY_SIZE)*sizeof(int));
	      if (NULL == array)
		{
		  printf("Out of Memory in line %d", __LINE__);
		  exit(-1);
		}
	      maxSize += INCREMENT_ARRAY_SIZE;
	    }
	  
	  array[curIndex++] = data;

	}
	if (!feof(pInputFile))
	{
		printf("Error in Input File\n");
		exit(-1);
	}
	fclose(pInputFile);

	printArray(array, curIndex);

	//bubbleSort(array, curIndex);
	//insertSort(array, curIndex);
	//shellSort(array, curIndex);
	//selectSort(array, curIndex);
	//quickSort(array, 1, curIndex-1);
	//mergeSort(array, array, 1, curIndex-1);
	heapSort(array, curIndex);
      
	printf("\nAfter Sort:\n");
	printArray(array, curIndex);
	free(array);
	return 0;
}

void bubbleSort(int array[], int max)
{
  int i, j;
  BOOL bChanged;
  int temp;
  printf("\nStart Bubble Sort\n");
  for (i = max-1; i > 1; i--)
    {
      bChanged = FALSE;
      for (j = 1; j < i; j++)
	{
	  if (array[j] > array[j+1])
	    {
	      temp = array[j];
	      array[j] = array[j+1];
	      array[j+1] = temp;
	      bChanged = TRUE;
	    }
	}
      if (bChanged == FALSE)
	break;
    }
}

void insertSort(int array[], int max)
{
  int i, j, temp;

  printf("\nStart Insert Sort\n");
  for (i = 2; i < max; i++)
    {
      if (array[i] < array[i-1])
	{
	  temp = array[i];
	  array[0] = temp;
	  for (j = i-1; array[j]>temp; j--)
	    {
	      array[j+1] = array[j];
	    }
	  array[j+1] = temp;
	}
    }
}

void shellSort(int array[], int max)
{
  int delta[3] = {5, 3, 1};
  int i, j ,k, d, temp;

  printf("\nStart Shell Sort\n");
  for (i = 0; i < 3; i++)
    {
      d = delta[i];
      for (j = 1+d; j < max; j++)
	{
	  if (array[j] < array[j-d])
	    {
	      temp = array[j];
	      for (k = j-d; k > 0 && array[k] > temp; k-=d)
		{
		  array[k+d] = array[k];
		}
	      array[k+d] = temp;
	    }

	}

    }
}

static int selectMinimal(int array[], int start, int end)
{
  int i,min, minIndex;

  minIndex = start;
  min = array[start];
  
  for (i = start+1; i <= end; i++)
    {
      if (array[i] < min)
	{
	  minIndex = i;
	  min = array[i];
	}
    }

  return minIndex;
}

void selectSort(int array[], int max)
{
  int i, j, temp;

  printf("\nStart Select Sort\n");
  for (i = 1; i < max-1; i++)
    {
      j = selectMinimal(array, i, max-1);
      if (i != j)
	{
	  temp = array[i];
	  array[i] = array[j];
	  array[j] = temp;
	}
    }
}

static int partion(int array[], int start, int end)
{
  int low = start;
  int high = end;
  int temp = array[start];

  while(low < high)
    {
      while (high > low && array[high] >= temp)
	high--;
      array[low] = array[high];
      while (high > low && array[low] <= temp)
	low++;
      array[high] = array[low];
    }

  array[low] = temp;
  return low;
}

void quickSort(int array[], int start, int end)
{
  int pivot;

  printf("\nStart Quick Sort\n");
  if (start >= end)
    return;

  pivot = partion(array, start, end);
  quickSort(array, start, pivot -1);
  quickSort(array, pivot+1, end);
}

static void heapAdjust(int array[], int start, int end)
{
  int i = start, j;
  int temp = array[i];

  for(; 2*i <= end;)
    {
      j = 2*i;
      if (j+1<=end && array[j+1] > array[j])
	j++;
      if (array[j] > temp)
	array[i] = array[j];
      else
	break;
      i = j;
    }
  array[i] = temp;
}

void heapSort(int array[], int max)
{
  int i, temp;

  printf("\nStart Heap Sort\n");
  for (i = (max-1)/2; i >=1; i--)
    heapAdjust(array, i, max-1);

  for (i = max-1; i > 1; i--)
    {
      temp = array[i];
      array[i] = array[1];
      array[1] = temp;
      heapAdjust(array, 1, i-1);
    }
}

static void merge(int dst[], int src[], int start, int end)
{
  int middle = (start + end)/2;
  int i, j, index;
  i = start;
  j = middle+1;
  index = start;
  while (i <= middle && j<= end)
    {
      if (src[i] < src[j])
	dst[index++] = src[i++];
      else
	dst[index++] = src[j++];
    }

  while (i<=middle)
    dst[index++] = src[i++];
  while (j <= end)
    dst[index++] = src[j++];
}

void mergeSort(int dst[], int src[],int start, int end)
{
  int *tempArray;
  int middle = (start + end)/2;

  if (end == start)
    {
      dst[start] = src[start];
      return;
    }
  else if (end < start)
    return;

  printf("\nStart Merge Sort\n");
  tempArray = (int *)malloc((end+1)*sizeof(int));
  if (NULL == tempArray)
    {
      printf("Out of Memory in line %d, function %s", __LINE__, __FUNCTION__);
      exit(-1);
    }
  mergeSort(tempArray, src, start, middle);
  mergeSort(tempArray, src, middle+1, end);
  merge(dst, tempArray, start, end);
  free(tempArray);
}

void printArray(int array[], int max)
{
  int i;

  for (i = 1; i < max; i++)
    printf("%4d%c", array[i], i%8?' ':'\n');
  putchar('\n');
}
