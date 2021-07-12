#include <stdio.h>
#include "fat.h"
#include "Disk.h"

void FatInit(void)
{
   // 2017203014 ���ȣ
   char buffer[BLOCK_SIZE] = {
       0,
   };

   DevCreateDisk();
   for (int i = 0; i < NUM_FAT_BLOCK; i++)
      DevWriteBlock(i, buffer);
}

/* newBlkNum�� �����ϴ� FAT entry�� value�� 0�� �ƴϸ� -1�� ������.
   lastBlkNum�� �����ϴ� FAT entry�� ���� -1�� �ƴϸ� -1�� ������. */
int FatAdd(int lastBlkNum, int newBlkNum)
{
   const int ENTRY_NUM = BLOCK_SIZE / 4;
   int lastBlkNo = lastBlkNum / ENTRY_NUM, lastBlkIdx = lastBlkNum % ENTRY_NUM;
   int newBlkNo = newBlkNum / ENTRY_NUM, newBlkIdx = newBlkNum % ENTRY_NUM;
   int buffer[ENTRY_NUM];

   // Write new entry
   DevReadBlock(newBlkNo, (char *)buffer);
   if (buffer[newBlkIdx] != 0)
      return -1;
   buffer[newBlkIdx] = -1;
   DevWriteBlock(newBlkNo, (char *)buffer);
   if (lastBlkNum == -1)
      return 0;

   // Modify last entry
   DevReadBlock(lastBlkNo, (char *)buffer);
   if (buffer[lastBlkIdx] != -1)
      return -1;
   buffer[lastBlkIdx] = newBlkNum;
   DevWriteBlock(lastBlkNo, (char *)buffer);
   return 1;
}

/* firstBlkNum�� �����ϴ� FAT entry�� value�� 0�̰ų�
   logicalBlkNum�� �����ϴ� physical block ��ȣ�� -1�̰ų� 0�� ���, -1�� ������ */
int FatGetBlockNum(int firstBlkNum, int logicalBlkNum)
{
   const int ENTRY_NUM = BLOCK_SIZE / 4;
   int buffer[ENTRY_NUM];

   for (; logicalBlkNum > 0; logicalBlkNum--)
   {
      DevReadBlock(firstBlkNum / ENTRY_NUM, (char *)buffer);
      if ((firstBlkNum = buffer[firstBlkNum % ENTRY_NUM]) <= -1)
         return -1;
   }

   return firstBlkNum;
}

/* firstBlkNum�� �����ϴ� FAT entry�� value�� 0�̰ų�
   startBlkNm�� �����ϴ� FAT entry�� value�� 0�� ���, -1�� ������.*/
int FatRemove(int firstBlkNum, int startBlkNum)
{
   const int ENTRY_NUM = BLOCK_SIZE / 4;
   int nextBlkNum, count = 0;
   int buffer[ENTRY_NUM];

   // Find start entry
   while (1)
   {
      DevReadBlock(firstBlkNum / ENTRY_NUM, (char *)buffer);
      if ((nextBlkNum = buffer[firstBlkNum % ENTRY_NUM]) <= 0)
         return -1;

      if (nextBlkNum == startBlkNum)
      {
         buffer[firstBlkNum % ENTRY_NUM] = -1;
         DevWriteBlock(firstBlkNum / ENTRY_NUM, (char *)buffer);
         break;
      }
      else
         firstBlkNum = nextBlkNum;
   }

   // Remove entry
   while ((startBlkNum = nextBlkNum) != -1)
   {
      DevReadBlock(startBlkNum / ENTRY_NUM, (char *)buffer);
      nextBlkNum = buffer[startBlkNum % ENTRY_NUM];
      buffer[startBlkNum % ENTRY_NUM] = 0;
      DevWriteBlock(startBlkNum / ENTRY_NUM, (char *)buffer);
      count++;
   }

   return count;
}
