
#include "../include/biTree.h"

void visit(void *pData)
{
  putchar((*(char *)pData));
}

int main()
{
  LP_BI_TREE_NODE pRoot = NULL;

  if (createTreeV1(&pRoot) != OK)
    {
      exit(-1);
    }
  
  printf("\nStart PreOrderTraverse:");
  preOrderTraverse(pRoot, visit);
  printf("\nStart InOderTraverse:");
  inOrderTraverse(pRoot, visit);
  printf("\nStart PostOrderTraver:");
  postOrderTraverse(pRoot, visit);
  putchar ('\n');
  //preOrderTraverStack(pTree, visit);
  //inOrderTraverseStack1(pTree, visit);
  //inOrderTraverseStack2(pTree, visit);
 

  return 0;
}
