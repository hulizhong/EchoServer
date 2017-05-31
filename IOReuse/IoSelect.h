/*************************************************************************
	> File Name: IoSelect.h
	> Author: 
	> Mail: 
	> Created Time: Thursday, April 13, 2017 PM07:17:46 HKT
 ************************************************************************/

#ifndef _IOSELECT_H
#define _IOSELECT_H

/*
// According to POSIX.1-2001 
#include <sys/select.h>

// According to earlier standards
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

int select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout);
void FD_CLR(int fd, fd_set *set);
int  FD_ISSET(int fd, fd_set *set);
void FD_SET(int fd, fd_set *set);
void FD_ZERO(fd_set *set);

#include <sys/select.h>
int pselect(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, const struct timespec *timeout, const sigset_t *sigmask);
*/


class IoSelect
{
};

#endif
