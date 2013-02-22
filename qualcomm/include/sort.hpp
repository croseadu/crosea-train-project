#ifndef _MY_SORT_HPP
#define _MY_SORT_HPP
#include "iterator.hpp"
#include <iostream>
namespace MyUtil
{
  // forward iterator is minimal requrest
  template<class iterator>
  void bubbleSort(iterator start, iterator end)
  {
    typedef typename iterator_traits<iterator>::value_type valueType;
    
    iterator nextEnd = end;
    bool changed = true;
    while (changed)
      {
	changed = false;
	iterator ii = start;
	iterator jj = ii;
	++jj;
	while ( jj!= nextEnd)
	  {
	    if (*ii > *jj)
	      {
		valueType temp = *ii;
		*ii = *jj;
		*jj = temp;
		changed = true;
	      }
	    ++ii;
	    ++jj;
	  }
	nextEnd = ii;
      }

  }

  // forward iterator is minimal request
  template <class iterator>
  iterator selectMin(iterator begin, iterator end)
  {
    iterator min = begin;
    iterator ii = begin;
    ++ii;
    while (ii != end)
      {
	if (*ii < *min)
	  min = ii;
	++ii;
      }
    return min;
  }

  template <class iterator>
  void selectSort(iterator start, iterator end)
  {
    typedef typename iterator_traits<iterator>::value_type valueType;
    
    iterator ii = start;
    while (ii != end)
      {
	iterator minIter = selectMin(ii, end);
	if (minIter != ii)
	  {
	    valueType temp = *ii;
	    *ii = *minIter;
	    *minIter = temp;
	  }
	++ii;
      }
  }

  // bidiretion iterator is minimal request
  template <class iterator>
  void insertSort(iterator start, iterator end)
  {
    // Validate iterator category
    typename iterator_traits<iterator>::iterator_category a;
    typedef typename iterator_traits<iterator>::value_type valueType;
    bidirection_iter_tag b = a;

    iterator ii = start;
    ++ii;
    while (ii != end)
      {
	valueType temp = *ii;
	iterator insertPt = ii;
	--insertPt;
	if (*insertPt <= temp)
	  {
	    ++ii;
	    continue;
	  }

	iterator swapPt = insertPt;
	++swapPt;
	while( *insertPt > temp)
	  {
	    *swapPt = *insertPt;
	    if (insertPt == start)
	      break;
	    --swapPt;
	    --insertPt;
	  }
	if (*insertPt <= temp)
	  ++insertPt;
	*insertPt = temp;
	++ii;
      }
  }

  template <class iterator>
  void _doShellSort(iterator start, iterator end, int step)
  {
    typedef typename iterator_traits<iterator>::value_type valueType;
    
    iterator ii = start + step;
    while (ii != end)
      {
	iterator insertPt = ii -step;
	valueType temp = *ii;
	//std::cout<<"idx :"<< ii -start << "value = " << *ii<<" "<<*insertPt<<std::endl;
	while (*insertPt > temp)
	  {
	    iterator swapPt = insertPt + step;
	    *swapPt = *insertPt;
	    if (insertPt - start < step)
	      break;
	    insertPt -= step; 
	  }
	if (*insertPt <= temp)
	  insertPt += step;
	*insertPt = temp;
	++ii;
      }
    

  }

  // minimal is random_access_iterator
  template <class iterator>
  void shellSort(iterator start, iterator end)
  {
    // Validate iterator category
    typename iterator_traits<iterator>::iterator_category a;
    random_iter_tag b = a;

    typedef typename iterator_traits<iterator>::value_type valueType;
    int dt[3]={5,3,1};
    for (int i = 0; i < 3; i++)
      _doShellSort(start, end, dt[i]);

  }

  // minimal is random_access_iterator
  template <class iterator>
  void heapSort(iterator start, iterator end)
  {
    // Validate iterator category
    typename iterator_traits<iterator>::iterator_category a;
    random_iter_tag b = a;
  }
}

#endif
