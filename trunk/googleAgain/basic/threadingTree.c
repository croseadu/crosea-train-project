#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/mytype.h"
#include "../include/stack.h"

typedef struct _ThreadTreeNode {
  char *pData;
  bool isLeftChildTag;
  bool isRightChildTag;
  struct _ThreadTreeNode *pLeftChild, *pRightChild;
}ThreadTreeNode, *LPThreadTreeNode;

typedef struct _ThreadTree {
  LPThreadTreeNode pRoot;
  unsigned int elementSize;
  PrintFunc printer;
  CompareFunc equal;
  CompareFunc less;
}ThreadTree, *LPThreadTree;


bool initThreadTree(LPThreadTree *ppTree, unsigned int elementSize, PrintFunc printer,
	      CompareFunc eq, CompareFunc less)
{
  LPThreadTree pTree = (LPThreadTree)malloc(sizeof(ThreadTree));
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


static void cleanUp(LPThreadTreeNode pNode)
{
  if (pNode->pLeftChild && pNode->isLeftChildTag == false)
    cleanUp(pNode->pLeftChild);
  if (pNode->pRightChild && pNode->isRightChildTag == false)
    cleanUp(pNode->pRightChild);
  free(pNode->pData);
  free(pNode);
}

void destroyThreadTree(LPThreadTree *ppTree)
{
  if ((*ppTree)->pRoot)
    cleanUp((*ppTree)->pRoot);
  free(*ppTree);
  *ppTree = NULL;
}

LPThreadTreeNode createNode(const LPThreadTree pTree, void *data)
{
  LPThreadTreeNode pNode = (LPThreadTreeNode)malloc(sizeof(ThreadTreeNode));
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
  pNode->isLeftChildTag = pNode->isRightChildTag = false;
  return pNode;
}



void inOrderTraverse(LPThreadTreeNode pNode, VisitFunc visitor)
{
  if (!pNode->isLeftChildTag && pNode->pLeftChild)
    inOrderTraverse(pNode->pLeftChild, visitor);
  visitor((void *)pNode->pData);
  if (!pNode->isRightChildTag && pNode->pRightChild)
    inOrderTraverse(pNode->pRightChild, visitor);
}

LPThreadTreeNode createFromString(const LPThreadTree, const char **);

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


LPThreadTreeNode inOrderThreadingTree(LPThreadTree pTree, VisitFunc visitor)
{
  LPStack pStack = NULL;
  LPThreadTreeNode p = pTree->pRoot;
  LPThreadTreeNode pPrev, pFakeRoot;
  char holder = '#';
  
  pFakeRoot = createNode(pTree, &holder);
  if  (NULL == pFakeRoot) {
    printf("Out Of Memory in %s", __func__);
    return NULL;
  }

  pPrev = pFakeRoot;
  pFakeRoot->pLeftChild = pTree->pRoot;
  pFakeRoot->isLeftChildTag = false;
  initStack(&pStack,sizeof(LPThreadTreeNode));
  if (NULL == pStack)
    return;

  while (p || !isStackEmpty(pStack)) {
    if (p) {
      while(p) {
	push(pStack, &p);
	p = p->pLeftChild;
      }
    }
    else {
      pop(pStack, &p);
      visitor(p->pData);
      if (pPrev->pRightChild == NULL) {
	pPrev->pRightChild = p;
	pPrev->isRightChildTag = true;
      }
      if (p->pLeftChild == NULL) {
	p->pLeftChild = pPrev;
	p->isLeftChildTag = true;
      }
      pPrev = p;
      p = p->pRightChild;
    }  
  }

  pPrev->pRightChild = pFakeRoot;
  pPrev->isRightChildTag = true;
  pFakeRoot->pRightChild = pPrev;
  pFakeRoot->isRightChildTag = false;

  destroyStack(&pStack);
  return pFakeRoot;
}

void threadTreeTraverse(LPThreadTreeNode pFakeRoot, VisitFunc visitor)
{
  LPThreadTreeNode pStart = pFakeRoot->pLeftChild;

  while(pStart != pFakeRoot) {
    while(pStart->pLeftChild && pStart->isLeftChildTag == false)
      pStart = pStart->pLeftChild;
    visitor(pStart->pData);
    while(pStart->isRightChildTag && pStart->pRightChild != pFakeRoot) {
      pStart = pStart->pRightChild;
      visitor(pStart->pData);
    }
    pStart = pStart->pRightChild;
  }
}

int main()
{

  LPThreadTree pTree = NULL;
  LPThreadTreeNode pRoot = NULL;
  LPThreadTreeNode pLead = NULL;
  const char *p = "ABC  DE  F  GH I   ";
  

  initThreadTree(&pTree, sizeof(char), print, equal, less);
  pRoot = createFromString(pTree, &p);
  
  pTree->pRoot = pRoot;
  
  printf("inOrder   :");
  inOrderTraverse(pTree->pRoot, print);
  putchar('\n');

  pLead = inOrderThreadingTree(pTree, print);
  putchar('\n');
  inOrderTraverse(pTree->pRoot, print);
  putchar('\n');
  printf("inOrderThreading :");
  threadTreeTraverse(pLead, print);
  putchar('\n');


  destroyThreadTree(&pTree);
  free(pLead);




  return 0;
}


LPThreadTreeNode createFromString(const LPThreadTree pTree, const char **pp)
{
  const char *p = *pp;
  LPThreadTreeNode pNode;
  
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
