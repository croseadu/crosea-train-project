#include "doubleLinkList.h"
#include "doubleLinkList.h"




#include "utils.h"

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>



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
	LPDoubleLinkList pList = NULL;
	FILE *fp = NULL;
	int elementData;
	IteratorOfDoubleLinkList it;

	if (False == createDoubleLinkList(&pList, sizeof(int), print, less)) {
		exit(-1);
	}


	if ((fp = fopen("input.txt", "r")) == NULL ) {
		destroyDoubleLinkList(&pList);
	}

	while (fscanf(fp, "%d", &elementData) > 0) {
		printf("\n Got one data.");
		insertToTailOfDoubleLinkList(pList, &elementData);
	}
	fclose(fp);

	printf("\nList:\n");
	count = 0;
	traverseDoubleLinkList(pList, print);		
	if (count % 5 != 0) {
		putchar('\n');
	}

	reverseDoubleLinkList(pList);
	
	printf("After reverse:\n");
	count = 0;
	traverseDoubleLinkList(pList, print);		
	if (count % 5 != 0) {
		putchar('\n');
	}

	elementData = 1;
	while (1) {
		it = findInDoubleLinkList(pList, &elementData);
		if ( (*it) == pList->pHead )
			break;
		eraseFromDoubleLinkList(pList, it);
	}

	printf("After find-erase:\n");
	count = 0;
	traverseDoubleLinkList(pList, print);		
	if (count % 5 != 0) {
		putchar('\n');
	}

	elementData = 2;
        removeInDoubleLinkList(pList, &elementData);
    	

	printf("After remove:\n");
	count = 0;
	traverseDoubleLinkList(pList, print);		
	if (count % 5 != 0) {
		putchar('\n');
	}

        removeIfInDoubleLinkList(pList, times3);
    	

	printf("After remove-If:\n");
	count = 0;
	traverseDoubleLinkList(pList, print);		
	if (count % 5 != 0) {
		putchar('\n');
	}

	sortDoubleLinkList(pList);

	printf("After sorting:\n");
	count = 0;
	traverseDoubleLinkList(pList, print);		
	if (count % 5 != 0) {
		putchar('\n');
	}

	uniqueDoubleLinkList(pList);


	printf("After unique:\n");
	count = 0;
	traverseDoubleLinkList(pList, print);		
	if (count % 5 != 0) {
		putchar('\n');
	}

	destroyDoubleLinkList(&pList);
	
	return 0;
}




