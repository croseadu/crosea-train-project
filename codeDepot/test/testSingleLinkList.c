
#include "singleLinkList.h"
#include "utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>


BOOL
mod3(const void *data)
{
	int val = *(int *)data;
	return ( val % 3 == 0 ) ? True : False;
}

int main()
{
	FILE *fp = NULL;
	LPSingleLinkList pList = NULL;
	int temp;



	if (NULL == (fp = fopen("input.txt", "r"))) {
		DBG(printf("Failed to open input file\n"));
		goto Fail;
	}
	if (False == createSingleLinkList(&pList, sizeof(int), lessInt, printInt)) {
		DBG(printf("Failed to create single link list!\n"));
		goto Fail;
	}

	
	while (fscanf(fp, "%d", &temp) > 0) {
		insertToHeadOfSingleLinkList(pList, &temp);

	}

	printf("\nCreated List:");
	printSingleLinkList(pList);

	reverseSingleLinkList(pList);
	printf("after reverser:");
	printSingleLinkList(pList);

	sortSingleLinkList(pList);
	printf("after Sorted:");
	printSingleLinkList(pList);

	temp = 2;
	removeInSingleLinkList(pList, &temp);
	printf("after remove value 2:");
	printSingleLinkList(pList);

	removeIfInSingleLinkList(pList, mod3);
	printf("After remove mod3: ");
	printSingleLinkList(pList);	


	uniqueSingleLinkList(pList);
	printf("After Unique:");
	printSingleLinkList(pList);

	
	
Fail:

	if (NULL != fp)
		fclose(fp);

	if (NULL != pList)
		destroySingleLinkList(&pList);


}
