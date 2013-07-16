#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "../include/stack.h"

#define M 10

int map[M][M] = 
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

#define IS_START(i,j) (i == 1 && j == 1)

#define IS_END(i, j) (i == 8 && j == 8)

enum DIR
{
  W = 0,
  N,
  E,
  S,
  NOPATH
};

typedef struct _Step
{
  int row;
  int col;
  int dir;
}Step, *LPStep;

typedef struct _COORD
{
  int i;
  int j;
}COORD, *LPCOORD;

void getNext(int curI, int curJ, int dir, int *i, int *j)
{
  if (dir == W) {
    *i = curI;
    *j = curJ - 1;
  }
  else if (dir == N) {
    *i = curI - 1;
    *j = curJ;
  }
  else if (dir == E) {
    *i = curI;
    *j = curJ + 1;
  }
  else if (dir == S) {
    *i = curI + 1;
    *j = curJ;
  }
  else 
    assert(0);

}

bool isInPath(int row, int col, Step path[], int length)
{
  int i = 0;
  for (i = 0; i <= length; ++i) {
    if (path[i].row == row && path[i].col == col)
      return true;
  }

  return false;
}

int getIndexInPath(int row, int col, Step path[], int length)
{
  int i = 0;
  for (i = 0; i <= length; ++i) {
    if (path[i].row == row && path[i].col == col)
      return i;
  }

  return -1;
}

static bool isValidPos(int i, int j)
{
  return (i >= 0 && i < M && j >= 0 && j < M && map[i][j] == 0);
}

static void printPath(Step path[], int length)
{
  int i, j;
  putchar('\n');
  for (i = 0; i < M; ++i){
    putchar('\n');
    for (j = 0; j < M; ++j) {
      if (map[i][j])
	putchar('#');
      else if (isInPath(i,j, path, length)) {
	int index = getIndexInPath(i, j, path, length);
	if (index == 0)
	  putchar('S');
	else if (index == length)
	  putchar('E');
	else if(path[index-1].dir == E || path[index-1].dir == W)
	  putchar('-');
	else
	    putchar('|');
      }
      else 
	putchar(' ');
    }
  }
}



int main()
{
  LPStep path = NULL;
  int length = 0;
  COORD t;
  int i, j;

  path = (LPStep)malloc(sizeof(Step)*M*M);
  if (NULL == path) {
    printf("Out Of Memory in %s", __func__);
    exit(-1);
  }

  path[0].row = 1;
  path[0].col = 1;
  path[0].dir = -1;
  length = 0;
  while (length >= 0)
  {
    if (IS_END(path[length].row, path[length].col)) {
      printPath(path, length);
      --length;
    }
    else {
      
      while (++path[length].dir < NOPATH) {
	getNext(path[length].row, path[length].col,
		path[length].dir, &i, &j);
	if (isValidPos(i, j) && !isInPath(i, j, path, length))
	  break;
      }
      if (path[length].dir < NOPATH) {
	++length;
	path[length].row = i;
	path[length].col = j;
	path[length].dir = -1;
      }
      else
	--length;
    }  
  }

  

  free(path);

  return 0;
}
