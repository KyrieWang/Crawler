#include <memory>
#include <fstream>
#include <string>
#include "confparser.h"

using namespace std;

Confparser::Confparser(){

}

shared_ptr<Confparser> Confparser::getInstance()
{
	if (self_ptr == NULL)
		self_ptr = make_shared<Confparser>();
	return self_ptr;
}

int Confparser::loader(const string& conf_filepath)
{
	const string& delim = m_Delimiter;
	const string& comm = m_Comment;

	ifstream in(conf_filepath);

	if(in)
		return 1;

	while(!in.eof())
	{
		string line;
		
		getline(in, line);
		line = line.substr(0, line.find(comm));
		size_type delim_pos = line.find(delim);

		if (pos != npos)
		{
			string key = line.substr(0, delim_pos);
		}
	}
}

CONF_FILE* Confparser::getConfFile()
{
	return &conf_file;
}

void Confparser::Trim()
{

}



