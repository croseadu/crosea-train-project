#include "../include/binaryTree.h"

LPTreeNode createFromString(const LPTree, const char **);

void print(void *data)
{
  char *p = (char *)data;
  putchar(*p);
}

bool equal(void *lhs, void *rhs)
{
  char *pLhs = (char *)lhs;
  char *pRhs = (char *)rhs;
  return *pLhs == *pRhs;
}
bool less(void *lhs, void *rhs)
{
  char *pLhs = (char *)lhs;
  char *pRhs = (char *)rhs;
  return *pLhs < *pRhs;
}


int main()
{

  LPTree pTree = NULL;
  LPTreeNode pRoot = NULL;
  const char *p = "ABC  DE  F  GH I   ";
  

  initBinaryTree(&pTree, sizeof(char), print, equal, less);
  pRoot = createFromString(pTree, &p);
  
  pTree->pRoot = pRoot;
  
  printf("PreOrder  :");
  preOrderTraverse(pTree->pRoot, print);
  putchar('\n');
  preOrderTraverseUseStack(pTree->pRoot, print);
  putchar('\n');
  
  printf("inOrder   :");
  inOrderTraverse(pTree->pRoot, print);
  putchar('\n');
  inOrderTraverseUseStack1(pTree->pRoot, print);
  putchar('\n');
  inOrderTraverseUseStack2(pTree->pRoot, print);
  putchar('\n');
  inOrderTraverseUseStack3(pTree->pRoot, print);
  putchar('\n');


  printf("PostOrder :");
  postOrderTraverse(pTree->pRoot, print);
  putchar('\n');
  postOrderTraverseUseStack(pTree->pRoot, print);
  putchar('\n');


  destroyBinaryTree(&pTree);





  return 0;
}

LPTreeNode createFromString(const LPTree pTree, const char **pp)
{
  const char *p = *pp;
  LPTreeNode pNode;
  
  if (**pp == ' ') {
    ++*pp;
    return NULL;
  }
  
  
  pNode = createNode(pTree, (void *)p);
  if (NULL == pNode) {
    return NULL;
  }
  ++*pp;
  pNode->pLeftChild = createFromString(pTree, pp);
  pNode->pRightChild = createFromString(pTree, pp);

  return pNode;
}
