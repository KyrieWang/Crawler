#ifndef SOCKET_H_
#define SOCKET_H_

#include <socket.h>
#include "http.h"

class Socket
{
public:
	Socket();
	~Socket();
	
	int build_connect(Url* url);
	int dis_connect();
	int send_request(Url* url);
	int parse_response(Response* resp_ptr);
//	int setSocketMod()

private:

private:
	int sock_fd; //句柄
//	Http m_http;
	char* buf;
};

#endif