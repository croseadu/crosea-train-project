

#include "doubleLinkList.h"
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
	LPDoubleLinkList pList = NULL;
	int temp;



	if (NULL == (fp = fopen("input.txt", "r"))) {
		DBG(printf("Failed to open input file\n"));
		goto Fail;
	}
	if (False == createDoubleLinkList(&pList, sizeof(int), lessInt, printInt)) {
		DBG(printf("Failed to create double link list!\n"));
		goto Fail;
	}

	
	while (fscanf(fp, "%d", &temp) > 0) {
		insertToHeadOfDoubleLinkList(pList, &temp);

	}

	printf("\nCreated List:");
	printDoubleLinkList(pList);

	reverseDoubleLinkList(pList);
	printf("after reverser:");
	printDoubleLinkList(pList);

	sortDoubleLinkList(pList);
	printf("after Sorted:");
	printDoubleLinkList(pList);

	temp = 2;
	removeInDoubleLinkList(pList, &temp);
	printf("after remove value 2:");
	printDoubleLinkList(pList);

	removeIfInDoubleLinkList(pList, mod3);
	printf("After remove mod3: ");
	printDoubleLinkList(pList);	


	uniqueDoubleLinkList(pList);
	printf("After Unique:");
	printDoubleLinkList(pList);

	
	
Fail:

	if (NULL != fp)
		fclose(fp);

	if (NULL != pList)
		destroyDoubleLinkList(&pList);


}
