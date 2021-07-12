#include <stdio.h>
#include <stdlib.h>
#include "buf.h"
#include "queue.h"


void BufInit(void)
{

}

void BufRead(int blkno, char* pData)
{

}


void BufWrite(int blkno, char* pData)
{

}

void BufSync(void)
{

}



/*
 * GetBufInfoByListNum: Get all buffers in a list specified by listnum.
 *                      This function receives a memory pointer to "ppBufInfo" that can contain the buffers.
 */
void GetBufInfoByListNum(StateList listnum, Buf** ppBufInfo, int* pNumBuf)
{

}



/*
 * GetBufInfoInLruList: Get all buffers in a list specified at the LRU list.
 *                         This function receives a memory pointer to "ppBufInfo" that can contain the buffers.
 */
void GetBufInfoInLruList(Buf** ppBufInfo, int* pNumBuf)
{

}


/*
 * GetBufInfoInBufferList: Get all buffers in the buffer list.
 *                         This function receives a memory pointer to "ppBufInfo" that can contain the buffers.
 */
void GetBufInfoInBufferList(Buf** ppBufInfo, int* pNumBuf)
{

}
