#pragma once
#include <vector>
#include "runnable.h"

namespace OSSim {
	class short_term_scheduler{
	public:
		short_term_scheduler(IRunnable* queue);
		~short_term_scheduler();
		void add_job(PCB_info info, std::vector<Instruction>* instructions);
		void execute_job();
	private:
		IRunnable* runnable_process;
	};
}
