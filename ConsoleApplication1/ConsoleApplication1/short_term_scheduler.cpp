#include "short_term_scheduler.h"

void short_term_scheduler::schedule(int cpu_number, loader* ld) {
	if (ld->get_ready()->size() > 0) {
		PCB_info* process = ld->get_ready()->at(0);
		uint16_t b = process->pc.job_memory_address;
		std::cout << "My b is " << b << std::endl;
		std::cout << "This is job " << process->pc.job_number << endl;
		cpus->at(cpu_number)->setBase(b);
		if (cpus->at(cpu_number)->isCache()) {
			cpus->at(cpu_number)->set_running(process);
			//cpus->at(cpu_number)->appendRunning(process);
			for (int i = 0; i < process->pc.job_size * 4; i += 4) {
				cpus->at(0)->writeCache(i, mem->getMem(i + (b * 4)));
			}
		}
		//for (int i = 0; i < process->pc.job_size * 4; i += 4) {
		//	mem->deallocate(i + (b * 4));
		//}
		load->move_running(0);
		std::cout << "My job size is " << process->pc.job_size << std::endl;
	}
}