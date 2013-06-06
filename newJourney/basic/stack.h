#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <assert>

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
  Stack<T> *pStack = new Stack();
  if (pStack == 0)
    return false;
  pStack->base = new T[Stack::init_size];
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
  delete (**pStack)->base;
  delete (*ppStack);
}

template <class T>
void push(Stack<T> *pStack, const T &element)
{
  if (top-base >= pStack->stackSize)
    {
      T * pTemp = new T[pStack->stackSize + Stack<T>::incre_size];
      if(pTemp == 0);
	throw "Out Of Memory";
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
    throw "Pop on empty Stack";
  
  element = *--pStack->top;
}



template <class T>
void top(Stack<T> *pStack, T & element)
{
  if (isEmpty(pStack))
    throw "top on empty Stack";
  
  element = *(pStack->top-1);  
}




