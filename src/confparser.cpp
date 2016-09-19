#include <memory>
#include <fstream>
#include <string>
#include "confparser.h"

using namespace std;

Confparser* Confparser::self_ptr = nullptr;

Confparser* Confparser::getInstance()
{
	if (self_ptr == NULL)
		self_ptr = new Confparser();
	return self_ptr;
}

int Confparser::Loader(const char* conf_filepath)
{
	const string& delim = m_Delimiter;
	const string& comm = m_Comment;
	const string::size_type skip = delim.length();

	ifstream in(conf_filepath);

	if(!in)
		return 1;

	while(!in.eof())
	{
		string line;
		
		getline(in, line);
		line = line.substr(0, line.find(comm)); //去注释
		string::size_type delim_pos = line.find(delim);

		if (delim_pos != string::npos)
		{
			string key = line.substr(0, delim_pos);
			string value = line.replace(0, delim_pos+skip, "");

			Trim(key);
			Trim(value);

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

	return 0;
}

CONF_FILE* Confparser::getConfFile()
{
	return &conf_file;
}

void Confparser::Trim(string& str)
{
	string space = " ";

	string::size_type begin_pos = str.find_first_not_of(space);
	if(begin_pos != string::npos)
	{
		str.erase(0, begin_pos);
	}

	string::size_type end_pos = str.find_last_not_of(space);
	if(end_pos != string::npos)
	{
		str.erase(str.begin()+end_pos+1, str.end());
	}
}



