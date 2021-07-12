#include <stdio.h>
#include <stdlib.h>
#include "fat.h"
#include "validate.h"

#define FAT_START_ENTRY_NUM		(NUM_FAT_BLOCK)
#define FAT_END_ENTRY_NUM		(NUM_FAT_BLOCK*BLOCK_SIZE/sizeof(int) - 1)

void testcase1(void)
{
	int lblkno = 0;
	int j = 0;
	int i = 0;

	FatInit();
	FatAdd(-1, FAT_START_ENTRY_NUM);
	for (i = FAT_START_ENTRY_NUM; i <= FAT_END_ENTRY_NUM - 2; i += 2)
	{
		lblkno++;
		j = i + 2;
		if (FatAdd(i, j) < 0)
		{
			printf("testcase1: fail O.O\n");
			return;
		}
		if (j != FatGetBlockNum(FAT_START_ENTRY_NUM, lblkno))
		{
			printf("testcase1: fail O.O\n");
			return;
		}
	}
	printFAT();

	j = 0;
	lblkno = 0;
	FatAdd(-1, FAT_START_ENTRY_NUM + 1);
	for (i = FAT_START_ENTRY_NUM + 1; i <= FAT_END_ENTRY_NUM - 2; i += 2)
	{
		lblkno++;
		j = i + 2;
		if (FatAdd(i, j) < 0)
		{
			printf("testcase1: fail O.O\n");
			return;
		}
		if (j != FatGetBlockNum(FAT_START_ENTRY_NUM + 1, lblkno))
		{
			printf("testcase1: fail O.O\n");
			return;
		}

	}
	printFAT();

	return;
}

void testFatRemove(int firstBlkNum, int startBlkNum)
{
	if (FatRemove(firstBlkNum, startBlkNum) < 0)
	{
		printf("testcase1: first blk no:%d, start blk no:%d fail O.O\n",
			firstBlkNum, startBlkNum);
	}
}


void testcase2(void)
{
	int lblkno = 0;
	int j = 0;
	int i = 0;

	FatInit();
	FatAdd(-1, FAT_START_ENTRY_NUM);
	for (i = FAT_START_ENTRY_NUM; i <= FAT_END_ENTRY_NUM - 2; i += 2)
	{
		lblkno++;
		j = i + 2;
		if (FatAdd(i, j) < 0)
		{
			printf("testcase2: fail O.O\n");
			return;
		}
		if (j != FatGetBlockNum(FAT_START_ENTRY_NUM, lblkno))
		{
			printf("testcase2: fail O.O\n");
			return;
		}
	}

	testFatRemove(16, 100);
	printFAT();

	testFatRemove(16, 18);
	printFAT();

	FatAdd(16, 18);

	FatAdd(18, 30);

	FatAdd(30, 35);

	FatAdd(35, 75);

	FatAdd(75, 90);

	FatAdd(90, 127);
	printFAT();

	testFatRemove(16, 30);
	printFAT();

	return;
}

int main(int argc, char* argv[])
{
	int tcNum;

	if (argc != 2)
	{
		printf("Input TestCase Number!\n");
		exit(0);
	}
	tcNum = atoi(argv[1]);

	switch (tcNum)
	{
	case 1:
		testcase1();
		break;
	case 2:
		testcase2();
		break;
	}

	return 0;
}
