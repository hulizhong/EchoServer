/*************************************************************************
	> File Name: main.cpp
	> Author: 
	> Mail: 
	> Created Time: Saturday, March 04, 2017 PM04:57:31 HKT
 ************************************************************************/

#include "TcpSocketServer.h"
#include "EventServer.h"
#include <iostream>
using namespace std;

void TcpSocketServerTest()
{
    TcpSocketServer tcpSer = TcpSocketServer("172.22.48.101");
    bool res = tcpSer.start();
    if (!res)
    {
        std::cout << "EchoServer start failed .." << std::endl;
        return;
    }
    std::cout << "this is EchoServer" << std::endl;
}

void TcpServerTest()
{
    TcpServer tcpSer = TcpServer("172.22.48.101");
    bool res = tcpSer.start();
    if (!res)
    {
        std::cout << "event-EchoServer start failed .." << std::endl;
        return;
    }
    std::cout << "this is event-EchoServer" << std::endl;
}

int main(void)
{
    //TcpSocketServerTest();
    TcpServerTest();
    return 0;
}

