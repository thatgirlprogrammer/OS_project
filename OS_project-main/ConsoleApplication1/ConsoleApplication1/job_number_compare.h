#pragma once
#include "pcb.h"

namespace OSSim {
	class job_number_compare {
	public:
		job_number_compare(PCB_info pcb_info) {
			info = pcb_info;
		}

		bool operator< (const job_number_compare other) const {
			return info.pc.job_number < other.info.pc.job_number;
		}

		PCB_info get_pcb_info() {
			return info;
		}

	private:
		PCB_info info;
	};
}
