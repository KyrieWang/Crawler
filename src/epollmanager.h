#ifndef EPOLLMANAGER_H_
#define EPOLLMANAGER_H_

#include <epoll.h>

class EpollManager
{
public:
	EpollManager(int num); //initial epoll
	~EpollManager(); //release the handle

	int regSockHandle(int handle);
	int releaseHandl();

private:
	int m_epollHandle;
	int m_taskNum; //抓取的最大任务数
};

#endif