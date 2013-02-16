#ifndef _MY_ITERATOR_TRAITS_HPP
#define _MY_ITERATOR_TRAITS_HPP 
namespace MyUtil
{
  class forward_iter_tag{};
  class bidirection_iter_tag:public forward_iter_tag {};
  class random_iter_tag:public bidirection_iter_tag {};


  template <class iterator>
  struct iterator_traits
  {
    typedef typename iterator::iter_tag iterator_category;
  };

  template <class T>
  struct iterator_traits< T* >
  {
    typedef random_iter_tag iterator_category;
  };
}
#endif
