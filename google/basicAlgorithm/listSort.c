#include "../include/singleList.h"


void printValue(void *pData)
{
	printf("%5d", *(int *)pData);
}

void modAndPrintValue(void *pData)
{
	printf("%5d", (*(int *)pData)%5);
}

int main()
{
	int data;
	FILE *pInputFile;
	LP_SINGLE_LIST_NODE pListHead = NULL;
	VISIT_FUNC visit = NULL;

		

	if (createSingleList(&pListHead, sizeof(int)))
	{
		printf("Create List Failed\n");
		exit(-1);
	}


	pInputFile = fopen("inputData.txt", "r");
	if (NULL == pInputFile)
	{
		printf("Cannot Open File : inputData.txt\n");
		exit(-1);
	}


	while(fscanf(pInputFile, "%d", &data) != EOF)
	{
		if (insertToTail(pListHead, &data))
		{
			printf("Insert To List Failed\n");
			exit(-1);
		}
	}
	if (!feof(pInputFile))
	{
		printf("Error in Input File\n");
		exit(-1);
	}
	fclose(pInputFile);

	putchar('\n');
	listTraverse(pListHead, modAndPrintValue);
	putchar('\n');

	destroySingleList(pListHead);
	
	return 0;
}
