#pragma once
#include <string>

class interrupt
{
public:
	interrupt(std::string code1);
	~interrupt();
private:
	std::string code;
};

