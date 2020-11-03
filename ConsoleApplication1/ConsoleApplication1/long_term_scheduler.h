#pragma once
#include <vector>
#include "pcb.h"
#include "Memory.h"
#include "disk.h"
#include "loader.h"

namespace OSSim
{
	class long_term_scheduler
	{
	public:
		long_term_scheduler(Memory* memory, disk* dk, loader* ld) {
			ram = memory;
			dsk = dk;
			load = ld;
			new_q = load->get_new_q();
			ready = load->get_ready();
		}
		void write_to_ram(uint16_t index, int32_t data) {
			ram->allocate(index * 4);
			ram->setMem(index * 4, data);
		}
		int32_t read(uint16_t index) {
			return ram->getMem(index);
		}
		void schedule();
	private:
		Memory* ram;
		disk* dsk;
		loader* load;
		vector<PCB_info*>* new_q;
		vector<PCB_info*>* ready;
	};
}
