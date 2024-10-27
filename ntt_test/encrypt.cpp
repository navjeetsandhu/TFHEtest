#include <iostream>
#include <array>
#include <cstdint>


static constexpr uint64_t  moduli = 4611686018427365377ULL;

void printBinary(uint64_t num)
{
    if (num > 1)
    {
        printBinary(num/2);
    }
    std::cout << num % 2;
}

void divide_64()
{

    int64_t a = 1LL << 61;
    int64_t b = -a;

    uint64_t d = b;
    uint64_t c = d/a;

    std::cout << std::hex << "c  " << c << " " << std::endl;

}







int main()
{
    printBinary(1);
}


