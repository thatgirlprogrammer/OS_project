#pragma once
#include "runnable.h"
#include "pcb.h"

namespace OSSim {
	class job_priority {
	public:
		job_priority() {}

		void add_job(PCB_info job) {
			priorities* jc1 = new priorities(job);
			compare.push_back(*(jc1));
		}

		void sort() {
			std::sort(compare.begin(), compare.end());
		}

		PCB_info get_pcb(int index) {
			return compare.at(index).get_pcb_info();
		}

		size_t pcb_list_size() {
			return compare.size();
		}

	private:
		std::vector<priorities> compare;
	};
}
