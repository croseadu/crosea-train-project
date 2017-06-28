#include "common.h"
#include "utils.h"
#include "stack.h"
#include "queue.h"



#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define N 10

int maze[N][N] = 
{
{1,1,1,1,1,1,1,1,1,1},
{0,0,0,1,0,0,0,1,0,1},
{1,0,0,1,0,0,0,0,0,1},
{1,0,0,0,0,1,1,0,0,1},
{1,0,1,1,1,0,0,0,0,1},
{1,0,0,0,1,0,0,0,0,1},
{1,0,1,0,0,0,1,0,0,1},
{1,0,1,1,1,0,1,1,0,1},
{1,1,0,0,0,0,0,0,0,0},
{1,1,1,1,1,1,1,1,1,1}
};

int trace[N][N];

#define ENTRY_X 1
#define ENTRY_Y 0

#define EXIT_X 8
#define EXIT_Y 9


typedef enum _DIR
{
	START_DIR,
	NORTH,
	EAST,
	SOUTH,
	WEST,
	LAST_DIR
}DIR;


typedef struct _Pos
{
	int x;
	int y;
	DIR dir;
}Pos, *LPPos;

#define IS_ENTRY(x, y) (x == ENTRY_X && y == ENTRY_Y)
#define IS_EXIT(x, y) (x == EXIT_X && y == EXIT_Y)

void print();

void
printPath(const Pos path[], unsigned int lenOfPath)
{
	unsigned int i;
	memcpy(trace, maze, sizeof(maze));
	for (i = 0; i < lenOfPath; ++i)
		trace[path[i].x][path[i].y] = 1;

	print();

}

void
print()
{
	unsigned int i, j;
	printf("\nSolution :\n");
	for (i = 0; i < N; ++i) {
		for (j = 0; j < N; ++j) {
			if (i == ENTRY_X && j == ENTRY_Y)
				putchar('S');
			else if (i == EXIT_X && j == EXIT_Y)
				putchar('E');
			else if (maze[i][j] != 0) {
				putchar('#');
			} else if (trace[i][j] != 0) {
				putchar('.');
			} else 
				putchar(' ');
		}	
		putchar('\n');
	}
}

Pos
getNext(Pos pos)
{
	Pos newPos;

	newPos.dir = START_DIR;

	switch(pos.dir) {
		case NORTH: 
			newPos.x = pos.x - 1;
			newPos.y = pos.y;
			break;
		case SOUTH:
			newPos.x = pos.x + 1;
			newPos.y = pos.y;
			break;
		case EAST:
			newPos.x = pos.x;
			newPos.y = pos.y + 1;
			break;
		case WEST:
			newPos.x = pos.x ;
			newPos.y = pos.y - 1;
			break;

		default:
			assert(0);
			break;
	}

	return newPos;
}


Pos
getPrevious(Pos pos)
{
	Pos newPos;

	newPos.dir = START_DIR;

	switch(pos.dir) {
		case NORTH: 
			newPos.x = pos.x + 1;
			newPos.y = pos.y;
			break;
		case SOUTH:
			newPos.x = pos.x - 1;
			newPos.y = pos.y;
			break;
		case EAST:
			newPos.x = pos.x;
			newPos.y = pos.y - 1;
			break;
		case WEST:
			newPos.x = pos.x;
			newPos.y = pos.y + 1;
			break;

		default:
			assert(0);
			break;
	}

	return newPos;
}


BOOL
isObstacle(Pos pos)
{
	Pos newPos;

	if (pos.dir == NORTH && pos.y == 0)
		return True;
	if (pos.dir == SOUTH && pos.y + 1 == N)
		return True;

	if (pos.dir == WEST && pos.x == 0)
		return True;
	if (pos.dir == EAST && pos.x + 1 == N)
		return True;
	newPos = getNext(pos);

	return maze[newPos.x][newPos.y] ? True : False;
	
}

BOOL
isInPath(Pos pos)
{
	Pos newPos = getNext(pos);
	return trace[newPos.x][newPos.y] ? True : False;
}

