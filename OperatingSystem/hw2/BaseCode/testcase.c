#include <stdio.h>
#include <string.h>

#include "buf.h"
#include "Disk.h"

#define BUF_SIZE	(BLOCK_SIZE)

void PrintBufInfo();
void PrintDiskInfo(int start_blk, int end_blk);
void PrintDiskAccessCountInfo();

int testcase1(){
	int  i;
	char pData[BUF_SIZE];
	Buf* pBuf;

	DevResetDiskAccessCount();

	for( i = 0; i < 16; i++ ){

		sprintf(pData, "[block %d]", i);
		BufWrite(i, pData);
	}

	PrintBufInfo();

	{
		sprintf(pData, "[block %d]", 16);
		BufWrite(16, pData);
		sprintf(pData, "[block %d]", 17);
		BufWrite(17, pData);
	}

 
	for( i = 16; i < 32; i++ ) {
		
		sprintf(pData, "[block %d]", i);
		BufWrite(i, pData);
	}

	PrintBufInfo();

	printf("========= BufSync() =========\n" );
	
	for (i = 0;i < 32;i++) {
		if ((pBuf = BufGet(i)) != NULL && (pBuf->state == BUF_STATE_DIRTY)) 
			BufSyncBlock(i);	 

 	}

	PrintBufInfo();
	PrintDiskInfo(0, 31);

	PrintDiskAccessCountInfo(); //modified

	return 1;
}

int testcase2(){
    	int  i;
	char pData[BUF_SIZE];
	Buf* pBuf = NULL;

	DevResetDiskAccessCount();
	for( i = 0; i < MAX_BUF_NUM/2; i++ ){

		BufRead(i, pData);
		printf("read[%d]:%s ", i, (char *)pData);
		if ((pBuf = BufGet(i)) == NULL || pBuf->state == BUF_STATE_DIRTY) 
   			printf("testcase2: failed\n");
	}
	printf( "\n----------------------------------\n" );

	PrintBufInfo();

	for( i = MAX_BUF_NUM/2; i < MAX_BUF_NUM; i++ ){

		BufRead(i, pData);
		printf("read[%d]:%s ", i, (char *)pData);
		if ((pBuf = BufGet(i)) == NULL)
			printf("testcase2: failed\n");

	}
	printf( "\n----------------------------------\n" );

	PrintBufInfo();

	PrintDiskAccessCountInfo();

	return 1;
}

int testcase3(){
	int  i;
	char pData[BUF_SIZE];
	Buf* pBuf = NULL;

	DevResetDiskAccessCount();

	for( i = 16; i < 16 + MAX_BUF_NUM; i++ ){

		BufRead(i,pData);
		printf("read[%d]:%s ", i, (char *)pData);

		sprintf(pData, "[block %d]", i + 100);
		BufWrite(i,pData);
		if ((pBuf = BufGet(i)) != NULL && i % 2 == 0)
			BufSyncBlock(i);
	}
	printf( "\n----------------------------------\n" );

	printf("========= BufSync() =========\n" );
	BufSync();

	PrintBufInfo();
	PrintDiskInfo(0, 31);

	for( i = 32; i < 32 + MAX_BUF_NUM; i++ ){

		sprintf(pData, "[block %d]", i + 100);
		BufWrite(i,pData);
	}
	printf("========= BufSync() =========\n" );
	BufSync();

	PrintBufInfo();
	PrintDiskInfo(0, 47);
	
	PrintDiskAccessCountInfo();//modified

    return 1;
}

int main()
{
    BufInit();

	if ( testcase1() == 1 )
		printf("\n testcase 1 complete. \n\n");
	else
		goto out;	

	if ( testcase2() == 1 )
		printf("\n testcase 2 complete. \n\n");
	else
		goto out;	

	if ( testcase3() == 1 )
		printf("\n testcase 3 complete. \n\n");
	else
		goto out;

out:

    return 0;
}

