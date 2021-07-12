#include "MySem.h"
#include "MyShm.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>

int shmid = 0; //공유 메모리의 id
int *shmaddr = NULL; //공유 메모리의 데이터 접근 주소

int semidServ = 0; //서버의 세마포어 id
int semidClnt = 0; //클라이언트의 세마포어 id

void signalHandler(int signum) { //시그널 신호가 들어왔을 때
	if (signum != SIGINT) return; //시그널이 인터럽트일 때만 기능 수행
	shmdt(shmaddr); //공유 메모리를 프로세스에서 분리
	exit(0); //프로그램 종료
}

int main(int argc, char const *argv[]) {
	char buf[SHM_MAX_SIZE]; //공유 메모리를 통해 읽은 데이터를 담아둘 버퍼

	shmid = openShm(MY_SHM_KEY); //서버가 생성했을 공유 메모리에 대한 id 가져오기
	shmaddr = shmat(shmid, NULL, 0); //공유 메모리의 주소를 공유 메모리의 id를 통해 받아옴

	semidServ = openSem(MY_SEM_SERV_KEY); //서버가 생성했을 서버에 대한 세마포어 id 가져오기
	semidClnt = openSem(MY_SEM_CLNT_KEY); //서버가 생성했을 클라이언트에 대한 세마포어 id 가져오기

	signal(SIGINT, signalHandler); //인터럽트 시그널 오면 signalHandler 함수 실행

	while(1) { //메세제 계속 보내기 위해 무한루프
		printf("송신할 메세지를 적어주세요.(bye to quit): "); //메세지 입력하라는 문구
		fflush(stdout); //문구 출력 안될까봐 플러쉬
		buf[read(0, buf, SHM_MAX_SIZE) - 1] = '\0'; //scanf 하면 공백 안받아지고 fgets 쓰자니 시스템 함수 쓰고싶어서 read사용 또한 마지막은 문자열 종결 '\0' 표시
		if (!strcmp(buf, "bye")) break; //메세지로 "bye"입력 될 경우 무한 루프 종료

		lockSem(semidClnt); //내 세마포어를 잠그고 서버가 풀어줄 때 까지 대기
		memcpy(shmaddr, buf, SHM_MAX_SIZE); //내 세마포어가 풀리면 공유 메모리에 메세지 저장
		unlockSem(semidServ); //서버가 클라이언트에서 보낸 메세지를 읽을 수 있게 서버 세마포어 풀기
	}
	return 0;
}
