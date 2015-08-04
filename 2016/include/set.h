#ifndef _MY_SET_H
#define _MY_SET_H


#include "common.h"

typedef struct _SetInternalNode
{
	void *data;
	struct _SetInternalNode *pNextNode;
}SetInternalNode, *LPSetInternalNode;

typedef LPSetInternalNode * SetIter;


typedef struct _Set{
	LPSetInternalNode pHead;
	unsigned int elementSize;
	Less   less;
	Printer printer;
	unsigned int size;
}Set, *LPSet;

enum BOOL createSet(LPSet *ppSet,
	            unsigned int keySize,
		    Less less, 
		    Printer printer);
void destroySet(LPSet *ppSet);

enum BOOL isSetEmpty(const LPSet pSet);
unsigned int getSizeOfSet(const LPSet pSet);


enum BOOL insertToSet(LPSet pSet,
		      const void *data);
enum BOOL eraseFromSet(LPSet pSet,
		       SetIter iter);
enum BOOL removeFromSet(LPSet pSet,
			const void *key);

SetIter findInSet(LPSet pSet, const void *key);
unsigned int countInSet(LPSet pSet, const void *key);


#endif
