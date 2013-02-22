#ifndef _MY_ALGORITHM_HPP
#define _MY_ALGORITHM_HPP
#include <iostream>
#include "iterator.hpp"

namespace MyUtil
{
  template <class iterator>
  int distance(iterator start, iterator end)
  {
    typename iterator_traits<iterator>::iterator_category tag;
    return _distance(start, end, tag);
  }

  template <class iterator>
  int _distance(iterator start, iterator end, forward_iter_tag)
  {
    std::cout<<"In Normal distance version"<<std::endl;
    int offset = 0;
    while (start++ != end)
      offset++;
    return offset;
  }
  template <class iterator>
  int _distance(iterator start, iterator end, random_iter_tag)
  {
    std::cout<<"In Fast distance version"<<std::endl;
    return end - start;
  }


}

#include "sort.hpp"




#endif
