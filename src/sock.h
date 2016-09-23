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
	int dis_connect(Url* url);
	int send_request(Url* url);
	int recv_response();
//	int setSocketMod()

private:

private:
	int sock_fd; //句柄
	Http http;
	char* buf;
};

#endif