#include "common.h"
#include <stdio.h>

enum BOOL isEOF(const char in)
{
	return in == EOF ? True : False;
}

void skipSpace(char **ppChar)
{
	char * pChar = *ppChar;
	while (*pChar == ' ')
		++pChar;
	*ppChar = pChar;
}


enum BOOL match(const char in, const char ref)
{
	return in == ref ? True : False;
}

void advanceTill(char **ppChar, const char ref)
{
	char * pChar = *ppChar;
	while (*pChar != ref)
		++pChar;
	*ppChar = pChar;

}
