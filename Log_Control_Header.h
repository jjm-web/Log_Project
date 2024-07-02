// Log_Control_Header.h
// Log_Control
//
// Created by 장준명 on 2024/06/18/14.
// Copyrlght @ 2024 장준명. All rights reserved.
//

#ifndef Log_control_Header_h
#define Log_control_Header_h
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>
#include <signal.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>

#define DEFAULT_PROTOCOL 0
#define MAX_LINE 100

struct receiverecord {
    char datetime[40]; // 날짜, 시간
    char message[60]; // 메시지 크기를 늘림
};

struct parameter {
    int seq;       // 번호 부여용
    char key[10];  // 키 값
    char value[30];// 벨류 값
};

#endif // Log_control_Header_h

