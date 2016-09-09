#include "spiderApp.h"

int main(int argc, char const *argv[])
{
	/*程序初始化*/
	spiderApp app;

	if (app.initApp(argc ,argv) == 0)
	{
		SPIDER_LOG(SPIDER_LEVEL_ERROR, "app init is failed");
		return 1;
	}

	if (app.run() == 0)
	{
		SPIDER_LOG_ERROR(SPIDER_LEVEL_ERROR, "main app has exception");
		return 1;
	}

	return 0;
}