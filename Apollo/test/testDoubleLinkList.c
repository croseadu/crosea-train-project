
#include "doubleLinkList.h"
#include "utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>




BOOL mod3(const void *data)
{
	int val = *(const int *)data;
	return val % 3 == 0 ? True : False;
}

BOOL mod4(const void *data)
{
	int val = *(const int *)data;
	return val % 4 == 0 ? True : False;
}

int main()
{

	LPDoubleLinkList pList = NULL;
	FILE *fp;
	int temp;
	DoubleLinkListIter it;	

	if (False == createDoubleLinkList(&pList,
					  sizeof(int),
					  intPrinter,
					  intLess)) {
		exit(-1);
	}

	
	if ( NULL == ( fp = fopen("input.txt", "r") )) {
		goto lexit;
	}
	

	while(fscanf(fp, "%d", &temp) != EOF) {
		printf("\nInsert %d to List:", temp);
		insertToTailOfDoubleLinkList(pList, &temp);

	}

	fclose(fp);
	
	printf("\nList:");
	dumpDoubleLinkList(pList," ", 5);
	
	reverseDoubleLinkList(pList);
	printf("\nList after reverse");
	dumpDoubleLinkList(pList, " ", 5);
	

	sortDoubleLinkList(pList);
	printf ("\nList after sorting");
	dumpDoubleLinkList(pList, " ", 5);

	removeIfInDoubleLinkList(pList, mod3);
	printf ("\nList after remove mod3");
	dumpDoubleLinkList(pList, " ", 5);

	temp = 5;
	it = findInDoubleLinkList(pList, &temp);
	removeFromDoubleLinkList(pList, it);
	printf ("\nList after remove 5");
	dumpDoubleLinkList(pList, " ", 5);


	it = findIfInDoubleLinkList(pList, mod4);
	removeFromDoubleLinkList(pList, it);
	printf ("\nList after remove one mod4");
	dumpDoubleLinkList(pList, " ", 5);


	
lexit:

	destroyDoubleLinkList(&pList);

	return 0;
}
