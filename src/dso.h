#ifndef DSO_H_
#define DSO_H_

#include <iostream>
#include <map>
#include <list>
#include <string>

#define MODULE_OK 0
#define MODULE_ERR 1

#define MAGIC_MAJOR_NUMBER 1
#define MAGIC_MINOR_NUMBER 0

#define STANDARD_MODULE_STUFF MAGIC_MAJOR_NUMBER, \
							  MAGIC_MINOR_NUMBER, \
							  _FILE_

using namespace std;

typedef struct Module
{
	int version;
	int sub_version;
	char* name;
	void (*init)(Module*);
	int (*handle)(void*);	
};

struct htmlParserParam
{
	string url;
	list<string> urls;
};

class DSO_Manager
{
public:
	DSO_Manager();
	~DSO_Manager();

	int load(char* path, char* name);
	Module* getModule(char* name);

private:
	map<string, Module*> modules;
	
};

#endif