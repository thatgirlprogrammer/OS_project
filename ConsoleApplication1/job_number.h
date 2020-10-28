#pragma once
#include "runnable.h"
#include "instruction.h"

namespace OSSim {
	class job_number : public IRunnable {
	public:
		job_number() {}
		~job_number() {}
		void add_job(PCB_info job, std::vector<Instruction>* lst);
		void sort();
		void print_compare();
		PCB_info get_pcb(int index) {
			return compare.at(index).get_pcb_info();
		}
		size_t pcb_list_size();
		void run_job() {
			compare.at(0).decode_istructions();
			compare.at(0).execute_instrustions();
			compare.erase(compare.begin());
		}
	private:
		std::vector<job_numbers> compare;
	};
}
