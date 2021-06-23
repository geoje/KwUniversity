#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "buf.h"
#include "fat.h"
#include "fs.h"

FileDescTable *pFileDescTable = NULL;

void FileSysInit(void)
{
    BufInit();
}

int OpenFile(const char *szFileName, OpenFlag flag, AccessMode mode)
{
}

int WriteFile(int fileDesc, char *pBuffer, int length)
{
}

int ReadFile(int fileDesc, char *pBuffer, int length)
{
}

int CloseFile(int fileDesc)
{
}

int RemoveFile(const char *szFileName)
{
}

/* 파일이 많은 폴더일 경우 여러 블록을 사용했을 테니 다음 블록 번호가 뭔지 FAT Table에서 다음 넘버를 가져옴
   -1이 리턴된 경우 다음 블록 없는 것임 */
int GetNextFatEntryNo(int fatEntryNo)
{
    const int ENTRY_NUM = BLOCK_SIZE / sizeof(int);
    int block[ENTRY_NUM];
    BufRead(FAT_START_BLOCK + fatEntryNo / ENTRY_NUM, (char *)block);
    return block[fatEntryNo % ENTRY_NUM];
}
int MakeDirectory(const char *szDirName, AccessMode mode)
{
    // 파일 시스템 정보 읽기
    FileSysInfo *fsi = malloc(BLOCK_SIZE);
    BufRead(FILEINFO_START_BLOCK, (char *)fsi);

    // 새로 지정할 Fat table 번호 찾고 -1 넣기
    int newEntryNo = FatGetFreeEntryNum();
    FatAdd(-1, newEntryNo);

    // 새로 만들 디렉토리 경로를 슬래시 기준으로 쪼개기 위함
    char fullPath[BLOCK_SIZE];
    strcpy(fullPath, szDirName);

    // 현재 Fat table의 번호
    int curFatEntryNo = DATA_START_BLOCK;

    // 현재 보고 있는 디렉토리 엔트리
    DirEntry dirents[NUM_OF_DIRENT_PER_BLK];
    BufRead(DATA_START_BLOCK, (char *)dirents);

    // 쪼갠 경로를 순차적으로 탐색 후 폴더 생성
    char *curDirName = strtok(fullPath, "/");
    char *nextDirName = strtok(NULL, "/");
    while (curDirName != NULL)
    {
        for (int i = 0; i < NUM_OF_DIRENT_PER_BLK; i++)
        {
            // 최종 폴더 명이 경우: 현재 위치에 없을 때 까지 찾은 후 생성하기
            if (nextDirName == NULL)
            {
                // 폴더가 이미 있을 경우 실패 처리
                if (strcmp(curDirName, dirents[i].name) == 0)
                    return -1;
                // 현재 서칭 폴더 명이 없을 경우 빈 폴더 발견!
                else if (strlen(dirents[i].name) == 0)
                {
                    strcpy(dirents[i].name, curDirName);
                    dirents[i].mode = mode;
                    dirents[i].startBlockNum = newEntryNo;
                    dirents[i].filetype = FILE_TYPE_DEV;
                    dirents[i].numBlocks = 1;

                    // 새 폴더 작성
                    BufWrite(curFatEntryNo, (char *)dirents);

                    // 파일 시스템 정보 업데이트
                    fsi->blocks++;
                    fsi->numAllocBlocks++;
                    fsi->numFreeBlocks--;
                    fsi->numAllocFiles++;
                    BufWrite(FILEINFO_START_BLOCK, (char *)fsi);
                    BufSync();

                    return 0;
                }

                // 마지막 엔트리까지 봤을 경우 현재 폴더 다음 블럭 서칭 (다음 블럭이 있을 경우만)
                if (i == NUM_OF_DIRENT_PER_BLK - 1)
                {
                    curFatEntryNo = GetNextFatEntryNo(curFatEntryNo);
                    if (curFatEntryNo != -1)
                    {
                        // Change to next dirents
                    }
                }
            }
            // 아닐 경우: 찾은 뒤 들어가기
            else
            {
                // 들어갈 폴더를 찾았을 경우
                if (strcmp(curDirName, dirents[i].name) == 0)
                    break;
                // 마지막까지 갔는데 폴더가 없을 경우 실패 처리
                else if (i == NUM_OF_DIRENT_PER_BLK - 1)
                    return -1;
            }
        }
        curDirName = nextDirName;
        nextDirName = strtok(NULL, "/");
    }
}

int RemoveDirectory(const char *szDirName)
{
}

void Format(void)
{
    FatAdd(-1, DATA_START_BLOCK); // 130번 Entry에 -1 넣기

    // 루트 디렉토리 생성
    DirEntry dirents[NUM_OF_DIRENT_PER_BLK] = {
        0,
    };
    strcpy(dirents[0].name, ".");
    dirents[0].mode = ACCESS_MODE_READWRITE;
    dirents[0].startBlockNum = DATA_START_BLOCK;
    dirents[0].filetype = FILE_TYPE_DIR;
    dirents[0].numBlocks = 1;
    BufWrite(DATA_START_BLOCK, (char *)dirents);

    // 파일 시스템 정보 설정 (루트 디렉토리 반영)
    char fsiBuf[BLOCK_SIZE] = {
        0,
    };
    FileSysInfo fsi = {
        blocks : 3,
        rootFatEntryNum : DATA_START_BLOCK,
        diskCapacity : FS_DISK_CAPACITY,
        numAllocBlocks : 1,
        numFreeBlocks : MAX_FILE_NUM - 1,
        numAllocFiles : 1,
        fatTableStart : FAT_START_BLOCK,
        dataStart : DATA_START_BLOCK
    };
    memcpy(fsiBuf, &fsi, sizeof(FileSysInfo)); // 메모리에 할당된 블럭에 파일 시스템 정보 넣기
    BufWrite(FILEINFO_START_BLOCK, fsiBuf);    // 그 블럭을 디스크에 작성
    // BufSync();
}

void Mount(void)
{
}

void Unmount(void)
{
    BufSync();
}

Directory *OpenDirectory(char *szDirName)
{
}

FileInfo *ReadDirectory(Directory *pDir)
{
}

int CloseDirectory(Directory *pDir)
{
}