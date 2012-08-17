#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "list.h"



class POLY
{
public:
  int coef_;
  unsigned int exponent_;
  POLY():coef_(0),exponent_(0xFFFFFFFF){}
  explicit POLY(int c, unsigned int e):coef_(c), exponent_(e){}
  bool operator<(const POLY &rhs) const
  {
    return exponent_ < rhs.exponent_;
  }
  bool operator>(const POLY &rhs) const
  {
    return exponent_ > rhs.exponent_;
  }
};

 using namespace std;
 using namespace MyUtil;

int main()
{
  
  std::ifstream input("in.txt");
  List<POLY> polyOp1;
  List<POLY> polyOp2;
  std::string line;
  int coef;
  unsigned int  exponent;
  std::string::size_type pos = 0;

  if (!input)
    {
      std::cout<<"Input File doesn't Exist"<<std::endl;
      return (-1);
    }

  if (!std::getline(input, line))
    {
      std::cout<<"No Input"<<std::endl;
      return (-1);
    }
  
  while((pos = line.find_first_of('(', pos)) != std::string::npos)
    {
      char t;
      ++pos;
      std::istringstream inputstring(std::string(line, pos));

      inputstring >> coef;
      inputstring >> t;
      while (t != ',')
        {
          inputstring >> t;
        }
      inputstring >> exponent;
      
      polyOp1.push_before(POLY(coef, exponent));
    }

  if (!std::getline(input, line))
    {
      std::cout<<"No Input"<<std::endl;
      return (-1);
    }
  pos = 0;
  while((pos = line.find_first_of('(', pos)) != std::string::npos)
    {
      char t;
      ++pos;
      std::istringstream inputstring(std::string(line, pos));

      inputstring >> coef;
      inputstring >> t;
      while (t != ',')
        {
          inputstring >> t;
        }
      inputstring >> exponent;
      
      polyOp2.push_before(POLY(coef, exponent));
    }
    
  std::cout<<"List 1: ";
  for (List<POLY>::const_iterator ii = polyOp1.begin(); ii != polyOp1.end(); ++ii)
    std::cout<<(*ii).coef_<<"*X^"<<(*ii).exponent_<<" ";
  std::cout<<std::endl;

  std::cout<<"List 2: ";
  for (List<POLY>::const_iterator ii = polyOp2.begin(); ii != polyOp2.end(); ++ii)
    std::cout<<(*ii).coef_<<"*X^"<<(*ii).exponent_<<" ";
  std::cout<<std::endl;

  std::cout<<"After Sort: "<<std::endl;
  polyOp1.sort();
  polyOp2.sort();
  
  std::cout<<"List 1: ";
  for (List<POLY>::const_iterator ii = polyOp1.begin(); ii != polyOp1.end(); ++ii)
    std::cout<<(*ii).coef_<<"*X^"<<(*ii).exponent_<<" ";
  std::cout<<std::endl;

  std::cout<<"List 2: ";
  for (List<POLY>::const_iterator ii = polyOp2.begin(); ii != polyOp2.end(); ++ii)
    std::cout<<(*ii).coef_<<"*X^"<<(*ii).exponent_<<" ";
  std::cout<<std::endl;


  List<POLY>::iterator ll = polyOp1.begin();
  List<POLY>::iterator rr = polyOp2.begin();
  while (ll != polyOp1.end() && rr != polyOp2.end())
    {
      if ((*ll).exponent_ < (*rr).exponent_)
        ++ll;
      else if ((*ll).exponent_ == (*rr).exponent_)
        {
          if (ll->coef_ + rr->coef_ == 0)
            {
              List<POLY>::iterator k = ll;
              ++k;
              polyOp1.erase(ll);
              ll = k;
            }
          else
            {
              ll->coef_ = ll->coef_ + rr->coef_;
            }
          ++rr;
        }
      else
        {
          polyOp1.insert(ll, *rr);
          ++rr;
        }
    }

  while (rr != polyOp2.end())
    {
      polyOp1.push_back(*rr);
      ++rr;
    }

  std::cout<<std::endl<<"After Merge: "<<std::endl;
  
  std::cout<<"List 1: ";
  for (List<POLY>::const_iterator ii = polyOp1.begin(); ii != polyOp1.end(); ++ii)
    std::cout<<(*ii).coef_<<"*X^"<<(*ii).exponent_<<" ";
  std::cout<<std::endl;

  return 0;
}


