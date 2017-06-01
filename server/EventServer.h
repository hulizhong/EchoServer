/*************************************************************************
	> File Name: EventServer.h
	> Author: 
	> Mail: 
	> Created Time: Thursday, April 13, 2017 PM03:25:42 HKT
 ************************************************************************/

#ifndef _EVENTSERVER_H
#define _EVENTSERVER_H

#include "event2/event.h"
#include <string>

class TcpServer
{
public:
    TcpServer(std::string ip);
    ~TcpServer();
    bool start();

protected:
    bool doEchoWork();

private:
    struct event_base *evbase;
};

#endif
