#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "buf.h"
#include "fat.h"
#include "fs.h"

FileTable *pFileTable = NULL;
FileDescTable *pFileDescTable = NULL;

void FileSysInit(void)
{
    BufInit();
    pFileTable = (FileTable *)calloc(sizeof(FileTable), 1);
    pFileDescTable = (FileDescTable *)calloc(sizeof(FileDescTable), 1);
    pFileSysInfo = (FileSysInfo *)calloc(sizeof(FileSysInfo), 1);
}

/* 파일이 많은 폴더일 경우 여러 블록을 사용했을 테니 다음 블록 번호가 뭔지 FAT Table에서 다음 넘버를 가져옴
   -1이 리턴된 경우 다음 블록 없는 것임 */
int GetNextEntryNo(int fatEntryNo)
{
    const int ENTRY_NUM = BLOCK_SIZE / sizeof(int);
    int block[ENTRY_NUM];
    BufRead(FAT_START_BLOCK + fatEntryNo / ENTRY_NUM, (char *)block);
    return block[fatEntryNo % ENTRY_NUM];
}
// 파일을 테이블에 추가하고 디스크립터 번호 반환
int AddFileToTable(File file)
{
    for (int i = 0; i < MAX_FILE_NUM; i++)
    {
        if (pFileTable->pFile[i].bUsed)
            continue;

        pFileTable->pFile[i].bUsed = 1;
        pFileTable->pFile[i].flag = file.flag;
        pFileTable->pFile[i].dirBlkNum = file.dirBlkNum;
        pFileTable->pFile[i].entryIndex = file.entryIndex;
        pFileTable->pFile[i].fileOffset = file.fileOffset;
        pFileTable->numUsedFile++;

        pFileDescTable->pEntry[i].bUsed = 1;
        pFileDescTable->pEntry[i].fileTableIndex = i;
        pFileDescTable->numUsedDescEntry++;
        return i;
    }
}
void UpdateFileSysInfoBuf()
{
    char fsiBuf[BLOCK_SIZE] = {
        0,
    };
    memcpy(fsiBuf, pFileSysInfo, sizeof(FileSysInfo));
    BufWrite(FILEINFO_START_BLOCK, fsiBuf);
}

int OpenFile(const char *szFileName, OpenFlag flag, AccessMode mode)
{
    // 현재 Fat table의 번호
    int searchEntryNo = DATA_START_BLOCK;

    // 현재 보고 있는 디렉토리 엔트리
    DirEntry dirents[NUM_OF_DIRENT_PER_BLK];
    BufRead(DATA_START_BLOCK, (char *)dirents);

    // 인자로 받은 경로를 쪼갠 뒤 순차적으로 탐색
    char fullPath[BLOCK_SIZE];
    strcpy(fullPath, szFileName);
    char *curName = strtok(fullPath, "/");
    char *nextName = strtok(NULL, "/");
    while (curName != NULL)
    {
        for (int i = 0;; i++)
        {
            // 들어갈 폴더 또는 열 파일을 찾았을 경우
            if (strcmp(curName, dirents[i].name) == 0)
            {
                // 마지막 파일 이름이고 타입이 파일이면 그냥 열기
                if (nextName == NULL)
                {
                    // 존재하는 파일 열기
                    if (dirents[i].filetype == FILE_TYPE_FILE)
                    {
                        File file = {
                            bUsed : 1,
                            flag : flag,
                            dirBlkNum : searchEntryNo,
                            entryIndex : i,
                            fileOffset : 0
                        };
                        return AddFileToTable(file);
                    }
                }
                else if (dirents[i].filetype == FILE_TYPE_DIR)
                {
                    searchEntryNo = dirents[i].startBlockNum;
                    BufRead(searchEntryNo, (char *)dirents);
                }
                break;
            }
            // 현재 서칭 파일명이 없을 경우 만들기
            else if (strlen(dirents[i].name) == 0)
            {
                // 마지막 경로 즉, 파일일 경우 진행
                if (nextName == NULL)
                {
                    // 현재 디렉토리 엔트리에 새 파일 정보 작성
                    strcpy(dirents[i].name, curName);
                    dirents[i].mode = mode;
                    dirents[i].startBlockNum = -1;
                    dirents[i].filetype = FILE_TYPE_FILE;
                    dirents[i].numBlocks = 0;
                    BufWrite(searchEntryNo, (char *)dirents);

                    File file = {
                        bUsed : 1,
                        flag : flag,
                        dirBlkNum : searchEntryNo,
                        entryIndex : i,
                        fileOffset : 0
                    };

                    // 파일 시스템 정보 업데이트
                    pFileSysInfo->numAllocFiles++;
                    UpdateFileSysInfoBuf();
                    //BufSyncBlock(FILEINFO_START_BLOCK);

                    return AddFileToTable(file);
                }
                else
                    return -1;
            }

            // 마지막 엔트리까지 봤을 경우 현재 폴더 다음 블럭 서칭 (다음 블럭이 있을 경우만)
            if (i == NUM_OF_DIRENT_PER_BLK - 1)
            {
                // 다음 폴더 연결된 것이 없을 경우 새로 만들고 연결시키기!
                int nextEntryNo = GetNextEntryNo(searchEntryNo);
                if (nextEntryNo == -1)
                {
                    int conDirFatEntryNo = FatGetFreeEntryNum();
                    FatAdd(searchEntryNo, conDirFatEntryNo);
                    searchEntryNo = conDirFatEntryNo;
                    memset(dirents, 0, BLOCK_SIZE);

                    // 파일 시스템 정보 업데이트
                    pFileSysInfo->numAllocBlocks++;
                    pFileSysInfo->numFreeBlocks--;
                    UpdateFileSysInfoBuf();
                    //BufSyncBlock(FILEINFO_START_BLOCK);
                }
                // 다음 폴더 연결되어 있으면 그거 읽어서 쓰기
                else
                    BufRead(searchEntryNo = nextEntryNo, (char *)dirents);
                i = -1; // 처음부터 4개 다시 탐색
            }
        }
        curName = nextName;
        nextName = strtok(NULL, "/");
    }
}

