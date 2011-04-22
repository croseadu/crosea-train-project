#include "../include/common.h"
#include "../include/biTree.h"



typedef struct _TREE
{
  char data;
  struct _TREE *pFirstChild;
  struct _TREE *pNextSibling;
}TREE_NODE, *LP_TREE_NODE;


void visit(void *pData)
{
  putchar((*(char *)pData));
}

void visitData(void *data)
{
  putchar((char)data);
}
void genForestFromTree(LP_TREE_NODE *ppForest, LP_BI_TREE_NODE pRoot);
void genBinaryTreeForForest(LP_BI_TREE_NODE *ppNewRoot, LP_TREE_NODE pForest);
void preOrderForest(LP_TREE_NODE pForest, VISIT_FUNC visit);
void inOrderForest(LP_TREE_NODE pForest, VISIT_FUNC visit);
void destroyForest(LP_TREE_NODE pForest);
int main()
{

  LP_TREE_NODE pForest;
  LP_BI_TREE_NODE pRoot, pNewRoot;
  
  
  createTreeV1(&pRoot);

  printf("\nPreOrder Binary Tree\n");
  preOrderTraverse(pRoot, visit);

  printf("\nInOrder Binary Tree\n");
  inOrderTraverse(pRoot, visit);
  putchar('\n');

  
  genForestFromTree(&pForest, pRoot);
  printf("\nPreOrder Forest\n");
  preOrderForest(pForest, visitData);
  printf("\nInOrder Forest\n");
  inOrderForest(pForest, visitData);
  putchar('\n');
  

  genBinaryTreeForForest(&pNewRoot, pForest);
  printf("\nPreOrder New Binary Tree\n");
  preOrderTraverse(pNewRoot, visit);

  printf("\nInOrder New Binary Tree\n");
  inOrderTraverse(pNewRoot, visit);
  putchar('\n');
  


  destroyTree(pRoot);
  destroyTree(pNewRoot);
  destroyForest(pForest);




  return 0;
}

void genForestFromTree(LP_TREE_NODE *ppForest, LP_BI_TREE_NODE pRoot)
{
  LP_TREE_NODE pFirst = NULL, pPrev, pCur;

  if (pRoot == NULL)
    {
      *ppForest = NULL;
      return;
    }

  while (pRoot)
    {
      pCur = (LP_TREE_NODE)malloc(sizeof(TREE_NODE));
      if (NULL == pCur)
	{
	  printf("Out Of Memory in Line %d, Function %s", __LINE__, __FUNCTION__);
	  exit(OVERFLOW);
	}
      
      if (pFirst)
	{
	  pPrev->pNextSibling = pCur;
	}
      else
	{
	  pFirst = pCur;
	}
      pPrev = pCur;
      genForestFromTree(&pCur->pFirstChild, pRoot->pLeftChild);

      pCur->data = *(char *)pRoot->pData;
      pRoot = pRoot->pRightChild;
    }
  pPrev->pNextSibling = NULL;

  *ppForest = pFirst;
}

void genBinaryTreeForForest(LP_BI_TREE_NODE *ppNewRoot, LP_TREE_NODE pForest)
{
  LP_BI_TREE_NODE pRoot;

  if (pForest == NULL)
    {
      *ppNewRoot = NULL;
      return;
    }

  pRoot = (LP_BI_TREE_NODE)malloc(sizeof(BI_TREE_NODE));
  if (NULL == pRoot)
    {
      printf("Out Of Memory in Line %d, Function %s", __LINE__, __FUNCTION__);
      exit(OVERFLOW);      
    }
  pRoot->pData = (char *)malloc(sizeof(char));
  if (NULL == pRoot->pData)
    {
      printf("Out Of Memory in Line %d, Function %s", __LINE__, __FUNCTION__);
      exit(OVERFLOW);      
    }
  
  memcpy(pRoot->pData, &pForest->data, sizeof(char));
  genBinaryTreeForForest(&pRoot->pLeftChild, pForest->pFirstChild);
  genBinaryTreeForForest(&pRoot->pRightChild, pForest->pNextSibling);
  *ppNewRoot = pRoot;
}

void preOrderForest(LP_TREE_NODE pForest, VISIT_FUNC v)
{
  LP_TREE_NODE pIter = pForest;

  if (pIter == NULL)
    return;

  v((void *)pIter->data);
  preOrderForest(pIter->pFirstChild, v);
  preOrderForest(pIter->pNextSibling, v);
}

void inOrderForest(LP_TREE_NODE pForest, VISIT_FUNC v)
{
  LP_TREE_NODE pIter = pForest;
  
  if (pIter == NULL)
    return;

  inOrderForest(pIter->pFirstChild, v);
  v((void *)pIter->data);    
  inOrderForest(pIter->pNextSibling, v);
}

void destroyForest(LP_TREE_NODE pForest)
{
  if (pForest == NULL)
    return;
  
  destroyForest(pForest->pNextSibling);
  destroyForest(pForest->pFirstChild);
  free(pForest);
}
