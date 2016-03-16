#include "singleLinkList.h"
#include "singleLinkList.h"




#include "utils.h"

#include <stdio.h>
#include <assert.h>




#include "common.h"


static int count = 0;
void print(const void *data)
{
	int val = *(int *)data;

	printf("%5d", val);
	++count;
	if (count % 5 == 0)
		putchar('\n');
}



bool less(const void *lhs, const void *rhs)
{
	return *(int*)lhs < *(int*)rhs ? True : False;
}

bool times3(const void *data)
{
	int val = *(int*)data;
	return val % 3 == 0 ? True : False; 
}

int main()
{
	LPSingleLinkList pList = NULL;
	FILE *fp = NULL;
	int elementData;
	IteratorOfSingleLinkList it;

	if (False == createSingleLinkList(&pList, sizeof(int), print, less)) {
		exit(-1);
	}


	if ((fp = fopen("input.txt", "r")) == NULL ) {
		destroySingleLinkList(&pList);
	}

	while (fscanf(fp, "%d", &elementData) > 0) {
		printf("\n Got one data.");
		insertToTailOfSingleLinkList(pList, &elementData);
	}
	fclose(fp);

	printf("\nList:\n");
	count = 0;
	traverseSingleLinkList(pList, print);		
	if (count % 5 != 0) {
		putchar('\n');
	}

	reverseSingleLinkList(pList);
	
	printf("After reverse:\n");
	count = 0;
	traverseSingleLinkList(pList, print);		
	if (count % 5 != 0) {
		putchar('\n');
	}

	elementData = 1;
	while (1) {
		it = findInSingleLinkList(pList, &elementData);
		if ( (*it) == NULL )
			break;
		eraseFromSingleLinkList(pList, it);
	}

	printf("After find-erase:\n");
	count = 0;
	traverseSingleLinkList(pList, print);		
	if (count % 5 != 0) {
		putchar('\n');
	}

	elementData = 2;
        removeInSingleLinkList(pList, &elementData);
    	

	printf("After remove:\n");
	count = 0;
	traverseSingleLinkList(pList, print);		
	if (count % 5 != 0) {
		putchar('\n');
	}

        removeIfInSingleLinkList(pList, times3);
    	

	printf("After remove-If:\n");
	count = 0;
	traverseSingleLinkList(pList, print);		
	if (count % 5 != 0) {
		putchar('\n');
	}

	sortSingleLinkList(pList);

	printf("After sorting:\n");
	count = 0;
	traverseSingleLinkList(pList, print);		
	if (count % 5 != 0) {
		putchar('\n');
	}

	uniqueSingleLinkList(pList);


	printf("After unique:\n");
	count = 0;
	traverseSingleLinkList(pList, print);		
	if (count % 5 != 0) {
		putchar('\n');
	}

	destroySingleLinkList(&pList);
	
	return 0;
}