void PrintBufInfo()
{
	int		i, j, numBuf = 0;
	Buf*	ppBufInfo[MAX_BUF_NUM];


        memset( ppBufInfo, 0, (MAX_BUF_NUM * sizeof(Buf*)) );
        for (i = 0 ; i < HASH_ENTRY_NUM;i++) {
 		GetBufInfoInBufferList(i, ppBufInfo, &numBuf );

        	printf( "Hash entry num:%d, Num of Bufs in the buffer list : %d\n", i, numBuf );
    		for( j = 0; j < numBuf; j++ ){
                	printf( "Buf[%d,", ppBufInfo[j]->blkno );
                	if ( ppBufInfo[j]->state == BUF_STATE_CLEAN )
                	{
                        	printf( "C, " );
                	}
                	else if ( ppBufInfo[j]->state ==  BUF_STATE_DIRTY )
                	{
                        	printf( "D, " );
                	}
                	else {
                        	printf( "I, " );
               	}
    		}
	}

	printf( "\n----------------------------------\n" );


	memset( ppBufInfo, 0, (MAX_BUF_NUM * sizeof(Buf*)) );
	GetBufInfoByListNum( BUF_LIST_DIRTY, ppBufInfo, &numBuf );

	printf( "Num of Bufs in the BUF_LIST_DIRTY : %d\n", numBuf );
	for( i = 0; i < numBuf; i++ ){
		printf( "Buf[%d,", ppBufInfo[i]->blkno );
		if ( ppBufInfo[i]->state == BUF_STATE_CLEAN )
		{
			printf( "C, " );
		}
		else if ( ppBufInfo[i]->state ==  BUF_STATE_DIRTY )
		{
			printf( "D, " );
		}
		else {
			printf( "I, " );
		}
		printf( "%s], ", (char*)ppBufInfo[i]->pMem );
	}

 	printf( "\n----------------------------------\n" );


	memset( ppBufInfo, 0, (MAX_BUF_NUM * sizeof(Buf*)) );
	GetBufInfoByListNum( BUF_LIST_CLEAN, ppBufInfo, &numBuf );

	printf( "Num of Bufs in the BUF_LIST_CLEAN : %d\n", numBuf );
	for( i = 0; i < numBuf; i++ ){
		printf( "Buf[%d,", ppBufInfo[i]->blkno );
		if ( ppBufInfo[i]->state == BUF_STATE_CLEAN )
		{
			printf( "C, " );
		}
		else if ( ppBufInfo[i]->state ==  BUF_STATE_DIRTY )
		{
			printf( "D, " );
		}
		else {
			printf( "I, " );
		}
		printf( "%s], ", (char*)ppBufInfo[i]->pMem );
	}


	printf( "\n----------------------------------\n" );

	memset( ppBufInfo, 0, (MAX_BUF_NUM * sizeof(Buf*)) );
	GetBufInfoInLruList( ppBufInfo, &numBuf );

	printf( "Num of Bufs in the LRU list : %d\n", numBuf );
	for( i = 0; i < numBuf; i++ ){
		printf( "Buf[%d,", ppBufInfo[i]->blkno );
		if ( ppBufInfo[i]->state == BUF_STATE_CLEAN )
		{
			printf( "C], " );
		}
		else if ( ppBufInfo[i]->state ==  BUF_STATE_DIRTY )
		{
			printf( "D], " );
		}
		else {
			printf( "I], " );
		}
	}

	printf( "\n----------------------------------\n" );

}

void PrintDiskInfo(int start_blk, int end_blk)
{
	int i;
	char buf[BUF_SIZE];

	printf( "Disk block Info\n" );
	for ( i = start_blk; i <= end_blk; i++)
	{
		DevReadBlock( i, buf );
		printf("%d : %s ", i, buf);
	}
	printf( "\n----------------------------------\n" );
}

void PrintDiskAccessCountInfo() //modified
{
	printf("---------- Informaion of Disk Access Count ---------- \n");
	printf("Disk Read Count : %d\n",DevGetDiskReadCount());
	printf("Disk Write Count : %d\n",DevGetDiskWriteCount());
	printf("Disk Read Count + Disk Write Count : %d\n",DevGetDiskReadCount() + DevGetDiskWriteCount());
	printf("----------------------------------------------------- \n");	
}
