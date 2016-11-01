#ifndef SOCKET_H_
#define SOCKET_H_

#include <socket.h>
#include <stddef.h>

/*http响应*/
typedef struct http_response
{
	ResHead *head_ptr;
	char *content;
	size_t cont_len;
}Response;

/*http响应头*/
typedef struct response_head
{
	char *cont_type;
	int sta_code;
}ResHead;

class Socket
{
public:
	Socket();
	~Socket();
	
	int build_connect(Url* url);
	int dis_connect();
	int send_request(Url* url);
	int recv_response(UrlManager url_mang);
	int getSockfd();

private:
	int save_content(Response *resp);
	ResHead* parse_head(char *head);
	int parse_content(UrlManager url_mang, Response *resp);

private:
	int sock_fd; //句柄
};

#endif