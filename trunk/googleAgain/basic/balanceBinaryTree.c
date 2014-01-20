#include "../include/mytype.h"
#include <stdio.h>
#include <stdlib.h>
#include "../include/stack.h"
#include <assert.h>

typedef int KeyType;

enum BalanceFactor{
  LeftHigh = 1,
  Equal = 0,
  RightHigh = -1,
};

typedef struct _BSTree
{
  KeyType key;
  enum BalanceFactor bf;
  struct _BSTree *pLeftChild;
  struct _BSTree *pRightChild;
}Tree, *LPTree;


void validateTree(LPTree pRoot);


void inOrder(LPTree pRoot)
{
  if (pRoot->pLeftChild)
    inOrder(pRoot->pLeftChild);
  printf(" %d ", pRoot->key);
  if (pRoot->pRightChild)
    inOrder(pRoot->pRightChild);
}

LPTree createNode(KeyType val)
{
  LPTree pNewNode;

  pNewNode = (LPTree)malloc(sizeof(Tree));
  if (NULL == pNewNode) {
    printf ("Out Of Memory in %s", __func__);
    return NULL;
  }
  pNewNode->key = val;
  pNewNode->pLeftChild = NULL;
  pNewNode->pRightChild = NULL;
  pNewNode->bf = Equal;

  return pNewNode;
}

void leftRotate(LPTree *ppRoot)
{
  LPTree p = *ppRoot;
  *ppRoot = p->pRightChild;
  p->pRightChild = (*ppRoot)->pLeftChild;
  (*ppRoot)->pLeftChild = p;
}

void rightRotate(LPTree *ppRoot) {
  LPTree p = *ppRoot;
  *ppRoot = p->pLeftChild;
  p->pLeftChild = (*ppRoot)->pRightChild;
  (*ppRoot)->pRightChild = p;
}

bool insertToTree(LPTree *ppRoot, KeyType val)
{
  LPTree *ppIter;
  LPStack pStack;
  LPTree *ppChild, *ppFather;

  if (*ppRoot == NULL) {
    *ppRoot = createNode(val);
    return true;
  }

  initStack(&pStack, sizeof(LPTree *));
  ppIter = ppRoot;
  while (*ppIter) {
    if ((*ppIter)->key == val)
      return false;
    push(pStack, &ppIter);
    if ((*ppIter)->key > val)
      ppIter = &((*ppIter)->pLeftChild);
    else
      ppIter = &((*ppIter)->pRightChild);
  }
  
  *ppIter = createNode(val);
  ppChild = ppIter;
 
  while (!isStackEmpty(pStack)) {
    pop(pStack, &ppFather);
    if ((*ppFather)->pLeftChild == *ppChild) {
      if ((*ppFather)->bf == RightHigh) {
	(*ppFather)->bf = Equal;
	break;
      }
      else if((*ppFather)->bf == Equal) {
	(*ppFather)->bf = LeftHigh;
	ppChild = ppFather;
      }
      else if ((*ppFather)->bf == LeftHigh){
	if ((*ppChild)->bf == RightHigh) {
	  switch((*ppChild)->pRightChild->bf) {
	  case Equal: (*ppFather)->bf = Equal; (*ppChild)->bf = Equal; break;
	  case LeftHigh:(*ppFather)->bf = RightHigh; (*ppChild)->bf = Equal; break;
	  case RightHigh:(*ppChild)->bf = LeftHigh; (*ppFather)->bf = Equal; break;
	  }
	  (*ppChild)->pRightChild->bf = Equal;
	  leftRotate(ppChild);
	  
	}
	else {
	  (*ppFather)->bf = Equal;
	  (*ppFather)->pLeftChild->bf = Equal;
	}
	rightRotate(ppFather);

	break;
      }
    }
    else {
      if ((*ppFather)->bf == LeftHigh) {
	(*ppFather)->bf = Equal;
	break;
      }
      else if((*ppFather)->bf == Equal) {
	(*ppFather)->bf = RightHigh;
	ppChild = ppFather;
      }
      else if ((*ppFather)->bf == RightHigh){
	if ((*ppChild)->bf == LeftHigh) {
	  switch((*ppChild)->pLeftChild->bf) {
	  case Equal: (*ppFather)->bf = (*ppChild)->bf = Equal; break;
	  case LeftHigh: (*ppFather)->bf = Equal; (*ppChild)->bf = RightHigh; break;
	  case RightHigh: (*ppFather)->bf = LeftHigh; (*ppChild)->bf = Equal; break;
	  }
	  (*ppChild)->pLeftChild->bf = Equal;
	  rightRotate(ppChild);
	}
	else {
	  (*ppFather)->bf = Equal;
	  (*ppFather)->pRightChild->bf = Equal;
	}
	leftRotate(ppFather);
	break;
      }   
    }
  }
  validateTree(*ppRoot);
  destroyStack(&pStack);
  return true;
}

