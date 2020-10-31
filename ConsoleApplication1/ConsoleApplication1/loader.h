#pragma once

#include <string>
#include <fstream>
#include <vector>
#include "disk.h"
#include "pcb.h"
#include <mutex>

using namespace std;
using namespace OSSim;

class loader
{
public:
	loader(string file_name, disk* d);
	void load_file();
	void move_new_ready(int index);
	void move_running(int index);
	void move_waiting_ready(int index);
	void move_waiting(int index);
	void move_terminate(int index);
	void add_terminate(PCB_info* process);

	vector<PCB_info*>* get_new_q() { return new_q; }
	vector<PCB_info*>* get_ready() { return ready; }
	vector<PCB_info*>* get_running() { return running; }
	vector<PCB_info*>* get_waiting() { return waiting; }
	vector<PCB_info*>* get_terminated() { return terminated; }
private: 
	fstream file;
	disk* dsk;
	std::mutex mtx;
	vector<PCB_info*>* new_q;
	vector<PCB_info*>* ready;
	vector<PCB_info*>* running;
	vector<PCB_info*>* waiting;
	vector<PCB_info*>* terminated;
};
