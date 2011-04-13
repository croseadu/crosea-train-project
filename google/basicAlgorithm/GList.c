#include "../include/common.h"

typedef struct _STRING
{
  const char *pData;
  int length;
}STRING, *LP_STRING;

typedef struct _GLIST 
{
  BOOL bIsAtom;
  union
  {
    char value;
    struct
    {
      struct _GLIST *hp;
      struct _GLIST *tp;
    }ptr;
  }common;
}GLIST, *LP_GLIST;
STATUS createGList(LP_GLIST *ppGlist, const LP_STRING input);
void separateString(const STRING main, LP_STRING pHead, LP_STRING pTail);
void destroyGList(LP_GLIST pHead);
// (a, (b, (c,d, ()), e), ())
int main()
{
  STATUS status;
  const char *inputString =  "((a,(),(e,f)),(b,(c,d,(g,h,(k,i))),e),())";
  LP_GLIST pHead;
  STRING temp;

  temp.pData = inputString;
  temp.length= strlen(inputString);
  status = createGList(&pHead, &temp);
  if (status != OK)
    exit(-1);
  putchar('\n');
  printf("\n GList Length %d, Depth %d\n", calcLength(pHead), calcDepth(pHead));
  
  destroyGList(pHead);
  return 0;
}

int calcDepth(const LP_GLIST pGList)
{
  LP_GLIST pIter;
  int max = 0;
  int temp;

  if (pGList == NULL)
    return 1;
  else if (pGList->bIsAtom)
    return 0;
  
  pIter = pGList;
  while (pIter)
    {
      temp = calcDepth(pIter->common.ptr.hp);
      if (temp > max)
	max = temp;
      pIter = pIter->common.ptr.tp;
    }
  return 1+max;
}
int calcLength(const LP_GLIST pGList)
{
  LP_GLIST pIter;
  int length = 0;
  if (pGList == NULL || pGList->bIsAtom)
    return 1;
  
  pIter = pGList;
  while (pIter)
    {
      length++;
      pIter = pIter->common.ptr.tp;
    }
  return length;
}
STATUS createGList(LP_GLIST *ppGlist, const LP_STRING input)
{
  LP_GLIST pNode, pIter, pPrev;
  STRING subString, headString, tailString;

  printf("\n==Start Create GList for String %.*s", input->length, input->pData);
  if (input->length == 2 
      && input->pData[0] == '(' 
      && input->pData[1] == ')')
    {
      *ppGlist = NULL;
      return OK;
    }
  else if (input->length == 1
	   && isalpha (input->pData[0]))
    {
      pNode = (LP_GLIST)malloc(sizeof(GLIST));
      if (NULL == pNode)
	{
	  printf("Out Of Memory in Line %d, Function %s", __LINE__, __FUNCTION__);
	  return OVERFLOW;
	}

      pNode->bIsAtom = TRUE;
      pNode->common.value = input->pData[0];
      *ppGlist = pNode;
      return OK;
    }
  else
    {
      pNode = (LP_GLIST)malloc(sizeof(GLIST));
      if (NULL == pNode)
	{
	  printf("Out Of Memory in Line %d, Function %s", __LINE__, __FUNCTION__);
	  return OVERFLOW;
	}
      pNode->bIsAtom = FALSE;
      assert(input->pData[0] == '(');
      assert(input->pData[input->length-1] == ')');
      subString.pData = input->pData+1;
      subString.length = input->length-2;
      separateString(subString, &headString, &tailString);
      createGList(&pNode->common.ptr.hp, &headString);
      pPrev = pNode;
      while (tailString.length)
	{
	  pIter = (LP_GLIST)malloc(sizeof(GLIST));
	  if (NULL == pIter)
	    {
	      printf("Out Of Memory in Line %d, Function %s", __LINE__, __FUNCTION__);
	      return OVERFLOW;
	    }
	  pIter->bIsAtom = FALSE;
	  pPrev->common.ptr.tp = pIter;
	  separateString(tailString, &headString, &tailString);
	  createGList(&pIter->common.ptr.hp, &headString);
	  pPrev = pIter;
	}
      pPrev->common.ptr.tp = NULL;
      *ppGlist = pNode;
      return OK;
    }
  
}

void separateString(const STRING main, LP_STRING pHead, LP_STRING pTail)
{
  int k, i;
  for (k = 0, i = 0; i < main.length && !(k == 0 && main.pData[i] == ','); i++)
    {
      if (main.pData[i] == '(')
	k++;
      else if (main.pData[i] == ')')
	k--;
    }
  if (i < main.length)
    {
      pHead->pData = main.pData;
      pHead->length = i;
      pTail->pData = main.pData + i + 1;
      pTail->length = main.length - i -1;
    }
  else
    {
      pHead->pData = main.pData;
      pHead->length = main.length;
      pTail->pData = NULL;
      pTail->length = 0;
    }
}

void destroyGList(LP_GLIST pHead)
{
  LP_GLIST pIter;

  if (pHead == NULL)
    return;
  else if (pHead->bIsAtom)
    {
      free(pHead);
      return;
    }

  pIter = pHead;
  while (pIter)
    {
      destroyGList(pIter->common.ptr.hp);
      pIter = pIter->common.ptr.tp;
    }
  free(pHead);
}
