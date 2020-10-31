#include "short_term_scheduler.h"

void short_term_scheduler::schedule() {
	if (ready->size() > 0) {
		PCB_info* process = ready->at(0);
		uint16_t b = process->pc.job_memory_address;
		std::cout << "My b is " << b << std::endl;
		std::cout << "This is job " << process->pc.job_number << endl;
		cpus->at(0)->setBase(b);
		uint16_t j = 0;
		if (cpus->at(0)->isCache()) {
			cpus->at(0)->appendRunning(process);
			for (int i = 0; i < process->pc.job_size * 4; i += 4) {
				cpus->at(0)->writeCache(i, mem->getMem(i + (b * 4)));
			}
		}
		for (int i = 0; i < process->pc.job_size; ++i) {
			mem->deallocate(j + (b * 4));
			j += 4;
		}
		load->move_running(0);
		std::cout << "My job size is " << process->pc.job_size << std::endl;
	}
}