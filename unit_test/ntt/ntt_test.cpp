
#include <numeric>
#include "mult_fft.hpp"
#include"utils2.hpp"


template <int N>
void test_mult(const std::array<uint64_t, N>& p1, const std::array<uint64_t, N>& p2) {

    std::string string_msg = "Naive 64 bit Multiplication";
    print_results<uint64_t>("Input p1", p1.data(), p1.size());
    print_results<uint64_t>("Input p2", p2.data(), p1.size());
    std::array<uint64_t, N> result = {};
    PolyMulNaive<uint64_t, N>(result, p1, p2);
    print_results<int64_t>(string_msg, reinterpret_cast<int64_t *>(result.data()), result.size());

}

template<int N>
void test_mult()
{
    std::array<uint64_t,  N> p1{};
    std::array<uint64_t,  N> p2{};
    std::iota(p1.begin(), p1.end(), 1);
    std::iota(p2.begin(), p2.end(), 10);
    test_mult<N>(p1, p2);
}

int main()
{

    test_mult<1<<6>();
    return 0;
}
