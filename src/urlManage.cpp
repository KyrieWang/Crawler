#include <string>
#include <vector>
#include <map>
#include <deque>
#include "urlManage.h"

using namespace std;

UrlManager::urlManage()
{

}

UrlManager::~urlManage()
{

}

int UrlManager::addUrl(const std::string& url_str)
{
	Url url;
	url.parserUrl(url_str);

	m_urls.push_back(url);
	m_urlmap[url_str] = &url;
	m_urldeque.push_back(&url);
}

int UrlManager::addUrlVec(std::vector<Url> url_strs)
{
	for (auto var_url : url_strs)
	{
		m_urls.push_back(var_url);
		m_urlmap[var_url.getUrl().url] = &var_url;
		m_urldeque.push_back(&var_url);
	}
}

Url* UrlManager::getUrlForQuque()
{
	if(!m_urldeque.empty())
		return m_urldeque.front();
	else return nullptr; 
}

int UrlManager::removeUrlForQuque()
{
	if(!m_urldeque.empty())
	{
		m_urldeque.pop_front();
		return 0;
	}
	else return 1;
}

int UrlManager::setUrlState(Url* url_ptr)
{
	
}

Url* UrlManager::findUrl(std::string url_str)
{
	auto url_iter = m_urlmap.find(url_str);

	if(url_iter != m_urlmap.end())
		return url_iter->second;
	else return nullptr;
}