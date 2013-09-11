#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "../include/mytype.h"

typedef char ElementType;

typedef struct _TreeNode_B
{
  ElementType data;
  struct _TreeNode_B *pLeftChild, *pRightChild;
}TreeNode_B, *LPTreeNode_B;

/****************************************************/

typedef struct _Child
{
  int idx;
  struct _Child *pNextSibling;
}Child, *LPChild;

typedef struct _TreeNode
{
  ElementType data;
  LPChild pFirstChild;
}TreeNode, *LPTreeNode;

typedef struct _Tree
{
  LPTreeNode pNode;
  unsigned int count;
  unsigned capacity;
  LPChild pRootList;
}Tree, *LPTree;

typedef Tree Forest;
typedef LPTree LPForest;


#define INIT_SIZE 5
#define INCRE_SIZE 5


int findNode(LPTree pTree, ElementType key)
{
  int i;
  for (i = 0; i < pTree->count; ++i)
    if (pTree->pNode[i].data == key)
      return i;
  return -1;
}

int getNode(LPTree pTree, ElementType key)
{
  if (pTree->count >= pTree->capacity) {
    pTree->pNode = realloc(pTree->pNode, sizeof(TreeNode) * (pTree->capacity + INCRE_SIZE));
    if (NULL == pTree->pNode) {
      printf ("Out Of Memory in %s", __func__);
      return -1;
    }
    pTree->capacity += INCRE_SIZE;
  }
  
  pTree->pNode[pTree->count].data = key;
  pTree->pNode[pTree->count].pFirstChild = NULL;
  
  ++pTree->count;
  return pTree->count-1;
}

bool insertToRoot(LPTree pTree, unsigned int idx)
{
  LPChild pNewRoot;
  LPChild *pp = &pTree->pRootList;
  
  pNewRoot = (LPChild)malloc(sizeof(Child));
  if (NULL == pNewRoot) {
    printf ("Out Of Memory in %s", __func__);
    return false;
  }
  
  pNewRoot->idx = idx;
  pNewRoot->pNextSibling = NULL;
  
  while(*pp)
    pp = &(*pp)->pNextSibling;
  *pp = pNewRoot;
  return true;
}

bool addChild(LPTree pTree, unsigned int rootIdx, unsigned int childIdx)
{
  LPChild pNewChild;
  LPChild *pp = &pTree->pNode[rootIdx].pFirstChild;
  
  pNewChild = (LPChild)malloc(sizeof(Child));
  if (NULL == pNewChild) {
    printf ("Out Of Memory in %s", __func__);
    return false;
  }
  
  pNewChild->idx = childIdx;
  pNewChild->pNextSibling = NULL;
  
  while(*pp)
    pp = &(*pp)->pNextSibling;
  *pp = pNewChild;
  return true;
}


bool initTree(LPTree *ppTree)
{
  LPTree pTree;

  pTree = (LPTree)malloc(sizeof(Tree));
  if (NULL == pTree) {
    printf ("Out Of Memory in %s", __func__);
    return false;
  }

  pTree->pNode = (LPTreeNode)malloc(sizeof(TreeNode) * INIT_SIZE);
  if (NULL == pTree->pNode) {
    printf ("Out Of Memory in %s", __func__);
    return false;
  }
  
  pTree->capacity = INIT_SIZE;
  pTree->count = 0;
  pTree->pRootList = NULL;
  *ppTree = pTree;
  return true;
}

void skipSpace(const char **pp)
{
  while(**pp == ' ')
    ++*pp;
}
bool createTree(LPTree *ppTree, const char **pp)
{
  LPTree pTree;
  char root, child;
  const char *p;
  int rootIdx, childIdx;

  if (!initTree(ppTree))
    return false;
  pTree = *ppTree;
  skipSpace(pp);
  p = *pp;
  while (*p != '\0') {
    root = *p;
    ++p;
    rootIdx = findNode(pTree, root);
    if (rootIdx < 0) {
      rootIdx = getNode(pTree, root);
      insertToRoot(pTree, rootIdx);
    }
    skipSpace(&p);
    if (*p == ';' || *p == '\0') {
    }
    else {
      assert(*p == '(');
      ++p;
      while(*p!= ')') {
	assert(findNode(pTree, *p) == -1);
	childIdx = getNode(pTree, *p);
	addChild(pTree, rootIdx, childIdx);
	++p;
	skipSpace(&p);
	if (*p == ',')
	  ++p;
      }
      ++p;
    }
    if (*p == ';')
      ++p;
    skipSpace(&p);
  }
}

