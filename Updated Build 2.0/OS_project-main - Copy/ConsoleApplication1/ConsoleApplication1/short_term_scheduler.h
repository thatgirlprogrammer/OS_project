#pragma once
#include <vector>
#include "runnable.h"
#include "Memory.h"

namespace OSSim {
	static void schedule() {}

	class short_term_scheduler {
	public:
		short_term_scheduler(Memory* memory)
		{
			mem = memory;
		}
		~short_term_scheduler() {
			delete mem; mem = NULL;
		}
		void add_memory(uint16_t index, int32_t value) {
			mem->setMem(index * 4, value);
		}
	private:
		Memory* mem;
	};
}