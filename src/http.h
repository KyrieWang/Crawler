#ifndef HTTP_H_
#define HTTP_H_

#include <string>

using namespace std;

class Http
{
public:
	Http();
	~Http();

	int parseHead(void* buf);
	int creatHead();

	int getUrl(URL* url);
	int getContent(void* buf); //传入预先申请的缓冲区地址

	init();
	re_init();

	int updateUrl(URL* url); //更新HTTP头中的信息

private:
	URL url;
	void* buf;
};

#endif