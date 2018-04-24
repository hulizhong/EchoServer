/*************************************************************************
	> File Name: EventServer.h
	> Author: 
	> Mail: 
	> Created Time: Thursday, April 13, 2017 PM03:25:42 HKT
 ************************************************************************/

#ifndef _EVENTSERVER_H
#define _EVENTSERVER_H

#include "event2/bufferevent.h"
#include "event2/buffer.h"
#include "event2/listener.h"
#include "event2/util.h"
#include "event2/event.h"

#include <string>
#include <netinet/in.h>

#define SOCKET_SERVER_PORT 8899
#define SOCKET_SERVER_BUFFER_LEN 1024
#define SOCKET_SERVER_SEND_BUFFER_LEN 1024
#define SOCKET_SERVER_RECV_BUFFER_LEN 1024

class TcpServer
{
public:
    TcpServer(std::string ip);
    ~TcpServer();
    bool start();

protected:
    bool doEchoWork();

private:
	struct event_base *base;
	struct evconnlistener *listener;
	struct sockaddr_in sin;
};

#endif
