#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "../include/mytype.h"

#define INIT_SIZE 5

#define INCRE_SIZE 5

typedef char ElementType;

typedef struct _Tok
{
  ElementType first;
  ElementType second;
}Tok, *LPTok;

typedef struct _Node
{
  int parent;
  ElementType data;
}SetNode, *LPSetNode;

typedef struct _Set
{
  LPSetNode pNode;
  unsigned int capacity;
  unsigned int count;
}Set, *LPSet;

void dumpSet(LPSet pSet) 
{
  int i;
  putchar('\n');
  for (i = 0; i < pSet->count; ++i) {
    char p='#';
    if (pSet->pNode[i].parent >= 0)
      p = pSet->pNode[pSet->pNode[i].parent].data;
    printf(" %c(%c) ", pSet->pNode[i].data, p);
  }

}
void initSet(LPSet *ppSet)
{
  LPSet pSet = (LPSet)malloc(sizeof(Set));
  *ppSet = NULL;
  if (NULL == pSet) {
    printf("Out Of Memory in %s", __func__);
    return;
  }
  
  pSet->pNode = (LPSetNode)malloc(sizeof(SetNode) * INIT_SIZE);
  if (NULL == pSet->pNode) {
    printf ("Out Of Memory in %s", __func__);
    free(pSet);
    return;
  }

  pSet->capacity = INIT_SIZE;
  pSet->count = 0;
  *ppSet = pSet;
}

void destroySet(LPSet *ppSet) 
{
  free((*ppSet)->pNode);
  free(*ppSet);
  *ppSet = NULL;
}

void skipSpace(const char **pp)
{
  while(**pp == ' ')
    ++*pp;
}
bool getNextTok(LPTok pTok, const char **pp)
{
  skipSpace(pp);
  if (**pp == '\0')
    return false;
  if (**pp != '(')
    return false;
  ++*pp;
  skipSpace(pp);
  pTok->first = **pp;
  ++*pp;
  if (**pp != ',')
    return false;
  ++*pp;
  pTok->second = **pp;
  ++*pp;
  skipSpace(pp);
  if (**pp != ')')
    return false;
  ++*pp;
  return true;
}

void unionNode(LPSet pSet, int lhs, int rhs)
{
  int i,j;
  
  i = findRoot(pSet, lhs);
  j = findRoot(pSet, rhs);
  if (pSet->pNode[i].parent > pSet->pNode[j].parent 
      || (pSet->pNode[i].parent == pSet->pNode[j].parent
	  && i > j)) {
    pSet->pNode[j].parent += pSet->pNode[i].parent;
    pSet->pNode[i].parent = j;
  }
  else {
    pSet->pNode[i].parent += pSet->pNode[j].parent;
    pSet->pNode[j].parent = i;
  }
}

int findRoot(LPSet pSet, int i)
{
  int k = i, j;
  while (pSet->pNode[k].parent >= 0)
    k = pSet->pNode[k].parent;

  while (i != k) {
    j = pSet->pNode[i].parent;
    pSet->pNode[i].parent = k;
    i = j;
  }
  return k;
}

int findNode(LPSet pSet, ElementType data)
{
  int i;
  for (i = 0; i < pSet->count; ++i) {
    if (pSet->pNode[i].data == data)
      return i;
  }
  
  return -1;
}

int insertNode(LPSet pSet, ElementType data)
{
  if (pSet->count >= pSet->capacity) {
    pSet->pNode = realloc(pSet->pNode, sizeof(SetNode) * 
			  (pSet->count + INCRE_SIZE));
    if (NULL == pSet->pNode) {
      printf("Out Of Memory in %s", __func__);
      exit(-1);
    }
    pSet->capacity = pSet->count + INCRE_SIZE;
  }

  (pSet->pNode+pSet->count)->parent = -1;
  (pSet->pNode+pSet->count)->data = data;
  
  ++pSet->count;
  return pSet->count-1;
}

int main()
{
  FILE *fp;
  char buf[4096];
  unsigned int count;
  const char *p = buf;
  Tok token;
  int lhs, rhs;
  LPSet pSet = NULL;

  if (NULL == (fp = fopen("equiv.txt", "r"))) {
    printf("Can't Open input equiv.txt");
    return 0;
  }

  count = fread(buf, 1, 4095, fp);
  if (count <= 0) {
    printf("Not enough items in input");
    fclose(fp);
    return 0;
  }

  if (buf[count-1] == '\n')
    buf[count-1] = '\0';
  else
    buf[count] = '\0';
  
  initSet(&pSet);

  
  

  while(getNextTok(&token, &p)) {
    lhs = findNode(pSet, token.first);
    rhs = findNode(pSet, token.second);
    if (lhs < 0) {
      lhs = insertNode(pSet, token.first);
    }
    if (rhs < 0) {
      rhs = insertNode(pSet, token.second);
    }
    
    unionNode(pSet, lhs, rhs);
  }

  dumpSet(pSet);
  destroySet(&pSet);
  fclose(fp);
  return 0;
}
