#include <string>
#include "url.h"

using namespace std;

Url::Url()
{
	m_url.state = 0;
	m_url.deep = 0;
}

Url::~Url()
{

}

int Url::initUrl(const string& url_str)
{
	m_url.url = url_str;
	m_url.protocal = url_str.substr(0, url_str.find(":"));

	string::siza_type pos1 = url_str.find("//");
	string tmp1 = url_str.substr(pos+2, url_str.length()-(pos+2));
	m_url.domainName = tmp1.substr(0, tmp1.find_first_of("/"));

	string::siza_type pos2 = tmp1.find_first_of("/");
	string tmp2 = tmp1.substr(pos2, tmp1.length()-pos2;

	string::siza_type pos3 = tmp2.find_last_of("/");
	m_url.path = tmp2.substr(0, pos3);
	m_url.filename = tmp2.substr(pos3+1, tmp2.length()-(pos3+1));
}

URL* Url::getURL()
{
	return &m_url;
}