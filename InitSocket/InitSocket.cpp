#include "C:\Users\God_Win\Documents\socket\Windows\Common.h"
#include <iostream>

int f(int x) {
    if (x > 0) {
        return 0;   // 성공
    }
    else {
        WSASetLastError(WSAEINVAL);  // 오류 코드를 WSAEINVAL로 설정
        return SOCKET_ERROR;         // 실패
    }
}

int main(int argc, char *argv[]) {
    // 윈속 초기화
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(1, 1), &wsa) != 0)
        return 1;
    printf("[알림] 윈속 초기화 성공\n");

    std::cout << "wVersion: " << wsa.wVersion << std::endl;
    std::cout << "wHighVersion: " << wsa.wHighVersion << std::endl;
    std::cout << "szDescription: " << wsa.szDescription << std::endl;
    std::cout << "szSystemStatus: " << wsa.szSystemStatus << std::endl;

    int retval = f(1);
    if (retval == SOCKET_ERROR)
        err_quit("f()");

    // 소켓 생성
    SOCKET sockTCP = WSASocketA(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
    if (sockTCP == INVALID_SOCKET)
        err_quit("socket()");
    printf("[알림] 소켓 TCP 생성 성공\n");

    SOCKET sockUDP = WSASocketA(AF_INET, SOCK_DGRAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
    if (sockUDP == INVALID_SOCKET)
        err_quit("socket()");
    printf("[알림] 소켓 UDP 생성 성공\n");

    // 소켓 닫기
    if (closesocket(sockTCP) == 0)
        printf("[알림] 소켓 TCP 닫기 성공\n");

    if (closesocket(sockUDP) == 0)
        printf("[알림] 소켓 UDP 닫기 성공\n");

    // 윈속 종료
    if (WSACleanup() == 0)
        printf("[알림] 윈속 종료 성공\n");
    return 0;
}