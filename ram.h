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
        uint8_t storage[1030];
        PCB_info pcb_info;
    public:
        ram()
        {
            for (int i = 0; i < 1024; i++)
            {
                storage[i] = 0;
            }
        }

        void store(uint8_t hex, PCB_info info);
        bool isFull();
        uint8_t pass(int index);
    };
}
