#include "Process.h"

OSSim::Process::Process(int num, std::vector<std::string>* instructions1)
{
	processid = num;
	instructions = instructions1;
}

OSSim::Process::~Process()
{
	delete instructions;
}

void OSSim::Process::display() {
	std::cout << processid << ": " << std::endl;
	for (int i = 0; i < instructions->size(); i++) {
		std::cout << instructions->at(i) << std::endl;
	}
}
