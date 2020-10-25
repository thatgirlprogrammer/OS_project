#include <iostream>
#include <cstddef>
#include <cstdint>
#include <vector>
#include "pcb.h"
#include "instruction.h"

using namespace std;

namespace OSSim
{
    class ram
    {
    private:
        std::vector<Instruction> storage;
        PCB_info pcb_info;
    public:
        ram()
        {
            for (int i = 0; i < 1024; i++)
            {
                storage.push_back(Instruction(0));
            }
        }

        void store(vector<Instruction>* hex, PCB_info info);
        bool isFull();
        //Instruction pass(int index);
        std::vector<Instruction> get_intructions() {
            return storage;
        }
    };
}
