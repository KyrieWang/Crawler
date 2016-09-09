#ifndef UMLMANAGER_H_
#define UMLMANAGER_H_

#include <iostream>
#include <list>
#include <map>
#include <string>

using namespace std;

class UrlManager
{
public:
	UrlManager();
	~UrlManager();

	addUrl();
	saddUrlList();
	getUrlForQuque();
	removeUrlForQuque();
	setUrlValue();

private:
	findUrl();

private:
	list<Url> Urls;
	map<string, Url*> UrlMap;
	quque<Url*> UrlQuque;
};

#endif