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
#include "page_table_manager.h"
#include <string>

using namespace OSSim;

struct ProcessStats {
	unsigned int job_number;
	long long running_time;
	std::string waiting_time;
	int io_operations;
	unsigned long memory_in_use_at_completion;
	unsigned int my_cpu;
	unsigned int job_size;
	unsigned int page_faults;
	unsigned int io_requests;
	bool on_zero;
	bool on_one;
	bool on_two;
	bool on_three;
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

struct MethodStats run(SORT_METHOD method, int num_cpus);

int main() {
	auto number = run(NUMBER, 1);
	auto priority = run(PRIORITY, 1);
	auto shortest = run(LENGTH, 1);

	std::ofstream priority_file;
	priority_file.open("..\\..\\priority.csv");
	priority_file << "job number,running time,waiting time,io operations,memory in use,cpu #,job size,page faults,io requests,on zero,on one,on two,on three" << std::endl;
	for (auto it = priority.stats.begin(); it != priority.stats.end(); it++) {
		priority_file << it->job_number << "," << it->running_time << "," << it->waiting_time << "," << it->io_operations << "," << it->memory_in_use_at_completion << "," << it->my_cpu << "," << it->job_size << "," << it->page_faults << "," << it->io_requests << "," << it->on_zero << "," << it->on_one << "," << it->on_two << "," << it->on_three << std::endl;
	}
	priority_file.close();
	std::ofstream priority_memory;
	priority_memory.open("..\\..\\mem_priority.txt");
	priority_memory << priority.memory;

	std::ofstream number_file;
	number_file.open("..\\..\\number.csv");
	number_file << "job number,running time,waiting time,io operations,memory in use,cpu #,job size,page faults,io requests,on zero,on one,on two,on three" << std::endl;
	for (auto it = number.stats.begin(); it != number.stats.end(); it++) {
		number_file << it->job_number << "," << it->running_time << "," << it->waiting_time << "," << it->io_operations << "," << it->memory_in_use_at_completion << "," << it->my_cpu << "," << it->job_size << "," << it->page_faults << "," << it->io_requests << "," << it->on_zero << "," << it->on_one << "," << it->on_two << "," << it->on_three << std::endl;
	}
	number_file.close();
	std::ofstream number_memory;
	number_memory.open("..\\..\\mem_number.txt");
	number_memory << number.memory;

	std::ofstream short_file;
	short_file.open("..\\..\\shortest.csv");
	short_file << "job number,running time,waiting time,io operations,memory in use,cpu #,job size,page faults,io requests,on zero,on one,on two,on three" << std::endl;
	for (auto it = shortest.stats.begin(); it != shortest.stats.end(); it++) {
		short_file << it->job_number << "," << it->running_time << "," << it->waiting_time << "," << it->io_operations << "," << it->memory_in_use_at_completion << "," << it->my_cpu << "," << it->job_size << "," << it->page_faults << "," << it->io_requests << "," << it->on_zero << "," << it->on_one << "," << it->on_two << "," << it->on_three << std::endl;
	}
	short_file.close();
	std::ofstream short_memory;
	short_memory.open("..\\..\\mem_short.txt");
	short_memory << shortest.memory;

	auto number_m = run(NUMBER, 4);
	auto priority_m = run(PRIORITY, 4);
	auto shortest_m = run(LENGTH, 4);

	std::ofstream priority_file_m;
	priority_file_m.open("..\\..\\priority_m.csv");
	priority_file_m << "job number,running time,waiting time,io operations,memory in use,cpu #,job size,page faults,io requests,on zero,on one,on two,on three" << std::endl;
	for (auto it = priority_m.stats.begin(); it != priority_m.stats.end(); it++) {
		priority_file_m << it->job_number << "," << it->running_time << "," << it->waiting_time << "," << it->io_operations << "," << it->memory_in_use_at_completion << "," << it->my_cpu << "," << it->job_size << "," << it->page_faults << "," << it->io_requests << "," << it->on_zero << "," << it->on_one << "," << it->on_two << "," << it->on_three << std::endl;
	}
	priority_file_m.close();
	std::ofstream priority_memory_m;
	priority_memory_m.open("..\\..\\mem_priority_m.txt");
	priority_memory_m << priority_m.memory;

	std::ofstream number_file_m;
	number_file_m.open("..\\..\\number_m.csv");
	number_file_m << "job number,running time,waiting time,io operations,memory in use,cpu #,job size,page faults,io requests,on zero,on one,on two,on three" << std::endl;
	for (auto it = number_m.stats.begin(); it != number_m.stats.end(); it++) {
		number_file_m << it->job_number << "," << it->running_time << "," << it->waiting_time << "," << it->io_operations << "," << it->memory_in_use_at_completion << "," << it->my_cpu << "," << it->job_size << "," << it->page_faults << "," << it->io_requests << "," << it->on_zero << "," << it->on_one << "," << it->on_two << "," << it->on_three << std::endl;
	}
	number_file_m.close();
	std::ofstream number_memory_m;
	number_memory_m.open("..\\..\\mem_number_m.txt");
	number_memory_m << number_m.memory;

	std::ofstream short_file_m;
	short_file_m.open("..\\..\\shortest_m.csv");
	short_file_m << "job number,running time,waiting time,io operations,memory in use,cpu #,job size,page faults,io requests,on zero,on one,on two,on three" << std::endl;
	for (auto it = shortest_m.stats.begin(); it != shortest_m.stats.end(); it++) {
		short_file_m << it->job_number << "," << it->running_time << "," << it->waiting_time << "," << it->io_operations << "," << it->memory_in_use_at_completion << "," << it->my_cpu << "," << it->job_size << "," << it->page_faults << "," << it->io_requests << "," << it->on_zero << "," << it->on_one << "," << it->on_two << "," << it->on_three << std::endl;
	}
	short_file_m.close();
	std::ofstream short_memory_m;
	short_memory_m.open("..\\..\\mem_short_m.txt");
	short_memory_m << shortest_m.memory;

	std::cout << "All jobs completed." << std::endl;
}

struct MethodStats run(SORT_METHOD method, int num_cpus) {
	page_table_manager* page_t = new page_table_manager();
	disk* dsk = new disk;
	Memory* ram = new Memory;
	vector<DMA*>* dmas = new vector<DMA*>;
	DMA* dma = new DMA(ram, page_t);
	vector<CPU*>* cpus = new vector<CPU*>;
	loader* load = new loader("./Program-File.txt", dsk);

