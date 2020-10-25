#include "ram.h"

bool OSSim::ram::isFull()
{
    for (int i = 0; i < 1024; i++)
    {
        if (storage[0].get_inst() != 0 && storage[1024].get_inst() != 0)
        {
            //cout << "RAM FULL";
            return true;
            //cout << "CLEARED";
        }
    }
    return false;
}

/*Instruction OSSim::ram::pass(int index)
{
    ram check;
    Instruction p();
    return p;
}*/

void OSSim::ram::store(vector<Instruction>* hex, PCB_info info)
{
    ram check;
    pcb_info = info;
    check.isFull();
    for (int i = 0; i < 1024; i++)
    {
        if (storage.at(i).get_inst() == 0)
        {
            storage.at(i) = hex->at(i);
            break;
        }
    }
}
