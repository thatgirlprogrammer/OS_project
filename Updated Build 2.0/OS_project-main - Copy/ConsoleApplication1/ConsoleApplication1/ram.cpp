#include "ram.h"

using namespace OSSim;

void RandomAccess::store(int32_t hex, int start)
{
  //  assert(end < 1024);
    RandomAccess check;
    check.isFull();
    // queue.push_back(process);
    // pcbs.push_back(pcb1);
    /*
    for (int i = start; i < end; i++)
    {
        if (storage[i] == 0)
        {
            storage[i] = hex[i - start];
            break;
        }
    }*/
    storage[start] = hex;
}

int32_t RandomAccess::pass(int index)
{
    RandomAccess check;
    int32_t p;
    p = storage[index];
    return p;
    storage[index] = 0;
}

void RandomAccess::isFull()
{
    for (int i = 0; i < 1024; i++)
    {
        if (storage[0] != 0 && storage[1024] != 0)
        {
            cout << "RAM FULL";
            storage[i] = 0;
            cout << "CLEARED";
        }
    }
}