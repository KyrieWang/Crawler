#ifndef URL_H_
#define URL_H_

#include <string>

using namespace std;

typedef struct stru_url
{
	string url;
	string protocal;
	string sitename;
	string path;
	string filename;
	string filetype;
	int state;
	int deep;
}URL;

class Url
{
public:
	Url(string url_str); 
	~Url();

	int parseUrl(); //解析url，填充url结构

	strut stru_url* getUrlData();

private:
	struct stru_url m_url;
	
};

#endif