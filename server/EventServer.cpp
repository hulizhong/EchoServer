/*************************************************************************
	> File Name: TcpSocketServer.cpp
	> Author: 
	> Mail: 
	> Created Time: Thursday, April 13, 2017 PM03:27:29 HKT
 ************************************************************************/

#include "EventServer.h"
#include <string.h>
//#include <sys/socket.h>
//#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>


static void conn_readcb(struct bufferevent *bev, void *user_data)
{
	struct evbuffer *input = bufferevent_get_input(bev);
    size_t input_len = evbuffer_get_length(input);
	if (input_len == 0)
    {
		printf("read msg: null");
		bufferevent_free(bev);
    }
    else
    {
        bufferevent_write_buffer(bev, input);
		printf("read msg: %d, and data: %s\n", input_len, evbuffer_readln(input, &input_len, EVBUFFER_EOL_CRLF));
        /**
        * 为什么没有触发ev_write也能将output中的数据发送出去？？
        * 难道是因为output中只要有数据，当fd可写时就会被bufferevent自动发送出去。
        * */
        //bufferevent_enable(bev, EV_WRITE);
    }
}
static void conn_writecb(struct bufferevent *bev, void *user_data)
{
	//struct evbuffer *output = bufferevent_get_output(bev);
	//if (evbuffer_get_length(output) == 0) {
	//	printf("flushed answer -- nothing\n");
	//	bufferevent_free(bev);
	//}
}
static void conn_errorcb(struct bufferevent *bev, short events, void *user_data)
{
	if (events & BEV_EVENT_EOF) {
		printf("Connection closed.\n");
	} else if (events & BEV_EVENT_ERROR) {
		printf("Got an error on the connection: %s\n",
		    strerror(errno));/*XXX win32*/
	}
	/* None of the other events can happen here, since we haven't enabled
	 * timeouts */
	bufferevent_free(bev);
}


static void listener_cb(struct evconnlistener *listener, evutil_socket_t fd,
    struct sockaddr *sa, int socklen, void *user_data)
{
	struct event_base *base = (struct event_base *)user_data;
	struct bufferevent *bev = bufferevent_socket_new(base, fd, BEV_OPT_CLOSE_ON_FREE);
	if (!bev) {
		fprintf(stderr, "Error constructing bufferevent!");
		event_base_loopbreak(base);
		return;
	}
	//bufferevent_setcb(bev, NULL, conn_writecb, conn_errorcb, NULL);
	bufferevent_setcb(bev, conn_readcb, conn_writecb, conn_errorcb, NULL);
    /** 为什么不enable read不行？？？ -------因为如下，在conn_readcb中调用了evbuffer_add_buffer
    *#0  event_add (ev=0x604770, tv=0x0) at event.c:2389
    #1  0x00007ffff7b94814 in bufferevent_add_event_ (ev=0x604770, tv=0x604850) at bufferevent.c:972
    #2  0x00007ffff7b99225 in bufferevent_socket_outbuf_cb (buf=0x604970, cbinfo=0x7fffffffd880, arg=0x6046e0) at bufferevent_sock.c:118
    #3  0x00007ffff7b8ab30 in evbuffer_run_callbacks (buffer=0x604970, running_deferred=0) at buffer.c:508
    #4  0x00007ffff7b8ac16 in evbuffer_invoke_callbacks_ (buffer=0x604970) at buffer.c:529
    #5  0x00007ffff7b8c475 in evbuffer_add_buffer (outbuf=0x604970, inbuf=0x6048e0) at buffer.c:994
    #6  0x00007ffff7b93082 in bufferevent_write_buffer (bufev=0x6046e0, buf=0x6048e0) at bufferevent.c:442
    #7  0x0000000000402345 in conn_readcb (bev=0x6046e0, user_data=0x0) at /home/pro/echoServer/server/EventServer.cpp:27
    #8  0x00007ffff7b9293c in bufferevent_run_readcb_ (bufev=0x6046e0, options=0) at bufferevent.c:233
    #9  0x00007ffff7b99144 in bufferevent_trigger_nolock_ (bufev=0x6046e0, iotype=2, options=0) at bufferevent-internal.h:366
    #10 0x00007ffff7b993bf in bufferevent_readcb (fd=11, event=2, arg=0x6046e0) at bufferevent_sock.c:189
    #11 0x00007ffff7b9dc3f in event_persist_closure (base=0x604080, ev=0x6046f0) at event.c:1531
    #12 0x00007ffff7b9df28 in event_process_active_single_queue (base=0x604080, activeq=0x6044d0, max_to_process=2147483647, endtime=0x0) at event.c:1590
    #13 0x00007ffff7b9e551 in event_process_active (base=0x604080) at event.c:1689
    #14 0x00007ffff7b9ecad in event_base_loop (base=0x604080, flags=0) at event.c:1912
    #15 0x00007ffff7b9e5d9 in event_base_dispatch (event_base=0x604080) at event.c:1723
    #16 0x0000000000402599 in TcpServer::start (this=0x7fffffffdc90) at /home/pro/echoServer/server/EventServer.cpp:98
    #17 0x0000000000401ded in TcpServerTest () at /home/pro/echoServer/server/main.cpp:28
    #18 0x0000000000401eb5 in main () at /home/pro/echoServer/server/main.cpp:40
    * */
	bufferevent_enable(bev, EV_READ);
	//bufferevent_enable(bev, EV_WRITE);
}


TcpServer::TcpServer(std::string ip)
{
    base = event_base_new();

	memset(&sin, 0, sizeof(sin));
	sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = inet_addr(ip.c_str());  
	sin.sin_port = htons(SOCKET_SERVER_PORT);

	listener = evconnlistener_new_bind(base, listener_cb, (void *)base, 
            LEV_OPT_REUSEABLE|LEV_OPT_CLOSE_ON_FREE, -1,
            (struct sockaddr*)&sin, sizeof(sin));
}

TcpServer::~TcpServer()
{
	evconnlistener_free(listener);
	event_base_free(base);
}

bool TcpServer::start()
{
    event_base_dispatch(base);
    return true;
}

bool TcpServer::doEchoWork()
{
    return false;
}

