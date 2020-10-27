#pragma once

#include <string>
#include <fstream>
#include "disk.h"
using namespace OSSim;
using namespace std;
class loader
{
public:
	loader(string file_name);
	void load_file();
private: 
	fstream file;
	disk dsk;
};

