#include <stdio.h>
#include <stdlib.h>
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

int MakeDirectory(const char *szDirName, AccessMode mode)
{
}

int RemoveDirectory(const char *szDirName)
{
}

void Format(void)
{
    FatAdd(-1, DATA_START_BLOCK); // p9 과정

    // 루트 디렉토리 생성
    DirEntry dirents[NUM_OF_DIRENT_PER_BLK];
    strcpy(dirents[0].name, ".");
    dirents[0].mode = ACCESS_MODE_READWRITE;
    dirents[0].startBlockNum = DATA_START_BLOCK;
    dirents[0].filetype = FILE_TYPE_DIR;
    dirents[0].numBlocks = 1;
    BufWrite(DATA_START_BLOCK, dirents);

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