	for (int i = 0; i < num_cpus; ++i) {
		dmas->push_back(new DMA(ram, page_t));
		cpus->push_back(new CPU(ram, dmas->at(i), i, load));
	}

	long_term_scheduler* lts = new long_term_scheduler(ram, dsk, load, page_t);
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

	short_term_scheduler* sts = new short_term_scheduler(ram, load, cpus, page_t);

	while (load->get_terminated()->size() != 30) {
		lts->schedule();
                for (int i = 0; i < num_cpus; ++i) {
			sts->schedule(i, load);
		}
 
		for (int i = 0; i < num_cpus; ++i) {
			cpus->at(i)->setDone();
			cpus->at(i)->setPC();
		}

		while (load->get_terminated()->size() != 30) {
			lts->schedule();
			for (int i = 0; i < num_cpus; ++i) {
				if (cpus->at(i)->isDone() && load->get_waiting()->size() > 0) {
					sts->schedule(i, load);
				}
				else {
					if (cpus->at(i)->isDone()) {
						cpus->at(i)->setDone();
						cpus->at(i)->setPC();
						sts->schedule(i, load);
						dmas->at(i)->setIO();
					}
				}
				cpus->at(i)->step();
			}
		}
	}

	vector<ProcessStats> process_stats;
	auto terminated = load->get_terminated();
	for (auto it = terminated->begin(); it != terminated->end(); it++) {
		struct ProcessStats pstats {
			(*it)->pc.job_number,
				std::chrono::duration_cast<std::chrono::microseconds>((*it)->end - (*it)->start).count(),
				(*it)->wait,
				(*it)->ios,
				(*it)->total_memory_in_use,
				(*it)->pc.my_cpu,
				(*it)->pc.job_size,
				(*it)->pc.page_faults,
				(*it)->pc.io_requests,
				(*it)->pc.on_zero,
				(*it)->pc.on_one,
				(*it)->pc.on_two,
				(*it)->pc.on_three,
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
