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
	int fp;
	char buf[1024];
	char from, to;
	int readCount;
	int curIndex;
	int offset = 0;

	fp = open("temp", O_RDONLY);

	if (fp < 0)
		return -1;
	while (1)
	{
		readCount = read(fp, buf+offset, 1023);

		if (readCount <= 0)
			break;;
	
		buf[readCount] = '\n';
		printf("\nInput is %s", buf);

		curIndex = 0;
		while (buf[curIndex] == '\t' 
			   || buf[curIndex] == ' ' 
			   || curIndex < readCount)
			   curIndex++;


		if (curIndex+4 >= readCount)
		{
			memcpy(buf, buf+curIndex, readCount - curIndex);
			offset = readCount - curIndex;
			continue;
		}

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

	close(fp);

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