#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
using std::ifstream;
using std::ofstream;
using std::cin;
using std::cout;
using std::endl;

#include "linkList.h"

template <class T>
class equalTo
{
  T keyVal;
public:
  explicit equalTo(T val):keyVal(val){}
  bool operator()(T val) const
  {
    return val == keyVal;
  }
};

template <class T>
class modTo
{
  T keyVal;
public:
  explicit modTo(T val):keyVal(val){}
  bool operator()(T val) const
  {
    return val > 10 || (val < 8 && val > 5);
  }
};

int main()
{

  // **
  LinkList<int> *pHead = NULL;
  initLinkList(&pHead);

  int temp;
  while(std::cin>>temp)
    LinkListInsert(&pHead, temp, static_cast<LinkList<int> *>(0));
  PrintLinkList(pHead);
  
  //int Idx = locateItem(pHead, equalTo<int>(12));
  //cout<<endl<<"Find "<<12<<" Idx : " << Idx <<endl;
  
  //reverseLinkList(&pHead);
  //PrintLinkList(pHead);

  LinkListDeleteVal(&pHead, modTo<int>(3));

  PrintLinkList(pHead);

  //clearList(pHead);
  destroyLinkList(&pHead);




  return 0;

}


