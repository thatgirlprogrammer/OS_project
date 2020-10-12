#pragma once
#include "runnable.h"

namespace OSSim {
	class job_number : public IRunnable {
	public:
		job_number() {}

		void add_job(PCB_info job) {
			job_number_compare* jc1 = new job_number_compare(job);
			compare.push_back(*(jc1));
		}

		void run() {
			std::sort(compare.begin(), compare.end());
		}

		void print_compare() {
			for (int i = 0; i < compare.size(); i++) {
				auto val = compare.at(i);
				std::cout << "job number " << val.get_pcb_info().pc.job_number << std::endl;
			}
		}

		PCB_info get_pcb(int index) {
			return compare.at(index).get_pcb_info();
		}

		int pcb_list_size() {
			return compare.size();
		}
	private:
		std::vector<job_number_compare> compare;
	};
}
