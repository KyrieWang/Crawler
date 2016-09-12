#ifndef CONFPARSER_H_
#define CONFPARSER_H_

#include <string>
#include <memory>
#include <vector>

using namespace std;

struct stru_confFile
{
	int job_num; //并发任务数
	int deeps; //抓取深度
	int log_level; //输出日志等级
	char* seed; //url种子
	char* module_path; //模块存放路径
	vector<string> module_name; //模块名
	vector<string> file_type; //抓取的资源类型
};

/*
*配置文件读取模块
*/
class Confparser
{
public:
	shared_ptr<Confparser> getInstance();

	int loader(const char* conf_filepath); //读取配置文件
	struct stru_confFile* getConfFile();

private:
	Confparser();

	static shared_ptr<Confparser> self_ptr;

	struct stru_confFile conf_file;
};

#endif