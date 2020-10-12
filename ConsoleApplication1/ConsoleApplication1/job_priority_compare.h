#pragma once
#include "pcb.h"

namespace OSSim {
	class job_priority_compare {
	public:
		job_priority_compare(PCB_info pcb_info) {
			info = pcb_info;
		}

		bool operator< (const job_priority_compare other) const {
			return info.pc.job_priority < other.info.pc.job_priority;
		}

		PCB_info get_pcb_info() {
			return info;
		}

	private:
		PCB_info info;
	};
}

