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
	const size_type skip = delim.length();

	ifstream in(conf_filepath);

	if(in)
		return 1;

	while(!in.eof())
	{
		string line;
		
		getline(in, line);
		line = line.substr(0, line.find(comm)); //去注释
		size_type delim_pos = line.find(delim);

		if (delim_pos != npos)
		{
			string key = line.substr(0, delim_pos);
			string value = line.replace(0, delim_pos+skip, "");

			Trim(key);
			Trim(value)

			m_Contents[key] = value;
		}
	}

	conf_file.job_num = Read("job_num", conf_file.job_num);
	conf_file.deeps = Read("deeps", conf_file.deeps);
	conf_file.log_level = Read("log_level", conf_file.log_level);
	conf_file.seed = Read("seed", conf_file.seed);
	conf_file.module_path = Read("module_path", conf_file.module_path);
	conf_file.module_names = Read_Vec("module_names", conf_file.module_names);
	conf_file.file_types = Read_Vec("file_types", conf_file.file_types);
}

CONF_FILE* Confparser::getConfFile()
{
	return &conf_file;
}

void Confparser::Trim(string& str)
{
	string space = " ";

	size_type begin_pos = str.find_first_not_of(space);
	if (begin_pos != npos)
	{
		str.erase(0, begin_pos);
	}

	size_type end_pos = str.find_last_not_of(space);
	if (end_pos != npos)
	{
		str.erase(str.begin()+end_pos+1, str.end());
	}
}



