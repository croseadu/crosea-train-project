
#include "../include/biTree.h"

static STATUS createTreeRecursive(LP_BI_TREE_NODE *ppNode, char *pData, unsigned int *pCurIndex)
{
  LP_BI_TREE_NODE pNode;
  STATUS status;

  if (pData[*pCurIndex] == ' ')
    {
      (*pCurIndex)++;
      *ppNode = NULL;
      return OK;
    }

  pNode = (LP_BI_TREE_NODE)malloc(sizeof(BI_TREE_NODE));
  if (NULL == pNode)
    {
      printf("Out Of Memory in line %d function %s", __LINE__, __FUNCTION__);
      return OVERFLOW;
    }
  pNode->pData = (char *)malloc(sizeof(char));
  if (NULL == pNode->pData)
    {
      printf("Out Of Memory in line %d function %s", __LINE__, __FUNCTION__);
      free(pNode);
      return OVERFLOW;
    }
  *pNode->pData = pData[*pCurIndex];
  (*pCurIndex)++;
  
  status = createTreeRecursive(&pNode->pLeftChild, pData, pCurIndex);
  if (status != OK)
    return status;
  status = createTreeRecursive(&pNode->pRightChild, pData, pCurIndex);
  if (status != OK)
    return status;

  *ppNode = pNode;
  
  return OK;
}

/* Input is a preOrder data, and use ' ' to mark a NULL child */
STATUS createTreeV1(LP_BI_TREE_NODE *ppRoot)
{
  LP_BI_TREE_NODE pRoot = NULL;
  char *pInputData, c;
  unsigned int index = 0, maxSize;
  FILE *fp;
  
  if ((fp = fopen("inputData.txt", "r")) == NULL)
    {
      printf("Cannot Open File : inputData.txt\n");
      return ERROR;
    }

#define INIT_SIZE 10
#define INCRE_SIZE 5
  
  pInputData = (char *)malloc(sizeof(char)*INCRE_SIZE);
  if (NULL == pInputData)
    {
      printf("Out Of Memory in Line %d, Function %s", __LINE__, __FUNCTION__);
      return OVERFLOW;
    }
  maxSize = INIT_SIZE;

  while ((c = fgetc(fp)) != EOF)
    {
      pInputData[index++] = c;
      if (index >= maxSize)
	{
	  pInputData = (char *)realloc(pInputData, (maxSize + INCRE_SIZE)*sizeof(char));
	  if (NULL == pInputData)
	    {
	      printf("Out Of Memory in Line %d, Function %s", __LINE__, __FUNCTION__);
	      return OVERFLOW;
	    }	  
	  maxSize += INCRE_SIZE;
	}
    }

  pInputData[index] = ' ';

  index = 0;
  if (createTreeRecursive(&pRoot, pInputData ,&index) != OK)
    {
      free(pInputData);
      printf("Create Tree Recursive Fail\n");
      return ERROR;
    }

  *ppRoot = pRoot;
  return OK;
}
  
STATUS createTreeV2(LP_BI_TREE_NODE *ppRoot)
{

}


void preOrderTraverse(LP_BI_TREE_NODE pTree, VISIT_FUNC visit)
{
  visit(pTree->pData);
  if (pTree->pLeftChild)
    preOrderTraverse(pTree->pLeftChild, visit);
  if (pTree->pRightChild)
    preOrderTraverse(pTree->pRightChild, visit);
}

void inOrderTraverse(LP_BI_TREE_NODE pTree, VISIT_FUNC visit)
{
  if (pTree->pLeftChild)
    inOrderTraverse(pTree->pLeftChild, visit);
  visit(pTree->pData);
  if (pTree->pRightChild)
    inOrderTraverse(pTree->pRightChild, visit);
}

void postOrderTraverse(LP_BI_TREE_NODE pTree, VISIT_FUNC visit)
{
  if (pTree->pLeftChild)
    postOrderTraverse(pTree->pLeftChild, visit);
  if (pTree->pRightChild)
    postOrderTraverse(pTree->pRightChild ,visit);
  visit(pTree->pData);
}

void preOrderTraverStack(LP_BI_TREE_NODE pTree, VISIT_FUNC visit)
{
}
void inOrderTraverseStack1(LP_BI_TREE_NODE pTree, VISIT_FUNC visit)
{
}
void inOrderTraverseStack2(LP_BI_TREE_NODE pTree, VISIT_FUNC visit)
{
}
  
void destroyTree(LP_BI_TREE_NODE pRoot)
{
  if (pRoot->pLeftChild)
    destroyTree(pRoot->pLeftChild);
  if (pRoot->pRightChild)
    destroyTree(pRoot->pRightChild);
  free(pRoot->pData);
  free(pRoot);
}

  

