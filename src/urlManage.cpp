#include <string>
#include <vector>
#include <map>
#include <deque>
#include <arpa/inet.h>
#include <event2/evdns.h>
#include <event2/util.h>
#include <event2/event.h>
#include "urlManage.h"

using namespace std;

UrlManager::urlManage()
{

}

UrlManager::~urlManage()
{

}

deque<Url> UrlManager::src_urldeq;
map<std::string, std::string> UrlManager::host_ip_map;
deque<Url> UrlManager::parse_urldeq;

int UrlManager::addUrl(const std::string& url_str)
{
	shared_ptr<Url> url_ptr = make_shared<Url>();
	
	initUrl(url_str, *url_ptr);

	src_urldeq.push_back(url_ptr);

	return 0;
}

int UrlManager::addUrls(const std::vector<std::string>& url_strs)
{
	for (auto str : url_strs)
	{
		addUrl(str);
	}

	return 0;
}

Url* UrlManager::getUrlForParseDeque()
{	
	Url *url_ptr = nullptr;

	if(!parse_urldeq.empty())
	{
		url_ptr = parse_urldeq.front();
		parse_urldeq.pop_front();
	}
	
	return url_ptr;
}

/*
int UrlManager::removeUrlForQuque(std::deque<Url>& url_deque)
{
	if(!url_deque.empty())
	{
		url_deque.pop_front();
		return 0;
	}
	else return 1;
}
*/
/*
int UrlManager::setUrlState(Url* url_ptr)
{

}
*/

int UrlManager::parserUrl()
{
	Url *url_ptr = nullptr;
	map<string,string>::const.iterator ip_iter;

	while(1)
	{
		url_ptr = src_urldeq.front();
		src_urldeq.pop_front();

		ip_iter = host_ip_map.find(url_ptr->domainName);

		if (ip_iter == host_ip_map.end())
		{
		/*dns解析*/
			event_base *base = event_init();
			evdns_init();
			evdns_resolve_ipv4(url_ptr->domainName, 0, dns_callback, url_ptr);
			event_dispatch();
			event_base_free();
		}
		else
		{
			url_ptr->ip = ip_iter->second;
			parse_urldeq.push_back(url_ptr);
		}
	}
}

void UrlManager::initUrl(const std::string& url_str， Url& m_url)
{
	m_url.state = 0;
	m_url.deep = 0;

	m_url.url = url_str;
	m_url.protocal = url_str.substr(0, url_str.find_first_of(":")); //协议

	string::size_type pos1 = url_str.find("//");
	string tmp1 = url_str.substr(pos1+2, url_str.length()-(pos1+2));
	string::size_type pos2 = tmp1.find_first_of("/");
	string tmp2 = tmp1.substr(0, pos2);

	string::size_type pos3 = tmp2.find(":");
	if (pos3 != string::npos)
	{
		m_url.domainName = tmp2.substr(0, pos3); //域名
		m_url.port = tmp2.substr(pos3, tmp2.length()-pos3); //端口
	}
	else
	{
		m_url.domainName = tmp2;
		m_url.port = 80;
	}
	
	m_url.path = tmp1.substr(pos2, tmp1.length()-pos2); //资源路径
}

void UrlManager::dns_callback(int result, char type, int count, int ttl, void *addresses, void *arg)
{
	Url *url_ptr = (Url*)arg;
	struct in_addr *addrs = (in_addr*)addresses;

	if (result != DNS_ERR_NONE || count == 0)
	{
		cout << "dns resolve failed:" << url_ptr->domainName << endl;
	}
	else
	{
		char *ip_addr = inet_ntoa(addrs[0]);
		cout << "dns resolve ok:" << url_ptr->domainName << ip_addr << endl;
		
		host_ip_map[url_ptr->domainName] = strdup(ip_addr);
		url_ptr->ip = strdup(ip_addr)
		parse_urldeq.push_back(url_ptr);
	}

	event_loopexit(NULL);
}

/*
string* UrlManager::findIp(const std::string& host_str)
{
	auto ip_iter = host_ip_map.find(host_str);
	string *ip = nullptr;

	if(ip_iter != host_ip_map.end())
		ip = &(ip_iter->second);
	
	return ip;
}
*/