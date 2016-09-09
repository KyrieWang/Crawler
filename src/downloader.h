#ifndef DOWNLOADER_H_
#define DOWNLOADER_H_

#include <string>

using namespace std;

class Downloader
{
public:
	Downloader();
	~Downloader();

	int getResource(URL* url);
	void* getResourceContent();

	int init();
	int re_init();

	int getSocketHandle();

private:
	//socket封装

	//HTTP协议处理
	
};

#endif