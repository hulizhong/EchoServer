/*************************************************************************
	> File Name: TcpSocketClient.cpp
	> Author: 
	> Mail: 
	> Created Time: Thursday, April 13, 2017 PM04:34:57 HKT
 ************************************************************************/

#include "TcpSocketClient.h"
#include <string.h>
#include <iostream>
#include <unistd.h>
#include <fstream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


TcpSocketClient::TcpSocketClient(std::string serip)
{
    memset(&mSerAddr,0,sizeof(mSerAddr));  
    mSerAddr.sin_family = AF_INET;  
    //mSerAddr.sin_addr.s_addr = htonl(INADDR_ANY);  
    mSerAddr.sin_addr.s_addr = inet_addr(serip.c_str());  
    mSerAddr.sin_port = htons(SOCKET_SERVER_PORT);  
}

TcpSocketClient::~TcpSocketClient()
{
    ;
}

bool TcpSocketClient::start()
{
    mFd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (mFd < 0)
    {
        return false;
    }  

    bool res = sendEchoMsg();
    for (int i=0; i<10; i++)
        res = sendEchoMsg();
    if (!res)
        std::cout << "sendEchoMsg failed!" << std::endl;  

    return true;
}

bool TcpSocketClient::sendEchoMsg()
{
    char buffer[SOCKET_SERVER_BUFFER_LEN] = {0};  
    strcpy(buffer, getUUID().c_str());

    int res = 0;
    int e = 0;
    /*
    socklen_t elen = sizeof(e);
    getsockopt(mFd, SOL_SOCKET, SO_ERROR, (void*)&e, &elen);
    std::cout << strerror(e) << " " << e << std::endl;
    */
    e = recv(mFd, NULL, 0, MSG_PEEK);
    if (e != 0)
    {
        res = connect(mFd, (struct sockaddr*)&mSerAddr,sizeof(mSerAddr));
        if (res < 0)
        {
            std::cout << "connect to EchoServer failed. " << res << std::endl;
            perror("EXT");
            //close(mFd); 
            //return false;
        }
    }

    //res = send(mFd, buffer, sizeof(buffer), 0); //will send SOCKET_SERVER_BUFFER_LEN even if no enough data.
    res = send(mFd, buffer, strlen(buffer), 0);
    if (res > 0)
    {
        std::cout << "EchoClient SEND: " << buffer << std::endl;  
    }  
    else if (res < 0)
    {
        std::cout << "send echoMsg failed. " << res << std::endl;  
        perror("EXT");
        close(mFd); 
        return false;
    }
    else
    {
        std::cout << "send echoMsg failed. and res == 0 ??????????????" << std::endl;  
        close(mFd); 
        return false;
    }

    //memset(buffer, 0, sizeof(buffer));
    //res = recv(mFd, buffer, sizeof(buffer), 0);
    //if (res > 0)
    //    std::cout << "EchoClient RECV: " << buffer << std::endl;  
    //else if (res == 0)
    //    std::cout << "EchoServer close connection." << std::endl;  
    //else
    //    std::cout << "recv data from EchoServer failed!" << res << std::endl;  

    //close(mFd); 
    return true;
}

std::string TcpSocketClient::getUUID()
{
    std::ifstream ifs("/proc/sys/kernel/random/uuid");  
    if (!ifs.is_open())  
    {
        return std::string("default_uuid");
    } 
    char uuid[64] = {0};
    ifs.getline(uuid, 63, '-');
    ifs.close();
    return std::string(uuid);
    //return std::move(string(uuid));
}

