#ifndef SOCKET_H_
#define SOCKET_H_

#include <socket.h>

class Socket
{
public:
	Socket();
	~Socket();
	
	int connect(URL* url);
	disconnect();
	request();
	int response();
	setSocketMod();
	void* getData();

private:

private:
	int socketHandle; //句柄
	char* buf;	
};

#endif