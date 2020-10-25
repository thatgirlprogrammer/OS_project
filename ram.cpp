#include "ram.h"

bool OSSim::ram::isFull()
{
    for (int i = 0; i < 1024; i++)
    {
        if (storage[0] != 0 && storage[1024] != 0)
        {
            //cout << "RAM FULL";
            return true;
            //cout << "CLEARED";
        }
    }
    return false;
}

uint8_t OSSim::ram::pass(int index)
{
    ram check;
    uint8_t p;
    p = storage[index];
    storage[index] = 0;
    return p;
}

void OSSim::ram::store(uint8_t hex, PCB_info info)
{
    ram check;
    pcb_info = info;
    check.isFull();
    for (int i = 0; i < 1024; i++)
    {
        if (storage[i] == 0)
        {
            storage[i] = hex;
            break;
        }
    }
}
