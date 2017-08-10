#include "common.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define N 8

extern int total;
void dump(int board[N][N])
{
	int i, j;

	putchar('\n');
	for (i = 0; i < N; ++i) {
		for (j = 0; j < N; ++j) {
			printf("%s", board[i][j] != 0 ? "Q": ".");
		}
		putchar('\n');
	}
	putchar('\n');
}

void dumpCol(int col[N])
{
	int i, j;

	putchar('\n');
	for (i = 0; i < N; ++i) {
		for (j = 0; j < N; ++j) {
			printf("%s", j == col[i] ? "Q": ".");
		}
		putchar('\n');
	}
	putchar('\n');
}

BOOL
isValid(int board[N][N], int i, int j)
{

	int k, d;

	for (k = 0; k < i; ++k) {
		if (board[k][j])
			return False;

		d = i - k;
		if (j >= d && board[k][j-d])
			return False;
		if (j+d < N && board[k][j+d])
			return False; 
	}
	return True;
}


void try(int board[N][N], int cur)
{
	int i;


	if (cur == N) {
		++total;
		dump(board);
		return;
	}

	for (i = 0; i < N; ++i) {
		if (isValid(board, cur, i) == False)
			continue;

		board[cur][i] = 1;
		try(board, cur + 1);
		board[cur][i] = 0; 
	}
}

BOOL
isValidCol(int col[N], int i)
{
	int k, d;
	int tryIdx = col[i];
	for (k = 0; k < i; ++k) {
		d = tryIdx - col[k];
		if (d == 0 || d  == i - k || d == k - i)
			return False;
	}
	return True;
}



int total;
int main()
{
	int board[N][N] = {0};
	int col[N+1] = {0};	

	int i;
	total = 0;

	try(board, 0);
	

	printf("\nTotal = %d\n", total);

	total = 0;

	i = 0;
	col[i] = -1;
	while (i >= 0) {
		if (i == N) {
			dumpCol(col);
			++total;
			--i;		
		} else {
			++col[i];
			while (col[i] < N && isValidCol(col, i) == False)
				++col[i];
			if (col[i] == N) {
				--i;
			} else {
				++i;
				col[i] = -1;
			}
		}

	}
	printf("\nTOtal2 : %d\n", total);

	return 0;
}
