/*************************************************************************
	> File Name: TcpSocketServer.h
	> Author: 
	> Mail: 
	> Created Time: Thursday, April 13, 2017 PM03:25:42 HKT
 ************************************************************************/

#ifndef _TCPSOCKETSERVER_H
#define _TCPSOCKETSERVER_H

#include <netinet/in.h>

#define SOCKET_SERVER_PORT 8899
#define SOCKET_SERVER_BUFFER_LEN 1024
#define SOCKET_SERVER_SEND_BUFFER_LEN 1024
#define SOCKET_SERVER_RECV_BUFFER_LEN 1024

class TcpSocketServer
{
public:
    TcpSocketServer();
    ~TcpSocketServer();
    bool start();

protected:
    bool doEchoWork();

private:
    int mFd;
    sockaddr_in mAddr;
};

#endif
