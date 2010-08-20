#include "../../include/my.h"
#include "../../include/util.h"



int main()
{
	int maxElements, curIndex, data;
	int *array = NULL, arrayIndex, sizeOfArray;
	char *inputBuffer, c;

	inputBuffer = (char *)malloc(sizeof(char) * INIT_BUFFER_SIZE);
	if (NULL == inputBuffer)
	{
		Print(("Out of Memory when allocate inputBuffer"));
		exit(-1);
	}	
	maxElements = INIT_BUFFER_SIZE;

	c = getchar();
	curIndex = 0;
	while (c != '\n')
	{
		inputBuffer[curIndex++] = c;
		c = getchar();

		if (curIndex >= maxElements - 1)
		{
			maxElements += INCRE_BUFFER_SIZE;
			inputBuffer = (char *)realloc(inputBuffer, sizeof(char) * maxElements);
			if (inputBuffer == NULL)
			{
				Print(("Out of Memory when enlarge input buffer"));
				exit(-1);
			}
		}
	}
	inputBuffer[curIndex] = '\0';

	array = (int *)malloc(sizeof(int) * INIT_BUFFER_SIZE);
	if (NULL == array)
	{
		Print(("Out of Memory when allocate array"));
		exit(-1);
	}	
	sizeOfArray = INIT_BUFFER_SIZE;

	curIndex = 0;
	arrayIndex = 1;
	while ((status = getNextNumber(inputBuffer, &curIndex, &data)) == OK)
	{
		Print(("NextNumber is %d\n", data));
		if (arrayIndex >= sizeOfArray)
		{
			sizeOfArray += INCRE_BUFFER_SIZE;
			array = (char *)realloc(array, sizeof(int) * sizeOfArray);
			if (array == NULL)
			{
				Print(("Out of Memory when enlarge array buffer"));
				exit(-1);
			}
		}
		array[arrayIndex++] = data;
	}
	free(inputBuffer);

	printf("Input Array is:")
	printArray(array, arrayIndex);
	
	bubbleSort(array, arrayIndex);
	printf("After Sort, Array is:");
	printArray(array, arrayIndex);


	return 0;
}

void printArray(int array, int maxIndex)
{

	for ()


}


