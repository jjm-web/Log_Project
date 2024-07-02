//
//	MessageClint.c
//	Log_Control
//
//	Create by 장준명 on 2024/06/18.
//	Copyight @ 2024 장준명. All rights reserved.
//

#include "Log_Control_Header.h"

void message_log(char* data, struct receiverecord r, int fd, const char* port);
char* get_ip(void);

int main(int argc, const char * argv[]) {
    struct sockaddr_in serv_addr;
    struct receiverecord r;
    int serv_fd, clnt_fd, file_fd;
   
    if ((serv_fd = socket(PF_INET, SOCK_STREAM, DEFAULT_PROTOCOL)) == EOF) { // 클라이언트측 소켓 열기
        printf("\n소켓 생성 에러\n");
        exit(0);
    }

    // 소켓 주소 설정. 서버 통신을 위한 터미널에서 파일실행시 ip, 포트번호를 적기때문에 가져와 사용
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]));

    if (connect(serv_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == EOF) { // 서버에 연결요청
        printf("\n커넥트 에러\n");
        exit(0);
    }
    while(1){// 메세지를 입력받아 그 내용을 fd 저장
	    system("clear");
	    printf("\n입력할 data 작성후 엔터를 누르시오.\n(종료 : Exit 또는Quit\n<!!!주의!!! 띄어쓰기 없이 입력하시오.>\n\n==>");
	    scanf("%s", r.message);
	    message_log(r.message, r, serv_fd, argv[2]); //서버측으로 메세지 전송
	    if (strcmp(r.message, "Exit") == 0 || strcmp(r.message, "Quit") == 0) { // Exit 또는 Quit 입력 시 클라이언트 종료
										      		system("clear");
                break;
            }
    }
    close(serv_fd); // 부모 프로세스는 바로 종료, 서버는 백그라운드에서 계속 돌아감
    return 0;
}

void message_log(char *data, struct receiverecord r, int fd, const char* port) {
	sprintf(r.message, "%s %s %s", data, get_ip(), port);
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);

    snprintf(r.datetime, sizeof(r.datetime),"%04d/%02d/%02d %02d:%02d:%02d", tm.tm_year+1900, tm.tm_mon+1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
    write(fd, &r, sizeof(r));
} 

char* get_ip(void) {
    char host_name[80];
    struct hostent *host_entry;

    if (0 != gethostname(host_name, sizeof(host_name))) {
        printf("gethostname() 실행 실패(clint1)\n");
        exit(1);
    }

    host_entry = gethostbyname(host_name);

    if (!host_entry) {
        printf("gethostbyname() 실행 실패(clint2)\n");
        exit(1);
    }

    if (host_entry->h_addr_list[0]) {
        return inet_ntoa(*(struct in_addr*)host_entry->h_addr_list[0]);
    }

    return "0";
}
