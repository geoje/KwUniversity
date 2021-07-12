#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <pwd.h>
#include <grp.h>

int main(int argc, char **argv) {
	int return_stat;
	char *file_name;
	struct stat file_info;

	struct passwd *my_passwd;
	struct group  *my_group;

	mode_t file_mode;
	if (argc != 2) {
		printf("Usage: ./%s [file name]\n", argv[0]);
		exit(0);
	}
	file_name = argv[1];

	if ((return_stat = stat(file_name, &file_info)) == -1) {
		perror("Error: ");
		exit(0);
	}
	file_mode = file_info.st_mode;
	printf("파일 이름: %s\n", file_name);

	printf("파일 타입: ");
	if (S_ISREG(file_mode))		printf("정규파일\n");
	else if (S_ISLNK(file_mode))	printf("심볼릭 링크\n");
	else if (S_ISDIR(file_mode))	printf("디렉토리\n");
	else if (S_ISCHR(file_mode))	printf("문자 디바이스\n");
	else if (S_ISBLK(file_mode))	printf("블럭 디바이스\n");
	else if (S_ISFIFO(file_mode))	printf("FIFO\n");
	else if (S_ISSOCK(file_mode))	printf("소켓\n");

	printf("파일 권한: ");
	if (S_ISDIR(file_mode)) 	printf("d"); else printf("-");
	if (file_mode & S_IRUSR)	printf("r"); else printf("-");
	if (file_mode & S_IWUSR)	printf("w"); else printf("-");
	if (file_mode & S_IXUSR)	printf("x"); else printf("-");
	if (file_mode & S_IRGRP)	printf("r"); else printf("-");
	if (file_mode & S_IWGRP)	printf("w"); else printf("-");
	if (file_mode & S_IXGRP)	printf("x"); else printf("-");
	if (file_mode & S_IROTH)	printf("r"); else printf("-");
	if (file_mode & S_IWOTH)	printf("w"); else printf("-");
	if (file_mode & S_IXOTH)	printf("x"); else printf("-");
	printf("\n\n");

	my_passwd = getpwuid(file_info.st_uid);
	my_group  = getgrgid(file_info.st_gid);
	printf("소유자: %s\n", my_passwd->pw_name);
	printf("그룹  : %s\n", my_group ->gr_name);
	printf("파일 크기: %d\n", (int)file_info.st_size);
	printf("마지막 읽은 시간: %d\n", (int)file_info.st_atime);
	printf("마지막 수정 시간: %d\n", (int)file_info.st_mtime);
	printf("하드링크된 파일 수: %d\n", (int)file_info.st_nlink);

	return 0;
}
