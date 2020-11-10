#pragma once
#include <cstddef>
#include <cstdint>

class page_table
{
public:
	void addPage(int frame, int processID, int pageNumber);
	int getFrame(int processID, int pageNumber);
	bool getValid(int frame);
private:
	int process[256];
	int page[256];
	bool valid[256] = { false };

};

