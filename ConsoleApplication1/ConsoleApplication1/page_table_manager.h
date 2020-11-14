#pragma once
#include "page.h"
class page_table_manager
{
public:
	page_table_manager();
	void addPage(int frame, int p_id, unsigned int pg_num);
	int getPage(int p_id, unsigned int pg_num);
private:
	int process_id[256];
	int page_num[256];

};

