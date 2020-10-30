#include <iostream>
#include <string>
#include <vector>
#include "pcb.h"
#include "Instruction.h"
#include "short_term_scheduler.h"
#include "Disassemble.h"
#include "disk.h"
#include "loader.h"
#include "CPU.h"
#include "Memory.h"
#include "long_term_scheduler.h"
#include <algorithm>
#include "job_priority.h"
#include "job_number.h"

using namespace OSSim;

enum SORT_METHOD { NUMBER, PRIORITY, LENGTH };

void print(PCB_info* info) {
	std::cout << "pcb info:" << std::endl;
	std::cout << "\tnumber: " << info->pc.job_number << std::endl;
	std::cout << "\tpriority: " << info->pc.job_priority << std::endl;
	std::cout << "\tdisk address: " << info->pc.job_disk_address << std::endl;
	std::cout << "\tinstruction count: " << info->pc.job_instruction_count << std::endl;
	std::cout << "\tin memory: " << info->pc.job_in_memory << std::endl;
	std::cout << "\tstatus: " << info->pc.process_status << std::endl;
	std::cout << "\tsize: " << info->pc.job_size << std::endl;
}

int main() {
	std::vector<Instruction> instructions;	
	uint32_t val = 0x4bd63000;
	instructions.push_back(*(new Instruction(val)));

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

	SORT_METHOD method = PRIORITY;
	disk* dsk = new disk;
	Memory* ram = new Memory;
	CPU* cpu = new CPU(ram);
	loader* load = new loader("./Program-File.txt", dsk);
	long_term_scheduler* lts = new long_term_scheduler(ram, dsk, load);
	load->load_file();
	
	vector<PCB_info> v;

	switch (method) {
	case SORT_METHOD::PRIORITY: {
		job_priority j;
		for (int i = 0; i < load->get_new_q()->size(); i++)
			j.add_job(*load->get_new_q()->at(i));
		j.sort();

		for (int i = 0; i < load->get_new_q()->size(); i++) {
			v.push_back(j.get_pcb(i));
		}
		load->get_new_q()->clear();
		for (int i = 0; i < v.size(); i++) {
			load->get_new_q()->push_back(&v.at(i));
		}
	} break;
	case SORT_METHOD::LENGTH: {
		job_len j;
		for (int i = 0; i < load->get_new_q()->size(); i++) {
			j.add_job(*load->get_new_q()->at(i));
		}
		j.sort();

		for (int i = 0; i < load->get_new_q()->size(); i++) {
			v.push_back(j.get_pcb(i));
		}
		load->get_new_q()->clear();
		for (int i = 0; i < v.size(); i++) {
			load->get_new_q()->push_back(&v.at(i));
		}
	} break;
	default:
		break;
	}
	
	for (int i = 0; i < load->get_ready()->size(); i++)
		print(load->get_ready()->at(i));
	short_term_scheduler* sts = new short_term_scheduler(ram, load, cpu);
	
	for (int i = 0; i < 2048; ++i) {
		std::cout << dsk->read(i) << "\n";
	}
	
	while (!sts->isDone()) {
		lts->schedule();
		sts->schedule();
		cpu->setDone();
		cpu->setPC();
		while (!cpu->isDone()) {
			cpu->step();
		}
		load->move_terminate(0);
		cout << endl;
	}
	
	std::cout << "Printing RAM" << std::endl;
	ram->dump();

	delete dsk;
	delete load;
	delete ram;
	delete lts;
	return 0;
}
