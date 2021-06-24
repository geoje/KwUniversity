#include <stdio.h>
#include "Disk.h"
#include "fat.h"
#include "buf.h"
#include "fs.h"

void FatInit(void)
{
    BufInit();
}

/* newBlkNum이 지정하는 FAT entry의 value가 0이 아니면 -1을 리턴함.
   lastBlkNum이 지정하는 FAT entry의 값이 -1이 아니면 -1을 리턴함. */
int FatAdd(int lastBlkNum, int newBlkNum)
{
    const int ENTRY_NUM = BLOCK_SIZE / 4;
    int block[ENTRY_NUM];
    int lastBlkNo = lastBlkNum / ENTRY_NUM, newBlkNo = newBlkNum / ENTRY_NUM;   // 디스크상 블럭 넘버
    int lastBlkIdx = lastBlkNum % ENTRY_NUM, newBlkIdx = newBlkNum % ENTRY_NUM; // 블럭 내부의 인덱스 넘버

    // Write new entry
    BufRead(FAT_START_BLOCK + newBlkNo, (char *)block);
    if (block[newBlkIdx] != 0)
        return -1;
    block[newBlkIdx] = -1;
    BufWrite(FAT_START_BLOCK + newBlkNo, (char *)block);
    if (lastBlkNum == -1)
        return 0;

    // Modify last entry
    BufRead(FAT_START_BLOCK + lastBlkNo, (char *)block);
    if (block[lastBlkIdx] != -1)
        return -1;
    block[lastBlkIdx] = newBlkNum;
    BufWrite(FAT_START_BLOCK + lastBlkNo, (char *)block);
    return 1;
}

/* firstBlkNum이 지정하는 FAT entry의 value가 0이거나
   logicalBlkNum에 대응하는 physical block 번호가 -1이거나 0인 경우, -1을 리턴함 */
int FatGetBlockNum(int firstBlkNum, int logicalBlkNum)
{
    const int ENTRY_NUM = BLOCK_SIZE / sizeof(int);
    int block[ENTRY_NUM];

    for (; logicalBlkNum > 0; logicalBlkNum--)
    {
        BufRead(FAT_START_BLOCK + firstBlkNum / ENTRY_NUM, (char *)block);
        if ((firstBlkNum = block[firstBlkNum % ENTRY_NUM]) <= -1)
            return -1;
    }

    return firstBlkNum;
}

/* firstBlkNum이 지정하는 FAT entry의 value가 0이거나
   startBlkNm이 지정하는 FAT entry의 value가 0인 경우, -1을 리턴함.*/
int FatRemove(int firstBlkNum, int startBlkNum)
{
    const int ENTRY_NUM = BLOCK_SIZE / sizeof(int);
    int nextBlkNum, count = 0;
    int block[ENTRY_NUM];

    // Find start entry
    while (1)
    {
        BufRead(FAT_START_BLOCK + firstBlkNum / ENTRY_NUM, (char *)block);
        nextBlkNum = block[firstBlkNum % ENTRY_NUM];
        if (nextBlkNum <= 0)
        {
            if (firstBlkNum == startBlkNum)
            {
                block[firstBlkNum % ENTRY_NUM] = 0;
                BufWrite(FAT_START_BLOCK + firstBlkNum / ENTRY_NUM, (char *)block);
                return 1;
            }
            else
                return -1;
        }

        if (firstBlkNum == startBlkNum)
        {
            block[firstBlkNum % ENTRY_NUM] = 0;
            BufWrite(FAT_START_BLOCK + firstBlkNum / ENTRY_NUM, (char *)block);
            count++;
            break;
        }
        else if (nextBlkNum == startBlkNum)
        {
            block[firstBlkNum % ENTRY_NUM] = -1;
            BufWrite(FAT_START_BLOCK + firstBlkNum / ENTRY_NUM, (char *)block);
            break;
        }
        else
            firstBlkNum = nextBlkNum;
    }

    // Remove entry
    while ((startBlkNum = nextBlkNum) != -1)
    {
        BufRead(FAT_START_BLOCK + startBlkNum / ENTRY_NUM, (char *)block);
        nextBlkNum = block[startBlkNum % ENTRY_NUM];
        block[startBlkNum % ENTRY_NUM] = 0;
        BufWrite(FAT_START_BLOCK + startBlkNum / ENTRY_NUM, (char *)block);
        count++;
    }

    return count;
}

// Data region (130 Entry) 부터 탐색하여 빈 것 찾기
int FatGetFreeEntryNum(void)
{
    const int ENTRY_NUM = BLOCK_SIZE / sizeof(int);
    int block[ENTRY_NUM], i = DATA_START_BLOCK - 1;

    do
        BufRead(FAT_START_BLOCK + (++i) / ENTRY_NUM, (char *)block);
    while (block[i % ENTRY_NUM]);
    return i;
}