int WriteFile(int fileDesc, char *pBuffer, int length)
{
    File file = pFileTable->pFile[pFileDescTable->pEntry[fileDesc].fileTableIndex];
    int newEntryNo = FatGetFreeEntryNum();

    // Fat table 추가
    FatAdd(-1, newEntryNo);

    // 파일이 있는 디렉토리의 해당 엔트리 업데이트
    DirEntry dirents[NUM_OF_DIRENT_PER_BLK];
    BufRead(file.dirBlkNum, (char *)dirents);
    dirents[file.entryIndex].startBlockNum = newEntryNo;
    dirents[file.entryIndex].numBlocks = 1;
    BufWrite(file.dirBlkNum, (char *)dirents);

    // 파일에 해당하는 블럭 작성
    char block[BLOCK_SIZE] = {
        0,
    };
    memcpy(block, pBuffer, length);
    BufWrite(newEntryNo, block);

    // 파일시스템 정보 변경
    pFileSysInfo->numAllocBlocks++;
    pFileSysInfo->numFreeBlocks--;
    UpdateFileSysInfoBuf();
}

int ReadFile(int fileDesc, char *pBuffer, int length)
{
    File file = pFileTable->pFile[pFileDescTable->pEntry[fileDesc].fileTableIndex];

    // 디렉토리 내에서 파일에 해당하는 엔트리 정보 읽기
    DirEntry dirents[NUM_OF_DIRENT_PER_BLK];
    BufRead(file.dirBlkNum, (char *)dirents);
    char block[BLOCK_SIZE] = {
        0,
    };
    BufRead(dirents[file.entryIndex].startBlockNum, block);

    // Call by reference로 반환
    memcpy(pBuffer, block, length);
    return 0;
}

int CloseFile(int fileDesc)
{
    memset(pFileTable->pFile + pFileDescTable->pEntry[fileDesc].fileTableIndex, 0, sizeof(File));
    memset(pFileDescTable->pEntry + fileDesc, 0, sizeof(DescEntry));

    pFileTable->numUsedFile--;
    pFileDescTable->numUsedDescEntry--;
}

