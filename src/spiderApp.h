#ifndef SPIDERAPP_H_
#define SPIDERAPP_H_

#include <iostream>

#define CONF_PATH "spider.conf"

using namespace std

class SpiderApp
{
public:
	SpiderApp();
	~SpiderApp();

	int initApp(); //初始化环境
	int run(); //主处理流程
	int deamon(); //按守护进程模式运行
	
private:
	/*处理参数*/
	int initArgv(int argc, char* argv[]);

	int isDeamon;
};

#endif