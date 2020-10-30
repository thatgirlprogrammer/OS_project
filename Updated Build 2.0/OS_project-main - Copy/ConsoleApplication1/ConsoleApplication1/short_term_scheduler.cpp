#include "short_term_scheduler.h"

void short_term_scheduler::schedule() {
	if (ready->size() > 0) {
		PCB_info* process = ready->at(0);
		uint16_t b = process->pc.job_memory_address;
		std::cout << "This is job " << process->pc.job_number << endl;
		cpu->setBase(b);
		uint16_t j = 0;
		for (int i = 0; i < process->pc.job_size; ++i) {
			mem->deallocate(j + (b * 4));
			j += 4;
		}
		ready->erase(ready->begin() + 0);
		std::cout << "My job size is " << process->pc.job_size << std::endl;
	}
}
