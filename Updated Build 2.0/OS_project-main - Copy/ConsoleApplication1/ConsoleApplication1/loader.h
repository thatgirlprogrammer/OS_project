#pragma once

#include <string>
#include <fstream>
#include <vector>
#include "disk.h"
#include "pcb.h"

using namespace std;
using namespace OSSim;

class loader
{
public:
	loader(string file_name, disk* d);
	void load_file();
	PCB_info get_info(int index);
private: 
	fstream file;
	disk* dsk;
	vector<PCB_info> collection;
};