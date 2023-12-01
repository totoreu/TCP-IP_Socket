#include "C:\Users\God_Win\Documents\socket\Windows\Common.h"
#include <iostream>

int f(int x) {
    if (x > 0) {
        return 0;   // ����
    }
    else {
        WSASetLastError(WSAEINVAL);  // ���� �ڵ带 WSAEINVAL�� ����
        return SOCKET_ERROR;         // ����
    }
}

int main(int argc, char *argv[]) {
    // ���� �ʱ�ȭ
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(1, 1), &wsa) != 0)
        return 1;
    printf("[�˸�] ���� �ʱ�ȭ ����\n");

    std::cout << "wVersion: " << wsa.wVersion << std::endl;
    std::cout << "wHighVersion: " << wsa.wHighVersion << std::endl;
    std::cout << "szDescription: " << wsa.szDescription << std::endl;
    std::cout << "szSystemStatus: " << wsa.szSystemStatus << std::endl;

    int retval = f(1);
    if (retval == SOCKET_ERROR)
        err_quit("f()");

    // ���� ����
    SOCKET sockTCP = WSASocketA(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
    if (sockTCP == INVALID_SOCKET)
        err_quit("socket()");
    printf("[�˸�] ���� TCP ���� ����\n");

    SOCKET sockUDP = WSASocketA(AF_INET, SOCK_DGRAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
    if (sockUDP == INVALID_SOCKET)
        err_quit("socket()");
    printf("[�˸�] ���� UDP ���� ����\n");

    // ���� �ݱ�
    if (closesocket(sockTCP) == 0)
        printf("[�˸�] ���� TCP �ݱ� ����\n");

    if (closesocket(sockUDP) == 0)
        printf("[�˸�] ���� UDP �ݱ� ����\n");

    // ���� ����
    if (WSACleanup() == 0)
        printf("[�˸�] ���� ���� ����\n");
    return 0;
}