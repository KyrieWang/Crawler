#ifndef UMLMANAGER_H_
#define UMLMANAGER_H_

#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <string>
#include "url.h"

using namespace std;

class UrlManager
{
public:
	UrlManager();
	~UrlManager();

	int addUrl(string urlStr); //添加一个全新的URL 加入到list and quque中，同时生存索引
	int addUrlList(list<URL> urlStrs); //批量添加
	URL* getUrlForQuque(); //取一个未处理的URL对象指针
	int removeUrlForQuque(); 
	int setUrlstate(URL* url); //设置URL处理状态

private:
	URL* findUrl(string urlStr);

private:
	list<URL> m_urls; //所有的url
	map<string, URL*> m_urlmap; //所有URL的索引
	queue<URL*> m_urlqueue; //维护等待抓取的URL
};

#endif