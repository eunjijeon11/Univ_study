# 리눅스 텀 프로젝트: 커널레벨 소켓 프로그래밍

## 1. 사전조사 진행

- kernel level과 user level의 차이

  - kernel level에서는 직접 시스템 리소스에 접근할 수 있음
  - user level에서의 구현은 kernel level과의 상호작용을 포함함. 따라서 kernel level에서의 구현이 상대적으로 더 빠름.
  - 운영체제 커널 내에서 실행되므로 시스템 리소스에 대한 접근 권한을 제어할 수 있음 => 보안상 좋음
  - kernel level에서의 구현은 특정 운영체제나 하드웨어 아키텍처에 종속적임

- system call 구현과정

  - 시스템 콜 함수 구현
  - 시스템 콜의 Makefile에 등록 (kernel/Makefile)
  - 시스템 콜 테이블에 등록 (arch/x86/entry/syscalls)
  - 시스템 콜 헤더파일에 틍록 (include/linux/syscalls.h)
  - 커널 컴파일&재부팅

- user level 구현

  - 만든 systeml call을 user level에서 사용하는 코드
  - 여러가지 추가기능 제공

- WSL 커널 오픈소스

  - 리눅스 커널 오픈소스와 구조 비슷함
  - include/linux 디렉터리에 헤더파일 위치

- 추가기능

  - 채팅방 기능 (채팅 내용 저장, 불러오기)
  - 이미지, 동영상 스트리밍
  - 채팅방에 상대가 들어왔는지 아닌지 보여줌 (상대가 없으면 메세지를 보낼 수 없음)

- 참고자료

  - https://youtu.be/f3g1f2tTNDM 패킷단위 네트워트 처리설명

---

## 2. 시스템 콜 함수 구현

- 시스템 콜 함수로는 간단한 소켓 통신 과정만 구현한다.

- asmlinkage: 어셈블리 코드에서 직접 링크할 수 있는 함수라는 의미. 호출규약이 필요하여 함수의 인자를 레지스터나 스택에 담아 전달한다.

- include error 원인: 커널소스의 include 파일이 아니라 지금 사용하고 있는 리눅스 루트의 usr/include 파일 안에 있는 헤더파일들을 사용중이었다!!!!!!!! 이걸고치자
  => 해결 https://stackoverflow.com/questions/10176238/how-do-i-add-an-include-path-for-kernel-module-makefile

- system call compile에서 문제

  - 모두 다 \_\_x64\_ 붙이기 => **x64\_**x64_sys 가 없다고 나옴.. 이게 뭔가
  - tbl 파일에만 붙이기 => 1번과 동일
  - tbl 파일에만 안붙이기 => 타입오류 (syscall_64.c:10)
  - 타입을 맞게 고치면? => 성공 => 궤변인가?
  - http://egloos.zum.com/rousalome/v/9995340
  - read 시스템 콜을 뜯어서 따라함 => 성공

- 커널 컴파일이 오래걸리는 문제
  - 커널 모듈로 소켓을 구현하여 해결

---

## 3. 커널 모듈로 작동하는 소켓 코드 만들기

- listen 함수 : backlog https://velog.io/@techy-yunong/socket-programming-listen-API-backlog
- kthread: 멀티스레드로 실시간 채팅 기능
- accept 함수: 4.11 부터 바뀜 https://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git/commit/?id=cdfbabfb2f0ce983fdaa42f20e5f7842178fc01e

```c
#include<stdio.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<unistd.h>
#include<string.h>
#include<pthread.h>

void error_handling(char* msg) {
	printf("ERROR: %s\n", msg);
	exit(1);
}

struct sockInfo {
	int sockfd;
	struct sockaddr_in serv_addr;
};

int thr;

struct sockInfo* connectServer(char *addr, char *PORT) {
  	struct sockInfo *sock = (struct sockInfo*)malloc(sizeof(struct sockInfo));

  	sock->sockfd = socket(PF_INET,SOCK_STREAM,0);
  	if(sock->sockfd == -1) error_handling("socket failed");

  	memset(&sock->serv_addr,0,sizeof(sock->serv_addr));
  	sock->serv_addr.sin_family = AF_INET;
  	sock->serv_addr.sin_addr.s_addr=inet_addr(addr);
  	sock->serv_addr.sin_port=htons(atoi(PORT));

  	if(connect(sock->sockfd,(struct sockaddr*)&sock->serv_addr,sizeof(sock->serv_addr))==0) {
		printf("서버와 연결되었습니다.\n");
		return sock;
	} else {
		printf("서버와 연결할 수 없습니다.\n");
		return NULL;
	}
}

int login(struct sockInfo *sock) {
	char username[10];
	printf("이름을 입력하세요\n");
	scanf("%s", username);
	int res = write(sock->sockfd, username, sizeof(username));

	char password[10];
	printf("비밀번호를 입력하세요\n");
	scanf("%s", password);
	int res2 = write(sock->sockfd, password, sizeof(password));

	char loginResult[20];
	int result = read(sock->sockfd, loginResult, sizeof(loginResult));

	if (res > -1 && res2 > -1) {
		printf("메세지를 성공적으로 전송하였습니다. %d\n", res);
	} else {
		printf("메세지 전송에 실패하였습니다.\n");
	}
  	return 0;
}

int recvResult(struct sockInfo *sock) {
	char result[100];
	int len = read(sock->sockfd, result, sizeof(result));
	printf("%s\n", result);
	return 0;
}

void *print_f(void *data) {
	struct sockInfo *sock = (struct sockInfo *)data;

	printf("==========chat starts=========\n");
	int result = 0;

	char res[100];
	while(thr) {
		result = read(sock->sockfd, res, sizeof(res));
		if (result > 0) printf("%s\n", res);
	}
	pthread_exit((void *)0);
}

int main(int argc, char *argv[]) {
	char input[100];
	int process = 1;
	struct sockInfo *sock;

	pthread_t threads[2];

	while(process) {
		printf(">> ");
		scanf("%s", input);
		switch(input[0]) {
			case 'c':
				sock = connectServer(argv[1], argv[2]);
				recvResult(sock);
				login(sock);
				break;
			case 'p':
				thr = 1;
				//pthread_create(&threads[0], (void *)sock, &print_f, "print");

				while(thr) {
					scanf("%s", input);
					send(sock->sockfd, input, sizeof(input), 0);
					if (input[0] == 'Q') thr = 0;
				}

				//pthread_cancel(threads[0]);

				break;
			case 'q':
				if (sock != NULL) close(sock->sockfd);
				process = 0;
				break;
		}
	}
	return 0;
}
```
