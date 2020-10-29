#include <iostream>
#include <string>
#include <vector>
#include "pcb.h"
#include "Runnable.h"
#include "Instruction.h"
#include "short_term_scheduler.h"
#include "job_number.h"
#include "Disassemble.h"
#include "disk.h"
#include "ram.h"
#include "loader.h"
#include "CPU.h"
#include "Memory.h"

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

	disk* dsk = new disk;
	RAM* ram = new RAM;
	Memory* mem = new Memory;
	loader load("./Program-File.txt", dsk);
	load.load_file();

	CPU cpu(mem);
	while (!cpu.isDone())
		cpu.step();

	return 0;
}
