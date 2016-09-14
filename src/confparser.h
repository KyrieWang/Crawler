#ifndef CONFPARSER_H_
#define CONFPARSER_H_

#include <string>
#include <memory>
#include <vector>
#include <sstream>

using namespace std;

typedef struct stru_confFile
{
	int job_num; //并发任务数
	int deeps; //抓取深度
	int log_level; //输出日志等级
	string seed; //url种子
	string module_path; //模块存放路径
	vector<string> module_names; //模块名
	vector<string> file_types; //抓取的资源类型
}CONF_FILE;

/*
*配置文件读取模块，单例模式
*/
class Confparser
{
protected:
	string m_Delimiter = "=";
	string m_Comment = "#";
	map<string, string> m_Contents; //存储key和value

public:
	shared_ptr<Confparser> getInstance();

	int Loader(const char* conf_filepath); //读取配置文件
	CONF_FILE* getConfFile();

private:
	template<class T>
	T Read(const string& in_key, const T& in_value) const;

	template<class T>
	T Read_Vec(const string& in_key, const T& vec) const;

	template<class T>
	T String_to_T(const string& str);

	void Trim(string& str); //去掉首尾的空格


private:
	Confparser();

	static shared_ptr<Confparser> self_ptr;

	CONF_FILE conf_file;
};

template<class T>
T Confparser::Read(const string& in_key, const T& in_value) const
{
	map<string, string>::const_iterator mapci = m_Contents.find(in_key);

	if(mapci == m_Contents.end() )
		return in_value;

	return String_to_T<T>(mapci->second);
}

template<class T>
T Confparser::Read_Vec(const string& in_key, const T& vec ) const
{
	map<string, string>::const_iterator mapci = m_Contents.find(in_key);

	string line = mapci->second;
	string in_line;
	string comma = ",";
	
	size_type pos = line.find(comma);
	size_type skip = comma.length();

	if (pos != npos)
	{
		while(pos ！= npos)
		{
			in_line = line.substr(0, pos);
			vec.push_back(in_line);
			line = line.replace(0, pos+skip, "");
			pos = line.find(comma);
		}
		vec.push_back(line);
	}
	else vec.push_back(line);

	return vec;
}

template<class T>
T Confparser::String_to_T(const string& str)
{
	T t;
	istringstream ist(str);
	ist >> t;
	return t;
}

/*
template<class T>
string Confparser::String_to_T<string>(const string& str)
{
	return str;
}
*/

#endif