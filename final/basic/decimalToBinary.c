#include "stack.h"




#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


static
void print(const void *data)
{}

static
void
convertToBinary(const int val)
{

	LPStack pStack;
	int curVal = val;
	unsigned int bit;

	if (False == createStack(&pStack, sizeof(unsigned int),print)) {
		return;
	}

	while (curVal) {
		bit = (curVal & 0x1) ? 1 : 0;
		push(pStack, &bit);
		curVal >>= 1;
	}

	printf("\nConvert to binary: 0b");
	while (False == isStackEmpty(pStack)) {
		pop(pStack, &bit);
		putchar(bit == 1 ? '1': '0');
	}
	putchar('\n');


	curVal = val;
	while (curVal) {
		bit = (curVal & 0xF);
		push(pStack, &bit);
		curVal >>= 4;
	}

	printf("\nConvert to hex: 0X");
	while (False == isStackEmpty(pStack)) {
		pop(pStack, &bit);
		if (bit < 10) {
			putchar('0'+bit);
		} else {
			putchar('A'+bit-10);
		}
	}
	putchar('\n');


	printf("use print hex: %x\n", val);
}





int main()
{
	
	int value;

	printf("Convert data from hex to binary.\n");
	printf("Input: ");
	scanf("%d", &value);
	
	convertToBinary(value);
	
	return 0;
}

