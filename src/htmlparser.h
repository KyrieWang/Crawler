#ifndef HTMLPARSER_H_
#define HTMLPARSER_H_

#include <string>

using namespace std;

class HtmlParser
{
public:
	HtmlParser();
	~HtmlParser();

	list<string> getUrls(string page);

private:
	
	
};

#endif