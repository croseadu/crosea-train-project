#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>


#define OK 0
#define ERROR 1

#define END	3

#define TRUE 1
#define FALSE 0


#ifdef DEBUG
	#define Print(arg) printf arg
#else
	#define Print(arg)
#endif 

typedef int STATUS;
typedef int BOOL;