void findAll()
{
	

	int k;
	Pos paths[N*N];
	unsigned int lenOfPath = 0;
	Pos newPos;

	k = 0;
	paths[k].x = ENTRY_X;
	paths[k].y = ENTRY_Y;
	paths[k].dir = START_DIR;

	memset(trace, 0 ,sizeof(trace));
	while (k >= 0) {
		if (IS_EXIT(paths[k].x, paths[k].y)) {
			print();
			trace[paths[k].x][paths[k].y] = 0;
			--k;
			continue;
		} 
		++paths[k].dir;
		while (paths[k].dir < LAST_DIR && (isObstacle(paths[k]) == True || isInPath(paths[k]) == True) )
			++paths[k].dir;
		if (paths[k].dir >= LAST_DIR) {
			trace[paths[k].x][paths[k].y] = 0;
			--k;
			continue;
		}	

		newPos = getNext(paths[k]);
		paths[++k] = newPos;
		trace[paths[k].x][paths[k].y] = 1;		 
	}


}


void findShortest()
{
	LPQueue pQueue = NULL;

	Pos pos,newPos;
	Pos pathInfo[N][N] = {0};

	if (False == createQueue(&pQueue,
				 sizeof(Pos),
				 defaultPrinter)) {
		return;
	}

	memset(trace, 0, sizeof(trace));


	pos.x = ENTRY_X;
	pos.y = ENTRY_Y;
	pos.dir = START_DIR;

	enQueue(pQueue, &pos);
	trace[pos.x][pos.y] = 1;
	pathInfo[pos.x][pos.y] = pos;	

	while (isQueueEmpty(pQueue) == False) {
		deQueue(pQueue, &pos);
		if (IS_EXIT(pos.x, pos.y)) {
			break;
		}
		for (pos.dir = NORTH; pos.dir < LAST_DIR; ++pos.dir) {
			if (isObstacle(pos) == True)
				continue;
			newPos = getNext(pos);
			if (trace[newPos.x][newPos.y])
				continue;

			trace[newPos.x][newPos.y] = 1;
			newPos.dir = pos.dir;
			pathInfo[newPos.x][newPos.y] = newPos;
			enQueue(pQueue, &newPos);
		}

	}

	printf("done searching\n");
	if (IS_EXIT(pos.x, pos.y)) {
		memset(trace, 0, sizeof(trace));
		while ( !IS_ENTRY(pos.x, pos.y)) {
			pos = pathInfo[pos.x][pos.y];
			pos = getPrevious(pos);
			trace[pos.x][pos.y] = 1;
		}		
		print();

	} else {
		printf("Failed to find a path!\n");
	}

	
	if (pQueue != NULL)
		destroyQueue(&pQueue);
}

BOOL
isValid(int x, int y)
{
	if (x < 0 || y < 0)
		return False;
	if (x >= N || y >= N)
		return False;

	return True;
}

void findOne()
{
	LPStack pStack = NULL;
	Pos curPos;
	Pos topPos;

	if (False == createStack(&pStack,
				 sizeof(Pos),
				 defaultPrinter)) {
		goto lexit;
	}

	curPos.x = ENTRY_X;
	curPos.y = ENTRY_Y;
	curPos.dir = NORTH;

	memset(trace, 0, sizeof(trace));
	while (1) {
		if (IS_EXIT(curPos.x, curPos.y))
			break;
		if ( isValid(curPos.x, curPos.y) == True && trace[curPos.x][curPos.y] == 0 && maze[curPos.x][curPos.y] == 0) {
			pushToStack(pStack, &curPos);
			trace[curPos.x][curPos.y] = 1;
			curPos = getNext(curPos);
			curPos.dir = NORTH;
			
		} else {
			if (isStackEmpty(pStack) == True)
				break;
			getTopFromStack(pStack, &curPos);
			popFromStack(pStack);
			trace[curPos.x][curPos.y] = 0;
			while (curPos.dir == WEST && isStackEmpty(pStack) == False) {
				getTopFromStack(pStack, &curPos);
				popFromStack(pStack);
				trace[curPos.x][curPos.y] = 0;
				
			}
			
			if (curPos.dir == WEST)
				break;
			++curPos.dir;
			pushToStack(pStack, &curPos);
			trace[curPos.x][curPos.y] = 1;

			curPos = getNext(curPos);
			curPos.dir = NORTH;
		}
	}
	

	if (IS_EXIT(curPos.x, curPos.y)) {
		print();
	}

lexit:
	if (pStack != NULL) {
		destroyStack(&pStack);
	}

}


int main()
{
	findAll();
	findShortest();
	findOne();
	return 0;
}

