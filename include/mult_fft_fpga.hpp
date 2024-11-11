#pragma once
#include <array>
#include "mult_fft.hpp"

#ifdef USE_FPGA
#include <fft_processor_fpga.h>
FFT_Processor_FPGA fftp = fftFpgaLvli;

template <int N>
inline void TwistFpgaFFT(std::array<uint64_t, N> &res, const std::array<double, N> &a)
{
    fftFpgaLvli.execute_direct_torus64(res.data(), a.data());
}

template <int N>
inline void TwistFpgaFFT(std::array<uint32_t, N> &res, const std::array<double, N> &a)
{
    fftFpgaLvli.execute_direct_torus32(res.data(), a.data());
}

template <int N>
inline void TwistFpgaIFFT(std::array<double, N> &res, const std::array<uint64_t, N> &a)
{
    fftFpgaLvli.execute_reverse_torus64(res.data(), a.data());
}

template <int N>
inline void TwistFpgaIFFT(std::array<double, N> &res, const std::array<uint32_t, N> &a)
{
    fftFpgaLvli.execute_reverse_torus32(res.data(), a.data());
}
#else

template <int N>
inline void TwistFpgaFFT(std::array<uint64_t, N> &res, const std::array<double, N> &a)
{
    fftplvl1.execute_direct_torus64(res.data(), a.data());
}

template <int N>
inline void TwistFpgaFFT(std::array<uint32_t, N> &res, const std::array<double, N> &a)
{
    fftplvl1.execute_direct_torus32(res.data(), a.data());
}

template <int N>
inline void TwistFpgaIFFT(std::array<double, N> &res, const std::array<uint64_t, N> &a)
{
    fftplvl1.execute_reverse_torus64(res.data(), a.data());
}

template <int N>
inline void TwistFpgaIFFT(std::array<double, N> &res, const std::array<uint32_t, N> &a)
{
    fftplvl1.execute_reverse_torus32(res.data(), a.data());
}
#endif

template <class T, int N>
void PolyMulFpgaFFT(std::array<T, N> &res, const std::array<T, N>  &a,
                const std::array<T, N>  &b)
{
    alignas(64) std::array<double, N> ffta{};
    TwistFpgaIFFT<N>(ffta, a);
    alignas(64) std::array<double, N> fftb{};
    TwistFpgaIFFT<N>(fftb, b);
    MulInFD<N>(ffta, fftb);
    TwistFpgaFFT<N>(res, ffta);
}




