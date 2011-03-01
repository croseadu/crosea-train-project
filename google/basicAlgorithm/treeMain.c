
#include "../include/biTree.h"

void visit(void *pData)
{
  putchar((*(char *)pData));
}

int main()
{
  LP_BI_TREE_NODE pRoot = NULL;

  /*
  if (createTreeV1(&pRoot) != OK)
    {
      exit(-1);
    }
  */
  if (createTreeV2(&pRoot) != OK)
    {
      printf("Exit: failed to create tree\n");
      exit(-1);
    }

  printf("\nStart PreOrderTraverse:");
  preOrderTraverse(pRoot, visit);
  printf("\nStart InOderTraverse:");
  inOrderTraverse(pRoot, visit);
  printf("\nStart PostOrderTraverse:");
  postOrderTraverse(pRoot, visit);
  printf("\nStart PreOrder Stack Traverse:");
  preOrderTraverStack(pRoot, visit);
  printf("\nStart InOrder Stack Traverse V1:");
  inOrderTraverseStack1(pRoot, visit);
  printf ("\nStart InOrder Stack Traverse V2:");
  inOrderTraverseStack2(pRoot, visit);
  putchar('\n');
 
  destroyTree(pRoot);
  return 0;
}
