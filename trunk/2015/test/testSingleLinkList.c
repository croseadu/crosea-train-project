#include <stdio.h>
#include <assert.h>




#include "../include/singleLinkList.h"

void print(void *data)
{
  printf("%5d", *(int *)data);
}

BOOL less(void *lhs, void *rhs)
{
  return *(int *)lhs < *(int *)rhs;
}
 
BOOL equal(void *lhs, void *rhs)
{
  return *(int *)lhs == *(int *)rhs;
}

int main()
{
  LPSingleLinkList pList;


  int data;
  FILE *fp;

  fp = fopen("input.txt", "r");
  if (NULL == fp) {
    printf("Can't open input file\n");
    goto cleanup; 
  }
  

  if( createSingleLinkList(&pList,
			   sizeof(int),
			   print,
			   less,
			   equal)){
    goto cleanup;
  }
  
  while (fscanf(fp, "%d", &data) > 0) {
    insertToHeadOfSingleLinkList(pList, &data);
  }

  printf("List:\n");
  printSingleLinkList(pList);
  sortSingleLinkList(pList);
  printf("After Sorting:\n");
  printSingleLinkList(pList);
  reverseSingleLinkList(pList);
  printf("After reverse:\n");
  printSingleLinkList(pList);
  

 cleanup:
  if (fp) {
    fclose(fp);
    fp = NULL;
  }
  if (pList) {
    destroySingleLinkList(&pList);
  }

}
