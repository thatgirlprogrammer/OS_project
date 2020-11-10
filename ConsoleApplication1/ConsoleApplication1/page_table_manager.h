#pragma once
#include "page_table.h"
class page_table_manager
{
public:
	page_table_manager();
	void addPage(int frame, int processID, int pageNumber);
	page_table* getPageTable() { return page_t; }
	bool hasPage(int size);
	int pageStart(int size);
private:
	page_table* page_t = new page_table();
};

