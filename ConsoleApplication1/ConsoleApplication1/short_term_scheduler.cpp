#include "short_term_scheduler.h"

void short_term_scheduler::schedule(int cpu_number, loader* ld) {
	if (ld->get_ready()->size() > 0) {
		PCB_info* process = ld->get_ready()->at(0);
		uint16_t b = process->pc.job_memory_address;
		process->pc.my_cpu = cpu_number;
		cpus->at(cpu_number)->setBase(b);
		if (cpus->at(cpu_number)->isCache()) {
			cpus->at(cpu_number)->set_running(process);
			for (int i = 0; i < process->pc.job_size * 4; i += 4) {
				cpus->at(cpu_number)->writeCache(i, mem->getMem(b, i));
			}
		}
		load->move_running(0);
	}
}