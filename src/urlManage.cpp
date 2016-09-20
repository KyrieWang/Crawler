#include <string>
#include <vector>
#include <map>
#include <deque>
#include <event2/dns.h>
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
	Url url;
	url.initUrl(url_str);

	src_urldeq.push_back(&url);

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
	Url *Url_ptr = nullptr;
	URL *URL_ptr = nullptr;
	map<string,string>::const.iterator ip_iter;

	Url_ptr = src_urldeq.front();
	src_urldeq.pop_front();

	URL_ptr = Url_ptr->getURL();
	ip_iter = host_ip_map.find(URL_ptr->domainName);

	if (ip_iter == host_ip_map.end())
	{
		/*dns解析*/
	}
	else
	{
		URL_ptr->ip = ip_iter->second;
		parse_urldeq.push_back(Url_ptr);
	}
}

void UrlManager::dns_callback(int result, char type, int count, int ttl,void *addresses, void *arg)
{
	
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