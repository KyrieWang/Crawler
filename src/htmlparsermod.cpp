#include "../src/dso.h"
#include "htmlparsermod.h"

void init(MODULE* module)
{

}

int handle(void* data)
{
	struct htmlParserParam* lparam = (struct htmlParserParam*)param;
	htmlParser loParser;
	param->urls = loParser.getUrls(param->url);
	
	if(param->urls.count() == 0)
		return MODULE_ERR;

	return MODULE_OK;
}