#include "short_term_scheduler.h"

void short_term_scheduler::schedule(int cpu_number, loader* ld) {
	if (load->get_waiting()->size() > 0) {
		PCB_info* process = load->get_waiting()->at(0);
		//load->move_waiting_ready(0);
		//load->move_running(load->get_ready()->size() - 1);
		load->move_waiting_running(process);
		process->pc.process_status = WAIT;
		int j;
		int i = 0;
		int p;
		
		for (j = 0; j < process->pc.job_instruction_count * 4; j += 4) {
			cpus->at(cpu_number)->writeOneCache(j, process->pc.itCache[j]);
			cpus->at(cpu_number)->writeOneCache(j + 1, process->pc.itCache[j + 1]);
			cpus->at(cpu_number)->writeOneCache(j + 2, process->pc.itCache[j + 2]);
			cpus->at(cpu_number)->writeOneCache(j + 3, process->pc.itCache[j + 3]);
		}
		p = j;
		for (j = j; j < (process->b.input_buffer * 4) + p; j += 4) {
			cpus->at(cpu_number)->writeOneCache(j, process->pc.ipCache[i]);
			cpus->at(cpu_number)->writeOneCache(j + 1, process->pc.ipCache[i + 1]);
			cpus->at(cpu_number)->writeOneCache(j + 2, process->pc.ipCache[i + 2]);
			cpus->at(cpu_number)->writeOneCache(j + 3, process->pc.ipCache[i + 3]);
			i += 4;
		}
		i = 0;
		p = j;
		for (j = j; j < (process->b.output_buffer * 4) + p; j += 4) {
			cpus->at(cpu_number)->writeOneCache(j, process->pc.oCache[i]);
			cpus->at(cpu_number)->writeOneCache(j + 1, process->pc.oCache[i + 1]);
			cpus->at(cpu_number)->writeOneCache(j + 2, process->pc.oCache[i + 2]);
			cpus->at(cpu_number)->writeOneCache(j + 3, process->pc.oCache[i + 3]);
			i += 4;
		}
		i = 0;
		p = j;
		for (j = j; j < (process->b.temp_buffer * 4) + p; j += 4) {
			cpus->at(cpu_number)->writeOneCache(j, process->pc.tempCache[i]);
			cpus->at(cpu_number)->writeOneCache(j + 1, process->pc.tempCache[i + 1]);
			cpus->at(cpu_number)->writeOneCache(j + 2, process->pc.tempCache[i + 2]);
			cpus->at(cpu_number)->writeOneCache(j + 3, process->pc.tempCache[i + 3]);
			i += 4;
		}
		uint8_t l;
		for (l = 0; l < 16; ++l) {
			cpus->at(cpu_number)->writeRegisters(l, process->pc.registers[l]);
		}
		cpus->at(cpu_number)->setValuePC(process->pc.program_counter - 4);
		cpus->at(cpu_number)->set_running(process);
		cpus->at(cpu_number)->setDone();
		return;
	}
	if (ld->get_ready()->size() > 0) {
		PCB_info* process = ld->get_ready()->at(0);
		//uint16_t b = process->pc.job_memory_address;
		vector<unsigned int> vec = process->pc.pages;
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
		cpus->at(cpu_number)->setDone();
		cpus->at(cpu_number)->setPC();
		//cpus->at(cpu_number)->setBase(b);
		load->move_running(process);
	}
}