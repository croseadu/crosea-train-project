
#include "../include/my.h"
#include "../include/util.h"



STATUS getNextNumber(const char *inputBuffer, int *pCurIndex, int *pData)
{
	int index, data = 0;
	BOOL bGetData = FALSE;

	index = *pCurIndex;

	while (1)
	{
		switch (inputBuffer[index])
		{
			case ' ':
			case '\t':
				if (bGetData)
				{
					*pCurIndex = index;
					*pData = data;
					return OK;
				}
				index++;
				break;
			case '\n':
			case '\0':
				*pCurIndex = index;
				if (bGetData)
				{
					*pData = data;
					return OK;
				}
				else
					return END;
			case '0':
				data = 0;
				bGetData = TRUE;
				index++;
				break;
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				if (bGetData)
					return ERROR;
				do
				{
					data *= 10;
					data += inputBuffer[index++] - '0';	
				}while(isdigit(inputBuffer[index]));

				bGetData = TRUE;
				break;
			default:
				*pCurIndex = index;
				return ERROR;
			
		}
	}


}