int RemoveFile(const char *szFileName)
{
    int searchEntryNo = DATA_START_BLOCK;          // 현재 Fat table의 번호
    int curEntryNo = searchEntryNo;                // 현재 디렉토리 시작 엔트리 위치
    int removeEntryNo = -1, removeEntryIndex = -1; // 제거될 엔트리의 위치

    // 현재 보고 있는 디렉토리 엔트리
    DirEntry dirents[NUM_OF_DIRENT_PER_BLK];
    BufRead(DATA_START_BLOCK, (char *)dirents);

    // 인자로 받은 경로를 쪼갠 뒤 순차적으로 탐색
    char fullPath[BLOCK_SIZE];
    strcpy(fullPath, szFileName);
    char *curName = strtok(fullPath, "/");
    char *nextName = strtok(NULL, "/");
    while (curName != NULL)
    {
        for (int i = 0;; i++)
        {
            // 마지막 파일 찾는중일 경우
            if (nextName == NULL)
            {
                // 삭제할 파일 찾았으면 삭제할거라고 removeEntryNo에 저장
                if (strcmp(curName, dirents[i].name) == 0 && dirents[i].filetype == FILE_TYPE_FILE)
                {
                    removeEntryNo = searchEntryNo;
                    removeEntryIndex = i;
                }

                // 끝까지 왔을 때 삭제할게 지정되어 있으면 제거 처리
                int isLast;
                if (i == NUM_OF_DIRENT_PER_BLK - 1)
                    isLast = GetNextEntryNo(searchEntryNo) == -1;
                else
                    isLast = strlen(dirents[i + 1].name) == 0;
                if (isLast && removeEntryNo != -1)
                {
                    // 엔트리가 하나만 있는 블럭이면 제거하여 공간 절약
                    if (i == 0)
                    {
                        FatRemove(removeEntryNo, searchEntryNo);
                        pFileSysInfo->numAllocBlocks--;
                        pFileSysInfo->numFreeBlocks++;
                    }
                    // 파일 Fat table 에서 제거
                    FatRemove(dirents[i].startBlockNum, dirents[i].startBlockNum);

                    // 마지막 엔트리 백업 후 없애기
                    DirEntry de;
                    memcpy(&de, dirents + i, sizeof(DirEntry));
                    memset(dirents + i, 0, sizeof(DirEntry));
                    BufWrite(searchEntryNo, (char *)dirents);

                    // 마지막 엔트리를 제거된 위치로 옮기기
                    BufRead(removeEntryNo, (char *)dirents);
                    memcpy(dirents + removeEntryIndex, &de, sizeof(DirEntry));
                    BufWrite(removeEntryNo, (char *)dirents);

                    break;
                }
            }
            // 중간 폴더 탐색 중일 경우
            else
            {
                // 들어갈 폴더 또는 열 파일을 찾았을 경우
                if (strcmp(curName, dirents[i].name) == 0 && dirents[i].filetype == FILE_TYPE_DIR)
                {
                    searchEntryNo = curEntryNo = dirents[i].startBlockNum;
                    BufRead(searchEntryNo, (char *)dirents);
                    break;
                }

                // 끝까지 봤는데 없을 경우 실패
                if (strlen(dirents[i].name) == 0)
                    return -1;
            }

            // 마지막 엔트리까지 봤을 경우 현재 폴더 다음 블럭 서칭 (다음 블럭이 있을 경우만)
            if (i == NUM_OF_DIRENT_PER_BLK - 1)
            {
                // 다음 폴더 연결된 것이 없을 경우 새로 만들고 연결시키기!
                int nextEntryNo = GetNextEntryNo(searchEntryNo);
                if (nextEntryNo == -1)
                    return -1;
                // 다음 폴더 연결되어 있으면 그거 읽어서 쓰기
                else
                    BufRead(searchEntryNo = nextEntryNo, (char *)dirents);
                i = -1; // 처음부터 4개 다시 탐색
            }
        }
        curName = nextName;
        nextName = strtok(NULL, "/");
    }
}

