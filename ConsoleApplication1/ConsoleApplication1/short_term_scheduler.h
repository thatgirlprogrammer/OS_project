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
		short_term_scheduler(Memory* memory, loader* ld, vector<CPU*>* c)
		{
			mem = memory;
			load = ld;
			cpus = c;
		}
		~short_term_scheduler() {}
		void schedule(int cpu_number, loader* ld);
	private:
		Memory* mem;
		vector<CPU*>* cpus;
		loader* load;
	};
}
