
#include "linkList.h"
#include <stdio.h>

static int counter = 0;
static void printInt(void *val)
{
  printf("%5d", *(int *)val);
  ++counter;
  if (!(counter%4))
    putchar('\n');
}

static bool less(void *lhs, void *rhs)
{
  int op0 = *(int *)lhs;
  int op1 = *(int *)rhs;
  return op0 < op1;
}


static bool equal(void *lhs, void *rhs)
{
  int op0 = *(int *)lhs;
  int op1 = *(int *)rhs;
  return op0 == op1;
}


static void findModN(void *val)
{
  const int n = 3;
  int temp = *(int *)val;
  if (!(temp%3)){
    printf("Find %d is Mod %d\n", temp, n);

  }
}
static bool isModN(void *val)
{
  const int n = 3;
  int temp = *(int *)val;
  return (temp%3) == 0;
}

int main()
{
  FILE *fp;
  char buf[4096];

  LPLinkList pList = NULL;
  int data;

  if ((fp = fopen("in.txt","r")) == NULL) {
    printf("Can't open input file\n");
    return -1;
  }

  if (!initLinkList(&pList, sizeof(int), printInt, equal, less)){
    printf("Failed to create List\n");
    return -1;
  }
  
  while (fscanf(fp, "%d", &data) != EOF)
    {
      insertToLinkListTail(pList,&data);
    }
  printf("\nList is :");
  printLinkList(pList);
  
  sortLinkList(pList);

  printf("After Sorted:\n");
  printLinkList(pList);

  visitLinkList(pList, findModN);
  deleteIfInLinkList(pList, isModN);
  printf("After remove ModN\n");
  printLinkList(pList);
  reverseLinkList(pList);
  printf("After reverse LinkList\n");
  printLinkList(pList);
  destroyLinkList(&pList);

  fclose(fp);
  return 0;
}