int MakeDirectory(const char *szDirName, AccessMode mode)
{
    // 현재 Fat table의 번호와 탐색중인 번호
    int curEntryNo = DATA_START_BLOCK, searchEntryNo = curEntryNo;

    // 현재 보고 있는 디렉토리 엔트리
    DirEntry dirents[NUM_OF_DIRENT_PER_BLK];
    BufRead(DATA_START_BLOCK, (char *)dirents);

    // 현재 탐색중인 폴더 접근 모드
    AccessMode curDirMode = dirents[0].mode;

    // 인자로 받은 경로를 쪼갠 뒤 순차적으로 탐색 후 폴더 생성
    char fullPath[BLOCK_SIZE];
    strcpy(fullPath, szDirName);
    char *curDirName = strtok(fullPath, "/");
    char *nextDirName = strtok(NULL, "/");
    while (curDirName != NULL)
    {
        for (int i = 0;; i++)
        {
            // 폴더가 이미 있을 경우
            if (strcmp(curDirName, dirents[i].name) == 0 &&
                dirents[i].filetype == FILE_TYPE_DIR)
            {
                // 만들어야 하는데 이미 있는 경우 함수 종료
                if (nextDirName == NULL)
                    return -1;
                // 그 폴더로 들어가야 한다면 들어가기
                else
                {
                    searchEntryNo = curEntryNo = dirents[i].startBlockNum;
                    BufRead(curEntryNo, (char *)dirents);
                    curDirMode = dirents[0].mode;
                    break;
                }
            }
            // 현재 서칭 폴더 명이 없을 경우 빈 공간 탐색 완료
            else if (strlen(dirents[i].name) == 0)
            {
                // 새로 지정할 Fat table 번호 찾고 -1 넣기
                int newEntryNo = FatGetFreeEntryNum();
                FatAdd(-1, newEntryNo);

                // 현재 디렉토리 엔트리에 새 폴더 정보 작성
                strcpy(dirents[i].name, curDirName);
                dirents[i].mode = mode;
                dirents[i].startBlockNum = newEntryNo;
                dirents[i].filetype = FILE_TYPE_DIR;
                dirents[i].numBlocks = 1;
                BufWrite(searchEntryNo, (char *)dirents);

                // 새로 만드는 디렉토리 엔트리 작성
                memset(dirents, 0, BLOCK_SIZE);
                strcpy(dirents[0].name, ".");
                dirents[0].mode = mode;
                dirents[0].startBlockNum = newEntryNo;
                dirents[0].filetype = FILE_TYPE_DIR;
                dirents[0].numBlocks = 1;

                // 상위 디렉토리 작성
                strcpy(dirents[1].name, "..");
                dirents[1].mode = curDirMode;
                dirents[1].startBlockNum = curEntryNo;
                dirents[1].filetype = FILE_TYPE_DIR;
                dirents[1].numBlocks = 1;
                BufWrite(newEntryNo, (char *)dirents);

                // 파일 시스템 정보 업데이트
                pFileSysInfo->numAllocBlocks++;
                pFileSysInfo->numFreeBlocks--;
                pFileSysInfo->numAllocFiles++;
                UpdateFileSysInfoBuf();
                //BufSyncBlock(FILEINFO_START_BLOCK);

                if (nextDirName == NULL)
                    return 0;
                else
                {
                    BufRead(searchEntryNo, (char *)dirents);
                    i--;
                }
            }

            // 마지막 엔트리까지 봤을 경우 현재 폴더 다음 블럭 서칭 (다음 블럭이 있을 경우만)
            if (i == NUM_OF_DIRENT_PER_BLK - 1)
            {
                // 다음 폴더 연결된 것이 없을 경우 새로 만들고 연결시키기!
                int nextEntryNo = GetNextEntryNo(searchEntryNo);
                if (nextEntryNo == -1)
                {
                    int conDirFatEntryNo = FatGetFreeEntryNum();
                    FatAdd(searchEntryNo, conDirFatEntryNo);
                    searchEntryNo = conDirFatEntryNo;
                    memset(dirents, 0, BLOCK_SIZE);

                    // 파일 시스템 정보 업데이트
                    pFileSysInfo->numAllocBlocks++;
                    pFileSysInfo->numFreeBlocks--;
                    UpdateFileSysInfoBuf();
                    //BufSyncBlock(FILEINFO_START_BLOCK);
                }
                // 다음 폴더 연결되어 있으면 그거 읽어서 쓰기
                else
                    BufRead(searchEntryNo = nextEntryNo, (char *)dirents);
                i = -1; // 처음부터 4개 다시 탐색
            }
        }
        curDirName = nextDirName;
        nextDirName = strtok(NULL, "/");
    }
}

