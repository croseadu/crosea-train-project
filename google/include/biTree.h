#ifndef _BI_TREE_H
#define _BI_TREE_H

#include "common.h"

typedef struct _BI_TREE
{
  char *pData;
  struct _BI_TREE *pLeftChild;
  struct _BI_TREE *pRightChild;
}BI_TREE_NODE, *LP_BI_TREE_NODE;

typedef void (*VISIT_FUNC)(void *);

STATUS createTreeV1(LP_BI_TREE_NODE *ppRoot);
STATUS creatTreeV2(LP_BI_TREE_NODE *ppRoot);
  
void preOrderTraverse(LP_BI_TREE_NODE pRoot, VISIT_FUNC visit);
void inOrderTraverse(LP_BI_TREE_NODE pRoot, VISIT_FUNC visit);
void postOrderTraverse(LP_BI_TREE_NODE pRoot, VISIT_FUNC visit);

void preOrderTraverStack(LP_BI_TREE_NODE pRoot, VISIT_FUNC visit);
void inOrderTraverseStack1(LP_BI_TREE_NODE pRoot, VISIT_FUNC visit);
void inOrderTraverseStack2(LP_BI_TREE_NODE pRoot, VISIT_FUNC visit);
#endif


