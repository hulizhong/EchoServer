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


TcpSocketServer::TcpSocketServer()
{
    memset(&mAddr,0,sizeof(mAddr));  
    mAddr.sin_family = AF_INET;  
    mAddr.sin_addr.s_addr = htonl(INADDR_ANY);  
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
    if( bind(mFd,(sockaddr*) &mAddr,sizeof(mAddr)) < 0 ) 
    {
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


