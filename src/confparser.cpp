#include <memory>
#include "confparser.h"

using namespace std;

Confparser::Confparser(){

}

shared_ptr<Confparser> Confparser::getInstance(){
	if (self_ptr == NULL)
		self_ptr = make_shared<Confparser>();
	return self_ptr;
}

int Confparser::loader(char* conf_filepath){

}

int Confparser::getJobNum(){

}

int Confparser::getDeep(){

}

int Confparser::getLogLevel(){

}

char Confparser::getUrlSeed(){

}

char* Confparser::getModulePath(){

}

vector<string> Confparser::getModules(){

}

vector<string> Confparser::getFileTypes(){

}