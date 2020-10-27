#include <iostream>
#include <cstddef>
#include <cstdint>
#include <cassert>

using namespace std;

class RAM
{
private:
    uint8_t storage[1030];
public:
    RAM()
    {
        for (int i = 0; i < 1024; i++)
        {
            storage[i] = 0;
        }
    }
    void store(uint8_t hex, int start, int end);
    void isFull();
    uint8_t pass(int index);
};

void RAM::store(uint8_t hex, int start, int end)
{
    assert(end < 1024);
    RAM check;
    check.isFull();
    for (int i = start; i < end; i++)
    {
        if (storage[i] == 0)
        {
            storage[i] = hex;
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
