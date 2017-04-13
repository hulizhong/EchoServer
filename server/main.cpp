/*************************************************************************
	> File Name: main.cpp
	> Author: 
	> Mail: 
	> Created Time: Saturday, March 04, 2017 PM04:57:31 HKT
 ************************************************************************/

#include "TcpSocketServer.h"
#include <iostream>
using namespace std;

int main(void)
{
    TcpSocketServer tcpSer = TcpSocketServer();
    bool res = tcpSer.start();
    if (!res)
    {
        std::cout << "EchoServer start failed .." << std::endl;
        return -1;
    }
    std::cout << "this is EchoServer" << std::endl;

    return 0;
}

