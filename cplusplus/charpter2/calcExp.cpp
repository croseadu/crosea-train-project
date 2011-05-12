#include <iostream>


int main()
{
  int base, exponent;

  std::cout<<"Input Base & exponent"<<std::endl;

  std::cin>>base>>exponent;
  if (base <= 0
      || exponent < 0)
    std::cout<<"Error in Input"<<std::endl;
  
  int i = exponent;
  int result = 1;
  
  while (i-->0)
    result *= base;

  std::cout<<base<<"^"<<exponent<<" = "<<result<<std::endl;

  return 0;
}
