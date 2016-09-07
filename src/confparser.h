#ifndef CONFPARSER_H_
#define CONFPARSER_H_

#include <string>
#include <memory>
#include <vector>

using namespace std;

class Confparser
{
public:
	shared_ptr<Confparser> getInstance();

	int loader(const char* conf_filepath);
	int getJobNum();
	int getDeep();
	int getLogLevel();
	char getUrlSeed();
	char* getModulePath();
	vector<string> getModules();
	vector<string> getFileTypes();

private:
	Confparser();

	static shared_ptr<Confparser> self_ptr;

	int job_num;
	int deeps;
	int log_level;
	char* seed;
	char* module_path;
	vector<string> module_name;
	vector<string> file_type;
};

#endif