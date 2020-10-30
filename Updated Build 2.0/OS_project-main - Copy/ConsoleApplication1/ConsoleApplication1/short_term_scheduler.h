#pragma once
#include <vector>
#include "runnable.h"
#include "Memory.h"
#include "pcb.h"
#include "loader.h"
#include "CPU.h"

namespace OSSim {
	static void schedule() {}

	class short_term_scheduler {
	public:
		short_term_scheduler(Memory* memory, loader* ld, CPU* c)
		{
			mem = memory;
			load = ld;
			cpu = c;
			ready = ld->get_ready();
			waiting = ld->get_waiting();
			running = ld->get_running();
			terminated = ld->get_terminated();
		}
		~short_term_scheduler() {
			delete mem; mem = NULL;
		}
		void schedule();
		//void add_memory(uint16_t index, int32_t value) {
		//	mem->setMem(index * 4, value);
		//}
	private:
		Memory* mem;
		CPU* cpu;
		loader* load;
		vector<PCB_info*>* ready;
		vector<PCB_info*>* waiting;
		vector<PCB_info*>* running;
		vector<PCB_info*>* terminated;
	};
}
