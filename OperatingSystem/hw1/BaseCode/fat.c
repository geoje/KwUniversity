#include <stdio.h>
#include "fat.h"
#include "Disk.h"

void FatInit(void)
{

}


/* newBlkNum�� �����ϴ� FAT entry�� value�� 0�� �ƴϸ� -1�� ������.
   lastBlkNum�� �����ϴ� FAT entry�� ���� -1�� �ƴϸ� -1�� ������. */
int FatAdd(int lastBlkNum, int newBlkNum)
{

}

/* firstBlkNum�� �����ϴ� FAT entry�� value�� 0�̰ų�
   logicalBlkNum�� �����ϴ� physical block ��ȣ�� -1�̰ų� 0�� ���, -1�� ������ */
int FatGetBlockNum(int firstBlkNum, int logicalBlkNum)
{

}

/* firstBlkNum�� �����ϴ� FAT entry�� value�� 0�̰ų�
   startBlkNm�� �����ϴ� FAT entry�� value�� 0�� ���, -1�� ������.*/

int FatRemove(int firstBlkNum, int startBlkNum)
{

}
