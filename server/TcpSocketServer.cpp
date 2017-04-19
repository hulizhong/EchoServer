/*************************************************************************
	> File Name: TcpSocketServer.cpp
	> Author: 
	> Mail: 
	> Created Time: Thursday, April 13, 2017 PM03:27:29 HKT
 ************************************************************************/

#include "TcpSocketServer.h"
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <string.h>
#include <iostream>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>


//#define BindApiCanReuse

TcpSocketServer::TcpSocketServer(std::string ip)
{
    memset(&mAddr,0,sizeof(mAddr));  
    mAddr.sin_family = AF_INET;  
    //mAddr.sin_addr.s_addr = htonl(INADDR_ANY);  
    mAddr.sin_addr.s_addr = inet_addr(ip.c_str());  
    mAddr.sin_port = htons(SOCKET_SERVER_PORT);  
}

TcpSocketServer::~TcpSocketServer()
{
    ;
}

bool TcpSocketServer::start()
{
    mFd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (mFd < 0)
    {
        return false;
    }  
    
    #ifdef BindApiCanReuse
    /**
     * 从代码的角度来修改：
     * process bind() failed.  ----> Address already in use
     *
     * 从系统配置的角度来修改：（以下两项均要同时开启）
     * net.ipv4.tcp_tw_reuse = 1表示开启重用。允许将TIME-WAIT sockets重新用于新的TCP连接，默认为0，表示关闭；
     * net.ipv4.tcp_tw_recycle = 1表示开启TCP连接中TIME-WAIT sockets的快速回收，默认为0，表示关闭。
     * 注：/proc/sys/net/ipv4/tcp_fin_timeout = 60
     * */
    int reuse = 1;
    setsockopt(mFd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));
    #endif

    if( bind(mFd,(sockaddr*) &mAddr,sizeof(mAddr)) < 0 ) 
    {
        std::cout << "bind failed: " << strerror(errno) << std::endl;
        return false;
    }  

    if( listen(mFd,10) < 0 ) {  
        return false;
    }  

    bool res = doEchoWork();

    return true;
}

bool TcpSocketServer::doEchoWork()
{
    char buffer[SOCKET_SERVER_BUFFER_LEN] = {0};  
    int res = 0;
    while( true ) {  
        sockaddr_in clientAddr;
        socklen_t addrLen = sizeof(struct sockaddr_in);  
        int cliFd = 0;

        cliFd = accept(mFd, (struct sockaddr*)&clientAddr, &addrLen);
        if (cliFd < 0)
        {  
            std::cout << "Accept error!" << std::endl;
            continue;  
        }  
        std::cout << "Received a connection from " << inet_ntoa(clientAddr.sin_addr) <<". " << std::endl;

        memset(buffer, 0, sizeof(buffer));
        res = recv(cliFd, buffer, sizeof(buffer), 0);
        if (res > 0)
        {
            std::cout << "EchoServer RECV: " << buffer << std::endl;  
            usleep(100000);//echoserver process every request time.
            res = send(cliFd, buffer, res, 0);
            if (res > 0)
                std::cout << "EchoServer SEND: " << buffer << std::endl;  
            else if (res < 0)
                std::cout << "send data to EchoClient failed!" << std::endl;  
            else
                std::cout << "send data to EchoClient failed! caue send = 0 ??????????" << std::endl;  
        }
        else if (res == 0)
            std::cout << "EchoClient close connection." << std::endl;  
        else
            std::cout << "recv data from EchoClient failed!" << std::endl;  

        close(cliFd);
    }  
    return true;
}


