#include "mytype.h"


#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _TreeNode
{
  char *pData;
  struct _TreeNode *pLeftChild, *pRightChild;
}TreeNode, *LPTreeNode;

typedef struct _Tree
{
  LPTreeNode pRoot;
  unsigned int elementSize;
  PrintFunc printer;
  CompareFunc equal;
  CompareFunc less;
}Tree, *LPTree;

bool initBinaryTree(LPTree *ppTree, unsigned int elementSize, PrintFunc printer,
	      CompareFunc eq, CompareFunc less)
{
  LPTree pTree = (LPTree)malloc(sizeof(Tree));
  if (NULL == pTree) {
    printf("Out Of Memory in %s",__func__);
    return false;
  }

  pTree->pRoot = NULL;
  pTree->elementSize = elementSize;
  pTree->printer = printer;
  pTree->equal = eq;
  pTree->less = less;

  *ppTree = pTree;
  return true;
}
void preOrderTraverse(LPTreeNode pNode, VisitFunc visitor);
void preOrderTraverse(LPTreeNode pNode, VisitFunc visitor)
{
  visitor((void *)pNode->pData);
  if (pNode->pLeftChild)
    preOrderTraverse(pNode->pLeftChild, visitor);
  if (pNode->pRightChild)
    preOrderTraverse(pNode->pRightChild, visitor);
}

void preOrderTraverseUseStack(LPTreeNode pRoot, VisitFunc visitor)
{
  LPStack pStack = NULL;
  LPTreeNode pNode;
  initStack(&pStack, sizeof(LPTreeNode));
  if (NULL == pStack)
    return;

  push(pStack, &pRoot);
  while (!isStackEmpty(pStack)) {
    pop(pStack, &pNode);
    if (pNode->pRightChild)
      push(pStack, &pNode->pRightChild);
    if (pNode->pLeftChild)
      push(pStack, &pNode->pLeftChild);
    visitor((void *)pNode->pData);
  } // end of while

  destroyStack(&pStack);
}

void inOrderTraverse(LPTreeNode pNode, VisitFunc visitor)
{
  if (pNode->pLeftChild)
    inOrderTraverse(pNode->pLeftChild, visitor);
  visitor((void *)pNode->pData);
  if (pNode->pRightChild)
    inOrderTraverse(pNode->pRightChild, visitor);
}

void inOrderTraverseUseStack1(LPTreeNode pRoot, VisitFunc visitor)
{
  LPStack pStack = NULL;
  LPTreeNode pNode;
  initStack(&pStack, sizeof(LPTreeNode));
  if (NULL == pStack)
    return;
  
  push(pStack, &pRoot);
  while (pRoot->pLeftChild) {
    push(pStack, &pRoot->pLeftChild);
    pRoot = pRoot->pLeftChild;
  }
  while (!isStackEmpty(pStack)) {
    pop(pStack, &pNode);
    visitor(pNode->pData);
    pNode = pNode->pRightChild;
    while(pNode) {
      push(pStack, &pNode);
      pNode = pNode->pLeftChild;
    }
  }

  destroyStack(&pStack);
}

void inOrderTraverseUseStack2(LPTreeNode pRoot, VisitFunc visitor)
{
  LPStack pStack = NULL;
  LPTreeNode pNode;
  initStack(&pStack, sizeof(LPTreeNode));
  if (NULL == pStack)
    return;
  
  pNode = pRoot;
  while (pNode || !isStackEmpty(pStack)) {
    if (pNode) {
      push(pStack, &pNode);
      pNode = pNode->pLeftChild;
    }
    else {
      pop(pStack, &pNode);
      visitor((void *)pNode->pData);
      pNode = pNode->pRightChild;
    }
  }
  
  destroyStack(&pStack);
}

void inOrderTraverseUseStack3(LPTreeNode pRoot, VisitFunc visitor)
{
  LPStack pStack = NULL;
  LPTreeNode pNode;
  initStack(&pStack, sizeof(LPTreeNode));
  if (NULL == pStack)
    return;

  push(pStack, &pRoot);
  while (!isStackEmpty(pStack)) {
    getTop(pStack, &pNode);
    while(pNode) {
      push(pStack, &pNode->pLeftChild);
      pNode = pNode->pLeftChild;
    }
    pop(pStack, &pNode);
    if (!isStackEmpty(pStack)) {
      pop(pStack, &pNode);
      visitor((void *)pNode->pData);
      push(pStack, &pNode->pRightChild);
    }
  }
    
  destroyStack(&pStack);
}

void postOrderTraverse(LPTreeNode pNode, VisitFunc visitor)
{
  if (pNode->pLeftChild)
    postOrderTraverse(pNode->pLeftChild, visitor);
  if (pNode->pRightChild)
    postOrderTraverse(pNode->pRightChild, visitor);
  visitor((void *)pNode->pData);
}

void postOrderTraverseUseStack(LPTreeNode pRoot ,VisitFunc visitor)
{
  LPStack pStack = NULL;
  LPTreeNode pNode, pVisit, pGuard;
  initStack(&pStack, sizeof(LPTreeNode));
  if (NULL == pStack)
    return;
  
  push(pStack, &pRoot);
  pVisit = NULL;
  while (!isStackEmpty(pStack)) {
    getTop(pStack, &pNode);
    pGuard = pNode->pRightChild?pNode->pRightChild:pNode->pLeftChild;
    if ((pNode->pLeftChild == NULL && pNode->pRightChild == NULL)
	|| pGuard == pVisit) {
      pop(pStack, &pNode);
      visitor(pNode->pData);
      pVisit = pNode;
    }
    else {
      if (pNode->pRightChild)
	push(pStack, &pNode->pRightChild);
      if (pNode->pLeftChild)
	push(pStack, &pNode->pLeftChild);
    }
    
  }
  

  destroyStack(&pStack);
}


static void cleanUp(LPTreeNode pNode)
{
  if (pNode->pLeftChild)
    cleanUp(pNode->pLeftChild);
  if (pNode->pRightChild)
    cleanUp(pNode->pRightChild);
  free(pNode->pData);
  free(pNode);
}

void destroyBinaryTree(LPTree *ppTree)
{
  if ((*ppTree)->pRoot)
    cleanUp((*ppTree)->pRoot);
  free(*ppTree);
  *ppTree = NULL;
}


LPTreeNode createNode(const LPTree pTree, void *data)
{
  LPTreeNode pNode = (LPTreeNode)malloc(sizeof(TreeNode));
  if (NULL == pNode) {
    printf ("Out Of Memory in %s", __func__);
    return NULL;
  }
  pNode->pData = (char *)malloc(pTree->elementSize);
  if (NULL == pNode->pData) {
    printf ("Out Of Memory in %s", __func__);
    free(pNode);
    return NULL;
  }
  memcpy(pNode->pData, data, pTree->elementSize);
  pNode->pLeftChild = pNode->pRightChild = NULL;
  return pNode;
}
