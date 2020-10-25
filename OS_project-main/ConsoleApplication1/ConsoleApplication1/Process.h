#pragma once
#include <iostream>
#include <string>
#include <vector>

namespace OSSim {
	class Process {
	public: 
		Process(int num, std::vector<std::string>* instructions1);
		~Process();
		void display();
	private:
		int processid;
		std::vector<std::string>* instructions;
	};
}
