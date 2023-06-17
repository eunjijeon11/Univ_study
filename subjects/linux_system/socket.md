# Linux System: Socket Programming
2022312132 전은지


# 1.클라이언트와 서버에 대한 조사
코딩을 하기 전 소켓 프로그래밍에 대한 자료 조사를 진행했습니다.  

**1)	클라이언트 소켓 프로세스**  
클라이언트 소켓은 create – connect – send/recv – close 순서의 흐름을 가집니다. 처음에 소켓을 생성(create) 하고 서버 측에 연결(connect) 하면 데이터를 송수신(send/recv) 할 수 있습니다. 모든 과정이 끝나면 소켓을 닫습니다(close).  

**2)	서버 소켓 프로세스**  
서버 소켓에서는 create – bind – listen – accept – send/recv – close 순서의 흐름을 가집니다. 소켓을 생성(create) 하고, 서버가 사용할 IP 주소와 포트 번호를 생성한 소켓에 결합(bind) 시킵니다. 클라이언트로부터의 요청을 듣고(listen) 수신된 요청을 받아들여(accept) 데이터 통신을 위한 소켓을 생성합니다. 그럼 클라이언트와 마찬가지로 데이터를 송수신(send/recv) 할 수 있습니다. 모든 과정이 끝나면 소켓을 닫습니다(close).  

---

# 2. 필요한 함수 / 구조체
소켓 프로그래밍은 처음 해보는 것이기 때문에 소켓을 생성하고 실행하는 데에 있어 모르는 함수와 헤더파일을 많이 사용해야 했습니다. 때문에 이러한 함수/구조체를 이해하는 것부터 시작하였습니다.

**1) `socket(int domain, int type, int protocol)`**  
소켓을 생성하는 함수입니다. `<sys/socket.h>` 헤더파일에 있습니다. 인자인 `domain`은 어떤 영역에서 통신할 것인지 지정하는 것이로, 프로세스끼리 통신할 때 사용하는 `AF_UNIX`, IPv4의 `AF_INET`, IPv6의 `AF_INET6`가 들어갈 수 있습니다. `type`은 어떤 서비스 타입의 소켓을 생성할 것인지 적는 것으로, TCP를 사용할 때 `SOCK_STREAM`을, UDP를 사용할 때 `SOCK_DGRAM`을 쓸 수 있습니다. `protocol`은 소켓에서 사용하 프로토콜을 지정하는 것으로 type에서 이미 방식이 정해져있다면 0을 입력합니다.

함수의 리턴값은 int로 -1일 때는 소켓 실패를 의미하고 0이상의 값일 때는 소켓 디스크립터 값을 가집니다.

**2) `bind(int sockfd, struct sockaddr *myaddr, socklen_t addrlen)`**  
소켓과 서버의 정보를 묶어주는 함수로 서버에서 사용합니다. <sys/socket.h> 헤더파일이 필요합니다. `sockfd`에서 fd는 파일디스크립터의 약자로 소켓디스크립터를 넣어주면 됩니다. `myaddr`에는 서버의 IP주소를 넣습니다. `addrlen`에는 주소의 길이를 넣습니다.
bind를 성공했을 때 0, 실패했을 때 -1을 리턴합니다.

**3) `connect(int sockfd, struct sockaddr* serv_addr, socklen_t addrlen)`**  
클라이언트 측에서 서버로 연결을 요청할 때 사용하는 함수입니다. <sys/socket.h> 헤더파일이 필요합니다. `sockfd`는 클라이언트의 소켓 디스크립터 값을 넣어줍니다. `serv_addr`은 서버의 주소정보이고, `addrlen`은 두 번째 인자의 크기를 넣어줍니다.
성공 시 0, 실패 시 -1을 리턴합니다. 

**4) `listen(int sockfd, int backlog)`**  
클라이언트로부터 요청이 왔을 때 수락할 수 있도록 대기하는 함수로 서버에서 사용합니다. <sys/socket.h> 헤더파일이 필요합니다. `sockfd`는 소켓디스크립터를 의미하는 인자이고, `backlog`는 연결 대기열의 크기를 지정합니다. 
성공시 0을, 실패시 -1을 리턴합니다. 

**5) `read/write(int fd, void *buf, size_t count)`**  
데이터를 송수신하는 함수들입니다. 이 함수들은 OS에서 제공하는 저수준 입출력 함수로 <unistd.h> 헤더파일이 필요합니다. 클라이언트에서 `read()`를 사용할 때는 `fd`를 `socket()` 함수를 통해 생성된 소켓 디스크립터를 사용하면 되고, 서버에서 사용할 때는 `accept()` 함수로 생성된 소켓 디스크립터를 사용하면 됩니다. `write()`에서는 `fd`가 연결된 소켓의 디스크립터 번호입니다. `buf`는 읽어들인 데이터가 저장될, 또는 보낼 데이터가 저장될 버퍼의 주소입니다. `count`는 buf에 저장될 데이터의 크기를 넣습니다.

