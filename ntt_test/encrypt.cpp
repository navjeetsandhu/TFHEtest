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
    uint64_t digits = std::numeric_limits<uint64_t>::digits;
    std::cout << std::hex << "moduli " << moduli<< " " << std::endl;
    std::cout << std::hex << "mu     " << mu << " " << std::endl;
    std::cout << std::hex << "_mu    " << _mu << " " << std::endl;
    std::cout << std::hex << "mess   " << message << " " << std::endl;
    std::cout << std::hex << "_mess  " << _message << " " << std::endl;
    std::cout << std::hex << "_mess  ";

    std::cout << std::dec << "digits     " << digits << " " << std::endl;
    printBinary(_message);
    std::cout << " " << std::endl;

    uint32_t mu_32 = 1 << 29; // 536870912 (0x2000000) for 1
    uint32_t plain_modulus_32 = 1<<3;  // MSB 3 bits are for message 001_ (0x2) or 111_ (0xE)
    double maximum_m32 = static_cast<double>(1ULL << std::numeric_limits<uint32_t>::digits);
    uint32_t delta = maximum_m32/plain_modulus_32;

    std::cout << std::hex << "mu_32 " << mu_32<< " " << std::endl;
    std::cout << std::dec << "mu_32 " << mu_32 << " " << std::endl;
    std::cout << std::hex << "pm_32 " << plain_modulus_32 << " " << std::endl;
    std::cout << std::dec << "pm_32 " << plain_modulus_32 << " " << std::endl;
    std::cout << std::hex << "delta " << delta << " " << std::endl;
    std::cout << std::dec << "delta " << delta << " " << std::endl;


}


