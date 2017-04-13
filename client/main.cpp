/*************************************************************************
	> File Name: main.cpp
	> Author: 
	> Mail: 
	> Created Time: Saturday, March 04, 2017 PM04:57:31 HKT
 ************************************************************************/

#include "TcpSocketClient.h"
#include <iostream>
using namespace std;


int main(void)
{
    TcpSocketClient echoCli = TcpSocketClient("172.22.48.101");
    bool res = echoCli.start();
    if (!res)
        std::cout << "EchoClient start failed." << std::endl;

    return 0;
}

