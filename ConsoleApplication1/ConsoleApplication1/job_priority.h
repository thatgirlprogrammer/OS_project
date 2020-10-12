#pragma once
#include "runnable.h"
#include "pcb.h"

namespace OSSim {
	class job_priority : public IRunnable {
	public:
		job_priority() {}

		void add_job(int priority) {
			PCB_info pi2;
			pi2.pc.job_priority = priority;
			job_priority_compare* jc1 = new job_priority_compare(pi2);
			compare.push_back(*(jc1));
		}

		void run() {
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

		int pcb_list_size() {
			return compare.size();
		}
	private:
		std::vector<job_priority_compare> compare;
	};
}