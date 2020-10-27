#include "loader.h"
#include <fstream>
#include <string>
#include <iostream>
#include <cstddef>
#include <cstdint>
#include <iomanip>

using namespace std;
using namespace OSSim;

loader::loader(string file_name) {
	file.open(file_name, ios::in);
}
void loader::load_file() {
	if (file.is_open()) {
		string line;
		uint8_t current = 0;
		while (getline(file, line)) {
			if (line.find("JOB") != std::string::npos) {
				cout << "Job encountered." << "\n";
				string num1 = "0x";
				string num2 = "0x";
				string num3 = "0x";
				int i = 7;
				num1 += line[i];
				++i;
				while (line[i] != ' ' && i < line.size()) {
					num1 += line[i];
					++i;
				}
				++i;
				num2 += line[i];
				++i;
				while (line[i] != ' ' && i < line.size()) {
					num2 += line[i];
					++i;
				}
				++i;
				num3 += line[i];
				++i;
				while (line[i] != ' ' && i < line.size()) {
					num3 += line[i];
					++i;
				}
				++i;
				int32_t job_number = strtoul(num1.c_str(), nullptr, 16);
				int32_t job_priority = strtoul(num2.c_str(), nullptr, 16);
				int32_t job_count = strtoul(num3.c_str(), nullptr, 16);
				cout << num1 << " " << num2 << " " << num3 << "\n";
			}
			else if (line.find("Data") != std::string::npos) {
				cout << "Data encountered." << "\n";
				int i = 8;
				string num1 = "0x";
				string num2 = "0x";
				string num3 = "0x";
				num1 += line[i];
				++i;
				while (line[i] != ' ' && i < line.size()) {
					num1 += line[i];
					++i;
				}
				++i;
				num2 += line[i];
				++i;
				while (line[i] != ' ' && i < line.size()) {
					num2 += line[i];
					++i;
				}
				++i;
				num3 += line[i];
				++i;
				while (line[i] != ' ' && i < line.size()) {
					num3 += line[i];
					++i;
				}
				++i;
				int32_t iBuffer = strtoul(num1.c_str(), nullptr, 16);
				int32_t oBuffer = strtoul(num2.c_str(), nullptr, 16);
				int32_t sBuffer = strtoul(num3.c_str(), nullptr, 16);
				cout << num1 << " " << num2 << " " << num3 << "\n";
			}
			else if (line.find("END") != std::string::npos) {
				cout << "End of file." << "\n";
			}
			else {
				if (current >= 2048) {
					cout << "Too much in disk!";
				}
				else {
					cout << "Writing to disk" << "\n";
					int32_t number = strtoul(line.c_str(), nullptr, 16);
					dsk.write(number, current);
					++current;
				}
			}
		}
		file.close();
	}
}
