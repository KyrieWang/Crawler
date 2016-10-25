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

int EpollManager::regSockHandle(int handle)
{
    struct epoll_event ev;
    ev.events = EPOLLIN | EPOLLET;
    ev.data.fd = handle;

    if(epoll_ctl(m_epollHandle, EPOLL_CTL_ADD, handle, &ev) == -1)
    {
        perror("epoll_ctl: sock_fd");
        return -1;
    }
}

int EpollManager::releaseHandl()
{
    close(m_epollHandle);
}

int EpollManager::getEpfd()
{
    return m_epollHandle;
}