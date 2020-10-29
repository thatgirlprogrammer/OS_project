#pragma once
#include "runnable.h"
#include "instruction.h"
#include "job_numbers.h"

namespace OSSim {
	class job_len : public IRunnable {
	public:
		job_len() {}
		~job_len() {}
		void add_job(PCB_info job);
		void sort();
		void print_compare();
		PCB_info get_pcb(int index) {
			return compare.at(index).get_pcb_info();
		}
		size_t pcb_list_size();
	private:
		std::vector<job_numbers> compare;
	};
}
