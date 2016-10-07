#include "common.h"
#include "stack.h"
#include "utils.h"
#include "queue.h"

#include "myMemory.h"


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>



#define N 10

#define ENTRY_X 1
#define ENTRY_Y 1

#define EXIT_X 8
#define EXIT_Y 8


const int maze[N][N] = 
{
{1,1,1,1,1,1,1,1,1,1},
{1,0,0,1,0,0,0,1,0,1},
{1,0,0,1,0,0,0,1,0,1},
{1,0,0,0,0,1,1,0,0,1},
{1,0,1,1,1,0,0,0,0,1},
{1,0,0,0,1,0,0,0,0,1},
{1,0,1,0,0,0,1,0,0,1},
{1,0,1,1,1,0,1,1,0,1},
{1,1,0,0,0,0,0,0,0,1},
{1,1,1,1,1,1,1,1,1,1}
};

int mark[N][N];

typedef struct
{
	int x;
	int y;
}Pos, *LPPos;

enum Dir
{
	E = 0,
	S,
	W,
	N,	
	End,
};

typedef struct 
{
	Pos pos;
	enum Dir dir;
}Step, *LPStep;

static
Pos getNextPos(LPStep pStep)
{
	switch(pStep->dir) {
		case E:
		return {pStep->pos.x+1, pStep->pos.y};
		case S:
		return {pStep->pos.x, pStep->pos.y+1};
		case W:
		return {pStep->pos.x-1, pStep->pos.y};
		case N:
		return {pStep->pos.x, pStep->pos.y-1};
		default:
		assert(0);
	}

}

BOOL isValidPos(LPPos pPos)
{
	return (pPOs->x < N && pPOs->x >= 0 && pPos->y < N && pPos->y >= 0 && maze[pPos->x][pPos->y] == 0) ? True : False;

}

BOOL isBeenMarked(LPPOs pPos, int mark[N][N])
{
	return mark[pPos->x][pPos->y] == 1 ? True : False;
}

BOOL isExit(LPPOs pPOs)
{
	return (pPos->x == EXIT_X && pPos->y == EXIT_Y) ? True : False;
}

void print(const void *)
{
}

int main()
{
	LPStack pStack = NULL;

	if (False == createStack(&pStack, sizeof(Step), print)) {
		return;
	}











	destroyStack(&pStack);

	return 0;
}
