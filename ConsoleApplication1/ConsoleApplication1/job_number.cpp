#include "job_number.h"


void OSSim::job_number::add_job(PCB_info job, std::vector<Instruction>* lst)
{
	job_numbers* jc1 = new job_numbers(job, lst);
	compare.push_back(*(jc1));
}

void OSSim::job_number::sort()
{
	std::sort(compare.begin(), compare.end());
}

void OSSim::job_number::print_compare()
{
	for (int i = 0; i < compare.size(); i++) {
		auto val = compare.at(i);
		std::cout << "job number " << val.get_pcb_info().pc.job_number << std::endl;
	}
}

int OSSim::job_number::pcb_list_size()
{
	return compare.size();
}
