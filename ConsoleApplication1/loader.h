#pragma once

#include <string>
#include <fstream>
#include "disk.h"
#include "pcb.h"

using namespace std;
using namespace OSSim;

class loader
{
public:
	loader(string file_name);
	void load_file();
	PCB_info get_info();
private: 
	fstream file;
	disk dsk;
	PCB_info info;
};
