#include "MySem.h"
#include "MyShm.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/types.h>

int shmid = 0; //공유 메모리의 id
int *shmaddr = NULL; //공유 메모리의 데이터 접근 주소

int semidServ = 0; //서버의 세마포어 id
int semidClnt = 0; //클라이언트의 세마포어 id

void signalHandler(int signum) { //시그널 신호가 들어왔을 때
	if (signum != SIGINT) return; //시그널이 인터럽트일 때만 기능 수행
	closeSem(semidClnt); //서버에 대한 공유 메모리 접근 자원 반환
	closeSem(semidServ); //클라이언트에 대한 공유 메모리 접근 자원 반환

	shmdt(shmaddr); //공유 메모리를 프로세스에서 분리
	closeShm(shmid); //공유 메모리를 제거
	exit(0); //프로그램 종료
}

int main(int argc, char const *argv[]) {
	char buf[SHM_MAX_SIZE]; //공유 메모리를 통해 읽은 데이터를 담아둘 버퍼
	union semun semunBuf; //세마포어 셋팅에 대한 정보를 담아둘 공용 구조체

	shmid = creatShm(MY_SHM_KEY); //헤더파일에 선언되어 있는 상수 키 값을 사용해 공유 메모리 생성
	shmaddr = shmat(shmid, NULL, 0); //생성된 공유 메모리의 주소를 공유 메모리의 id를 통해 받아옴

	semidServ = creatSem(MY_SEM_SERV_KEY); //서버에 대한 세마포어 생성
	semunBuf.val = 0; //세마포어 초기상태는 닫힌상태(접근불가), 서버가 메세지를 받는 상태로 있어야 하니깐
	semctl(semidServ, 0, SETVAL, semunBuf); //위에서 만들어 놓은 셋팅대로 세마포어 설정

	semidClnt = creatSem(MY_SEM_CLNT_KEY); //클라이언트에 대한 세마포어 생성
	semunBuf.val = 1; //세마포어 초기상태는 열린상태(접근가능), 클라이언트가 메세지를 먼저 보내야 하니깐
	semctl(semidClnt, 0, SETVAL, semunBuf); //위에서 만들어 놓은 셋팅대로 세마포어 설정

	signal(SIGINT, signalHandler); //인터럽트 시그널 오면 signalHandler 함수 실행

	while(1) { //클라이언트한테서 계속 받아야하니깐 무한루프
		lockSem(semidServ); //처음 서버의 세마포어는 닫힌 상태로 만들고 클라이언트가 풀어줄 때 까지 대기
		memcpy(buf, shmaddr, SHM_MAX_SIZE); //클라이언트가 내 세마포어 풀어주면 그제서야 데이터에 접근
		unlockSem(semidClnt); //데이터 읽었으니깐 클라이언트가 다시 보낼 수 있게 클라이언트 세마포어 열기

		printf("Client: %s\n", buf); //읽은 메세지 출력
		fflush(stdout); //메세지가 버퍼에 남아서 출력안되면 버퍼 플러쉬 해서 출력
	}
	return 0;
}
