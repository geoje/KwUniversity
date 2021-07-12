#include <stdio.h>
#include "fat.h"
#include "Disk.h"

void FatInit(void)
{

}


/* newBlkNum이 지정하는 FAT entry의 value가 0이 아니면 -1을 리턴함.
   lastBlkNum이 지정하는 FAT entry의 값이 -1이 아니면 -1을 리턴함. */
int FatAdd(int lastBlkNum, int newBlkNum)
{

}

/* firstBlkNum이 지정하는 FAT entry의 value가 0이거나
   logicalBlkNum에 대응하는 physical block 번호가 -1이거나 0인 경우, -1을 리턴함 */
int FatGetBlockNum(int firstBlkNum, int logicalBlkNum)
{

}

/* firstBlkNum이 지정하는 FAT entry의 value가 0이거나
   startBlkNm이 지정하는 FAT entry의 value가 0인 경우, -1을 리턴함.*/

int FatRemove(int firstBlkNum, int startBlkNum)
{

}
