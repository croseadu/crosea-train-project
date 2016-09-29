#include "utils.h"
#include "memory.h"
#include "common.h"


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


#define NUM_QUEEN 8


void
output(int idx[])
{
	int i, j;
	putchar('\n');
	for(i = 0; i < NUM_QUEEN; ++i) {
		for(j = 0; j < NUM_QUEEN; ++j) {
			if (idx[i] == j) 
				putchar('Q');
			else
				putchar('.');
		}
	
		putchar('\n');
	}

}



BOOL
valid(int k, int i, int n, int idx[])
{
	int j;
	int d;
	if (i == 0)
		return True;

	for(j = 0; j < i; ++j) {
	
		d = i - j;	
		if (idx[j] == k)
			return False;

		else if (idx[j] < k && k - idx[j] == d) {
			return False;
		} else if (idx[j] - k == d)
			return False;

	}

	return True;
}

void
queen(int i, int n, int idx[])
{
	int j;
	if (i == n) {
		output(idx);
		return;
	}
	
	for(j = 0; j < NUM_QUEEN; ++j) {
		if (False == valid(j, i, n, idx)) {
			continue;
		}
		idx[i] = j;
		queen(i+1, n, idx);
	}

}

int main()
{
	int idx[NUM_QUEEN+1];
	int i = 0;
	int curK;
	int n = NUM_QUEEN;

	//queen(0, NUM_QUEEN, idx);

	idx[0] = -1;
	while (i >= 0) {
		if (i == n) {
			output(idx);
			--i;
			continue;
		}
		curK = idx[i];
		++curK;
		while(curK < n && valid(curK, i, n, idx) == False)
			++curK;

		if (curK >= n) {
			--i;
		} else {
			idx[i] = curK;
			++i;
			idx[i] = -1;
		}

	}



	return 0;
}

