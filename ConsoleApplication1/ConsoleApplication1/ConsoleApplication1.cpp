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
#include "DMA.h"

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
	SORT_METHOD method = PRIORITY;
	disk* dsk = new disk;
	Memory* ram = new Memory;
	DMA* dma = new DMA(ram);
	CPU* cpu = new CPU(ram, dma);
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
		int cycles = 0;
		while (!cpu->isDone()) {
			cpu->step();
			cycles++;
		}
		load->move_terminate(0);
		cout << endl;
	}
	std::cout << "Printing RAM" << std::endl;
	ram->dump();
	std::cout << "I/O operations run " << dma->get_io_number() << std::endl;

	std::cout << "Testing Luke's github thing." << std::endl;

	delete dsk;
	delete load;
	delete ram;
	delete lts;
	return 0;
}
