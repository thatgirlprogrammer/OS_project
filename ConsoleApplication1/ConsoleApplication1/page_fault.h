#pragma once
class page_fault
{
public:
	page_fault() {}
	bool interrupt(bool valid) { return valid; }
private:
};

