#ifndef CONFPARSER_H_
#define CONFPARSER_H_

#include <string>
#include <memory>
#include <vector>

using namespace std;

typedef struct stru_confFile
{
	int job_num; //并发任务数
	int deeps; //抓取深度
	int log_level; //输出日志等级
	string seed; //url种子
	string module_path; //模块存放路径
	vector<string> module_name; //模块名
	vector<string> file_type; //抓取的资源类型
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
	CONFFILE* getConfFile();

private:
	template<class T>
	T Read(const string& in_key, const T& in_value) const;

	template<class T>
	T String_to_T(const string& s)const;

	void Trim(string& inout_s); //去掉首尾的空格


private:
	Confparser();

	static shared_ptr<Confparser> self_ptr;

	CONF_FILE conf_file;
};

template<class T>
T Confparser::Read(const string& in_key, const T& in_value)
{

}

template<class T>
T Confparser::String_to_T(const string& s)
{
	
}

#endif