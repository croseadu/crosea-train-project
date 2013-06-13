#include <iostream>
#include "stack.h"


int main()
{
  int data, toMode;

  std::cin>>data>>toMode;

  if (data <= 0 || toMode <= 0)
    {
      std::cout<<"incorrect parameters"<<std::endl;
      return 0;
    }

  Stack<unsigned int> *digits = 0;
  initStack(&digits);

  while (data)
    {
      push(digits, (unsigned int)data%toMode);
      data /= toMode;
    }

  std::cout<<std::endl<<"Result is :["<<toMode<<"] ";
  while (!isEmpty(digits))
    {
      unsigned int temp;
      pop(digits, temp);
      std::cout<<temp;
    }
  std::cout<<std::endl;
  destroyStack(&digits);
}


