#include "../include/common.h"

typedef struct _NODE 
{
  int weight;
  int key;
  char *grade;
  struct _NODE *pLeftChild;
  struct _NODE *pRightChild;
}NODE, *LP_NODE;

LP_NODE recursiveBuild(LP_NODE pStartNode, int *w, int from, int end);
void preOrder(LP_NODE pRoot);
void inOrder(LP_NODE pRoot);
  const int NODE_NUM = 5;
// Build a Near Optimal Search Tree
//
int main() 
{
  LP_NODE pStartNode, pRoot;
  int *w = NULL;

  int i;


  pStartNode = (LP_NODE)malloc(sizeof(NODE) * NODE_NUM);
  if (NULL == pStartNode)
    {
      printf("Out Of Memory in line %d, file %s", __LINE__, __FILE__);
      exit(OVERFLOW);
    }

  memset(pStartNode, 0, sizeof(NODE) * NODE_NUM);

  (pStartNode)->weight = 10;
  (pStartNode)->grade = "fail";
  (pStartNode)->key = 59;

  (pStartNode+1)->weight = 30;
  (pStartNode+1)->grade = "meet";
  (pStartNode+1)->key = 69;

  (pStartNode+2)->weight = 30;
  (pStartNode+2)->grade = "good";
  (pStartNode+2)->key = 79;

  (pStartNode+3)->weight = 20;
  (pStartNode+3)->grade = "exceed";
  (pStartNode+3)->key = 89;

  (pStartNode+4)->weight = 10;
  (pStartNode+4)->grade = "outstanding";
  (pStartNode+4)->key = 99;

  w = (int *)malloc(sizeof(int)*NODE_NUM);
  if (NULL == w)
    {
      printf("Out Of Memory in Line %d, File %s", __LINE__, __FILE__);
      exit(OVERFLOW);
    }

  w[0] = (pStartNode)->weight;
  for (i = 1; i < NODE_NUM; i++)
    w[i] = w[i-1] + (pStartNode+i)->weight;

  pRoot = recursiveBuild(pStartNode, w, 0, NODE_NUM-1);
  
  printf("\nPreOrder:\n");
  preOrder(pRoot);
  printf("\nInOrder:\n");
  inOrder(pRoot);
  
  free(pStartNode);
  free(w);
  return 0;
}

void preOrder(LP_NODE pRoot)
{
  printf(" %s ", pRoot->grade);
  if (pRoot->pLeftChild)
    preOrder(pRoot->pLeftChild);
  if (pRoot->pRightChild)
    preOrder(pRoot->pRightChild);
}
void inOrder(LP_NODE pRoot)
{
  if (pRoot->pLeftChild)
    inOrder(pRoot->pLeftChild);
  printf(" %s ", pRoot->grade);
  if (pRoot->pRightChild)
    inOrder(pRoot->pRightChild);
}

LP_NODE recursiveBuild(LP_NODE pStartNode, int *w, int from, int end)
{
  LP_NODE pRoot;
  int min, minIndex;
  int gap, i;

  min = 0x7FFFFFFF;
  minIndex = -1;

  for (i = from; i <= end; i++)
    {
      gap = w[end] - w[i] - (i>0?w[i-1]:0);
      if (gap < 0)
	gap = -gap;

      if (gap < min)
	{
	  min = gap;
	  minIndex = i;
	}
    }

  i = minIndex;
  pRoot = pStartNode+i;
  if (i > from)
    pRoot->pLeftChild = recursiveBuild(pStartNode, w, from, i-1);
  else
    pRoot->pLeftChild = NULL;

  if (i < end)
    pRoot->pRightChild = recursiveBuild(pStartNode, w, i+1, end);
  else
    pRoot->pRightChild = NULL;
      
  return pRoot;
}
