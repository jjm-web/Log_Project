
//
//	demonServer.c
//	Log_Control
//
//	Create by 장준명 on 2024/06/18.
//	Copyight @ 2024 장준명. All rights reserved.
//

#include "Log_Control_Header.h"

void message_log(char * data, struct receiverecord r, int fd, const char* port);
char* get_ip(void);

int main(int argc, const char * argv[]) {
    struct sockaddr_in serv_addr, clnt_addr;
    struct receiverecord r;
    int serv_fd, clnt_fd, file_fd;
    int pid = 0;
    socklen_t clnt_addr_len = sizeof(clnt_addr);

    if ((serv_fd = socket(PF_INET, SOCK_STREAM, DEFAULT_PROTOCOL)) == EOF) { // 서버측 소켓 열기
        printf("\n소켓 생성 에러\n");
        exit(0);
    }

    // 소켓 주소 설정
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));

    if (bind(serv_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == EOF) { // 바인딩
        printf("\n바인딩 에러\n");
        exit(0);
    }
	

    // writelog.txt 파일을 쓰기 모드로 열기
    file_fd = open("writelog.txt", O_WRONLY | O_CREAT | O_APPEND, 0644);
    message_log("서버 오픈", r, file_fd, argv[1]); // 서버 열릴 시 메시지 전송
    listen(serv_fd, 3);

    pid = fork(); // 자식 프로세스 생성
    
    if (pid == 0) {
        while (1) {
            if ((clnt_fd = accept(serv_fd, (struct sockaddr *)&clnt_addr, &clnt_addr_len)) == EOF) { // 클라이언트 접속 허용
                printf("\n엑셉트 에러\n");
                exit(0);
            }
            if (fork() == 0) { // 자식 프로세스의 자식 프로세스 사용
                while (1) {
			read(clnt_fd, &r, sizeof(r)); //클라이언트 메세지를 버퍼에 저장
			if (strncmp(r.message, "Exit", 4) == 0 || strncmp(r.message, "Quit", 4) == 0) { // Exit 또는 Quit 입력 시 클라이언트 종료
                        	close(clnt_fd);
                        	exit(0);
                    	}
			write(file_fd, &r, sizeof(r)); //버퍼 저장된 메세지 파일에 쓰기      
                }
            }
        }
    }
    close(serv_fd); // 부모 프로세스는 바로 종료, 서버는 백그라운드에서 계속 돌아감
    return 0;
}

void message_log(char * data, struct receiverecord r, int fd, const char* port) {
	sprintf(r.message, "%s %s %s", data, get_ip(), port);
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);

    	snprintf(r.datetime, sizeof(r.datetime),"%04d/%02d/%02d %02d:%02d:%02d", tm.tm_year+1900, tm.tm_mon+1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
    	write(fd, &r, sizeof(r));
} // 메세지 전송 함수, 클라이언트에서 입력받은 메세지를 서버에서 sprint 적힌 형태로 받아 적는 구문.

char* get_ip(void) {
    char host_name[80];
    struct hostent *host_entry;

    if (0 != gethostname(host_name, sizeof(host_name))) {
        printf("gethostname() 실행 실패(server1)\n");
        exit(1);
    }
    printf("%s \n", host_name);
    host_entry = gethostbyname(host_name);
    
    if (!host_entry) {
        printf("gethostbyname() 실행 실패(server2)\n");
        exit(1);
    }

    if (host_entry->h_addr_list[0]) {
        
        return inet_ntoa(*(struct in_addr*)host_entry->h_addr_list[0]);
    }

    return "0";
}// 호스트 ip 받아 적는 구문. gethostname() 함수를 이용하여 host 이름을 불러오고, 그 이름을 바탕으로 DNS에서 해당 호스트 아이피를 불러와 저장

