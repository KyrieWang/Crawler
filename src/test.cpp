#include <iostream>
#include <memory>
#include "confparser.h"

using namespace std;

int main(int argc, char const *argv[])
{
	auto fptr = Confparser::getInstance();
	fptr->Loader("/home/hehe/crawler/test/spider.conf");

	CONF_FILE* conffile_ptr = fptr->getConfFile();

	cout << "jobnum is " << conffile_ptr->job_num << endl;
	cout << "deeps is " << conffile_ptr->deeps << endl;
	cout << "log_level is " << conffile_ptr->log_level << endl;
	cout << "seed is " << conffile_ptr->seed << endl;
	cout << "module_path is " << conffile_ptr->module_path << endl;

	for(auto var : conffile_ptr->module_names)
		cout << "module_names are " << var << endl;

	for(auto var : conffile_ptr->file_types)
		cout << "file_types are " << var << endl;

	return 0;
}