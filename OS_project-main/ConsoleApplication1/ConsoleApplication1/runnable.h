#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include "pcb.h"
#include "job_priority_compare.h"
#include "job_numbers.h"
#include "Instruction.h"

namespace OSSim {
	__interface IRunnable {
	public:
		void sort();
		void print_compare();
		void add_job(PCB_info info, std::vector<Instruction>* lst);
		PCB_info get_pcb(int index);
		std::size_t pcb_list_size();
		void run_job();
	};
}
