#include<iostream>
#include <numeric>
#include "mult_ntt_hexl.hpp"
#include "mult_fft.hpp"
#include"utils2.hpp"

std::unique_ptr<intel::hexl::NTT> create_ntt(uint64_t N, uint64_t modulus) {
    auto ntt = std::make_unique<intel::hexl::NTT>(N, modulus);
    return ntt;
}

void poly_mult_ntt(uint64_t *result, const uint64_t *p1, const uint64_t *p2,
                       uint64_t degree, uint64_t modulus) {
    auto ntt = create_ntt(degree, modulus);
    std::vector<uint64_t> output(degree), p1_output(degree), p2_output(degree);
    hexl::compute_forward(p1_output.data(), p1, *ntt);
    hexl::compute_forward(p2_output.data(), p2, *ntt);
    hexl::eltwise_mult_mod(output.data(), p1_output.data(),
                     p2_output.data(), degree, modulus);
    hexl::compute_inverse(result, output.data(), *ntt);
}


template <int N>
void test_mult(const std::array<uint64_t, N>& p1, const std::array<uint64_t, N>& p2) {

    std::string string_msg = "Naive 64 bit Multiplication";
    print_results<uint64_t>("Input p1", p1.data(), p1.size());
    print_results<uint64_t>("Input p2", p2.data(), p1.size());
    std::array<uint64_t, N> result = {};
    std::array<int64_t, N> resultP = {};
    PolyMulNaive<uint64_t, N>(result, p1, p2);
    print_results<int64_t>(string_msg, reinterpret_cast<int64_t *>(result.data()), result.size());

    std::fill(result.begin(), result.end(), 0);
    poly_mult_ntt(result.data(), p1.data(), p2.data(), N, 4611686018427365377ULL);
    string_msg = "hexl NTT 64 bit Multiplication with mod=4611686018427365377ULL and N="+ std::to_string(N);
    to_int64_t<N>(resultP, result,4611686018427365377ULL);
    print_results<int64_t>(string_msg,  resultP.data(), resultP.size());

    std::fill(result.begin(), result.end(), 0);
    poly_mult_ntt(result.data(), p1.data(), p2.data(), N, 1073707009);
    string_msg = "hexl NTT 64 bit Multiplication with mod=1073707009 and N=" + std::to_string(N);
    to_int64_t<N>(resultP, result,1073707009);
    print_results<int64_t>(string_msg,  resultP.data(), resultP.size());

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
