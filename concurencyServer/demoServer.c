#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <signal.h>
#include <error.h>
#include <arpa/inet.h>

void sigHander(int sigNum)
{
    int ret = 0;
    //资源回收
    //to do...

    //return ret;
}

#define BUFFER_SIZE 128
#define SERVER_SIZE 9999
#define MAX_LISTEN 128
#define LOCAL_IPADDRESS "127.0.0.1"
int main()
{
    //注册信号
    // signal(SIGINT, sigHander);
    // signal(SIGTSTP, sigHander);
    // signal(SIGTSTP, sigHander);

    //创建socket套接字
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
        perror("socket error");
        exit(-1);
    }
    int enableOpt = 1;
    int ret = setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (void*)&enableOpt, sizeof(enableOpt));
    if (ret == -1)
    {
        perror("setsockopt error");
        exit(-1);
    }
    

    //绑定
    #if 0
    //这个结构体不好用
    struct sockaddr localAddress;
    #else
    struct sockaddr_in localAddress;

    #endif
    memset(&localAddress, 0, sizeof(localAddress));

    localAddress.sin_family = AF_INET;
#if 0
    //ip转成大端
    localAddress.sin_addr = INADDR_ANY;//0x00000000
#else

    // inet_pton(AF_INET, LOCAL_IPADDRESS, &(localAddress.sin_addr.s_addr));
#endif
    //端口需要转成大端
    localAddress.sin_port = htons(SERVER_SIZE);
    
    int lcalAddressLen = sizeof(localAddress);
    ret = bind(sockfd, (struct sockaddr*)&localAddress, lcalAddressLen);
    if (ret == -1)
    {
        perror("bind error");
        exit(-1);
    }
    
    //监听
    ret = listen(sockfd, MAX_LISTEN);
    if (ret == - 1)
    {
        perror("listen error");
        exit(-1);
    }
    //客户信息
    struct sockaddr_in clienAddress;
    memset(&clienAddress, 0, sizeof(clienAddress)); 
   
    socklen_t clienAddressLen = 0;
    int acceptfd = accept(sockfd, (struct sockaddr *)&clienAddress, &clienAddressLen);
    if (acceptfd == -1)
    {
        perror("accept error");
        exit(-1);
    }
    char replyBytes[BUFFER_SIZE];
    memset(replyBytes, 0, sizeof(replyBytes));

    char buffer[BUFFER_SIZE];
    memset(buffer, 0, sizeof(buffer));
    //int recvNum = 0;
    int readBytes = 0;
    while (1)
    {
        readBytes = read(acceptfd, buffer, sizeof(buffer));
        if (readBytes <= 0)
        {
            perror("read error");
            printf("111\n");
            close(acceptfd);
            break;
        }
        else
        {
            
            //读到的字符串
            printf("buffer:%s\n", buffer);
            // if (buffer == "注册")
            // {
                
            // }
            // else if (buffer == "登录")
            // {

            // }

            sleep(3);
            
            strncpy(replyBytes, "一起加油", sizeof(replyBytes) - 1);
            write(acceptfd, replyBytes, strlen(replyBytes) + 1);
            

        }
        
    }
    
    //关闭文件描述符
    
    close(sockfd);
    
    return 0;
}