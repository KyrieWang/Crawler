#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include "confparser.h"
#include "urlManager.h"
#include "sock.h"
#include "epollmanager.h"
#include <sys/epoll.h>

using namespace std;

int main(int argc, char const *argv[])
{
	/*读取配置文件*/
	auto fptr = Confparser::getInstance();
	fptr->Loader("/home/hehe/crawler/test/spider.conf");
	CONF_FILE* conffile_ptr = fptr->getConfFile();

	struct epoll_event events[conffile_ptr->job_num];
	
}