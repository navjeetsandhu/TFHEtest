#include "mult_fft.hpp"
#include "mult_ntt_cuhe.hpp"
#include "mult_ntt_hexl.hpp"
#include"utils2.hpp"
#include <numeric>
#include <cmath>

template <int nbits>
void test_mult_fpga(const std::array<uint64_t, 1 << nbits>& p1, const std::array<uint64_t, 1 << nbits>& p2)
{

    constexpr int N = 1 << nbits;
    std::string string_msg = "Naive 64 bit Multiplication";
    print_results<uint64_t>("Input p1", p1.data(), p1.size());
    print_results<uint64_t>("Input p2", p2.data(), p1.size());
    std::array<uint64_t, N> result = {};
    PolyMulNaive<uint64_t, N>(result, p1, p2);
    print_results<int64_t>(string_msg,  reinterpret_cast<int64_t*>(result.data()), result.size());

    std::array<int64_t, N> resultP = {};
    std::fill(result.begin(), result.end(), 0);
    hexl::PolyMulFpga<N>(result, p1, p2);
    string_msg = "hexl FPGA NTT 64 bit Multiplication with mod=4611686018427365377ULL and N="+ std::to_string(N);
    to_int64_t<N>(resultP, result,4611686018427365377ULL);
    print_results<int64_t>(string_msg,  resultP.data(), resultP.size());
}


template <class P, int nbits>
void test_mult_fpga()
{
    constexpr int N = 1 << nbits;

    std::array<P,  N> p1{};
    std::array<P,  N> p2{};
    std::iota(p1.begin(), p1.end(), 1);
    std::iota(p2.begin(), p2.end(), 10);
    test_mult_fpga<nbits>(p1, p2);
}

int main()
{
    constexpr int nbit = 10; // lijie: for FPGA we need nbit =14
    test_mult_fpga<uint64_t, nbit>();
    return 0;
}