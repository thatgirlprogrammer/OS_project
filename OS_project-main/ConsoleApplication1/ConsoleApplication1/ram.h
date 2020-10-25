#include <iostream>
#include <cstddef>
#include <cstdint>
#include <vector>
#include "pcb.h"

using namespace std;

namespace OSSim
{
    class ram
    {
    private:
        std::vector<uint32_t> storage;
        PCB_info pcb_info;
    public:
        ram()
        {
            for (int i = 0; i < 1024; i++)
            {
                storage.push_back(0);
            }
        }

        void store(vector<uint32_t>* hex, PCB_info info);
        bool isFull();
        uint8_t pass(int index);
        std::vector<uint32_t> get_intructions() {
            return storage;
        }
    };
}
