#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include "protocol.h"

#define PORT 8888
#define BUF_SIZE sizeof(ClientToServerMessage)

int main()
{
    int sockfd;
    struct sockaddr_in serverAddr, clientAddr;
    ClientToServerMessage receivedMessage;
    ServerToClientMessage responseMessage;

    // 소켓 생성
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
    {
        perror("socket creation failed");
        return 1;
    }

    // 서버 주소 설정
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddr.sin_port = htons(PORT);

    // 소켓에 주소 바인딩
    if (bind(sockfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == -1)
    {
        perror("bind failed");
        return 1;
    }

    std::cout << "Server listening on port " << PORT << std::endl;

    while (true)
    {
        socklen_t clientLen = sizeof(clientAddr);

        // 클라이언트로부터 데이터 수신
        int recvBytes = recvfrom(sockfd, &receivedMessage, BUF_SIZE, 0, (struct sockaddr *)&clientAddr, &clientLen);
        if (recvBytes == -1)
        {
            perror("recvfrom failed");
            return 1;
        }

        std::cout << "Received message from client:" << std::endl;
        std::cout << "State Demand: " << receivedMessage.stateDemand << std::endl;
        std::cout << "Shutdown: " << receivedMessage.shutdown << std::endl;
        std::cout << "All Home: " << receivedMessage.allHome << std::endl;
        std::cout << "Axis Home: " << receivedMessage.axisHome << std::endl;
        std::cout << "Music Path: " << receivedMessage.musicPath << std::endl;

        sendto(sockfd, &responseMessage, sizeof(responseMessage), 0, (struct sockaddr *)&clientAddr, clientLen);
        std::cout << sizeof(responseMessage) << "\n";
    }

    close(sockfd);
    return 0;
}
