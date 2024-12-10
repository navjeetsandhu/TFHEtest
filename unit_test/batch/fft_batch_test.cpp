#include "mult_fft.hpp"
#include "mult_fft_fpga.hpp"
#include <numeric>
#include <cmath>
#include "c_assert.hpp"
#include <chrono>

template <int nbits,  int batch>
void test_fft()
{
    constexpr int N = 1 << nbits;
    constexpr unsigned size = batch *N;
    std::array<uint32_t, size> result{};
    std::fill(result.begin(), result.end(), 0);

    std::array<uint32_t,  size> p1{};
    std::iota(p1.begin(), p1.end(), 1);

    auto start = std::chrono::high_resolution_clock::now();

    alignas(64) std::array<double, size> fft{};
    TwistFpgaIFFTbatch(fft.data(), p1.data(), batch);

    auto finish1 = std::chrono::high_resolution_clock::now();

    TwistFpgaFFTbatch(result.data(), fft.data(), batch);

    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed = finish - start;
    std::chrono::duration<double, std::milli> elapsed1 = finish1 - start;
    std::chrono::duration<double, std::milli> elapsed2 = finish - finish1;

    std::cout << "batch: " << batch << " s\n";
    std::cout << "Total Elapsed IFFT time: " << elapsed1.count() << " ms\n";
    std::cout << "Total Elapsed FFT time: " << elapsed2.count() << " ms\n";
    std::cout << "Total Elapsed time: " << elapsed.count() << " ms\n";
}





int main()
{
    constexpr int nbit = 10;
    constexpr int batch = 2500;
    test_fft<nbit, batch>();
    return 0;
}