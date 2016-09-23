#include <socket.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <string>
#include "sock.h"

using namespace std;

Socket::Socket()
{

}

Socket::~Socket()
{

}

int Socket::build_connect(URL* url)
{
	const char *ip = (url->ip).c_str();
	int port = url->port;
	
	struct sockaddr_in serv_addr;
	bzero(&serv_addr, sizeof(struct sockaddr_in));

	serv_addr.sin_family = AF_NET; //ipv4地址
	serv_addr.sin_port = htons(port);

	if (!inet_aton(ip, &(serv_addr.sin_addr)))
	{
		return -1;
	}

	if ((sock_fd = socket(AF_NET, SOCK_STREAM|SOCK_NOBLOCK|SOCK_CLOEXEC, 0)) < 0)
	{
		return -1;
	}

	if (connect(sock_fd, (struct sockaddr *)&serv_addr, sizeof(struct sockaddr_in)) < 0)
	{
		close(sock_fd);
		return -1;
	}

	cout << "建立连接成功：" << ip << endl;
	return 0;
}

int Socket::dis_connect()
{
	close(sock_fd);
}

int Socket::send_request(Url* url)
{
	int need, begin, n;
	char response[1024] = {0};
	
	sprintf(request, "GET /%s HTTP/1.0\r\n"
					"Host: %s\r\n"
					"Accept: */*\r\n"
					"Connection: Keep-Alive\r\n"
					"User-Agent: Mozilla/5.0 (compatible)\r\n"
					"Referer: %s\r\n\r\n", url->path, url->domainName, url->domainName);

	cout << "send the request domain name" << url->domainName << endl;

	need = strlen(request);
	begin = 0;

	//send requests to server
	while(need)
	{
		n = write(sock_fd, request+begin, need);
		if (n <= 0)
		{
			if (errno == EAGAIN)
			{
				usleep(1000);
				continue;
			}

			cout << "send failed!" << endl;
			close(sock_fd);
			return -1;
		}
		begin += n; //起始点偏移
		need -= n; //直到发送完成
	}
	return 0;
}

int Socket::recv_response()
{
	int state = 0, trunc_head = 0, len = 0;

	buf = (char*)malloc(1024*1024);

	while(1)
	{
		state = read(sock_fd, buf+len, 1024);

		if (state < 0)
		{
			if (errno == EAGAIN || errno == EWOULDBLOCK || errno == EINTR)
			{
				usleep(100000);
				continue;
			}
		}
		else if (state == 0)
		{
			
		}
		else
		{
			len += state;
			buf[len] = '\0';

			if (!trunc_head)
			{
				
			}
		}
	}
}