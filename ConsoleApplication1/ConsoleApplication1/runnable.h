#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include "pcb.h"
#include "job_priority_compare.h"
#include "job_number_compare.h"

namespace OSSim {
	__interface IRunnable {
	public:
		void run();
		void print_compare();
		void add_job(int val);
		PCB_info get_pcb(int index);
		int pcb_list_size();
	};
}
