#include <iostream>
#include <cstddef>
#include <cstdint>
#include <cassert>
#include <vector>

using namespace std;

class RAM
{
private:
    vector<uint8_t*> queue;
    uint8_t storage[1030];
public:
    RAM()
    {
        for (int i = 0; i < 1024; i++)
        {
            storage[i] = 0;
        }
    }
    void store(uint8_t hex[], int start, int end, uint8_t* process);
    void isFull();
    uint8_t pass(int index);
};

void RAM::store(uint8_t hex[], int start, int end, uint8_t* process)
{
    assert(end < 1024);
    RAM check;
    check.isFull();
    queue.push_back(process);

    for (int i = start; i < end; i++)
    {
        if (storage[i] == 0)
        {
            storage[i] = hex[i-start];
            break;
        }
    }
}

uint8_t RAM::pass(int index)
{
    RAM check;
    uint8_t p;
    p = storage[index];
    return p;
    storage[index] = 0;
}

void RAM::isFull()
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
