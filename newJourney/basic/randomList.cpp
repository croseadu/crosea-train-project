

#include <iostream>

class List
{
public:
  int data;
  List *pNext;
  List *pRandom;
};

int main()
{
  int i;
  List *pHead;
  pHead = new List();
  pHead->data = 4;
  pHead->pNext = 0;
  for (i = 3; i > 0; i--)
    {
      List *pNode = new List();
      pNode->data = i;
      pNode->pNext = pHead;
      pHead = pNode;
    }

  pHead->pRandom = pHead->pNext->pNext;
  pHead->pNext->pRandom = pHead;
  pHead->pNext->pNext->pRandom = pHead->pNext->pNext->pNext;
  pHead->pNext->pNext->pNext->pRandom = pHead->pNext;

  List *pIter = pHead;
  while (pIter)
    {
    std::cout<<"[ "<< pIter->data<<" :"<<pIter->pRandom->data<<" ]";
    pIter = pIter->pNext;
    }
std::cout<<std::endl;

  
  List *pCopyHead;
  pIter = pHead;
  while (pIter)
    {
      List *pNode = new List();
      pNode->data = pIter->data+10;
      pNode->pRandom = pIter->pRandom;
      pNode->pNext = pIter->pRandom;
      pIter->pRandom = pNode;
      pIter = pIter->pNext;
    }
 pCopyHead = pHead->pRandom;
  pIter = pHead;
  while (pIter)
    {
      pIter->pRandom->pRandom = pIter->pRandom->pRandom->pRandom;
      pIter = pIter->pNext;
    }
 
  pIter = pHead;
  while (pIter)
    {
      List *p = pIter->pRandom;
      pIter->pRandom = pIter->pRandom->pNext;
      p->pNext = pIter->pNext?pIter->pNext->pRandom:0;
      pIter = pIter->pNext;
    }

  std::cout<<std::endl;
  pIter = pCopyHead;
  while (pIter)
    {
      std::cout<<"[ "<< pIter->data<<" :"<<pIter->pRandom->data<<" ]";
      pIter = pIter->pNext;
    }
    std::cout<<std::endl;
  return 0;
}
