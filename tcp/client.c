#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <strings.h>
#include <arpa/inet.h>

#define SERVER_PORT 1224

int main() {
    int socketFd;
    struct sockaddr_in server_addr; //sockaddr_in为结构体变量类型，server_addr为变量
    char buffer[1024];
    socketFd = socket(AF_INET, SOCK_STREAM, 0);

    //初始化服务器端的套接字，并用htons和htonl将端口和地址转成网络字节序
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    //ip可是是本服务器的ip，也可以用宏INADDR_ANY代替，代表0.0.0.0，表明所有地址
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    //连接
    if (connect(socketFd, (struct sockaddr *) &server_addr,sizeof(server_addr)) < 0) {
        perror("connect error");
    }
    printf("连接到主机...\n");

    //接收请求
    while (1) {
        printf("发送消息:");
        scanf("%s", buffer);
        printf("\n");
        if (strcmp(buffer, "quit") == 0){
            break;
        }
        send(socketFd, buffer, strlen(buffer), 0);
    }
    close(socketFd);
    return 0;
}