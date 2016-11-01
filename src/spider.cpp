#include <sys/epoll.h>

#include <iostream>
#include <string>
#include <thread>
#include <mutex>

#include "confparser.h"
#include "urlManager.h"
#include "sock.h"
#include "epollmanager.h"

using namespace std;

int main(int argc, char const *argv[])
{
	/*读取配置文件*/
	auto fptr = Confparser::getInstance();
	fptr->Loader("/home/hehe/crawler/test/spider.conf");
	CONF_FILE* conffile_ptr = fptr->getConfFile();
	
	UrlManager urlManage;
	urlManage.addUrl(conffile_ptr->seed);
	thread th_urlparse(&UrlManager::parserUrl, &urlManage);
	th_urlparse.detach();

	while(urlManage.is_parse_urldeq_empty())
		usleep(1000);

	EpollManager epmanage(conffile_ptr->job_num);
	int task_num = 0;
	Url* url_ptr = nullptr;
	while(task_num < conffile_ptr->job_num) {
		if(urlManage.is_parse_urldeq_empty())
			continue;

		auto sock_ptr = make_shared<Socket>();
		url_ptr = urlManage.getUrlForParseDeque();
		sock_ptr->build_connect(url_ptr);
		sock_ptr->send_request(url_ptr);
		epmanage.epRegister(sock_ptr);

		task_num++;
	}

	struct epoll_event events[10];
	int ep_num;
	while(1) {
		ep_num = epmanage.epWait(events, 10, 2000);

		if(ep_num <= 0) {
			cout << "epollerrno" << endl;
			continue;
		}
		
		for(int i = 0, i < n, i++) {
			if((events[i].events &EPOLLERR) ||
				(events[i].events &EPOLLHUP) ||
				(!(events[i].events &EPOLLIN))) {
					cout << "epoll fail!" << endl;
					close(events[i].data.fd);
					continue;
				}
			epmanage.epDelete(events[i].data.fd, &events[i]);
			cout << "epollevents:" << events[i].events << endl;
			thread th_parseResp(&Socket::recv_response, (Socket*)(events[i].data.ptr), urlManage);
			th_parseResp.detach();
		}
	}
}