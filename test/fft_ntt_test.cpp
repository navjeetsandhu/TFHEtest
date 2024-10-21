#include "mult_fft.hpp"
#include "mult_ntt_cuhe.hpp"
#include "mult_ntt_hexl.hpp"
#include"utils2.hpp"
#include <numeric>
#include <cmath>

template <int N>
void copyTorusArray(std::array<uint64_t, N>& p1, const std::array<cuHEpp::INTorus, N> ntt) {
    for (int i =0 ;i< N; i++)
        p1[i] = ntt[i].value;
}


template <int nbits>
void test_fft_ntt(const std::array<uint64_t, 1 << nbits>& p1)
{

    std::string string_msg = "Input p1";
    constexpr int N = 1 << nbits;

    print_results<uint64_t>(string_msg, p1.data(), p1.size());

    std::array<uint64_t, N> result;
    std::array<uint64_t, N> result1;
    std::fill(result.begin(), result.end(), 0);

    alignas(64) std::array<double, N> fft{};
    TwistIFFT<N>(fft, p1);

    string_msg = "TwistIFFT 64 bit";
    print_results<double>(string_msg,  fft.data(), fft.size());

    TwistFFT<N>(result, fft);
    string_msg = "TwistFFT 64 bit";
    print_results<int64_t>(string_msg,  reinterpret_cast<int64_t*>(result.data()), result.size());

    std::array<cuHEpp::INTorus, N> ntt;
    cuHEpp::TwistINTT<uint64_t, nbits>(ntt, p1);
    copyTorusArray<N>(result1, ntt);
    string_msg = "cuHE TwistINTT 64 bit";
    print_results<int64_t>(string_msg,  reinterpret_cast<int64_t*>(result1.data()), result1.size());
    std::fill(result.begin(), result.end(), 0);
    cuHEpp::TwistNTT<uint64_t, nbits>(result, ntt);
    string_msg = "cuHE TwistNTT 64 bit";
    print_results<int64_t>(string_msg,  reinterpret_cast<int64_t*>(result.data()), result.size());

    std::fill(result1.begin(), result1.end(), 0);
    hexl::TwistINTT<N>(result1, p1);
    string_msg = "hexl TwistINTT 64 bit";
    print_results<int64_t>(string_msg,  reinterpret_cast<int64_t*>(result1.data()), result1.size());
    std::fill(result.begin(), result.end(), 0);
    hexl::TwistNTT<N>(result, result1);
    string_msg = "hexl TwistNTT 64 bit";
    print_results<int64_t>(string_msg,  reinterpret_cast<int64_t*>(result.data()), result.size());

}

template <int nbits>
void test_fft_ntt(const std::array<uint32_t, 1 << nbits>& p1)
{

    std::string string_msg = "Input p1";
    constexpr int N = 1 << nbits;

    print_results<uint32_t>(string_msg, p1.data(), p1.size());

    std::array<uint32_t, N> result;
    std::array<uint64_t, N> result1;
    std::fill(result.begin(), result.end(), 0);

    alignas(64) std::array<double, N> fft{};
    TwistIFFT<N>(fft, p1);

    string_msg = "TwistIFFT 32 bit";
    print_results<double>(string_msg,  fft.data(), fft.size());

    TwistFFT<N>(result, fft);
    string_msg = "TwistFFT 32 bit";
    print_results<int32_t>(string_msg,  reinterpret_cast<int32_t*>(result.data()), result.size());

    std::array<cuHEpp::INTorus, N> ntt;
    cuHEpp::TwistINTT<uint32_t, nbits>(ntt, p1);
    copyTorusArray<N>(result1, ntt);
    string_msg = "cuHE TwistINTT 32 bit";
    print_results<int64_t>(string_msg,  reinterpret_cast<int64_t*>(result1.data()), result1.size());
    std::fill(result.begin(), result.end(), 0);
    cuHEpp::TwistNTT<uint32_t, nbits>(result, ntt);
    string_msg = "cuHE TwistNTT 32 bit";
    print_results<int32_t>(string_msg,  reinterpret_cast<int32_t*>(result.data()), result.size());
}



template <class P, int nbits>
void test_fft_ntt()
{
    constexpr int N = 1 << nbits;

    std::array<P,  N> p1{};
    std::array<P,  N> p2{};
    std::iota(p1.begin(), p1.end(), 1);
    test_fft_ntt<nbits>(p1);
}

int main()
{
    constexpr int nbit = 6;
    test_fft_ntt<uint32_t,nbit>();
    test_fft_ntt<uint64_t, nbit>();
    return 0;
}