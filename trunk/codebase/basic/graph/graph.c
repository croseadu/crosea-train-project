#include "../../include/my.h"
#include "../../include/util.h"


int main()
{
	int fp;
	char buf[1024];
	int readCount;

        fp = open("temp", O_RDONLY);

        if (fp < 0)
          	return -1;

        readCount = read(fp, buf, 1023);

        if (readCount <= 0)
		return -1;
	
	buf[readCount] = '\n';
	printf("\nInput is %s", buf);

	close(fp);

	return 0;



}


