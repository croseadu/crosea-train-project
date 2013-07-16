

#include <stdio.h>
#include "../include/mytype.h"
#define N 8

int counter = 0;
unsigned int myabs(int in)
{
  return in < 0?-in:in;
}

static bool isValid(int row[], int n)
{
  int i;
  for (i = 0; i < n; i++) {
    if (row[i] == row[n] ||
	myabs(row[i] - row[n]) == n - i) {
      return false;
    }
  }
  return true;
}



void output(int row[])
{
  int i,j;
  putchar('\n');
  for (i = 0; i < N; ++i) {
    
    for (j = 0; j < N; ++j) {
      char c = row[i] == j?'Q':'-';
      putchar(c);
    }
    putchar('\n');
  }

}

void try(int row[], int n)
{
  int i,j;
  bool isValid = true;
  for (i = 0; i < n; i++) {
    if (row[i] == row[n] ||
	myabs(row[i] - row[n]) == n - i) {
      isValid = false;
      break;
    }
  }

  if (isValid == false)
    return;

  if (n == N-1) {
    ++counter;
    output(row);
  }
  else{
    for (j = 0; j < N; ++j) { 
      row[n+1] = j;
      try(row, n+1);
    }
  }
}


int main()
{
  int i = 0;
  int row[N];
  int n;
  int noRecurCounter = 0;
  counter = 0;
  for (i = 0; i < N; ++i) {
    row[0] = i;
    try(row, 0);
  }
  printf("\n Total is %d possible arrangement\n", counter);

  n = 0;
  row[n] = -1;
  while (n >= 0) {
    for (i = row[n]+1; i < N; ++i) {
      row[n] = i;
      if (isValid(row, n))
	break;
    }
    if (i >= N) {
      --n;
      continue;
    }
    row[n] = i;
    if (n == N-1) {
      ++noRecurCounter;
   
      continue;
    }
    row[n+1] = -1;
    ++n;
  }

  printf("\nVersion2: Total is %d possible arrangement\n", noRecurCounter);
  
  return 0;
}