bool deleteFromTree(LPTree *ppRoot, KeyType val)
{
  LPStack pStack;
  LPTree *ppIter;
  LPTree pCur, pGrandChild;
  LPTree *ppChild, *ppFather;

  initStack(&pStack, sizeof(LPTree *));
  
  ppIter = ppRoot;
  while (*ppIter) {
    if ((*ppIter)->key == val)
      break;
    push(pStack, &ppIter);
    if ((*ppIter)->key > val)
      ppIter = &((*ppIter)->pLeftChild);
    else 
      ppIter = &((*ppIter)->pRightChild);
  }

  if (*ppIter == NULL)
    return false;

  if ((*ppIter)->pLeftChild && (*ppIter)->pRightChild) {
    push(pStack, &ppIter);
    pCur = *(ppIter);
    ppIter = &((*ppIter)->pLeftChild);
    
    while ((*ppIter)->pRightChild) {
      push(pStack, &ppIter);
      ppIter = &((*ppIter)->pRightChild);
    }
    
    pCur->key = (*ppIter)->key; 
  }
  pCur = *ppIter;
  *ppIter = (*ppIter)->pLeftChild?(*ppIter)->pLeftChild:(*ppIter)->pRightChild;
  free (pCur);
  ppChild = ppIter;
  while (!isStackEmpty(pStack)) {
    pop(pStack, &ppFather);
    if (&(*ppFather)->pLeftChild == ppChild) {
      if ((*ppFather)->bf == Equal) {
	(*ppFather)->bf = RightHigh;
	break;
      }
      else if ((*ppFather)->bf == LeftHigh) {
	(*ppFather)->bf = Equal;
	ppChild = ppFather;
      }
      else {
	// Do Rotation here.
	if ((*ppFather)->pRightChild->bf == LeftHigh) {
	  pGrandChild = (*ppFather)->pRightChild->pLeftChild;
	  switch (pGrandChild->bf) {
	  case Equal: (*ppFather)->bf = Equal; (*ppChild)->bf = Equal; break;
	  case LeftHigh: (*ppFather)->bf = Equal; (*ppChild)->bf = RightHigh; break;
	  case RightHigh: (*ppFather)->bf = LeftHigh; (*ppChild)->bf = Equal; break;
	  }
	  pGrandChild->bf = Equal;
	  rightRotate(&(*ppFather)->pRightChild);
	}
	else if ((*ppFather)->pRightChild->bf == Equal){
	  (*ppFather)->bf = RightHigh;
	  (*ppFather)->pRightChild->bf = LeftHigh;
	  
	}
	else {
	  (*ppFather)->bf = Equal;
	  (*ppFather)->pRightChild->bf = Equal;  
	}
	leftRotate(ppFather);	
	if ((*ppFather)->bf != Equal)
	  break;
	ppChild = ppFather;
      }
    }
    else {
      //
      assert ((*ppFather)->pRightChild == *ppChild);
      if ((*ppFather)->bf == Equal) {
	(*ppFather)->bf = LeftHigh;
	break;
      } 
      else if ((*ppFather)->bf == RightHigh) {
	(*ppFather)->bf = Equal;
	ppChild = ppFather;
      } 
      else {
	if ((*ppFather)->pLeftChild->bf == RightHigh) {
	  pGrandChild = (*ppFather)->pLeftChild->pRightChild;
	  switch (pGrandChild->bf) {
	  case Equal: (*ppFather)->bf = (*ppChild)->bf = Equal; break;
	  case LeftHigh: (*ppFather)->bf = RightHigh; (*ppChild)->bf =Equal; break;
	  case RightHigh: (*ppFather)->bf = Equal, (*ppChild)->bf = LeftHigh; break;
	  }
	  pGrandChild->bf = Equal;
	  leftRotate(&(*ppFather)->pLeftChild);
	}
	else {
	  (*ppFather)->bf = Equal;
	  (*ppFather)->pLeftChild->bf = Equal;
	}
	rightRotate(ppFather);
	if ((*ppFather)->bf != Equal)
	  break;
	ppChild = ppFather;
      }	
    }
  }

  validateTree(*ppRoot);
  destroyStack(&pStack);
}

