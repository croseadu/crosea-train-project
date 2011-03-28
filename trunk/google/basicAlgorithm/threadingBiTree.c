#include "../include/common.h"
#include "../include/stack.h"


typedef struct _T_BI_TREE
{
  char *pData;
  struct _T_BI_TREE *pLeftChild;
  struct _T_BI_TREE *pRightChild;
  BOOL bLeftTag;
  BOOL bRightTag;
}T_BI_TREE_NODE, *LP_T_BI_TREE_NODE;

static STATUS createTreeRecursive(LP_T_BI_TREE_NODE *, char *, unsigned int *);
void preOrderTraverse(LP_T_BI_TREE_NODE pRoot, VISIT_FUNC visit);
void inOrderTraverse(LP_T_BI_TREE_NODE pRoot, VISIT_FUNC visit);
void destroyTree(LP_T_BI_TREE_NODE pRoot);

void threadingTree(LP_T_BI_TREE_NODE pRoot, LP_T_BI_TREE_NODE *ppThreadRoot);
void threadVisit(LP_T_BI_TREE_NODE pThreadRoot, VISIT_FUNC visit);

static int count = 0;
void visitNode(void *pData)
{
  putchar((*(char *)pData));
}

void limitVisitNode(void *pData)
{
  if (count++ < 20)
    {
      putchar((*(char *)pData));
    }
}

int main()
{
  LP_T_BI_TREE_NODE pRoot = NULL, pThreadRoot = NULL;

  if (createTree(&pRoot) != OK)
    {
      printf("Exit: Failed to create tree\n");
      exit(-1);
    }
  printf("\nStart PreOrderTraverse:");
  preOrderTraverse(pRoot, visitNode);
  printf("\nStart InOderTraverse:");
  inOrderTraverse(pRoot, visitNode);
  
  printf("\nThreading The Binary Tree");
  threadingTree(pRoot, &pThreadRoot);
  printf("\nInOrder ThreadingVisit:");
  threadVisit(pThreadRoot, limitVisitNode);
  printf("\n");
  destroyTree(pRoot);
  return 0;
}

/* Input is a preOrder data, and use ' ' to mark a NULL child */
STATUS createTree(LP_T_BI_TREE_NODE *ppRoot)
{
  LP_T_BI_TREE_NODE pRoot = NULL;
  char *pInputData, c;
  unsigned int index = 0, maxSize;
  FILE *fp;
  
  if ((fp = fopen("inputDataTree.txt", "r")) == NULL)
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
  fclose(fp);
  return OK;
}

static STATUS createTreeRecursive(LP_T_BI_TREE_NODE *ppNode, char *pData, unsigned int *pCurIndex)
{
  LP_T_BI_TREE_NODE pNode;
  STATUS status;

  if (pData[*pCurIndex] == ' ')
    {
      (*pCurIndex)++;
      *ppNode = NULL;
      return OK;
    }

  pNode = (LP_T_BI_TREE_NODE)malloc(sizeof(T_BI_TREE_NODE));
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

  pNode->bLeftTag = FALSE;
  pNode->bRightTag = FALSE;
  
  status = createTreeRecursive(&pNode->pLeftChild, pData, pCurIndex);
  if (status != OK)
    return status;
  status = createTreeRecursive(&pNode->pRightChild, pData, pCurIndex);
  if (status != OK)
    return status;

  *ppNode = pNode;
  
  return OK;
}

void preOrderTraverse(LP_T_BI_TREE_NODE pTree, VISIT_FUNC visit)
{
  visit(pTree->pData);
  if (!pTree->bLeftTag && pTree->pLeftChild)
    preOrderTraverse(pTree->pLeftChild, visit);
  if (!pTree->bRightTag && pTree->pRightChild)
    preOrderTraverse(pTree->pRightChild, visit);
}

void inOrderTraverse(LP_T_BI_TREE_NODE pTree, VISIT_FUNC visit)
{
  if (!pTree->bLeftTag && pTree->pLeftChild)
    inOrderTraverse(pTree->pLeftChild, visit);
  visit(pTree->pData);
  if (!pTree->bRightTag && pTree->pRightChild)
    inOrderTraverse(pTree->pRightChild, visit);
}


void destroyTree(LP_T_BI_TREE_NODE pRoot)
{
  if (!pRoot->bLeftTag && pRoot->pLeftChild)
    destroyTree(pRoot->pLeftChild);
  if (!pRoot->bRightTag && pRoot->pRightChild)
    destroyTree(pRoot->pRightChild);
  free(pRoot->pData);
  free(pRoot);
}
static LP_T_BI_TREE_NODE pre;
void thread(LP_T_BI_TREE_NODE pRoot)
{
  if (pRoot->pLeftChild)
    thread(pRoot->pLeftChild);
  if (pre->pRightChild == NULL)
    {
      pre->pRightChild = pRoot;
      pre->bRightTag = TRUE;
    }
  if (pRoot->pLeftChild == NULL)
    {
      pRoot->pLeftChild = pre;
      pRoot->bLeftTag = TRUE;
    }
  pre = pRoot;
  if (pRoot->pRightChild)
    thread(pRoot->pRightChild);
}

void threadingTree(LP_T_BI_TREE_NODE pRoot, LP_T_BI_TREE_NODE *ppThreadRoot)
{

  pre = (LP_T_BI_TREE_NODE)malloc(sizeof(T_BI_TREE_NODE));
  if (NULL == pre)
    {
      printf("Out Of Memory in Line %d, Function %s", __LINE__, __FUNCTION__);
      exit(OVERFLOW);
    }

  *ppThreadRoot = pre;

  pre->pLeftChild = pRoot;
  pre->bLeftTag = FALSE;
  thread(pRoot);
  assert(pre->pRightChild == NULL);
  pre->pRightChild = *ppThreadRoot;
  pre->bRightTag = TRUE;
  (*ppThreadRoot)->pRightChild = pre;
}


void threadVisit(LP_T_BI_TREE_NODE pThreadRoot, VISIT_FUNC visit)
{
  LP_T_BI_TREE_NODE pIterNode;
  pIterNode = pThreadRoot->pLeftChild;
  while (pIterNode != pThreadRoot)
    {
      while (!pIterNode->bLeftTag && pIterNode->pLeftChild)
	pIterNode = pIterNode->pLeftChild;
      visit(pIterNode->pData);
      while (pIterNode->bRightTag && pIterNode->pRightChild != pThreadRoot)
	{
	  pIterNode = pIterNode->pRightChild;
	  visitNode(pIterNode->pData);
	}
      pIterNode = pIterNode->pRightChild;
    }
}
