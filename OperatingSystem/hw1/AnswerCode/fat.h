#ifndef __FAT_H__
#define __FAT_H__

#include "Disk.h"

/* the number of FAT blocks */
#define NUM_FAT_BLOCK (16)

void FatInit(void);
int FatAdd(int lastBlkNum, int newBlkNum);
int FatGetBlockNum(int firstBlkNum, int logicalBlkNum);
int FatRemove(int firstBlkNum, int startBlkNum);

#endif
