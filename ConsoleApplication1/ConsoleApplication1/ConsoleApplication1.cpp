#include <iostream>
#include <string>
#include <vector>
#include "pcb.h"
#include "Runnable.h"
#include "Instruction.h"
#include "short_term_scheduler.h"
#include "job_number.h"
#include "Disassemble.h"
#include "CPU.h"

using namespace OSSim;

void print(PCB_info info) {
	std::cout << "pcb info:" << std::endl;
	std::cout << "\tnumber: " << info.pc.job_number << std::endl;
	std::cout << "\tpriority: " << info.pc.job_priority << std::endl;
	std::cout << "\tdisk address: " << info.pc.job_disk_address << std::endl;
	std::cout << "\tinstruction count: " << info.pc.job_instruction_count << std::endl;
	std::cout << "\tin memory: " << info.pc.job_in_memory << std::endl;
	std::cout << "\tstatus: " << info.pc.process_status << std::endl;
}

int main() {
	//general_register* reg1 = new general_register(23657);
	//std::cout << reg1->get_content() << std::endl;
	//reg1->set_content(new std::string("65b810aa"));
	//std::cout << reg1->get_content() << std::endl;
	//delete reg1;
	
	//interrupt_register* ir = new interrupt_register();
	//ir->proccess_interrupt(*print);

	IRunnable* j = new job_number();
	PCB_info info;
	std::vector<Instruction> instructions;
	
	uint32_t val = 0x4bd63000;
	instructions.push_back(*(new Instruction(val)));

	short_term_scheduler* schedule = new short_term_scheduler(j);
	schedule->add_job(info, &instructions);
	print(info);

	//delete ir;
	delete schedule;
	schedule = nullptr;

	CPU cpu;
	for (int i = 0; i < 0x17; i++)
		cpu.step();

	return 0;
}
