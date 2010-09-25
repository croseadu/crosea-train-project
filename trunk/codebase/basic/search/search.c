#include "../../include/my.h"
#include "../../include/util.h"

void sortArray(int [], int);
int findInArray(int [], int , int);
void printArray(int [], int);
int binarySearch(int [], int , int);

int main()
{
	FILE *fp = NULL;
	int data, findData, arrayIndex, index;
	int *array;
	int sizeOfArray;

	if ((fp = fopen("temp.txt", "rt+")) == NULL)
	{
		Print(("Failed when open file\n"));
		exit(-1);
	}

	array = (int *)malloc(sizeof(int) * INIT_BUFFER_SIZE);
	if (NULL == array)
	{
		Print(("Out of Memory when allocate array"));
		exit(-1);
	}	
	sizeOfArray = INIT_BUFFER_SIZE;

	arrayIndex = 1;
	while (fscanf(fp, "%d", &data) != EOF)
	{	
		Print(("NextNumber is %d\n", data));
		if (arrayIndex >= sizeOfArray)
		{
			sizeOfArray += INCRE_BUFFER_SIZE;
			array = (int *)realloc(array, sizeof(int) * sizeOfArray);
			if (array == NULL)
			{
				Print(("Out of Memory when enlarge array buffer"));
				exit(-1);
			}
		}
		array[arrayIndex++] = data;
	}
	

	sortArray(array, arrayIndex);
	printArray(array, arrayIndex);
	printf("\nInput the data you want to search :");
	scanf("%d", &findData);
	index = findInArray(array, findData, arrayIndex);
	if (index <= 0)
	{
		printf("\nData(%d) isn't exist in Array.\n", findData);
	}
	else
	{
		printf("\nData(%d) is in Array[%d]\n", findData,index);
	}



	fclose(fp);	
	free(array);

	return 0;
}

void printArray(int array[], int maxIndex)
{
	int k = 0;
	int i = 1;
	for (;i < maxIndex; i++)
	{
		printf("%-5d%s", array[i], (++k%5)?"":"\n");
	}
	if (k%5)
		putchar('\n');
}

void sortArray(int array[], int maxIndex)
{
	int i, temp, j;

	for (i = 2; i < maxIndex; i++)
	{
		if (array[i] < array[i - 1])
		{
			array[0] = array[i];
			temp = array[i];
			for (j = i - 1; array[j] > temp; j--)
				array[j+1] = array[j];
			array[j+1] = temp;
		}
	}

}


int directSearch(int array[], int data, int maxIndex)
{
	int i = maxIndex - 1;	
	array[0] = data;
	while (array[i] != data)
		i--;
	return i;
}

int binarySearch(int array[], int data, int maxIndex)
{
	int start = 1, end = maxIndex;
	int middle;

	if (array[start] > data || array[end] < data)
		return 0;

	while (start <= end)
	{
		middle = (start + end)/2;
		if (array[middle] == data)
			return middle;
		if (array[middle] > data)
			end = middle - 1;
		else
			start = middle + 1;
	}
	return 0;

}

int findInArray(int array[], int data, int maxIndex)
{
	//return directSearch(array, data, maxIndex);
	return binarySearch(array ,data, maxIndex - 1);
}

STATUS buildTreeNode(LP_TREE_NODE *ppTreeNode, void *pData, unsigned int elementSize)
{
	*ppTreeNode = (LP_TREE_NODE)malloc(sizeof(TREE_NODE));
	if (NULL == *ppTreeNode)
	{

	}
}
void insertToBinaryTree(LP_TREE_NODE pRootNode, void *pData, unsigned int elementSize)
{
	

}

void buildBinaryOrderTree(int array[], int maxIndex, LP_TREE_NODE *ppTreeNode)
{
	LP_TREE_NODE pRootNode = NULL;		
	int i;

	for (i = 1; i < maxIndex; i++)
	{
		if (pRootNode == NULL)
		{
			buildTreeNode(&pRootNode,  &array[i], sizeof(array[i]));
		}
		else
		{		
			insertToBinaryTree(pRootNode, &array[i], sizeof(array[i]));
		}
	}
	*ppTreeNode = pRootNode;
}



