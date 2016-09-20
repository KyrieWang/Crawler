#ifndef UMLMANAGER_H_
#define UMLMANAGER_H_

#include <iostream>
#include <map>
#include <deque>
#include <string>
#include "url.h"

class UrlManager
{
public:
	UrlManager();
	~UrlManager();

	int addUrl(const std::string& url_str); //添加一个全新的URL到原始队列
	int addUrls(const std::vector<std::string>& url_strs); //批量添加到原始队列
	Url* getUrlForParseDeque(); //从解析后的url队列取出url
//	int removeUrlForDeque(std::deque<Url>& url_deque); //成功返回0，失败返回1
	int parserUrl(); //域名解析，添加到dns解析后的url队列
//	int setUrlState(Url* url_ptr); //设置URL处理状态

private:
	static void dns_callback(int result, char type, int count, int ttl,void *addresses, void *arg); //dns解析回调函数
//	string* findIp(const std::string& host_str); //根据域名查找ip

private:
	static std::deque<Url*> src_urldeq; //原始url队列
	static std::map<std::string, std::string> host_ip_map; //保存域名解析前后的url的主机名称和IP地址
	static std::deque<Url*> parse_urldeq; //dns解析后的url队列
};

#endif