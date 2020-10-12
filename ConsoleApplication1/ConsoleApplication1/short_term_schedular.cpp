#include "short_term_schedular.h"

OSSim::short_term_schedular::short_term_schedular(IRunnable* queue)
{
	runnable_process = queue;
}

OSSim::short_term_schedular::~short_term_schedular() {
	delete runnable_process;
	runnable_process = NULL;
}

void OSSim::short_term_schedular::add_job(PCB_info info) {
	runnable_process->add_job(info);
}
