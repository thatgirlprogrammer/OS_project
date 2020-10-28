#include <iostream>
#include <string>
#include <vector>
#include "pcb.h"
#include "Runnable.h"
#include "Instruction.h"
//#include "short_term_scheduler.h"
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
	std::cout << "\tstatus: " << info.pc.program_counter << std::endl;
	
	std::cout << "\nBuffer" << std::endl;
	std::cout << "\tinput buffer" << info.b.input_buffer << std::endl;
	std::cout << "\toutput buffer" << info.b.output_buffer << std::endl;
	std::cout << "\ttemp buffer" << info.b.temp_buffer << std::endl;
}

int main() {
	//general_register* reg1 = new general_register(23657);
	//std::cout << reg1->get_content() << std::endl;
	//reg1->set_content(new std::string("65b810aa"));
	//std::cout << reg1->get_content() << std::endl;
	//delete reg1;

	//interrupt_register* ir = new interrupt_register();
	//ir->proccess_interrupt(*print);

	PCB_info info;


	//short_term_scheduler* schedule = new short_term_scheduler();
	print(info);

	//delete ir;
	//delete schedule;
	//schedule = nullptr;

	//	std::vector<Instruction> i;
	//	i.push_back(Instruction(0xC0500070));
	//	i.push_back(Instruction(0x4B060000));
	//	i.push_back(Instruction(0x4B010000));
	//	i.push_back(Instruction(0x4B000000));
	//	i.push_back(Instruction(0x4F0A0070));
	//	i.push_back(Instruction(0x4F0D00F0));
	//	i.push_back(Instruction(0x4C0A0004));
	//	i.push_back(Instruction(0xC0BA0000));
	//	i.push_back(Instruction(0x42BD0000));
	//	i.push_back(Instruction(0x4C0D0004));
	//	i.push_back(Instruction(0x4C060001));
	//	i.push_back(Instruction(0x10658000));
	//	i.push_back(Instruction(0x56810018));
	//	i.push_back(Instruction(0x4B060000));
	//	i.push_back(Instruction(0x4F0900F0));
	//	i.push_back(Instruction(0x43900000));
	//	i.push_back(Instruction(0x4C060001));
	//	i.push_back(Instruction(0x4C090004));
	//	i.push_back(Instruction(0x43920000));
	//	i.push_back(Instruction(0x4C060001));
	//	i.push_back(Instruction(0x4C090004));
	//	i.push_back(Instruction(0x10028000));
	//	i.push_back(Instruction(0x55810060));
	//	i.push_back(Instruction(0x04020000));
	//	i.push_back(Instruction(0x10658000));
	//	i.push_back(Instruction(0x56810048));
	//	i.push_back(Instruction(0xC10000C0));
	//	i.push_back(Instruction(0x92000000));
	//	disassemble(i);

	CPU cpu;
	while (!cpu.isDone())
		cpu.step();

	return 0;
}