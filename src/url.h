#ifndef URL_H_
#define URL_H_

#include <string>

typedef struct stru_url
{
	std::string url; //完整的url
	std::string protocal; //协议类型
	std::string domainName; //域名
	std::string path; //资源路径
	std::string filename; //文件名
	//std::string filetype; //当前资源类型
	int state; //当前url处理状态
	int deep; //当前url深度
}URL;

class Url
{
public:
	Url();
	~Url();

	int parserUrl(const std::string& url_str); //解析url，填充url结构

	URL* getUrl();

private:
	URL m_url;
	
};

#endif