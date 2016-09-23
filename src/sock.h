#ifndef SOCKET_H_
#define SOCKET_H_

#include <socket.h>

class Socket
{
public:
	Socket();
	~Socket();
	
	int build_connect(Url* url);
	int dis_connect(Url* url);
	int send_request();
	int recv_response();
//	int setSocketMod()

private:

private:
	int sock_fd; //句柄
	char* buf;
};

#endif