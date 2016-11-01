#include <sys/epoll.h>
#include <errno.h>
#include <stdlib.h>

#include "epollmanager.h"

using namespace std;

EpollManager::EpollManager(int max_job_num)
{
    m_taskNum = max_job_num;
    m_epollHandle = epoll_create(m_taskNum);
}

EpollManager::~EpollManager()
{
    releaseHandl();
}

int EpollManager::epRegister(Socket* sock_ptr)
{
    struct epoll_event ev;
    int sock_fd = sock_ptr->getSockfd();
    ev.events = EPOLLIN | EPOLLET;
    ev.data.fd = sock_fd;
    ev.data.ptr = sock_ptr;

    if(epoll_ctl(m_epollHandle, EPOLL_CTL_ADD, sock_fd, &ev) == -1)
    {
        perror("epoll_ctl: sock_fd");
        return -1;
    }

    return 0;
}

int EpollManager::epWait(struct epoll_event* events, int maxevents, int timeout)
{
    int n = epoll_wait(m_epollHandle, events, maxevents, timeout);
    return n;
}

void EpollManager::epDelete(int handle, struct epoll_event* events)
{
    epoll_ctl(m_epollHandle, EPOLL_CTL_DEL, handle, events);
}

void EpollManager::releaseHandl()
{
    close(m_epollHandle);
}

int EpollManager::getEpfd()
{
    return m_epollHandle;
}