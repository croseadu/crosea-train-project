#include "../include/mytype.h"
#include <stdio.h>
#include <stdlib.h>

typedef int KeyType;

typedef struct _Tree
{
  KeyType key;
  struct _Tree *pLeftChild;
  struct _Tree *pRightChild;
}Tree, *LPTree;



void inOrder(LPTree pRoot)
{
  if (pRoot->pLeftChild)
    inOrder(pRoot->pLeftChild);
  printf(" %d ", pRoot->key);
  if (pRoot->pRightChild)
    inOrder(pRoot->pRightChild);
}

LPTree *searchInTree(LPTree *ppRoot, KeyType val)
{
  LPTree *ppIter = ppRoot;

  while (*ppIter != NULL) {
    if ((*ppIter)->key == val)
      break;
    else if ((*ppIter)->key > val)
      ppIter = &((*ppIter)->pLeftChild);
    else
      ppIter = &((*ppIter)->pRightChild);
  }

  return ppIter;
}

bool searchIfExist(LPTree pRoot, KeyType val)
{
  LPTree *ppFound;

  ppFound = searchInTree(&pRoot, val);
  return *ppFound != NULL;
}


bool insertToTree(LPTree *ppRoot, KeyType val)
{
  LPTree pNode;
  LPTree *ppInsertPos;

  
  ppInsertPos = searchInTree(ppRoot, val);
  if (*ppInsertPos != NULL)
    return false;
  

  pNode = (LPTree)malloc(sizeof(Tree));
  if (NULL == pNode) {
    printf ("Out OF Memory in %s", __func__);
    return false;
  }
  pNode->key = val;
  pNode->pLeftChild = NULL;
  pNode->pRightChild = NULL;

  *ppInsertPos = pNode;
  return true;
}



void deleteViaUsePred(LPTree *ppDeleted)
{
  LPTree *ppPred;
  LPTree p;

  ppPred = &((*ppDeleted)->pLeftChild);
  while ((*ppPred)->pRightChild)
    ppPred = &((*ppPred)->pRightChild);

  (*ppDeleted)->key = (*ppPred)->key;
  
  p = *ppPred;
  *ppPred = (*ppPred)->pLeftChild;
  free(p);
}

void deleteViaUseSucc(LPTree *ppDeleted)
{
  LPTree *ppSucc;
  LPTree p;

  ppSucc = &((*ppDeleted)->pRightChild);
  while ((*ppSucc)->pLeftChild)
    ppSucc = &((*ppSucc)->pLeftChild);

  (*ppDeleted)->key = (*ppSucc)->key;

  p = *ppSucc;
  *ppSucc = (*ppSucc)->pRightChild;
  free(p);
}

void deleteViaUseLeftChild(LPTree *ppDeleted)
{
  LPTree p = *ppDeleted,q ;
  

  *ppDeleted = p->pLeftChild;
  q = p->pLeftChild;
  while (q->pRightChild)
    q = q->pRightChild;
  q->pRightChild = p->pRightChild;
  free(p);
}

void deleteViaUseRightChild(LPTree *ppDeleted)
{
  LPTree p = *ppDeleted,q;
  
  *ppDeleted = p->pRightChild;
  q = p->pRightChild;
  while (q->pLeftChild)
    q = q->pLeftChild;
  q->pLeftChild = p->pLeftChild;
  free (p);
}

bool deleteFromTree(LPTree *ppRoot, KeyType val)
{
  LPTree *ppNode;
  LPTree p;

  ppNode = searchInTree(ppRoot, val);
  if (*ppNode == NULL) {
    printf("The val which deleted is not in the tree\n");
    return false;
  }

  if ((*ppNode)->pLeftChild == NULL) {
    p = *ppNode;
    *ppNode = (*ppNode)->pRightChild;
    free (p);
  }
  else if ((*ppNode)->pRightChild == NULL) {
    p = *ppNode;
    *ppNode = (*ppNode)->pLeftChild;
    free(p);
  }
  else {
    deleteViaUsePred(ppNode);
  }
  return true;  
 
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


int main()
{

  LPTree pRoot = NULL;
  char c = ' ';
  int data;

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
  }
  
  printf("\n Final Tree is :\n");
  inOrder(pRoot);
  putchar('\n');

  
  destroyTree(&pRoot);
  return 0;
}
