#include <socket.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stddef.h>
#include <errno.h>
#include <unistd.h>
#include <string>
#include <regex>
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
	char request[1024] = {0};
	
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

int Socket::recv_response(UrlManager url_mang)
{
	int trunc_head = 0, state = 0; 
	size_t len = 0;
	char *cont_ptr = nullptr;
	Response *res_ptr = (Response *)malloc(sizeof(Response));
	res_ptr->head_ptr = nullptr;
	res_ptr->content = (char *)malloc(1024*1024);
	res_ptr->cont_len = 0;
	
	while(1)
	{
		state = read(sock_fd, res_ptr->content+len, 1024);

		if (state < 0)
		{
			if (errno == EAGAIN || errno == EWOULDBLOCK || errno == EINTR)
			{
				usleep(100000);
				continue;
			}
		}
		else if (state == 0) //数据读完
		{
			res_ptr->cont_len = len;

			if (res_ptr->cont_len > 0)
			{
				//匹配正则表达式，提取url
				parse_content(url_mang, res_ptr);
				save_content(res_ptr);
			}
		}
		else
		{
			len += state; //更新已经读取的长度
			res_ptr->content[len] = '\0';

			if (!trunc_head) //未截去头部
			{
				if ((cont_ptr = strstr(res_ptr->content, "\r\n\r\n")) != nullptr)
				{
					*(cont_ptr + 2) = '\0';
					res_ptr->head_ptr = parse_head(res_ptr->content);
					
					if (res_ptr->head_ptr->sta_code != 200 && res_ptr->head_ptr->sta_code != 202) //模块检测
					{
						/*添加日志信息*/

						break;
					}

					trunc_head = 1;

					cont_ptr += 4;
					strcpy(res_ptr->content, cont_ptr);
					len = strlen(res_ptr->content);
				}
				continue;
			}
		}
	}

	close(sock_fd);
	free(res_ptr->head_ptr);
	free(res_ptr->content);
	free(res_ptr);
}

int Socket::save_content(Response *resp)
{

}

ResHead* Socket::parse_head(char *head)
{
	ResHead *h_ptr = (ResHead *)calloc(1, sizeof(ResHead));
	string tmp(head);
	
	string::size_type pos1 = tmp.find_first_of("\r\n");
	if (pos1 != string::npos)
	{
		string tmp1 = tmp.substr(0, pos1);
		string state_code = tmp1.substr(tmp1.find_first_of(" ")+1, tmp1.find_last_of(" "));
		h_ptr->sta_code = atoi(state_code.c_str());
	}

	string::size_type pos2 = tmp.find("Content-Type");
	if (pos2 != string::npos)
	{
		string tmp2 = tmp.substr(pos2, tmp.length()-pos2);
		string::size_type pos3 = tmp2.find_first_of(":");
		string c_type = tmp2.substr(pos3+1, tmp2.find_first_of(";")-pos3);
		h_ptr->cont_type = c_type.c_str();
	}

	return h_ptr;
}

int Socket::parse_content(UrlManager url_mang, Response *resp)
{
	string html_str(resp->content);
	string url_pattern("href=\"\\s*\\([^ >\"]*\\)\\s*\"");

	try
	{
		regex url_regex(url_pattern);

		for (sregex_iterator it(begin(html_str), end(html_str), url_regex), end_it; it != end_it; it++)
		{
			string url_str = it->str();
			string::size_type pos = url_str.find_first_of("=") + 2;
			url_str = url_str.substr(pos, url_str.length()-pos-1);

			url_mang.addUrl(url_str); //是否需要考虑线程安全？？？
		}
	}
	catch(regex_error e)
	{
		cout<<e.what()<<'\t'<<e.code()<<endl;
	}
}