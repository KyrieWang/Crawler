#ifndef URL_H_
#define URL_H_

#include <string>

using namespace std;

typedef struct stru_url
{
	string url; //完整的url
	string protocal; //协议类型
	string sitename; //域名
	string path; //资源路径
	string filename; //文件名
	string filetype; //当前资源类型
	int state; //当前url处理状态
	int deep; //当前url深度
}URL;

class Url
{
public:
	Url(); 
	~Url();

	int parseUrl(string url_str); //解析url，填充url结构

	strut stru_url* getUrlData();

private:
	struct stru_url m_url;
	
};

#endif