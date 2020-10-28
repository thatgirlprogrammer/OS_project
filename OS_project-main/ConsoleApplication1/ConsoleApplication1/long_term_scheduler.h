#pragma once
#include <vector>
#include "pcb.h"
#include "ram.h"

namespace OSSim
{
	class long_term_scheduler
	{
	public:
		long_term_scheduler() { ram1 = new RAM(); }
		~long_term_scheduler() { delete ram1; ram1 = nullptr; }
		void write_to_ram(uint8_t hex[], int start, int end, uint8_t* process, PCB_info pcb1) {
			ram1->store(hex, start, end, process, pcb1);
		}
		RAM get_RAM() { return *ram1; }
	private:
		RAM* ram1;
	};
}

