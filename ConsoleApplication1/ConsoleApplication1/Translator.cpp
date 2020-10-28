#include <iostream>
#include <string>
#include <stdio.h>
#include <bits/stdc++.h>

using namespace std;

class Translator
{
    private:
        uint8_t byte[10];
    public:
        Translator()
        {
            for(int i = 0; i < 10; i++)
            {
                byte[i] = 0;
            }
        }
        uint8_t recog(uint32_t word); //Only recognizes Dec or Bin
        uint8_t binToHex(uint32_t word);
        uint8_t decToHex(uint32_t word);
        uint32_t hexToBin(uint8_t hex);
        uint32_t hexToDec(uint8_t hex);
        uint32_t decToBin(uint32_t dec);
};

uint32_t Translator :: decToBin(uint32_t dec)
{
    uint32_t val[32];
    int i = 0;
    string bin = "";
    
    while(dec > 0)
    {
        val[i] = dec % 2;
        dec = dec / 2;
        i++;
    }
    
    for (int j = i - 1; j >= 0; j--)
    {
        bin += to_string(val[j]);
    }
    
    //cout << bin << "\n";
    
    uint32_t in = strtol(bin.c_str(), nullptr, 2);
    
    return in;
}

uint32_t Translator :: hexToBin(uint8_t hex)
{
    Translator send;
    uint32_t dec = send.hexToDec(hex);
    
    uint32_t in = send.decToBin(dec);
    
    return in;
}

uint32_t Translator :: hexToDec(uint8_t hex)
{
    uint32_t dec = (int)hex;

    return dec;
}

uint8_t Translator :: recog(uint32_t word)
{
    if (word == 0 || word == 1)
    {
        decToHex(word);
        cout << " 1 ";
    }
    else
    {
        int check = word;
        bool isBin = false;
        
        while(check != 0)
        {
            int temp = check%10;
            check = check/10;
            
            if(temp == 1 || temp == 0)
            {
                isBin = true;
            }
            else
            {
                return decToHex(word);
            }
        }
        if(isBin == true)
            return binToHex(word);
    }
}

uint8_t Translator :: binToHex(uint32_t word)
{
    int temp = word, i = 0, dec = 0;
    int r;
    while(temp != 0)
    {
        r = temp % 10;
        temp /= 10;
        dec += r * pow(2,i);
        i++;
    }
    
    return decToHex(dec);
}

uint8_t Translator :: decToHex(uint32_t word)
{
    int temp = word, i = 0;
    char t[8];
    
    while(temp != 0)
    {
        int r = temp % 16;
        
        if(r < 10)
        {
            t[i] = r + 48;
        }
        else
        {
            t[i] = r + 55;
        }
        i++;
        temp = temp/16;
    }
    
    int size = sizeof(t) / sizeof(char);
    
    string s = "";
    uint8_t b = 0;
    
    for (i = 0; i < size; i++) 
    { 
        s += t[i];
    }
    
    char sw = s[0];
    s[0] = s[1];
    s[1] = sw;

    b = std::strtol(s.c_str(),nullptr, 16);
    
    return b;
}

int main()
{
    /*Translator test;

    int tByte = 12;

    //uint8_t p = test.recog(tByte);
    
    uint32_t b = test.hexToBin(0xee);
    
    cout << to_string(b);*/
}


