#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "../include/mytype.h"

typedef float ElementType;

typedef struct _HuffmanTreeNode 
{
  ElementType data;
  int parent, leftChild, rightChild;
}HTNode, *LPHTNode;

typedef struct _Pair
{
  unsigned int first;
  unsigned int second;
}Pair;

void dump(HTNode *pRoot, int i)
{
  printf("[%d]%f(%d,%d)\n", i, pRoot[i].data, pRoot[i].leftChild, pRoot[i].rightChild);
  if (pRoot[i].leftChild >= 0)
    dump(pRoot, pRoot[i].leftChild);
  if (pRoot[i].rightChild >= 0)
    dump(pRoot, pRoot[i].rightChild);
}

Pair selectMinTwo(HTNode *ht, int n)
{
  int i = 0;
  int first, second;
  float min1, min2;
  Pair s;

  first = second = -1;
  for (i = 0; i < n; ++i) {
    if (ht[i].parent >= 0)
      continue;
    if (first == -1) {
      first = i;
      min1 = ht[first].data;
      continue;
    }
    if (second == -1) {
      second = i;
      if (ht[second].data < ht[first].data) {
	second = first;
	first = i;
	min1 = ht[first].data;
	min2 = ht[second].data;
      }
      else
	min2 = ht[second].data;
      continue;
    }
    
    if (ht[i].data < min1) {
      second = first;
      min2 = min1;
      first = i;
      min1 = ht[first].data;
    }
    else if (ht[i].data < min2) {
      second = i;
      min2 = ht[i].data;
    }
  }
  
  s.first = first;
  s.second = second;
  return s;
}
int main()
{

  float w[] = {0.05f, 0.29f,0.07f,0.08f,0.14f,0.23f,0.03f,0.11f};
  HTNode ht[sizeof(w)/sizeof(float)*2-1];
  int n,m;
  int i;
  int k, numOfBits;
  Pair min; 
  char code[n];

  n = sizeof(w)/sizeof(w[0]);
  m = 2*n-1;
  for (i = 0; i < n; ++i) {
    ht[i].data= w[i];
    ht[i].parent = -1;
    ht[i].leftChild = ht[i].rightChild = -1;
  }
   
  memset((void *)(&ht[n]), 0, (n-1)*sizeof(HTNode));
  
  for (i = n; i < m; ++i) {
    min = selectMinTwo(ht, i);
    ht[i].leftChild = min.first;
    ht[i].rightChild = min.second;
    ht[i].parent = -1;
    ht[i].data = ht[min.first].data + ht[min.second].data;
    ht[min.first].parent = ht[min.second].parent = i;
  }

  putchar('\n');
  dump(ht, m-1);
  putchar('\n');

  for ( i = 0; i < n; ++i) {
    memset((void *)code, 0, sizeof(code));
    numOfBits = 0;
    k = i;
    while(ht[k].parent >= 0) {
      ++numOfBits;
      k = ht[k].parent;
    }
    assert(numOfBits < n);
    k = i;
    code[numOfBits] = '\0';
    while(ht[k].parent >= 0) {
      if (ht[ht[k].parent].leftChild == k)
	code[numOfBits-1] = '0';
      else
	code[numOfBits-1] = '1';
      --numOfBits;
      k = ht[k].parent;
    }
    assert(numOfBits == 0);
    printf("%f %s\n", ht[i].data, code);
  }




  return 0;
}
