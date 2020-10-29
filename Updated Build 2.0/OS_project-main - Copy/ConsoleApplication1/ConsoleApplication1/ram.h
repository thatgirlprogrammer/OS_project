#include <iostream>
#include <cstddef>
#include <cstdint>
#include <cassert>
#include <vector>
#include "pcb.h"

using namespace std;

namespace OSSim {
    class RandomAccess
    {
    private:
        vector<int32_t*> queue;
        vector<OSSim::PCB_info> pcbs;
        int32_t storage[1030];
    public:
        OSSim::PCB_info get_pcb(int i) { return pcbs.at(i); }
        int32_t* get_process(int i) { return queue.at(i); }

        RandomAccess()
        {
            for (int i = 0; i < 1024; i++)
            {
                storage[i] = 0;
            }
        }
        void store(int32_t hex, int start);
        void isFull();
        int32_t pass(int index);
    };
}