#include "map.h"
#include "singleLinkList.h"
#include "vector.h"
#include "memory.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>




BOOL
compareName(const void *lhs, const void *rhs)
{
	char *lhsName = (char *)lhs;
	char *rhsName = (char *)rhs;

	return strcmp(lhsName, rhsName) < 0 ? True : False;

}

static LPMap pCurMap = NULL;
void
printMapItem(void *in)
{
	MapIter it = (MapIter)in;
	void *key;
	void *data;

	key = myAlloc(pCurMap->keySize);
	data = myAlloc(pCurMap->dataSize);
	assert(key && data);

	memcpy(key, in, pCurMap->keySize);
	memcpy(data, (char *)in + pCurMap->keySize, pCurMap->dataSize);

	printf("[%s] = %d\n", *(char **)key, *(int *)data);


	myFree(key);
	myFree(data);
}

void
namePrinter(const void *data)
{
	char *name = *(char **)data;
	printf("%s\n", name);
}


int main()
{
	LPMap pNameToAgeMap = NULL;
	char nameBuf[4096];
	unsigned int age,len;
	char *name = NULL;
	FILE *FP = NULL;
	LPVector pNameVec = NULL;	
	int i;	


	if ((FP = fopen("input.txt", "r")) == NULL) {
		goto cleanup;
	}

	if (False == createMap(&pNameToAgeMap, sizeof(char *), sizeof(unsigned int), compareName)) {
		goto cleanup;
	}
	if (False == createVector(&pNameVec, sizeof(char *), compareName, namePrinter)) {
		goto cleanup;
	}

	while(fscanf(FP, "%s %d", nameBuf, &age) > 1) {
		nameBuf[4096-1] = '\0';
		len = strlen(nameBuf);
		name = myAlloc(len+1);
		strcpy(name, nameBuf);
				
		pushBackInVector(pNameVec, &name);
		insertToMap(pNameToAgeMap, &name, &age);

	}

	printVector(pNameVec);
	pCurMap = pNameToAgeMap;
	traverseMap(pNameToAgeMap, printMapItem);



cleanup:
	if (pNameToAgeMap != NULL)
		destroyMap(&pNameToAgeMap);

	if (pNameVec) {
		for(i = 0; i < getSizeOfVector(pNameVec); ++i) {
			getIthInVector(pNameVec, i, (void *)&name);
			myFree(name);
		}
		destroyVector(&pNameVec);

	}
	return 0;
}
