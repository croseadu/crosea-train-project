#include "../../include/my.h"
#include "../../include/list.h"
#include "../../include/util.h"

int main()
{
	STATUS status;
	int data;
	int curIndex, maxElements;
	char *inputBuffer;

	inputBuffer = (char *)malloc(sizeof(char) * INIT_BUFFER_SIZE);
	if (NULL == inputBuffer)
	{
		Print("Out of Memory when allocate inputBuffer");
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
				Print("Out of Memory when enlarge input buffer");
				exit(-1);
			}
		}
	}
	inputBuffer[curIndex] = '\0';
	
	initList(&list);	

	curIndex = 0;
	while ((status = getNextNumber(inputBuffer, &curIndex, &data)) == Ok)
	{
		insertToList(data, list);
	}

	if (status == ERROR)
	{
		Print("error in input \n");
		free(inputBuffer);
		exit(-1);
	}
	
	Print("Input List is :");
	printList(list);	

	free(inputBuffer);
	
	return 0;
}
