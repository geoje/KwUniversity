#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	FILE *fs1, *fs2;
	struct stat filestat;
	int nRet = 0;

	if ((fs1 = fopen(argv[1], "rb")) != NULL) {
		unsigned char *pFile;

		fstat(fileno(fs1), &filestat);
		pFile = (unsigned char*)malloc(filestat.st_size);
		memset(pFile, 0x00, filestat.st_size);
		nRet = fread(pFile, 1, filestat.st_size, fs1);
		fclose(fs1);

		if((fs2 = fopen("CopyTestFile", "wb")) != NULL) {
			nRet = fwrite((void*)pFile, filestat.st_size, 1, fs2);
			fclose(fs2);
		}
		free(pFile);
	}
	return 0;
}
