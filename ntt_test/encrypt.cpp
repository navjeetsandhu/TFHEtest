#include <iostream>
#include <array>
#include <cstdint>


void printBinary(uint64_t num)
{
    if (num > 1)
    {
        printBinary(num/2);
    }
    std::cout << num % 2;
}

static constexpr uint64_t  moduli = 4611686018427365377ULL;
int main()
{
    uint64_t message = 0x1;
    uint64_t mu = 1LL << 58;;
    uint64_t _mu = moduli - mu;
    uint64_t _message = _mu/mu;
    std::cout << std::hex << "moduli " << moduli<< " " << std::endl;
    std::cout << std::hex << "mu     " << mu << " " << std::endl;
    std::cout << std::hex << "_mu    " << _mu << " " << std::endl;
    std::cout << std::hex << "mess   " << message << " " << std::endl;
    std::cout << std::hex << "_mess  " << _message << " " << std::endl;
    std::cout << std::hex << "_mess  ";
    printBinary(_message);
    std::cout << " " << std::endl;
}


