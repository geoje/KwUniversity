#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "buf.h"
#include "queue.h"
#include "Disk.h"

int bufCount = 0; // 버퍼 리스트에 있는 버퍼 개수

Buf *BufCreate(int blkno, BufState state);
void BufDetach(Buf *buf);

void BufInit(void)
{
    DevCreateDisk();

    for (int i = 0; i < HASH_ENTRY_NUM; i++)
        TAILQ_INIT(&ppBufList[i]);
    TAILQ_INIT(&ppStateListHead[BUF_LIST_CLEAN]);
    TAILQ_INIT(&ppStateListHead[BUF_LIST_DIRTY]);
    TAILQ_INIT(&pLruListHead);
}

void BufRead(int blkno, char *pData)
{
    Buf *buf = BufGet(blkno);

    if (buf)                                     // 버퍼 리스트에 있을 경우
        TAILQ_REMOVE(&pLruListHead, buf, llist); // 최근 리스트에서 제거
    else
    {
        if (bufCount < MAX_BUF_NUM) // 리스트가 꽉 차지 않았을 경우
        {
            buf = BufCreate(blkno, BUF_STATE_CLEAN); // 버퍼 만들기
            bufCount++;
        }
        else
        {
            BufDetach(buf = TAILQ_FIRST(&pLruListHead)); // 기존 버퍼를 떼어내기
            buf->blkno = blkno;                          // 블럭 번호 업데이트
        }

        DevReadBlock(blkno, buf->pMem);                                    // 디스크에서 읽기
        TAILQ_INSERT_HEAD(&ppBufList[blkno % HASH_ENTRY_NUM], buf, blist); // 버퍼 리스트 머리에 추가
        TAILQ_INSERT_TAIL(&ppStateListHead[BUF_LIST_CLEAN], buf, slist);   // 클린 리스트 꼬리에 추가
    }

    TAILQ_INSERT_TAIL(&pLruListHead, buf, llist); // 최근 리스트 꼬리에 추가
    memcpy(pData, buf->pMem, BLOCK_SIZE);         // 버퍼에서 읽은 데이터 담기
}

void BufWrite(int blkno, char *pData)
{
    Buf *buf = BufGet(blkno);

    if (buf) // 버퍼 리스트에 있을 경우
    {
        TAILQ_REMOVE(&pLruListHead, buf, llist); // 최근 리스트에서 제거
        if (buf->state == BUF_STATE_CLEAN)       // 버퍼가 깨끗한 상태일 경우
        {
            TAILQ_REMOVE(&ppStateListHead[BUF_LIST_CLEAN], buf, slist);      // 클린 리스트에서 제거
            TAILQ_INSERT_TAIL(&ppStateListHead[BUF_LIST_DIRTY], buf, slist); // 더티 리스트 꼬리에 추가
            buf->state = BUF_STATE_DIRTY;                                    // 상태를 더티로 변경
        }
    }
    else
    {
        if (bufCount < MAX_BUF_NUM) // 리스트가 꽉 차지 않았을 경우
        {
            buf = BufCreate(blkno, BUF_STATE_DIRTY); // 버퍼 만들기
            bufCount++;                              // 버퍼 개수 증가
        }
        else
        {
            BufDetach(buf = TAILQ_FIRST(&pLruListHead)); // 기존 버퍼를 모든 리스트에서 제거
            buf->state = BUF_STATE_DIRTY;                // 상태를 더티로 변경
            buf->blkno = blkno;                          // 블럭 번호 업데이트
        }

        TAILQ_INSERT_HEAD(&ppBufList[blkno % HASH_ENTRY_NUM], buf, blist); // 버퍼 리스트 머리에 추가
        TAILQ_INSERT_TAIL(&ppStateListHead[BUF_LIST_DIRTY], buf, slist);   // 더티 리스트 꼬리에 추가
    }

    TAILQ_INSERT_TAIL(&pLruListHead, buf, llist); // 최근 리스트 꼬리에 추가
    memcpy(buf->pMem, pData, BLOCK_SIZE);         // 데이터를 버퍼에 저장
}

