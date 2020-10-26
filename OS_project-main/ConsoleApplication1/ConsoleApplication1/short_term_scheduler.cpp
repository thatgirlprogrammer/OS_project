#include "short_term_scheduler.h"

OSSim::short_term_scheduler::short_term_scheduler(IRunnable* queue)
{
	runnable_process = queue;
}

OSSim::short_term_scheduler::~short_term_scheduler() {
	delete runnable_process;
	runnable_process = NULL;
}

void OSSim::short_term_scheduler::add_job(PCB_info info, std::vector<Instruction>* instructions)
{
	runnable_process->add_job(info, instructions);
}

void OSSim::short_term_scheduler::execute_job()
{
	runnable_process->run_job();
}

