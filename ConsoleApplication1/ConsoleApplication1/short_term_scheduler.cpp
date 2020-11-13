#include "short_term_scheduler.h"

void short_term_scheduler::schedule(int cpu_number, loader* ld) {
	if (ld->get_ready()->size() > 0) {
		PCB_info* process = ld->get_ready()->at(0);
		//uint16_t b = process->pc.job_memory_address;
		vector<int> vec = process->pc.pages;
		int16_t j = 0;
		for (int i = 0; i < process->pc.pages.size(); ++i) {
			int frame = page_t->getPage(process->pc.job_number, process->pc.pages.at(i));
			std::cout << "My frame is from " << frame << std::endl;
			cpus->at(cpu_number)->writeCache(j, mem->getMem(frame, 0));
			std::cout << "At " << j << " in CPU we wrote " <<  mem->getMem(frame, 0) << std::endl;
			cpus->at(cpu_number)->writeCache(j + 4, mem->getMem(frame, 1));
			std::cout << "At " << j + 4 << " in CPU we wrote " << mem->getMem(frame, 1) << std::endl;
			cpus->at(cpu_number)->writeCache(j + 8, mem->getMem(frame, 2));
			std::cout << "At " << j + 8 << " in CPU we wrote " << mem->getMem(frame, 2) << std::endl;
			cpus->at(cpu_number)->writeCache(j + 12, mem->getMem(frame, 3));
			std::cout << "At " << j + 12 << " in CPU we wrote " << mem->getMem(frame, 3) << std::endl;
			j += 16;
		}
		process->pc.my_cpu = cpu_number;
		cpus->at(cpu_number)->set_running(process);
		//cpus->at(cpu_number)->setBase(b);
		load->move_running(0);
	}
}