void destroyTree(LPTree *ppRoot)
{
  LPTree pRoot = *ppRoot;
  if (pRoot->pLeftChild)
    destroyTree(&pRoot->pLeftChild);
  if (pRoot->pRightChild)
    destroyTree(&pRoot->pRightChild);
  free(pRoot);
  *ppRoot = NULL;
}

int getTreeHeight(LPTree pRoot)
{
  int leftHeight, rightHeight;

  if (NULL == pRoot)
    return 0;

  leftHeight = getTreeHeight(pRoot->pLeftChild);
  rightHeight = getTreeHeight(pRoot->pRightChild);
  return 1 + (leftHeight>=rightHeight?leftHeight:rightHeight);
}

void validateTree(LPTree pRoot)
{
  int factor;
  if (pRoot->pLeftChild)
    validateTree(pRoot->pLeftChild);
  if (pRoot->pRightChild)
    validateTree(pRoot->pRightChild);
  
  factor = getTreeHeight(pRoot->pLeftChild);
  factor -= getTreeHeight(pRoot->pRightChild);
  if (factor != pRoot->bf)
    printf("\nIncorrect bf [%d]%d\n", pRoot->key, pRoot->bf);
  if (factor >= 2 || factor <= -2)
    printf("\nInvalid BST.\n");

}

void preOrder(LPTree pRoot)
{
  printf("%d", pRoot->key);
  printf("(%d,%d)", pRoot->pLeftChild?pRoot->pLeftChild->key:-1,
	 pRoot->pRightChild?pRoot->pRightChild->key:-1);
  if (pRoot->pLeftChild)
    preOrder(pRoot->pLeftChild);
  if (pRoot->pRightChild)
    preOrder(pRoot->pRightChild);
}

int main()
{

  char c = ' ';
  int data;
  LPTree pRoot = NULL;

  while(1) {
    if (c != '\n')
      printf("\nInsert(I) Or Delete(D) or Finished(F):");
    c = getchar();
    if (c == '\n')
      continue;
    if (c == 'F' || c == 'f')
      break;
    putchar('\n');
    printf("Key you want to operate: ");
    scanf("%d", &data);
    if (c == 'I' || c == 'i') {
      if (!insertToTree(&pRoot, data)) {
	printf("\nAlready Exist\n");
      }
    }
    else if (c == 'D' || c == 'd') {
      if (!deleteFromTree(&pRoot, data)) {
	printf("\nKey Don't exist\n");
      }
    }
    putchar('\n');
    inOrder(pRoot);
    putchar('\n');
    preOrder(pRoot);
    putchar('\n');
  }

  printf("\n Final Tree is :\n");
  inOrder(pRoot);
  putchar('\n');

  return 0;
}


