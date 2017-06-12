#include "singleLinkList.h"
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

	LPSingleLinkList pList = NULL;
	FILE *fp;
	int temp;
	SingleLinkListIter it;	

	if (False == createSingleLinkList(&pList,
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
		insertToTailOfSingleLinkList(pList, &temp);

	}

	fclose(fp);
	
	printf("\nList:");
	dumpSingleLinkList(pList," ", 5);

	reverseSingleLinkList(pList);
	printf("\nList after reverse");
	dumpSingleLinkList(pList, " ", 5);
	

	sortSingleLinkList(pList);
	printf ("\nList after sorting");
	dumpSingleLinkList(pList, " ", 5);

	removeIfInSingleLinkList(pList, mod3);
	printf ("\nList after remove mod3");
	dumpSingleLinkList(pList, " ", 5);

	temp = 5;
	it = findInSingleLinkList(pList, &temp);
	removeFromSingleLinkList(pList, it);
	printf ("\nList after remove 5");
	dumpSingleLinkList(pList, " ", 5);


	it = findIfInSingleLinkList(pList, mod4);
	removeFromSingleLinkList(pList, it);
	printf ("\nList after remove one mod4");
	dumpSingleLinkList(pList, " ", 5);



lexit:

	destroySingleLinkList(&pList);

	return 0;
}
