#ifndef HTTP_H_
#define HTTP_H_

#include <string>

using namespace std;

class Http
{
public:
	Http();
	~Http();

	int parseHead();
	int creatHead();

	int getUrl(URL* url);

private:
	
};

#endif