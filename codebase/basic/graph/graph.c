#include "../../include/my.h"
#include "../../include/util.h"

struct _EDGE;
typedef struct _NODE
{
	char data;
	struct _EDGE *pFirstEdgeIn;
	struct _EDGE *pFirstEdgeOut;
}NODE, *LP_NODE;

typedef struct _EDGE
{
	NODE *pFrom;
	NODE *pTo;
	struct _EDGE *pNextSameFrom;
	struct _EDGE *pNextSameTo;
}EDGE, *LP_EDGE;


int main()
{
	FILE *fp;
	char buf[1024];
	char from, to;
	int readCount;
	int curIndex;
	int offset = 0;

	if ((fp = fopen("temp", "rt")) == NULL)
	{
		Print(("Failed when open file\n"));
		exit(-1);
	}

	if (fp < 0)
		return -1;
	while (!feof(fp))
	{
		if(NULL == fgets(buf+offset, 100, fp))
			break;
		printf("\nInput is %s\n", buf);

		
		while (buf[curIndex] == '\t' 
			   || buf[curIndex] == ' ' 
			   || buf[curIndex] != 0)
			   curIndex++;
	
		if (buf[curIndex] == 0)
			continue;


		if (buf[curIndex] != '('
			|| !isalpha(buf[curIndex+1])
			|| buf[curIndex+2] != ','
			|| !isalpha(buf[curIndex+3])
			|| buf[curIndex+4] != ')')
		{
			Print(("Error in Input"));
			exit(-1);
		}

	}

	fclose(fp);

	return 0;



}

createGraphPool()
{

}

destoryGraphPool()
{

}
getNodeFromPool()
{

}
getEdgeFromPool()
{

}