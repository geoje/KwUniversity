#include <stdio.h>

#define BUFSIZE 128

int main() {
	FILE *fpin, *fpout;
	char line[BUFSIZE];

	fpin = popen("who", "r");
	fpout = popen("sort", "w");

	while (fgets(line, BUFSIZE, fpin) != (char*)NULL)
	fputs(line, fpout);

	pclose(fpin);
	pclose(fpout);
}
