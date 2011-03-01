
#include "../include/biTree.h"
#include "../include/stack.h"

static STATUS createTreeRecursiveV1(LP_BI_TREE_NODE *ppNode, char *pData, unsigned int *pCurIndex)
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
  
  status = createTreeRecursiveV1(&pNode->pLeftChild, pData, pCurIndex);
  if (status != OK)
    return status;
  status = createTreeRecursiveV1(&pNode->pRightChild, pData, pCurIndex);
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
  if (createTreeRecursiveV1(&pRoot, pInputData ,&index) != OK)
    {
      free(pInputData);
      printf("Create Tree Recursive Fail\n");
      return ERROR;
    }

  *ppRoot = pRoot;
  fclose(fp);
  return OK;
}

static STATUS createTreeRecursiveV2(LP_BI_TREE_NODE *ppRoot, const char *pPreData, const char * pInData, unsigned int size)
{
  LP_BI_TREE_NODE pRoot = NULL;
  char root;
  int index;
  STATUS status;

  if (size == 0)
    {
      *ppRoot = NULL;
      return OK;
    }

  root = pPreData[0];
  index = 0;
  while (index < size && pInData[index] != root)
    index++;

  if (index >= size)
    {
      printf("Error in Input, line %d", __LINE__);
      return ERROR;
    }
  pRoot = (LP_BI_TREE_NODE)malloc(sizeof(BI_TREE_NODE));
  if (NULL == pRoot)
    {
      printf("Out Of Memory in Line %d, Function %s", __LINE__, __FUNCTION__);
      return OVERFLOW;
    }
  pRoot->pData = (char *)malloc(sizeof(char));
  if (NULL == pRoot->pData)
    {
      printf("Out Of Memory in Line %d, Function %s", __LINE__, __FUNCTION__);
      return OVERFLOW;
    }
    
  *(char *)pRoot->pData = root;
  
  status = createTreeRecursiveV2(&pRoot->pLeftChild, pPreData+1, pInData, index);
  if (status != OK)
    return status;
  
  status = createTreeRecursiveV2(&pRoot->pRightChild, pPreData+index+1, pInData+index+1, size-index-1);
  if (status != OK)
    return status;
  
  *ppRoot = pRoot;
  return OK;
}  

STATUS createTreeV2(LP_BI_TREE_NODE *ppRoot)
{
  LP_BI_TREE_NODE pRoot = NULL;
  FILE *fp;
  char *pPreOrderData = NULL;
  char *pInOrderData = NULL;

#define MAX_SIZE 4096
  pPreOrderData = (char *)malloc(sizeof(char) * MAX_SIZE);
  pInOrderData = (char *)malloc(sizeof(char) * MAX_SIZE);

  if (NULL == pPreOrderData || NULL == pInOrderData)
    return OVERFLOW;
  memset (pPreOrderData, 0, MAX_SIZE * sizeof(char));
  memset (pInOrderData, 0, MAX_SIZE * sizeof(char)); 

  if ((fp = fopen("inputData.txt", "r")) == NULL)
    {
      printf("Cannot Open File InputData.txt\n");
      return ERROR;
    }

  fscanf(fp, "%s", pPreOrderData);
  if (feof(fp))
    return ERROR;
  fscanf(fp, "%s", pInOrderData);
  
  if (pPreOrderData[0] == 0 || pInOrderData[0] == 0)
    return ERROR;
  
  if (strlen(pPreOrderData) != strlen(pInOrderData))
    return ERROR;

  createTreeRecursiveV2(&pRoot, pPreOrderData, pInOrderData, strlen(pPreOrderData));  

  *ppRoot = pRoot;
  fclose(fp);
  free(pPreOrderData);
  free(pInOrderData);
  return OK;
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
  LP_STACK pStack = NULL;
  STATUS status;
  LP_BI_TREE_NODE pNode;


  status = createStack(&pStack, sizeof(LP_BI_TREE_NODE));
  if (status != OK)
    {
      printf("Create Stack Failed\n");
      return;
    }

  push(pStack, &pTree);
  while(!isStackEmpty(pStack))
    {
      pop(pStack, &pNode);
      visit(pNode->pData);
      if (pNode->pLeftChild)
	push (pStack, &pNode->pLeftChild);
      if (pNode->pRightChild)
	push (pStack, &pNode->pRightChild);
    }


  destroyStack(pStack);
}
void inOrderTraverseStack1(LP_BI_TREE_NODE pTree, VISIT_FUNC visit)
{
  LP_STACK pStack = NULL;
  STATUS status;
  LP_BI_TREE_NODE pNode;


  status = createStack(&pStack, sizeof(LP_BI_TREE_NODE));
  if (status != OK)
    {
      printf("Create Stack Failed\n");
      return;
    }

  pNode = pTree;
  while (pNode || !isStackEmpty(pStack))
    {
      if (pNode)
	{
	  while(pNode)
	    {
	      push (pStack, &pNode);
	      pNode = pNode->pLeftChild;
	    }
	}
      else
	{
	  pop(pStack, &pNode);
	  visit(pNode->pData);
	  pNode = pNode->pRightChild;
	}
    }
  destroyStack(pStack);
}
void inOrderTraverseStack2(LP_BI_TREE_NODE pTree, VISIT_FUNC visit)
{
  LP_STACK pStack = NULL;
  STATUS status;
  LP_BI_TREE_NODE pNode;


  status = createStack(&pStack, sizeof(LP_BI_TREE_NODE));
  if (status != OK)
    {
      printf("Create Stack Failed\n");
      return;
    }
  push (pStack, &pTree);
  while (!isStackEmpty(pStack))
    {
      getTop(pStack, &pNode);
 
    }
  destroyStack (pStack);
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

  

