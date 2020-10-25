#pragma once
#include <vector>
#include "pcb.h"
#include "ram.h"

namespace OSSim {
	class long_term_scheduler
	{
	public:
		long_term_scheduler();
		~long_term_scheduler();
		void write_to_ram(uint8_t hex, PCB_info info);
		void schedule();
	private:
		int calcuate_chunk_size(int cur_disk_address, pcb pcb_val);
		ram* ram1 = new ram();
	};
}
