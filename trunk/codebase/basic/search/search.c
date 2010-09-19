#include "../../include/my.h"
#include "../../include/util.h"





void sortArray(int array[], int maxIndex);
int findInArray(int array[], int data, int maxIndex);




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

int findInArray(int array[], int data, int maxIndex)
{
	int i = maxIndex - 1;	
	array[0] = data;
	while (array[i] != data)
		i--;
	return i;
}



