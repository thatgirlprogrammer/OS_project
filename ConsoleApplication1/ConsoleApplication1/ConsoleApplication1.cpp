#include <iostream>
#include <string>
#include "general_register.h"
#include "Process.h"
#include <vector>
#include "program_counter.h"
#include "interrupt_register.h"
#include "pcb.h"

using namespace OSSim;

void print() {
	std::cout << "hello" << std::endl;
	std::cout << "terminating";
}

int main() {
	//general_register* reg1 = new general_register(23657);
	//std::cout << reg1->get_content() << std::endl;
	//reg1->set_content(new std::string("65b810aa"));
	//std::cout << reg1->get_content() << std::endl;
	//delete reg1;
	
	//interrupt_register* ir = new interrupt_register();
	//ir->proccess_interrupt(*print);

	struct pcb a;
	a.job_disk_address = 0xfabee954;
	std::cout << std::hex << 0xf * 0xf; //a.job_disk_address;


	//delete ir;
	return 0;
}
