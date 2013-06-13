#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <assert.h>
#include "exceptions.h"
template <class T>
struct Stack
{
  T *base;
  T *top;
  unsigned int stackSize;
  static const unsigned int init_size = 10;
  static const unsigned int incre_size = 5;
};

template <class T>
bool initStack(Stack<T> **ppStack)
{
  Stack<T> *pStack = new Stack<T>();
  if (pStack == 0)
    return false;
  pStack->base = new T[Stack<T>::init_size];
  if (pStack->base == 0)
    {
      delete pStack;
      return false;
    }
  pStack->top = pStack->base;
  pStack->stackSize = Stack<T>::init_size;
  *ppStack = pStack;
  return true;
}
template <class T>
void destroyStack(Stack<T> **ppStack)
{
  delete (*ppStack)->base;
  delete (*ppStack);
}

template <class T>
void push(Stack<T> *pStack, const T &element)
{
  if (pStack->top-pStack->base >= pStack->stackSize)
    {
      T * pTemp = new T[pStack->stackSize + Stack<T>::incre_size];
      if(pTemp == 0);
      {
	throw MyException("Out Of Memory");
      }
      std::copy(pStack->base, pStack->top, pTemp);
      delete pStack->base;
      pStack->base = pTemp;
      pStack->stackSize += Stack<T>::incre_size;
    }
  
  *pStack->top++ = element;
}

template <class T>
bool isEmpty(Stack<T> *pStack)
{
  return pStack->top == pStack->base;
}

template <class T>
void pop(Stack<T> *pStack, T &element)
{
  if (isEmpty(pStack))
    {
      throw MyException("Pop on empty Stack");
    }
  
  element = *--pStack->top;
}



template <class T>
const T top(Stack<T> *pStack)
{
  if (isEmpty(pStack))
    {
      throw MyException("top on empty Stack");
    }
  return *(pStack->top-1);  
  
}


template <class T>
unsigned int size(Stack<T> *pStack)
{
  return pStack->top - pStack->base;
}

