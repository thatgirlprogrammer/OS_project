#include "job_number.h"
#include <algorithm>

void OSSim::job_len::add_job(PCB_info job)
{
	job_numbers* jc1 = new job_numbers(job);
	compare.push_back(*jc1);
}

void OSSim::job_len::sort()
{
	std::sort(compare.begin(), compare.end());
}

size_t OSSim::job_len::pcb_list_size()
{
	return 30;
}
