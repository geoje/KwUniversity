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
int GetNextEntryNo(int fatEntryNo)
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
            if (strcmp(curDirName, dirents[i].name) == 0)
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
                BufWrite(newEntryNo, (char *)dirents);

                // 상위 디렉토리 작성
                strcpy(dirents[1].name, "..");
                dirents[1].mode = curDirMode;
                dirents[1].startBlockNum = curEntryNo;
                dirents[1].filetype = FILE_TYPE_DIR;
                dirents[1].numBlocks = 1;
                BufWrite(newEntryNo, (char *)dirents);

                // 파일 시스템 정보 업데이트
                fsi->numAllocBlocks++;
                fsi->numFreeBlocks--;
                fsi->numAllocFiles++;
                BufWrite(FILEINFO_START_BLOCK, (char *)fsi);
                BufSyncBlock(FILEINFO_START_BLOCK);

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
                    fsi->numAllocBlocks++;
                    fsi->numFreeBlocks--;
                    BufWrite(FILEINFO_START_BLOCK, (char *)fsi);
                    BufSyncBlock(FILEINFO_START_BLOCK);
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
    // 파일 시스템 정보 읽기
    FileSysInfo *fsi = malloc(BLOCK_SIZE);
    BufRead(FILEINFO_START_BLOCK, (char *)fsi);

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
                    fsi->numAllocBlocks--;
                    fsi->numAllocFiles--;
                    fsi->numFreeBlocks++;

                    // 디렉토리 엔트리 정보에서 제거
                    memset(dirents + i, 0, sizeof(DirEntry));
                    BufWrite(searchEntryNo, (char *)dirents);

                    // 첫번째 항목 제거될 경우 엔트리 하나 연결 끊기
                    if (i == 0)
                    {
                        FatRemove(curEntryNo, searchEntryNo);
                        fsi->numAllocBlocks--;
                        fsi->numFreeBlocks++;
                    }

                    // 파일시스템 업데이트
                    BufWrite(FILEINFO_START_BLOCK, (char *)fsi);
                    BufSyncBlock(FILEINFO_START_BLOCK);
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
            if (strcmp(curDirName, dirents[i].name) == 0)
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
}