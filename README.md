# Log_Project - 소켓 프로그래밍

* __로그관리 프로젝트__   
* __소켓 프로그래밍을 활용한 클라이언트-서버 및 모니터링 시스템__

* __프로젝트 개요__
  * 모니터링 프로그램
    * 로그 파일을 실시간으로 읽어 사용자에게 출력
    * 설정 파일을 통해 로그 파일 경로를 동적으로 설정
    * 주기적으로 로그 파일을 읽어 새로운 로그 항목을 출력
  
  * 서버 프로그램
    * 클라이언트로부터 메시지를 수신하여 로그 파일에 기록
    * 클라이언트의 연결 요청을 수락하고, 클라이언트와 통신 유지
    * 서버가 열릴 때와 클라이언트가 메시지를 보낼 때마다 로그 기록
    * 특정 메시지(Exit 또는 Quit)가 수신되면 클라이언트 연결 종료
  
  * 클라이언트 메세지 프로그램
    * 서버에 연결하여 사용자로부터 메시지를 입력받아 서버로 전송
    * 실시간 데이터 모니터링 및 히스토리 데이터 조회
    * 특정 메시지(Exit 또는 Quit)가 입력되면 서버와의 연결 종료

* __개발환경__
   
  * 언어 : C
  * 개발프레임 : __Vim__
  * 라이브러리 : unistd.h, fcntl.h, string.h, time.h, signal.h, netinet/in.h, arpa/inet.h, sys/socket.h, sys/types.h, netdb.h
  * 통신 : __TCP/IP 소켓 프로그래밍__
  * 그 외 : MacOs, UTM(가상머신) Ubuntu Linux
--------------------------------

 ## 1. 앱 -> 서버 


<p align="center" />
    <img src="https://github.com/jjm-web/intellian_Project/assets/76840242/86c1d64c-de61-4fba-8bb0-354f03fa6db9"/>
    
</p> 

## 2. 서버 -> 웹


<p align="center" />
    <img src="https://github.com/jjm-web/intellian_Project/assets/76840242/108e4f3f-be90-4d9f-b94c-57f5d40a188e"/>
</p> 



----------------------------------------

* __주요 업무 및 성과__

  
  * 서버 개발 :
    * C로 TCP/IP 소켓 서버 개발, 클라이언트의 연결 요청 수락 및 메시지 수신 기능 구현
    * 메시지를 수신하여 로그 파일에 기록하는 기능 구현
    * 클라이언트의 특정 메시지(Exit, Quit) 처리 및 연결 종료 기능 구현
      

  * 클라이언트 개발:
    * C로 TCP/IP 소켓 클라이언트 개발, 서버에 메시지를 전송하는 기능 구현
    * 사용자로부터 메시지를 입력받아 서버로 전송하는 기능 구현
    * 특정 메시지(Exit, Quit) 입력 시 서버와의 연결 종료 기능 구현

  * 모니터링 프로그램 개발:
    * C로 로그 파일을 실시간으로 읽어 사용자에게 출력하는 모니터링 프로그램 개발
    * 설정 파일을 통해 로그 파일 경로를 동적으로 설정하는 기능 구현
    * 주기적으로 로그 파일을 읽어 새로운 로그 항목을 출력하는 기능 구현
  
  * 성능 최적화:
    * 멀티프로세싱을 사용하여 여러 클라이언트 요청을 동시에 처리함으로써 서버 성능 최적화
  
  * 로그 관리:
    * 서버의 활동을 로깅하여 시스템 상태 및 오류를 모니터링할 수 있도록 함.
    * 로그 파일을 통해 서버의 작업 내역을 기록하고 추적 가능하도록 구현

-----------------------------------------

  

