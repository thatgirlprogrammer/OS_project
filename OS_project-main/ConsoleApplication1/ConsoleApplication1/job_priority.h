#pragma once
#include "runnable.h"
#include "pcb.h"
#include "Instruction.h"

namespace OSSim {
	class job_priority : public IRunnable {
	public:
		job_priority() {}

		void add_job(PCB_info job, std::vector<Instruction>* lst) {
			priorities* jc1 = new priorities(job, lst);
			compare.push_back(*(jc1));
		}

		void sort() {
			std::sort(compare.begin(), compare.end());
		}

		void print_compare() {
			for (int i = 0; i < compare.size(); i++) {
				auto val = compare.at(i);
				std::cout << "job priority " << val.get_pcb_info().pc.job_priority << std::endl;
			}
		}

		PCB_info get_pcb(int index) {
			compare.at(index).get_pcb_info();
		}

		std::size_t pcb_list_size() {
			return compare.size();
		}

		void run_job() {
			compare.at(0).decode_istructions();
			compare.at(0).execute_instrustions();
			compare.erase(compare.begin());
		}
	private:
		std::vector<priorities> compare;
	};
}