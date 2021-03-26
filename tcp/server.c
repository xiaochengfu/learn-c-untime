#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <strings.h>

#define SERVER_PORT 1224

int main() {
    int socketFd, clientFd,num;
    struct sockaddr_in server_addr, client_addr; //sockaddr_in为结构体变量类型，server_addr为变量
    char buffer[1024];
    int client_addr_len = sizeof(client_addr);
    socketFd = socket(AF_INET, SOCK_STREAM, 0);

    //初始化服务器端的套接字，并用htons和htonl将端口和地址转成网络字节序
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    //ip可是是本服务器的ip，也可以用宏INADDR_ANY代替，代表0.0.0.0，表明所有地址
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    //绑定
    if (bind(socketFd, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0) {
        perror("bind error");
        return 1;
    }
    //监听
    if (listen(socketFd, 3) < 0) {
        perror("listen");
        return 1;
    }
    //接收请求
    while (1) {
        printf("监听端口: %d\n",SERVER_PORT);
        printf("等待连接...\n");
        clientFd = accept(socketFd, (struct sockaddr *) &client_addr, (socklen_t *) &client_addr_len);
        if (clientFd < 0) {
            perror("accept error");
            continue;
        }
        printf("等待消息...\n");
        while (1){
            buffer[0] = '\0';
            num = recv(clientFd,buffer,1024,0);
//            num = read(clientFd,buffer,1024);
            if (num<0){
                perror("recv null");
                continue;
            }
            printf("%s\n", buffer);
        }
    }
    close(socketFd);
    return 0;
}