int RemoveDirectory(const char *szDirName)
{
    // 현재 Fat table의 번호와 탐색중인 번호
    int curEntryNo = DATA_START_BLOCK, searchEntryNo = curEntryNo;

    // 현재 보고 있는 디렉토리 엔트리
    DirEntry dirents[NUM_OF_DIRENT_PER_BLK];
    BufRead(DATA_START_BLOCK, (char *)dirents);

    // 인자로 받은 경로를 쪼갠 뒤 순차적으로 탐색 후 폴더 제거
    char fullPath[BLOCK_SIZE];
    strcpy(fullPath, szDirName);
    char *curDirName = strtok(fullPath, "/");
    char *nextDirName = strtok(NULL, "/");
    while (curDirName != NULL)
    {
        for (int i = 0;; i++)
        {
            // 폴더를 발견했다면
            if (strcmp(curDirName, dirents[i].name) == 0)
            {
                // 마지막 폴더일 경우 제거 처리 시작
                if (nextDirName == NULL)
                {
                    // Fat table에서만 제거 (실제 데이터는 살아있을 수도!!)
                    FatRemove(dirents[i].startBlockNum, dirents[i].startBlockNum);
                    pFileSysInfo->numAllocBlocks--;
                    pFileSysInfo->numAllocFiles--;
                    pFileSysInfo->numFreeBlocks++;

                    // 디렉토리 엔트리 정보에서 제거
                    memset(dirents + i, 0, sizeof(DirEntry));
                    BufWrite(searchEntryNo, (char *)dirents);

                    // 첫번째 항목 제거될 경우 엔트리 하나 연결 끊기
                    if (i == 0)
                    {
                        FatRemove(curEntryNo, searchEntryNo);
                        pFileSysInfo->numAllocBlocks--;
                        pFileSysInfo->numFreeBlocks++;
                    }

                    // 파일시스템 업데이트
                    UpdateFileSysInfoBuf();
                    //BufSyncBlock(FILEINFO_START_BLOCK);
                }
                // 그 폴더로 들어가야 한다면 들어가기
                else
                {
                    searchEntryNo = curEntryNo = dirents[i].startBlockNum;
                    BufRead(searchEntryNo, (char *)dirents);
                    break;
                }
            }
            // 현재 서칭 폴더 명이 없을 경우 실패
            else if (strlen(dirents[i].name) == 0)
                return -1;

            // 마지막 엔트리까지 봤을 경우 현재 폴더 다음 블럭 서칭 (다음 블럭이 있을 경우만)
            if (i == NUM_OF_DIRENT_PER_BLK - 1)
            {
                // 다음 폴더 연결된 것이 없을 경우 실패!
                int nextEntryNo = GetNextEntryNo(searchEntryNo);
                if (nextEntryNo == -1)
                    return -1;
                // 다음 폴더 연결되어 있으면 그거 읽어서 쓰기
                else
                    BufRead(searchEntryNo = nextEntryNo, (char *)dirents);
                i = -1; // 처음부터 4개 다시 탐색
            }
        }
        curDirName = nextDirName;
        nextDirName = strtok(NULL, "/");
    }
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
    pFileSysInfo->blocks = 3;
    pFileSysInfo->rootFatEntryNum = DATA_START_BLOCK;
    pFileSysInfo->diskCapacity = FS_DISK_CAPACITY;
    pFileSysInfo->numAllocBlocks = 1;
    pFileSysInfo->numFreeBlocks = FS_DISK_CAPACITY / BLOCK_SIZE - DATA_START_BLOCK;
    pFileSysInfo->numAllocFiles = 1;
    pFileSysInfo->fatTableStart = FAT_START_BLOCK;
    pFileSysInfo->dataStart = DATA_START_BLOCK;

    UpdateFileSysInfoBuf();
    BufSyncBlock(FILEINFO_START_BLOCK);
}

