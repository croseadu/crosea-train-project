#include <iostream>
#include "stack.h"


using namespace MyUtil;

void convertTo(const unsigned int d, 
               const unsigned int f, 
               Stack<unsigned int > & r)
{
  unsigned int t = d;
  while (t)
    {
      r.push(t%f);
      t /= f;
    }
}


int main()
{
  Stack<unsigned int> result;
  int data, format;

  while(std::cin>>data>>format)
    {
      assert (data > 0 && format > 0);
      convertTo(data, format, result);
      std::cout<<"Result in format "<<format<<" is :";
      unsigned int t;
      while(!result.empty())
        {
          result.pop(t);
          std::cout<<t;
        }
      std::cout<<std::endl;
    }


  return 0;
}
