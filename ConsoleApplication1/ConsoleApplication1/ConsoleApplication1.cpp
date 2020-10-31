#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

#include "pcb.h"
#include "Instruction.h"
#include "short_term_scheduler.h"
#include "Disassemble.h"
#include "disk.h"
#include "loader.h"
#include "CPU.h"
#include "Memory.h"
#include "long_term_scheduler.h"
#include "job_priority.h"
#include "job_number.h"
#include "DMA.h"

using namespace OSSim;

struct ProcessStats {
	unsigned int job_number;
	long long running_time;
	long long waiting_time;
	int io_operations;
	unsigned long memory_in_use_at_completion;
};

struct MethodStats {
	vector<struct ProcessStats> stats;
	string memory;
};

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

struct MethodStats run(SORT_METHOD method);

int main() {
	auto priority = run(PRIORITY);
	auto number = run(NUMBER);

	std::ofstream priority_file;
	priority_file.open("..\\..\\priority.csv");
	priority_file << "job number,running time,waiting time,io operations,memory in use" << std::endl;
	for (auto it = priority.stats.begin(); it != priority.stats.end(); it++) {
		priority_file << it->job_number << "," << it->running_time << "," << it->waiting_time << "," << it->io_operations << "," << it->memory_in_use_at_completion << std::endl;
	}
	priority_file.close();
	std::ofstream priority_memory;
	priority_memory.open("..\\..\\mem_priority.txt");
	priority_memory << priority.memory;

	std::ofstream number_file;
	number_file.open("..\\..\\number.csv");
	number_file << "job number,running time,waiting time,io operations,memory in use" << std::endl;
	for (auto it = number.stats.begin(); it != number.stats.end(); it++) {
		number_file << it->job_number << "," << it->running_time << "," << it->waiting_time << "," << it->io_operations << "," << it->memory_in_use_at_completion << std::endl;
	}
	number_file.close();
	std::ofstream number_memory;
	number_memory.open("..\\..\\mem_number.txt");
	number_memory << number.memory;
}

struct MethodStats run(SORT_METHOD method) {
	disk* dsk = new disk;
	Memory* ram = new Memory;
	DMA* dma = new DMA(ram);
	//CPU* cpu = new CPU(ram, dma);
	vector<CPU*>* cpus = new vector<CPU*>;

	for (int i = 0; i < 1; ++i) {
		cpus->push_back(new CPU(ram, dma));
	}
	
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
	short_term_scheduler* sts = new short_term_scheduler(ram, load, cpus);

	for (int i = 0; i < 2048; ++i) {
		std::cout << dsk->read(i) << "\n";
	}

	while (!sts->isDone()) {
		lts->schedule();
		sts->schedule();
		cpus->at(0)->setDone();
		cpus->at(0)->setPC();
		int cycles = 0;
		while (!cpus->at(0)->isDone()) {
			cpus->at(0)->step();
			cycles++;
		}
		load->get_running()->at(0)->ios = dma->get_io_number();
		load->get_running()->at(0)->total_memory_in_use = ram->in_use;
		dma->setIO();
		load->move_terminate(0);
		cout << endl;
	}
	std::cout << "Printing RAM" << std::endl;
	std::stringstream builder;
	std::cout << "I/O operations run " << dma->get_io_number() << std::endl;

	vector<ProcessStats> process_stats;

	auto terminated = load->get_terminated();
	for (auto it = terminated->begin(); it != terminated->end(); it++) {
		struct ProcessStats pstats {
			(*it)->pc.job_number,
				std::chrono::duration_cast<std::chrono::microseconds>((*it)->end - (*it)->start).count(),
				std::chrono::duration_cast<std::chrono::microseconds>((*it)->start - (*it)->enter_new).count(),
				(*it)->ios,
				(*it)->total_memory_in_use,
		};
		process_stats.push_back(pstats);
	}

	struct MethodStats stats = {
		process_stats,
		ram->dump(),
	};

	delete dsk;
	delete load;
	delete ram;
	delete lts;

	return stats;
}