#pragma once
class Accumulator
{
public:
	Accumulator();
	~Accumulator();
	int get_value();
	void set_value();
private:
	int intermediate;
};

