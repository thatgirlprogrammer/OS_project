#pragma once
#include <vector>
#include "pcb.h"
#include "ram.h"
#include "disk.h"

namespace OSSim
{
	class long_term_scheduler
	{
	public:
		long_term_scheduler() { ram1 = new RandomAccess; }
		~long_term_scheduler() { delete ram1; ram1 = nullptr; }
		void write_to_ram(int32_t hex, int start) {
			ram1->store(hex, start);
		}
		int32_t read(int index) {
			return ram1->pass(index);
		}
		RandomAccess get_RAM() { return *ram1; }
	private:
		RandomAccess* ram1;
	};
}