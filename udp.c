#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>//sleep 函数

#define SERVER_PORT 8888
#define BUFF_LEN 4096
#define SERVER_IP "127.0.0.1"


static int init_server()
{
    int server_fd;
    struct sockaddr_in ser_addr;
    char buf[BUFF_LEN];  //接收缓冲区，1024字节
    socklen_t len=sizeof(ser_addr);

    server_fd = socket(AF_INET, SOCK_DGRAM, 0); //AF_INET:IPV4;SOCK_DGRAM:UDP
    if(server_fd < 0)
    {
        printf("create socket fail!\n");
        return -1;
    }

    memset(&ser_addr, 0, sizeof(ser_addr));
    ser_addr.sin_family = AF_INET;
    ser_addr.sin_addr.s_addr = htonl(INADDR_ANY); //IP地址，需要进行网络序转换，INADDR_ANY：本地地址
    ser_addr.sin_port = htons(SERVER_PORT);  //端口号，需要网络序转换
    if(bind(server_fd, (struct sockaddr*)&ser_addr, sizeof(ser_addr)) < 0)
    {
        printf("socket bind fail!\n");
        return -1;
    }


    while(1)
    {
        int ret = recvfrom(server_fd, buf, BUFF_LEN,MSG_DONTWAIT, (struct sockaddr*)&ser_addr, (socklen_t*)&len);
        if(ret <= 0)
        {
            continue;
        }
        printf("client:%s\n",buf);  //打印client发过来的信息
        memset(buf, 0, BUFF_LEN);
    }

    close(server_fd);
    return 0;
}


static int init_client()
{
    int client_fd;
    struct sockaddr_in ser_addr;
    socklen_t len =sizeof(ser_addr);
    client_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if(client_fd < 0)
    {
        printf("create socket fail!\n");
        return -1;
    }

    memset(&ser_addr, 0, sizeof(ser_addr));
    ser_addr.sin_family = AF_INET;
//    ser_addr.sin_addr.s_addr = inet_addr(SERVER_IP);
    ser_addr.sin_addr.s_addr = htonl(INADDR_ANY);  //注意网络序转换
    ser_addr.sin_port = htons(SERVER_PORT);  //注意网络序转换

    while(1)
    {
        char buf[BUFF_LEN] = "TEST UDP MSG!\n";
        sendto(client_fd, buf, BUFF_LEN, 0,(struct sockaddr*)&ser_addr, len);
        sleep(1);  //一秒发送一次消息
    }

    close(client_fd);

    return 0;
}


int main(int argc, char *argv[])
{

    if(argc<=1)
        init_server();
    else
        init_client();
    return 0;
}
