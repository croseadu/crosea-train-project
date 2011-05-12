#include <iostream>
#include "Sales_item.h"


int main()
{
  Sales_item item1, item2;

  std::cout<<"Input Two Item"<<std::endl;

  std::cin>>item1>>item2;

  if (item1.same_isbn(item2))
    {
      std::cout<<"Item1+Item2 = "<<item1+item2<<std::endl;
    }
  else
    {
      std::cout<<"Data aren't same"<<std::endl;
    }

  return 0;
}
