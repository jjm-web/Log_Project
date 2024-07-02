//
//	monitoring.c
//	Log_Control
//
//	Create by 장준명 on 2024/06/14.
//	copyright @ 2024 장준명. All rights reserved.
//

#include "Log_Control_Header.h"

int main(int argc, const char *argv[]) {
    struct receiverecord r;
    struct parameter p;

    int fd = 0;
    int pid = 0;
    int count_size_of_data = 1;
    int line = 0;

    long read_len = 1;

    char filename[20];
    char command[5];

    system("clear");

    puts("파일명을 입력 바랍니다.\n"); // setup.txt 불러오기 위한 파일명 입력
    scanf("%s", filename); // setup.txt를 입력하여 filename 저장

    printf("입력된 파일명: %s\n", filename);

    if ((fd = open(filename, O_RDONLY)) == -1) { // setup.txt open
        perror("파일이 없습니다");
        exit(1);
    }

    while (read_len > 0) {
        lseek(fd, line * sizeof(p), SEEK_SET); // setup.txt 앞줄에서 읽고, 그 값을 struct parameter p 구조체에 지정된 형식에 저장
        read_len = read(fd, &p, sizeof(p));
        if (read_len == -1) {
            perror("파일 읽기 오류");
            close(fd);
            exit(1);
        }
        if (strcmp(p.key, "file") == 0) { // 저장된 p.key 값이 file과 일치할 경우 strcmp는 0 반환, 그럴 경우 p.value 값을 filename 저장, fd종료, break
            strcpy(filename, p.value);
            close(fd);
            break;
        }
        line += 1; // 아닐 경우 맞을 때까지 line + 1 한다.
    }

    if ((fd = open(filename, O_RDONLY)) == -1) { // writelog.txt open
        perror("파일이 없습니다");
        exit(1);
    }

    pid = fork(); // 화면 구성용 자식 프로세스 생성

    if (pid == 0) {
        // 자식 프로세스: 로그 파일 모니터링 및 출력
        while (1) {
            count_size_of_data = 1;
            line = 0;

            while (count_size_of_data <= 10) { // 10개 로그만 보이도록 출력
                lseek(fd, line * sizeof(r), SEEK_SET);
                if (read(fd, &r, sizeof(r)) == 0) break;
                count_size_of_data += 1;
                line += 1;
            }

            system("clear"); // 화면 제작 시작
            printf("================== 로그 관리 프로그램 ==================\n");
            printf("datetime\t\tmessage\n");

            for (line = 1; line < count_size_of_data; line++) { // writelog.txt 데이터 호출 후 출력
                lseek(fd, -line * sizeof(r), SEEK_END); // 뒤에서부터 읽기 구현
                read(fd, &r, sizeof(r));
                printf("%s\t%s\n", r.datetime, r.message);
            }
            printf("\n종료를 원할 경우 Quit 또는 Exit를 정확히 입력하시오.\n>>>");
            sleep(2);
        }
    } else {
        // 부모 프로세스: 종료 명령 처리
        while (1) {
            scanf("%s", command); // 종료 입력받기
            if (strcmp(command, "Exit") == 0 || strcmp(command, "Quit") == 0) {
                kill(pid, SIGINT); // 자식 프로세스 종료
                break;
            } else {
                printf("잘못된 입력입니다.(Exit 또는 Quit)\n");
            }
        }
    }

    printf("\n");
    close(fd);
    system("clear");
    return 0;
}

