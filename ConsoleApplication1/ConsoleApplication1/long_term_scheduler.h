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
		void write_to_ram(uint8_t hex, int start, int end) {
			ram1->store(hex, start, end);
		}
	private:
		RAM* ram1;
	};
}
