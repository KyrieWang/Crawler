#ifndef UMLMANAGER_H_
#define UMLMANAGER_H_

#include <iostream>
#include <list>
#include <map>
#include <deque>
#include <string>
#include "url.h"

class UrlManager
{
public:
	UrlManager();
	~UrlManager();

	int addUrl(const std::string& url_str); //添加一个全新的URL 加入到vector and deque中，同时生存索引
	int addUrlVec(std::vector<Url> url_strs); //批量添加
	Url* getUrlForDeque(); //取一个未处理的Url对象指针
	int removeUrlForDeque(); //成功返回0，失败返回1
	int setUrlState(Url* url_ptr); //设置URL处理状态

private:
	Url* findUrl(std::string url_str);

private:
	std::vector<Url> m_urlvec; //url库
	std::map<std::string, Url*> m_urlmap; //所有URL的索引
	std::deque<Url*> m_urldeque; //维护等待抓取的URL
};

#endif