#include "../include/common.h"

typedef struct _BI_TREE
{
  int key;
  struct _BI_TREE *pLeftChild;
  struct _BI_TREE *pRightChild;
  int height;
}TREE, *LP_TREE;

#define H(a) ((a)?(a)->height:0)

void inOrder(LP_TREE pRoot);
void preOrder(LP_TREE pRoot);
void postOrder(LP_TREE pRoot);
void destroyTree(LP_TREE pRoot);
void insertToSortedTree(LP_TREE *ppTree, const int data);
void insertToBalenceSortedTree(LP_TREE *ppTree, const int data);
void RightRotate(LP_TREE *ppTree);
void LeftRotate(LP_TREE *ppTree);

int main()
{
  FILE *fp;
  char buf[4096];
  int *pInputData = NULL;
  int index, curIndex;
  LP_TREE pRoot = NULL;
  int i;

  fp = fopen("inputDataForSortedTree.txt", "r");
  if (NULL == fp)
    {
      printf("Cannot Open File:inputDataForSortedTree.txt\n");
      exit(-1);
    }

  pInputData = (int *)malloc(sizeof(int)*4096);
  index = 0;
  while (fgets(buf, 4095, fp))
    {
      curIndex = 0;

      while (buf[curIndex] == '\t' || buf[curIndex] == ' ')
	curIndex++;

      while (sscanf(buf+curIndex, "%d", pInputData+index))
	{
	  index++;
	  while (isdigit(buf[curIndex]))
	    curIndex++;
	  while (buf[curIndex] == '\t' || buf[curIndex] == ' ')
	    curIndex++;
	  if (buf[curIndex] == '\n')
	    break;
	}
	assert(index < 4096);
    }
  
  printf("\nInputData is :\n");
  for (i = 0; i < index; i++)
    {
      printf ("%5d", pInputData[i]);
    }
  putchar('\n');


  for (i = 0; i < index; i++)
    //insertToSortedTree(&pRoot, pInputData[i]);
    {
      insertToBalenceSortedTree(&pRoot, pInputData[i]);
      printf("\nInsert %d, newRoot %d\n",pInputData[i], pRoot->key);
    }
  printf("\nPre:");
  if (pRoot)
    preOrder(pRoot);
  printf("\nIn:");
  if (pRoot)
    inOrder(pRoot);
  printf("\nPost:");
  if (pRoot)
    postOrder(pRoot);
  putchar('\n');
  
  if (pRoot)
    destroyTree(pRoot);
  if (pInputData)
    free(pInputData);

  return 0;
}

void postOrder(LP_TREE pRoot)
{

  if (pRoot->pLeftChild)
    postOrder(pRoot->pLeftChild);
  if (pRoot->pRightChild)
    postOrder(pRoot->pRightChild);
  printf("%5d", pRoot->key);
}

void preOrder(LP_TREE pRoot)
{
  printf("%5d", pRoot->key);
  if (pRoot->pLeftChild)
    preOrder(pRoot->pLeftChild);
  if (pRoot->pRightChild)
    preOrder(pRoot->pRightChild);
}

void inOrder(LP_TREE pRoot)
{
  if (pRoot->pLeftChild)
    inOrder(pRoot->pLeftChild);
  printf("%5d", pRoot->key);
  if (pRoot->pRightChild)
    inOrder(pRoot->pRightChild);
}

void destroyTree(LP_TREE pRoot)
{
  if (pRoot->pLeftChild)
    destroyTree(pRoot->pLeftChild);
  if (pRoot->pRightChild)
    destroyTree(pRoot->pRightChild);
  free(pRoot);

}

void insertToSortedTree(LP_TREE *ppTree, const int data)
{
  LP_TREE pTree = *ppTree;

  if (NULL == pTree)
    {
      pTree = (LP_TREE)malloc(sizeof(TREE));
      if (NULL == pTree)
	{
	  printf("Out Of Memory in Line %d, Function %s", __LINE__, __FUNCTION__);
	  exit(OVERFLOW);
	}
      pTree->pLeftChild = pTree->pRightChild = NULL;
      pTree->key = data;
      pTree->height = 1;

      *ppTree = pTree;
    }
  else
    {
      if (pTree->key == data)
	{
	  return;
	}
      else if (pTree->key > data)
	{
	  insertToSortedTree(&pTree->pLeftChild, data);
	  if (pTree->pLeftChild->height + 1 > pTree->height)
	    pTree->height = pTree->pLeftChild->height+1;
	}
      else
	{
	  insertToSortedTree(&pTree->pRightChild, data);
	  if (pTree->pRightChild->height + 1 > pTree->height)
	    pTree->height = pTree->pRightChild->height+1;
	}
    }
}


