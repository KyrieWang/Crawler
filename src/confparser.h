#ifndef CONFPARSER_H_
#define CONFPARSER_H_

#include <string>
#include <memory>
#include <vector>
#include <sstream>
#include <map>

typedef struct stru_confFile
{
	int job_num; //并发任务数
	int deeps; //抓取深度
	int log_level; //输出日志等级
	std::string seed; //url种子
	std::string module_path; //模块存放路径
	std::vector<std::string> module_names; //模块名
	std::vector<std::string> file_types; //抓取的资源类型
}CONF_FILE;

/*
*配置文件读取模块，单例模式
*/
class Confparser
{
protected:
	std::string m_Delimiter = "=";
	std::string m_Comment = "#";
	std::map<std::string, std::string> m_Contents; //存储key和value

public:
	static Confparser* getInstance();
	
	int Loader(const char* conf_filepath); //读取配置文件
	CONF_FILE* getConfFile();

private:
	template<class T>
	T Read(const std::string& in_key, T& in_value) const;

	template<class T>
	T Read_Vec(const std::string& in_key, T& vec) const;

	template<class T>
	T String_to_T(const std::string& str) const;

	void Trim(std::string& str); //去掉首尾的空格


private:
	Confparser(){}

	static Confparser *self_ptr;

	CONF_FILE conf_file;
};

template<class T>
T Confparser::Read(const std::string& in_key, T& in_value) const
{
	std::map<std::string, std::string>::const_iterator mapci = m_Contents.find(in_key);

	if(mapci == m_Contents.end() )
		return in_value;

	return String_to_T<T>(mapci->second);
}

template<class T>
T Confparser::Read_Vec(const std::string& in_key, T& vec ) const
{
	std::map<std::string, std::string>::const_iterator mapci = m_Contents.find(in_key);

	std::string line = mapci->second;
	std::string in_line;
	std::string comma = ",";
	
	std::string::size_type pos = line.find(comma);
	std::string::size_type skip = comma.length();

	if (pos != std::string::npos)
	{
		while(pos != std::string::npos)
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
T Confparser::String_to_T(const std::string& str) const
{
	T t;
	std::istringstream ist(str);
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