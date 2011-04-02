#include "../include/common.h"

// %10 [0,60)  %30 [60,70) 30%[70,80) %15 [80,90) %5 [90,100]
// fail         meet       good       exceed       outstanding

// 1. Build Huffman Tree for search
// 2. Build Huffman Tree for code

typedef struct _TREE_NODE
{
  char *grade;
  int weight;
  int parent;
  int leftChild;
  int rightChild;
}TREE_NODE, *LP_TREE_NODE;

typedef struct 
{
  int first;
  int second;
}RESULT, *LP_RESULT;

// Huffman TREE always have 2n-1 node.

void inOrderTraverse(LP_TREE_NODE, int);
RESULT selectTwoMinimal(LP_TREE_NODE pStartNode, int from, int end);

int main()
{
  LP_TREE_NODE pStartNode;
  const int NODE_NUM = 5;
  int i = 0;
  RESULT result;
  char middle[10][30];
  static int middleIndex = 0;
  
  pStartNode = (LP_TREE_NODE)malloc((2*NODE_NUM - 1)*sizeof(TREE_NODE));
  if (NULL == pStartNode)
    {
      printf("Out Of Memory in Line %d, File %s", __LINE__, __FILE__);
      exit(OVERFLOW);
    }

  
  memset(middle, 0 ,sizeof(char)*10*30);
  memset(pStartNode , 0, sizeof(TREE_NODE)*(2*NODE_NUM - 1));

  (pStartNode)->grade = "fail";
  (pStartNode)->weight = 10;
  (pStartNode)->leftChild = -1;
  (pStartNode)->rightChild = -1;
  (pStartNode)->parent = -1;
  
  (pStartNode+1)->grade = "meet";
  (pStartNode+1)->weight = 30;
  (pStartNode+1)->leftChild = -1;
  (pStartNode+1)->rightChild = -1;
  (pStartNode+1)->parent = -1;

  (pStartNode+2)->grade = "good";
  (pStartNode+2)->weight = 30;
  (pStartNode+2)->leftChild = -1;
  (pStartNode+2)->rightChild = -1;
  (pStartNode+2)->parent = -1;
  
  (pStartNode+3)->grade = "exceed";
  (pStartNode+3)->weight = 20;
  (pStartNode+3)->leftChild = -1;
  (pStartNode+3)->rightChild = -1;
  (pStartNode+3)->parent = -1;

  (pStartNode+4)->grade = "outstanding";
  (pStartNode+4)->weight = 10;
  (pStartNode+4)->leftChild = -1;
  (pStartNode+4)->rightChild = -1;
  (pStartNode+4)->parent = -1;

  
  for (i = 0; i < NODE_NUM - 1; i++)
    {
      int dataIndex = 0;

      result = selectTwoMinimal(pStartNode, 0, NODE_NUM-1+i);
      (pStartNode + NODE_NUM + i)->leftChild = result.first;
      (pStartNode + NODE_NUM + i)->rightChild = result.second;
      (pStartNode + NODE_NUM + i)->parent = -1;
      (pStartNode + NODE_NUM + i)->weight = 
	(pStartNode + result.first)->weight + (pStartNode + result.second)->weight;

      (pStartNode + NODE_NUM + i)->grade = middle[middleIndex++];
      if ((pStartNode+result.first)->grade[1] != '+')
	{
	  (pStartNode + NODE_NUM + i)->grade[0] = (pStartNode+result.first)->grade[0];
	  dataIndex++;
	}
      else
	{
	  strcat((pStartNode + NODE_NUM + i)->grade, (pStartNode+result.first)->grade);
	  dataIndex += strlen((pStartNode+result.first)->grade);
	}
      (pStartNode + NODE_NUM + i)->grade[dataIndex++] = '+';
      if ((pStartNode+result.second)->grade[1] != '+')
	{
	  (pStartNode + NODE_NUM + i)->grade[dataIndex] = (pStartNode+result.second)->grade[0];
	}
      else
	{
	  strcat((pStartNode + NODE_NUM + i)->grade+dataIndex, (pStartNode+result.second)->grade);
	}


      (pStartNode + result.first)->parent = NODE_NUM + i;
      (pStartNode + result.second)->parent = NODE_NUM + i;  
      printf("\nSelect %d %s %d %s,Parent %d", 
	     result.first, 
	     (pStartNode+result.first)->grade?(pStartNode+result.first)->grade:"",
	     result.second,
	     (pStartNode+result.second)->grade?(pStartNode+result.second)->grade:"",
	     i);
    }

  inOrderTraverse(pStartNode,  2 * NODE_NUM - 2);
  putchar('\n');
  // Second Part, Encode

  






  return 0;
}
void inOrderTraverse(LP_TREE_NODE pStartNode, int rootIndex)
{
  static int count = 0;
  if((pStartNode + rootIndex)->leftChild >= 0)
    inOrderTraverse(pStartNode,(pStartNode + rootIndex)->leftChild);
    printf("\n%s", (pStartNode + rootIndex)->grade);

  if((pStartNode + rootIndex)->rightChild >= 0)
    inOrderTraverse(pStartNode,(pStartNode + rootIndex)->rightChild);
}

RESULT selectTwoMinimal(LP_TREE_NODE pStartNode, int from, int end)
{
  int i;
  RESULT result;
  
  result.first = -1;
  result.second = -1;
  
  for (i = from; i <= end; i++)
    {
      if ((pStartNode+i)->parent >= 0)
	continue;
      if (result.first == -1)
	result.first = i;
      else if((pStartNode + result.first)->weight > (pStartNode+i)->weight)
	{
	  result.second = result.first;
	  result.first = i;
	}
      else if (result.second == -1 ||
	       (pStartNode + result.second)->weight > (pStartNode+i)->weight )
	{
	  result.second = i;
	}
    }
  return result;
}