void Mount(void)
{
    pFileTable = (FileTable *)calloc(sizeof(FileTable), 1);
    pFileDescTable = (FileDescTable *)calloc(sizeof(FileDescTable), 1);
    pFileSysInfo = (FileSysInfo *)calloc(sizeof(FileSysInfo), 1);

    char fsiBuf[BLOCK_SIZE] = {
        0,
    };
    BufRead(FILEINFO_START_BLOCK, fsiBuf);
    memcpy(pFileSysInfo, fsiBuf, sizeof(FileSysInfo));
}

void Unmount(void)
{
    BufSync();
    free(pFileTable);
    free(pFileDescTable);
    free(pFileSysInfo);
}

Directory *OpenDirectory(char *szDirName)
{
    // 현재 Fat table의 번호
    int searchEntryNo = DATA_START_BLOCK;

    // 현재 보고 있는 디렉토리 엔트리
    DirEntry dirents[NUM_OF_DIRENT_PER_BLK];
    BufRead(DATA_START_BLOCK, (char *)dirents);

    // 인자로 받은 경로를 쪼갠 뒤 순차적으로 탐색
    char fullPath[BLOCK_SIZE];
    strcpy(fullPath, szDirName);
    char *curDirName = strtok(fullPath, "/");
    char *nextDirName = strtok(NULL, "/");
    while (curDirName != NULL)
    {
        for (int i = 0;; i++)
        {
            // 폴더를 찾았을 경우
            if (strcmp(curDirName, dirents[i].name) == 0 && dirents[i].filetype == FILE_TYPE_DIR)
            {
                searchEntryNo = dirents[i].startBlockNum;
                BufRead(searchEntryNo, (char *)dirents);

                // 마지막 폴더이면
                if (nextDirName == NULL)
                {
                    Directory *dir = (Directory *)malloc(sizeof(Directory));
                    dir->dirBlkNum = dirents[0].startBlockNum;
                    dir->entryIndex = strcmp(dirents[1].name, "..") == 0 ? 2 : 1;
                    return dir;
                }
                break;
            }
            // 현재 서칭 폴더 명이 없을 경우 존재하지 않는 폴더이므로 실패
            else if (strlen(dirents[i].name) == 0)
                return NULL;

            // 마지막 엔트리까지 봤을 경우 현재 폴더 다음 블럭 서칭 (다음 블럭이 있을 경우만)
            if (i == NUM_OF_DIRENT_PER_BLK - 1)
            {
                // 다음 폴더 연결된 것이 없을 경우 새로 만들고 연결시키기!
                int nextEntryNo = GetNextEntryNo(searchEntryNo);
                if (nextEntryNo == -1)
                    return NULL;
                // 다음 폴더 연결되어 있으면 그거 읽어서 쓰기
                else
                    BufRead(searchEntryNo = nextEntryNo, (char *)dirents);
                i = -1; // 처음부터 4개 다시 탐색
            }
        }
        curDirName = nextDirName;
        nextDirName = strtok(NULL, "/");
    }
}

FileInfo *ReadDirectory(Directory *pDir)
{
    if (pDir->dirBlkNum <= 0)
        return NULL;

    // 인자에 대한 블럭 읽기
    DirEntry dirents[NUM_OF_DIRENT_PER_BLK];
    BufRead(pDir->dirBlkNum, (char *)dirents);

    // 읽을 곳이 뭐가 없을 경우 리턴
    if (strlen(dirents[pDir->entryIndex].name) == 0)
        return NULL;

    // 리턴할 파일 정보 만들기
    FileInfo *fi = (FileInfo *)malloc(sizeof(FileInfo));
    strcpy(fi->name, dirents[pDir->entryIndex].name);
    fi->mode = dirents[pDir->entryIndex].mode;
    fi->startFatEntry = dirents[pDir->entryIndex].startBlockNum;
    fi->filetype = dirents[pDir->entryIndex].filetype;
    fi->numBlocks = dirents[pDir->entryIndex].numBlocks;

    // pDir 인덱스 업데이트 하는데 다음 블록 가르켜야하면 가르킴
    if (++(pDir->entryIndex) >= NUM_OF_DIRENT_PER_BLK)
    {
        pDir->dirBlkNum = GetNextEntryNo(pDir->dirBlkNum);
        pDir->entryIndex = 0;
    }

    return fi;
}

int CloseDirectory(Directory *pDir)
{
    free(pDir);
    return 0;
}