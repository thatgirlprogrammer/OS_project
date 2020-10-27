#include <iostream>
#include <cstddef>
#include <cstdint>

using namespace std;

class RAM
{
    private:
        uint8_t storage[1030];
    public:
        RAM()
        {
            for(int i = 0; i < 1024; i++)
            {
                storage[i] = 0;
            }
        }
        void store(uint8_t hex);
        void isFull();
        uint8_t pass(int index);
};

void RAM :: store(uint8_t hex)
{
    RAM check;
    check.isFull();
    for(int i = 0; i < 1024; i++)
    {
        if(storage[i] == 0)
        {
            storage[i] = hex;
            break;
        }
    }
}

uint8_t RAM :: pass(int index)
{
    RAM check;
    uint8_t p;
    p = storage[index];
    return p;
    storage[index] = 0;
}

void RAM :: isFull()
{
    for(int i = 0 ; i < 1024 ; i++)
    {
        if(storage[0] != 0 && storage[1024] != 0)
        {
            //cout << "RAM FULL";
            storage[i] = 0;
            //cout << "CLEARED";
        }
    }
}

int main()
{
    /*RAM test;
    
    int index = 0;
    uint8_t hex = 0xEE;
    
    test.store(hex);
    uint8_t res = test.pass(0);
    
    cout << "The result Stored was: " << unsigned(res);*/
}

