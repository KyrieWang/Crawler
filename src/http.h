#ifndef HTTP_H_
#define HTTP_H_

#include <string.h>

typedef struct http_response
{
	ResHead *head_ptr;
	char *content;
	int content_len;
}Response;

typedef struct response_head
{
	char *content_type;
	int status_code;
}ResHead;

class Http
{
public:
	Http();
	~Http();

	int parseResHead();
	int creatReqHead();

	int getUrl(URL* url);
	int getContent(void* buf); //传入预先申请的缓冲区地址

	init();
	re_init();

	int updateUrl(URL* url); //更新HTTP头中的信息

private:
	URL url;
	void* buf;
	char *request;
	Response response;
};

#endif