void insertToBalenceSortedTree(LP_TREE *ppTree, const int data)
{
  LP_TREE pTree = *ppTree;
  int delta;

  if (NULL == pTree)
    {
      pTree = (LP_TREE)malloc(sizeof(TREE));
      if (NULL == pTree)
	{
	  printf("Out Of Memory in Line %d, Function %s", __LINE__, __FUNCTION__);
	  exit(OVERFLOW);
	}
      pTree->pLeftChild = pTree->pRightChild = NULL;
      pTree->key = data;
      pTree->height = 1;

    }
  else
    {
      if (pTree->key == data)
	{
	  return;
	}
      else if (pTree->key > data)
	{
	  insertToBalenceSortedTree(&pTree->pLeftChild, data);
	  delta = pTree->pLeftChild->height -
	    ((pTree->pRightChild)?pTree->pRightChild->height:0);
	  if (delta >= 2)
	    {
	      //Insert To LeftChild's LeftChild
	      if (H(pTree->pLeftChild->pLeftChild) >
		  H(pTree->pLeftChild->pRightChild))
		{
		  RightRotate(&pTree);
		}
	      else
		{
		  LeftRotate(&pTree->pLeftChild);
		  RightRotate(&pTree);
		}

	    }

	  if (pTree->pLeftChild->height + 1 > pTree->height)
	    pTree->height = pTree->pLeftChild->height+1;
	}
      else
	{
	  insertToBalenceSortedTree(&pTree->pRightChild, data);
	  delta = pTree->pRightChild->height - 
	    ((pTree->pLeftChild)?pTree->pLeftChild->height:0);
	  if (delta >= 2)
	    {
	      //Insert To RightChild's Rightchild
	      if (H(pTree->pRightChild->pLeftChild) < 
		  H(pTree->pRightChild->pRightChild))
		{
		  LeftRotate(&pTree);
		}
	      else
		{
		  RightRotate(&pTree->pRightChild);
		  LeftRotate(&pTree);
		}

	    }


	  if (pTree->pRightChild->height + 1 > pTree->height)
	    pTree->height = pTree->pRightChild->height+1;
	}
    }

      *ppTree = pTree;
}

void RightRotate(LP_TREE *ppTree)
{
  LP_TREE pTree = *ppTree;
  LP_TREE newRoot = pTree->pLeftChild;
  
  printf("\nRightRotate:%d", pTree->key);
  pTree->pLeftChild = newRoot->pRightChild;
  pTree->height = 1 + MAX(pTree->pLeftChild?pTree->pLeftChild->height:0,
			  pTree->pRightChild?pTree->pRightChild->height:0);

  newRoot->pRightChild = pTree;
  newRoot->height = 1 +MAX(newRoot->pLeftChild?newRoot->pLeftChild->height:0,
			   newRoot->pRightChild?newRoot->pRightChild->height:0);

  *ppTree = newRoot;
}


void LeftRotate(LP_TREE *ppTree)
{
  LP_TREE pTree = *ppTree;
  LP_TREE newRoot = pTree->pRightChild;
  
  printf("\nLeftRotate:%d", pTree->key);
  pTree->pRightChild = newRoot->pLeftChild;
  pTree->height = 1 + MAX(pTree->pLeftChild?pTree->pLeftChild->height:0,
			  pTree->pRightChild?pTree->pRightChild->height:0);

  newRoot->pLeftChild = pTree;
  newRoot->height = 1 +MAX(newRoot->pLeftChild?newRoot->pLeftChild->height:0,
			   newRoot->pRightChild?newRoot->pRightChild->height:0);

  *ppTree = newRoot;
}
