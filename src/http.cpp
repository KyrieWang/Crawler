#include <string.h>
#include "http.h"

using namespace std;

int Http::parseResHead()
{

}

char* Http::getRequest()
{
	return request;
}

Response* Http::getResponse()
{
	return &response;
}