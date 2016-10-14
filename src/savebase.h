#ifndef SAVEBASE_H_
#define SAVEBASE_H_

#include <iostream>

using namespace std;

class SaveBase
{
public:
	SaveBase();
	~SaveBase();

	int setFilePathName();
	int save()
	int setFileData(void* data);
	
};

#endif