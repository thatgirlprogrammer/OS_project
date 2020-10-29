#pragma once
#include <vector>
#include "pcb.h"

namespace OSSim {
	class priorities {
	public:
		priorities(PCB_info pcb_info) {
			info = pcb_info;
		}

		bool operator< (const priorities other) const {
			return info.pc.job_priority < other.info.pc.job_priority;
		}

		PCB_info get_pcb_info() {
			return info;
		}

		void set_PCB_info(pcb pc, data d, buffer b, process_details pd) {
			info.pc = pc;
			info.d = d;
			info.b = b;
			info.pd = pd;
		}
	private:
		PCB_info info;
	};
}