void BufSync(void)
{
    Buf *buf = TAILQ_FIRST(&ppStateListHead[BUF_LIST_DIRTY]);
    if (!buf)
        return;
    Buf *nextBuf = buf ? TAILQ_NEXT(buf, slist) : NULL;

    // 더티 리스트에서 사라질 것이기 떄문에 미리 다음 엔트리를 가져옴
    for (; nextBuf; buf = nextBuf, nextBuf = TAILQ_NEXT(buf, slist))
        BufSyncBlock(buf->blkno);

    // 마지막 엔트리 처리
    BufSyncBlock(buf->blkno);
}

// 해당 블럭만 Sync 하는 것인데 clean block 은 들어오지 않는다고 하니 예외처리 필요 없음
void BufSyncBlock(int blkno)
{
    Buf *buf = BufGet(blkno);
    if (!buf)
        return;

    DevWriteBlock(buf->blkno, buf->pMem);                            // 디스크에 저장
    TAILQ_REMOVE(&ppStateListHead[BUF_LIST_DIRTY], buf, slist);      // 더티 리스트에서 제거
    buf->state = BUF_STATE_CLEAN;                                    // 클린 상태로 변경
    TAILQ_INSERT_TAIL(&ppStateListHead[BUF_LIST_CLEAN], buf, slist); // 클린 리스트 꼬리에 추가
}

// 버퍼 리스트에서 해당 블럭 넘버를 가진 버퍼 찾기
Buf *BufGet(int blkno)
{
    Buf *buf;
    TAILQ_FOREACH(buf, &ppBufList[blkno % HASH_ENTRY_NUM], blist)
    {
        if (buf->blkno == blkno)
            return buf;
    }
    return NULL;
}

// 버퍼 만들기
Buf *BufCreate(int blkno, BufState state)
{
    Buf *buf = malloc(sizeof(Buf));

    buf->blkno = blkno;
    buf->state = state;
    buf->pMem = malloc(BLOCK_SIZE);

    return buf;
}
// 버퍼 떼어내기
void BufDetach(Buf *buf)
{
    // 리스트들에서 제거
    if (buf->state == BUF_STATE_CLEAN)
        TAILQ_REMOVE(&ppStateListHead[BUF_LIST_CLEAN], buf, slist);
    else
    {
        DevWriteBlock(buf->blkno, buf->pMem);
        buf->state = BUF_STATE_CLEAN;
        TAILQ_REMOVE(&ppStateListHead[BUF_LIST_DIRTY], buf, slist);
    }
    TAILQ_REMOVE(&ppBufList[buf->blkno % HASH_ENTRY_NUM], buf, blist); // 버퍼 리스트에서 제거
    TAILQ_REMOVE(&pLruListHead, buf, llist);                           // 최근 리스트에서 제거
}

/*
 * GetBufInfoByListNum: Get all buffers in a list specified by listnum.
 *                      This function receives a memory pointer to "ppBufInfo" that can contain the buffers.
 */
void GetBufInfoByListNum(StateList listnum, Buf **ppBufInfo, int *pNumBuf)
{
    Buf *buf;
    int i = 0;

    TAILQ_FOREACH(buf, &ppStateListHead[listnum], slist)
    {
        ppBufInfo[i++] = buf;
    }
    *pNumBuf = i;
}

/*
 * GetBufInfoInLruList: Get all buffers in a list specified at the LRU list.
 *                         This function receives a memory pointer to "ppBufInfo" that can contain the buffers.
 */
void GetBufInfoInLruList(Buf **ppBufInfo, int *pNumBuf)
{
    Buf *buf;
    int i = 0;

    TAILQ_FOREACH(buf, &pLruListHead, llist)
    {
        ppBufInfo[i++] = buf;
    }
    *pNumBuf = i;
}

/*
 * GetBufInfoInBufferList: Get all buffers in the buffer list.
 *                         This function receives a memory pointer to "ppBufInfo" that can contain the buffers.
 */
void GetBufInfoInBufferList(int hashEntNum, Buf **ppBufInfo, int *pNumBuf)
{
    Buf *buf;
    int i = 0;

    TAILQ_FOREACH(buf, &ppBufList[hashEntNum % HASH_ENTRY_NUM], blist)
    {
        ppBufInfo[i++] = buf;
    }
    *pNumBuf = i;
}
