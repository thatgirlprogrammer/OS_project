#pragma once
#include <vector>
#include "runnable.h"
#include "Memory.h"
#include "pcb.h"
#include "loader.h"
#include "CPU.h"
#include "page_table_manager.h"

namespace OSSim {
	static void schedule() {}

	class short_term_scheduler {
	public:
		short_term_scheduler(Memory* memory, loader* ld, vector<CPU*>* c, page_table_manager* pg_t)
		{
			mem = memory;
			load = ld;
			cpus = c;
			page_t = pg_t;
		}
		~short_term_scheduler() {}
		void schedule(int cpu_number, loader* ld);
	private:
		Memory* mem;
		vector<CPU*>* cpus;
		loader* load;
		page_table_manager* page_t;
	};
}
