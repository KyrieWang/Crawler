#ifndef EPOLLMANAGER_H_
#define EPOLLMANAGER_H_

#include <epoll.h>

class EpollManager
{
public:
	EpollManager(int max_job_num); //initial epoll
	~EpollManager(); //release the handle

	int epRegister(Socket* sock_ptr);
	int epWait(struct epoll_event* events, int maxevents, int timeout);
	void epDelete(int handle, struct epoll_event* events);
	void releaseHandl();
	int getEpfd();

private:
	int m_epollHandle;
	int m_taskNum; //抓取的最大任务数
};

#endif