**6) `accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen)`**  
서버 소켓과 클라이언트를 연결하는 함수입니다. <sys/socket.h> 헤더파일이 필요합니다. `sockfd`는 서버 소켓 디스크립터를 넣어주고, `*addr`은 클라이언트의 정보를 담고 있는 구조체입니다. `*addrlen`은 클라이언트의 주소 정보를 가지고 있는 구조체의 크기입니다.
성공 시 소켓 디스크립터 번호를, 실패 시 -1을 리턴합니다. 

**7) `close(int sockfd)`**  
해당 소켓을 닫는 함수입니다.

**8) `sockaddr` 관련 구조체**  
sockaddr 구조체는 소켓의 주소를 담는 기본 구조체 역할을 합니다.
```c
struct sockaddr {
	u_short    sa_family;     // address family, 2 bytes
	char    sa_data[14];     // IP address + Port number, 14 bytes
};
```
`sa_family`는 주소체계를 구분하기 위한 변수이고, `sa_data`는 IP 주소와 포트넘버를 저장하는 변수입니다.

`sockaddr` 구조체는 주소체계에 따른 여러 구조체들과 함께 사용할 수 있습니다. 함수의 인자로 `sockaddr` 대신에 `sockaddr_in` 구조체를 전달해도 괜찮습니다. `sockaddr`을 그대로 사용하면 IP주소와 포트넘버가 조합되어 있어서 불편하기 때문에 다른 구조체를 사용합니다.

|struct name|family|IP struct|
|:---:|:---:|:---:|
|`sockaddr_in`|AF_INET|`in_addr`|
|`sockaddr_in6`|AF_INET6|`in6_addr`|
|`sockaddr_un`|AF_UNIX / AF_LOCAL| - |

이 중 이번 과제에서 사용할 `sockaddr_in`에 대해 더 자세히 알아보았습니다.
```c
struct sockaddr_in {
	short    sin_family;          // AF_INET
	u_short  sin_port;            // 포트 번호
	struct   in_addr  sin_addr;   // IP 주소
	char     sin_zero[8];         // 전체 크기를 16 비트로 맞추기 위한 dummy data
};

struct  in_addr {
	u_long  s_addr;     // 32비트 IP 주소를 저장 할 구조체
};
```

여기에서 `sin_zero`는 8바이트의 0으로 채워져있는 더미 데이터입니다. `sin_family` + `sin_port` + `sin_addr` 이 8바이트인데, 여기에 `sin_zero`를 더해 16바이트로 만들어 sockaddr 구조체와 크기를 맞출 수 있습니다.

---

# 3. 실제 구현

server 측 코드
```c
#include<stdio.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<unistd.h>
#include<string.h>

void error_handling(char* msg) {
	printf("ERROR: %s\n", msg);
	exit(1);
}

int main(int argc, char* argv[])
{
    int serv_sock;
    int clint_sock;

    struct sockaddr_in serv_addr;
    struct sockaddr_in clint_addr;
    socklen_t clnt_addr_size;

    serv_sock = socket(PF_INET, SOCK_STREAM,0);
    if(serv_sock == -1) error_handling("socket failed");
    
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));

    if(bind(serv_sock,(struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1) error_handling("bind failed");
    if(listen(serv_sock,5)==-1) error_handling("listen error");
    
    clnt_addr_size = sizeof(clint_addr);
    clint_sock = accept(serv_sock,(struct sockaddr*)&clint_addr,&clnt_addr_size);
    if(clint_sock == -1) error_handling("accept failed");

    char message[] = "Hello";
    write(clint_sock, message, sizeof(message));

		char receive[1024];
		read(clint_sock, receive, 1024);
		printf("message from client: %s\n", receive);

    close(serv_sock);
    close(clint_sock);
    return 0;
}
```

클라이언트 측 코드
```c
#include<stdio.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<unistd.h>
#include<string.h>

void error_handling(char* msg) {
	printf("ERROR: %s\n", msg);
	exit(1);
}

int main(int argc, char* argv[])
{
    int my_sock;
    struct sockaddr_in serv_addr;
    int str_len;
    
    my_sock = socket(PF_INET,SOCK_STREAM,0);
    if(my_sock == -1) error_handling("socket failed");

    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr=inet_addr(argv[1]);
    serv_addr.sin_port=htons(atoi(argv[2]));

    if(connect(my_sock,(struct sockaddr*)&serv_addr,sizeof(serv_addr))==-1) error_handling("connect failed");

    char receive[15];
    str_len = read(my_sock,receive,sizeof(receive)-1);
    if(str_len==-1) error_handling("read failed");

    printf("message from server: %s \n", receive);

		char message[] = "Hello";
		write(my_sock, message, sizeof(message));

    close(my_sock);
    return 0;
}
```

---
# 4. 실행화면
![server](https://user-images.githubusercontent.com/61264183/236246493-b8973de7-68ea-48fc-aaaa-1dcb5a6d1962.png)
![client](https://user-images.githubusercontent.com/61264183/236246555-6b13e482-0165-4d6b-a239-f05c335db9d7.png)