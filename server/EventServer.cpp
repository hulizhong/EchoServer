/*************************************************************************
	> File Name: TcpSocketServer.cpp
	> Author: 
	> Mail: 
	> Created Time: Thursday, April 13, 2017 PM03:27:29 HKT
 ************************************************************************/

#include "EventServer.h"

TcpServer::TcpServer(std::string ip)
{
    //struct event_base *event_base_new(void);
    evbase = event_base_new();
}

TcpServer::~TcpServer()
{
    event_base_free(evbase);
}

bool TcpServer::start()
{
    return doEchoWork();
}

bool TcpServer::doEchoWork()
{
    return false;
}
