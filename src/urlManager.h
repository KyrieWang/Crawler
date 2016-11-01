#ifndef UMLMANAGER_H_
#define UMLMANAGER_H_

#include <iostream>
#include <map>
#include <deque>
#include <string>

/*url结构体*/
typedef struct stru_url
{
	std::string url; //完整的url
	std::string protocal; //协议类型
	std::string domainName; //域名
	std::string path; //资源路径
	std::string ip; //IP
	int port; //端口
	int state; //当前url处理状态
	int deep; //当前url深度
}Url;

class UrlManager
{
public:
	UrlManager();
	~UrlManager();

	int addUrl(const std::string& url_str); //添加一个全新的URL到原始队列
	int addUrls(const std::vector<std::string>& url_strs); //批量添加到原始队列
	int parserUrl(); //域名解析，添加到dns解析后的url队列
	bool UrlManager::is_parse_urldeq_empty();
	Url* getUrlForParseDeque(); //从解析后的url队列取出url	

private:
	static void dns_callback(int result, char type, int count, int ttl,void *addresses, void *arg); //dns解析回调函数
	void initUrl(const std::string& url_str, Url& m_url); //填充url结构
	bool UrlManager::is_src_urldeq_empty();

private:
	static std::deque<Url*> src_urldeq; //原始url队列
	static std::map<std::string, std::string> host_ip_map; //保存域名解析前后的url的主机名称和IP地址
	static std::deque<Url*> parse_urldeq; //dns解析后的url队列
};

#endif