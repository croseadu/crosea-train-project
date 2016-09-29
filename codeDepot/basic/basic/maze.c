#include "stack.h"
#include "queue.h"


#include "utils.h"
#include "memory.h"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>


#define N 10 

const int maze[N][N] = {
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

#define ENTRY_X  1
#define ENTRY_Y  1

#define EXIT_X 8
#define EXIT_Y 8

typedef struct _Pos
{
	int x;
	int y;
}Pos, *LPPos;


enum Dir
{
	DIR_BEGIN,
	E_DIR,
	S_DIR,
	W_DIR,
	N_DIR,
	DIR_COUNT,
};

typedef struct _Path
{
	Pos pos;
	enum Dir dir;
}Path, *LPPath;

void findShortestPath();
void findAllPath();
void findOnePath();

void findAllPath2();

static int count = 0;

int main()
{
	//findAllPath2();
	findShortestPath();

	printf("\nTotal allowed board: %d\n", count);
	return 0;
}

Pos
next(Pos pos, enum Dir dir)
{

	Pos newPos = pos;
	switch(dir) {
		default: 
			assert(0); break;
		case E_DIR:
			++newPos.x;break; 
		case S_DIR:
			++newPos.y;break;
		case W_DIR:
			--newPos.x;break;
		case N_DIR:
			--newPos.y;break;
	}
	return newPos;
}


BOOL
validNext(Pos curPos, enum Dir dir)
{
	Pos pos = next(curPos, dir);
	return maze[pos.x][pos.y] == 0 ? True : False;

}

BOOL
alreadyInPath(Path paths[], int idx, Pos tryPos)
{
	int i;
	for (i = 0; i <= idx; ++i) {
		if (paths[i].pos.x == tryPos.x && paths[i].pos.y == tryPos.y)
			return True;
	}


	return False;
}



BOOL
isExit(Pos pos)
{
	return (pos.x == EXIT_X && pos.y == EXIT_Y) ? True : False;
}


void
output(const int pathMatrix[][N])
{
	int i, j;
	putchar('\n');
	for (i = 0; i < N; ++i) {
		for(j = 0; j < N; ++j) {
			if (maze[i][j] == 1) {
				putchar('#');
			} else {
				if (i == ENTRY_X && j == ENTRY_Y)
					putchar('O');
				else if (i == EXIT_X && j == EXIT_Y)
					putchar('O');
				else if (pathMatrix[i][j])
					putchar('.');
				else
					putchar(' ');

			}


		}
		putchar('\n');
	}
	++count;

}

void
findAllPath()
{
	int pathMatrix[N][N] = {0};
	Path paths[N * N], nextPath;
	int i = 0;
	Pos nextPos;

	nextPos.x = ENTRY_X;
	nextPos.y = ENTRY_Y;
	paths[0].pos = nextPos;
	paths[0].dir = DIR_BEGIN;
	pathMatrix[0][0] = 1;
	while (i >= 0) {
		if (True == isExit(paths[i].pos)) {
			output(pathMatrix);
			pathMatrix[paths[i].pos.x][paths[i].pos.y] = 0;
			--i;
			continue;
		} 	
		enum Dir dir = paths[i].dir;
		++dir;
		while (dir != DIR_COUNT && ( validNext(paths[i].pos, dir) == False || alreadyInPath(paths, i, next(paths[i].pos, dir)) == True) ) {
			++dir;
		}
		if (dir == DIR_COUNT) {
			pathMatrix[paths[i].pos.x][paths[i].pos.y] = 0;
			--i;
		} else {
			paths[i].dir = dir;

			nextPos = next(paths[i].pos, dir);
			nextPath.pos = nextPos;
			nextPath.dir = DIR_BEGIN;
			
			++i;
			paths[i] = nextPath;
			pathMatrix[nextPos.x][nextPos.y] = 1;	
		}
	}

}

void
findAllPath2()
{
	int pathMatrix[N][N] = {0};
	Path paths[N * N], nextPath;
	int i = 0;
	Pos nextPos;

	nextPos.x = ENTRY_X;
	nextPos.y = ENTRY_Y;
	paths[0].pos = nextPos;
	paths[0].dir = E_DIR;
	pathMatrix[0][0] = 1;

	nextPos = next(nextPos, paths[0].dir);
	
	while (i >= 0) {
		if (isExit(nextPos) == False && maze[nextPos.x][nextPos.y] == 0 && alreadyInPath(paths, i, nextPos) == False) {
			nextPath.pos = nextPos;
			nextPath.dir = E_DIR;
			++i;
			paths[i] = nextPath;
			pathMatrix[nextPos.x][nextPos.y] = 1;

			nextPos = next(nextPos, nextPath.dir);
			continue;
		} 
		if (True == isExit(nextPos)) {
			output(pathMatrix);	
		}
		while (i >= 0 && paths[i].dir == N_DIR)
		{
			pathMatrix[paths[i].pos.x][paths[i].pos.y] = 0;
			--i;
		}	
		if (i < 0)
			break;

		++paths[i].dir;
		nextPos = next(paths[i].pos, paths[i].dir);
	}

}



void
findOnePath()
{
	LPStack pStack = NULL;
	Pos curPos;
	enum Dir dir;
	Path tempPath;
	int pathMatrix[N][N] = {0};
	int deadPos[N][N] = {0};


	if (False == createStack(&pStack, sizeof(Path))) {
		goto cleanup;
	}
	
	curPos.x = ENTRY_X;
	curPos.y = ENTRY_Y;
	tempPath.pos = curPos;
	tempPath.dir = E_DIR;
	
	
	pushToStack(pStack, &tempPath);
	pathMatrix[ENTRY_X][ENTRY_Y] = 1;
	curPos = next(curPos, E_DIR);


	while (isStackEmpty(pStack) == False) {
		if (True == isExit(curPos)) {
			output(pathMatrix);
			break;
		}
		if (maze[curPos.x][curPos.y] == 1 ||
		    pathMatrix[curPos.x][curPos.y] == 1 ||
		    deadPos[curPos.x][curPos.y] == 1) {
			while(isStackEmpty(pStack) == False) {
				getTopOfStack(pStack, &tempPath);
				popFromStack(pStack);
				pathMatrix[tempPath.pos.x][tempPath.pos.y] = 0;
				if (tempPath.dir != N_DIR)
					break;
				deadPos[tempPath.pos.x][tempPath.pos.y] = 1;

			} 
			if (tempPath.dir == N_DIR)
				break;
			++tempPath.dir;
			curPos = next(tempPath.pos, tempPath.dir);
			pushToStack(pStack, &tempPath);
			pathMatrix[tempPath.pos.x][tempPath.pos.y] = 1;
		} else {
			pathMatrix[curPos.x][curPos.y] = 1;
			tempPath.pos = curPos;
			tempPath.dir = E_DIR;
			pushToStack(pStack, &tempPath);
			
			curPos = next(curPos, E_DIR);
		}


	}	
	

cleanup:
	if (pStack)
		destroyStack(&pStack);
	return;

}

Pos
prev(Pos pos, enum Dir dir) {
	Pos prevPos = pos;

	switch(dir) {
		default:
			assert(0); break;
		case E_DIR:
			--prevPos.x;break;
		case W_DIR:
			++prevPos.x;break;
		case S_DIR:
			--prevPos.y;break;
		case N_DIR:
			++prevPos.y;break;
	}


	return prevPos;

}

BOOL
isEntry(Pos pos) 
{
	return (pos.x == ENTRY_X && pos.y == ENTRY_Y) ? True : False;

}

void
findShortestPath()
{
	LPQueue pQueue = NULL;
	int inQueueSet[N][N] = {0};
	int pathMatrix[N][N] = {0};	
	enum Dir dirs[N][N] = {DIR_BEGIN};
	Pos curPos, nextPos;

	if (False == createQueue(&pQueue, sizeof(Pos), defaultPrinter)) {
		goto cleanup;
	}

	curPos.x = ENTRY_X;
	curPos.y = ENTRY_Y;
	enQueue(pQueue, &curPos);
	inQueueSet[ENTRY_X][ENTRY_Y] = 1;	

	while (isQueueEmpty(pQueue) == False) {
		deQueue(pQueue, &curPos);
		printf("\n Dequeue : (%d, %d)", curPos.x, curPos.y);

		if (True == isExit(curPos)) {
			break;
		}
		nextPos = next(curPos, E_DIR);
		if (maze[nextPos.x][nextPos.y] == 0 &&
		    inQueueSet[nextPos.x][nextPos.y] == 0) {
			enQueue(pQueue, &nextPos);
			inQueueSet[nextPos.x][nextPos.y] = 1;
			dirs[nextPos.x][nextPos.y] = E_DIR;
		}	
		nextPos = next(curPos, W_DIR);
		if (maze[nextPos.x][nextPos.y] == 0 &&
		    inQueueSet[nextPos.x][nextPos.y] == 0) {
			enQueue(pQueue, &nextPos);
			inQueueSet[nextPos.x][nextPos.y] = 1;
			dirs[nextPos.x][nextPos.y] = W_DIR;
		}	
		nextPos = next(curPos, S_DIR);
		if (maze[nextPos.x][nextPos.y] == 0 &&
		    inQueueSet[nextPos.x][nextPos.y] == 0) {
			enQueue(pQueue, &nextPos);
			inQueueSet[nextPos.x][nextPos.y] = 1;
			dirs[nextPos.x][nextPos.y] = S_DIR;
		}	

		nextPos = next(curPos, N_DIR);
		if (maze[nextPos.x][nextPos.y] == 0 &&
		    inQueueSet[nextPos.x][nextPos.y] == 0) {
			enQueue(pQueue, &nextPos);
			inQueueSet[nextPos.x][nextPos.y] = 1;
			dirs[nextPos.x][nextPos.y] = N_DIR;
		}	

	}


	if (isExit(curPos) == True) {
		while(isEntry(curPos) == False) {
			enum Dir dir = dirs[curPos.x][curPos.y];
			curPos = prev(curPos, dir);
			pathMatrix[curPos.x][curPos.y] = 1;

		}
		output(pathMatrix);

	}

cleanup:
	if (pQueue)
		destroyQueue(&pQueue);
	return;

}

