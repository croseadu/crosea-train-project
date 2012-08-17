#include <iostream>
#include <cstdlib>
#include "stack.h"

using namespace MyUtil;

int main()
{
  Stack<char> input;
  char t;
 
  while (std::cin>>t)
    {
      if (t == '\n')
        break;
      if (t == '#')
        {
          char temp;
          if (!input.empty())
            input.pop(temp);
        }
      else
        input.push(t);
    }
  
  Stack<char> output;
  while (!input.empty())
    {
      input.pop(t);
      output.push(t);
    }

  std::cout<<"The final input is "<<std::endl;

  while(!output.empty())
    {
      output.pop(t);
      std::cout<<t;
    }

  std::cout<<std::endl;
}
