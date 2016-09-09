#ifndef DSO_H_
#define DSO_H_

#include <iostream>
#include <map>
#include <string>

#define MODULE_OK 0
#define MODULE_ERR 1

#define MODULE_MAJOR_VERSION 1
#define MODULE_SUB_VERSION 0

using namespace std;

typedef struct Module
{
	int version;
	int sub_version;
	char* name;
	void (*init)(Module*);
	int (*handle)(void*);	
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