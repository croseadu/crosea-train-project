
#include "singleLinkList.h"
#include "common.h"

void printer(const void *data)
{
	const int *ptr = (const int *)data;
	printf("%5d", *ptr);
}

enum BOOL
less(const void *lhs, const void *rhs)
{
	int src0 = *(const int *)lhs;
	int src1 = *(const int *)rhs;
	return src0 < src1;	
	
}

int main()
{
	LPSingleLinkList pList = NULL;
	FILE *fp = NULL;
	int data;

	if (!createSingleLinkList(&pList,
				  sizeof(int),
				  printer,
				  less)) {
		printf("Unable to create new singe link list\n");
		exit(-1);

	}
	

	fp = fopen("input.txt", "r");
	if (NULL == fp) {
		printf("Unable to open input file\n");
		goto cleanup;
	}
	

	while (fscanf(fp, "%d", &data) > 0) {
		insertToHeadOfSingleLinkList(pList, &data);
	}


	printf("Input List is :\n");
	printSingleLinkList(pList);

	reverseSingleLinkList(pList);
	printf("After reverser, List is :\n");
	printSingleLinkList(pList);
	
	sortSingleLinkList(pList);
	printf("After Sort, List is :\n");
	printSingleLinkList(pList);
	
	

cleanup:

	destroySingleLinkList(&pList);

	return 0;
}
