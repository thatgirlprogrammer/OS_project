#pragma once
#include <vector>
#include "runnable.h"
//#include "ram.h"

namespace OSSim {
	class short_term_scheduler {
	public:
		short_term_scheduler(std::vector<uint8_t*>* queue)
		{
			runnable_process = queue;
		}
		~short_term_scheduler() {
			delete runnable_process;
			runnable_process = NULL;
		}
		void add_job(PCB_info info, uint8_t* process) {

		}
	private:
		std::vector<uint8_t*>* runnable_process;
	};
}

