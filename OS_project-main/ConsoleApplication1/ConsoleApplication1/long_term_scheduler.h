#pragma once
#include <vector>
#include "pcb.h"
#include "ram.h"

namespace OSSim 
{
	class long_term_scheduler
	{
	public:
		long_term_scheduler();
		~long_term_scheduler();
		void write_to_ram(vector<uint32_t>* hex, PCB_info info);
	private:
		ram* ram1 = new ram();
	};
}
