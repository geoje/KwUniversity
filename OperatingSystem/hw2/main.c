#include <stdio.h>
#include <stdlib.h>
#include "buf.h"

int main(void)
{
	char pData[32];
	BufInit();

	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 31; j++)
			pData[j] = 'a' + i;
		BufWrite(i, pData);
	}

	//BufSync();

	BufRead(4, pData);
	BufRead(5, pData);
	BufRead(6, pData);

	BufRead(0, pData);
	printf("%s\n", pData);
	BufRead(1, pData);
	printf("%s\n", pData);
	BufRead(2, pData);
	printf("%s\n", pData);

	return 0;
}