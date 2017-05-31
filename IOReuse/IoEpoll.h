/*************************************************************************
	> File Name: IoEpoll.h
	> Author: 
	> Mail: 
	> Created Time: Thursday, April 13, 2017 PM07:19:51 HKT
 ************************************************************************/

#ifndef _IOEPOLL_H
#define _IOEPOLL_H

/*
       #include <sys/epoll.h>

       int epoll_create(int size);
       int epoll_create1(int flags);

       int epoll_ctl(int epfd, int op, int fd, struct epoll_event *event);

       int epoll_wait(int epfd, struct epoll_event *events,
                      int maxevents, int timeout);
       int epoll_pwait(int epfd, struct epoll_event *events,
                      int maxevents, int timeout,
                      const sigset_t *sigmask);

       struct epoll_event {
           uint32_t     events;      // Epoll events
           epoll_data_t data;        // User data variable
       };
       typedef union epoll_data {
           void        *ptr;
           int          fd;
           uint32_t     u32;
           uint64_t     u64;
       } epoll_data_t;
*/



class IoEpoll
{

};
#endif