void preOrderTraverseTree(LPTree pTree, LPChild pList,  VisitFunc visitor)
{
  if (pList == NULL)
    return;
  visitor(&pTree->pNode[pList->idx].data);
  preOrderTraverseTree(pTree, pTree->pNode[pList->idx].pFirstChild, visitor);
  preOrderTraverseTree(pTree, pList->pNextSibling, visitor);
}

void postOrderTraverseTree(LPTree pTree, LPChild pList, VisitFunc visitor)
{
  if (pList == NULL)
    return;
  postOrderTraverseTree(pTree, pTree->pNode[pList->idx].pFirstChild, visitor);
  visitor(&pTree->pNode[pList->idx].data);
  postOrderTraverseTree(pTree, pList->pNextSibling, visitor);
}

LPTreeNode_B convertTreeToBTree(LPTree pTree, LPChild pList)
{
  LPTreeNode_B pNew;

  if (NULL == pList)
    return NULL;

  pNew = (LPTreeNode_B)malloc(sizeof(TreeNode_B));
  if (NULL == pNew) {
    printf ("Out Of Memory in %s", __func__);
    return pNew;
  }
  pNew->data = pTree->pNode[pList->idx].data;
  pNew->pLeftChild = convertTreeToBTree(pTree, pTree->pNode[pList->idx].pFirstChild);
  pNew->pRightChild = convertTreeToBTree(pTree, pList->pNextSibling);
  return pNew;
}

void print(void *data)
{
  printf("%c", *(char *)data);
}

void preOrderTraverseBTree(LPTreeNode_B pRoot, VisitFunc visitor) 
{
  visitor(&pRoot->data);
  if (pRoot->pLeftChild)
    preOrderTraverseBTree(pRoot->pLeftChild, visitor);
  if (pRoot->pRightChild)
    preOrderTraverseBTree(pRoot->pRightChild, visitor);
}
void inOrderTraverseBTree(LPTreeNode_B pRoot, VisitFunc visitor) 
{
  if (pRoot->pLeftChild)
    inOrderTraverseBTree(pRoot->pLeftChild, visitor);
  visitor(&pRoot->data);
  if (pRoot->pRightChild)
    inOrderTraverseBTree(pRoot->pRightChild, visitor);
}


int main()
{

  LPTree pTree = NULL;
  LPTreeNode_B pTree_B = NULL;
  char buf[4096];
  const char *p;
  FILE *fp;
  int count;

  if (NULL == (fp = fopen("tree.txt", "r"))) {
    printf("Can't Open input file tree.txt");
    return 0;
  }
  
  count = fread(buf, 1, 4095, fp);
  if (count <= 0) {
    printf("Not enough items in input");
    fclose(fp);
    return 0;
  }
  
  // A(B,C,D); B(F); E(H,I); I(J)

  buf[count] = '\0';
  if (buf[count-1] == '\n')
    buf[count-1] = '\0';
  p = buf;
  createTree(&pTree, &p);
  if (NULL == pTree) {
    printf ("Failed to Create Tree\n");
    fclose(fp);
    return 0;
  }
  

  pTree_B = convertTreeToBTree(pTree, pTree->pRootList);
  if (NULL == pTree_B) {
    printf ("Failed to Convert Tree To Binary Tree\n");
    fclose(fp);
    return 0;
  }
  
  printf("\nPreOrder Tree\n");
  preOrderTraverseTree(pTree, pTree->pRootList, print);
  putchar('\n');

  printf("\nPreOrder Binary Tree\n");
  preOrderTraverseBTree(pTree_B, print);
  putchar('\n');

  printf("\nPostOrder Tree\n");
  postOrderTraverseTree(pTree, pTree->pRootList, print);
  putchar('\n');

  printf("\nInOrder Binary Tree\n");
  inOrderTraverseBTree(pTree_B, print);
  putchar('\n');


  return 0;
}
