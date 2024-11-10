#include <array>
#include "mult_fft.hpp"

#ifdef USE_FPGA
    #include <fft_processor_fpga.h>
    FFT_Processor_FPGA fft = fftFpgaLvli;
    #else
        #ifdef USE_FFTW3
            #include <fft_processor_fftw.h>
            FFT_Processor_FFTW fft = fftplvl1;
        #else
            #include <fft_processor_spqlios.h>
            thread_local FFT_Processor_Spqlios fft = fftplvl1;
        #endif
#endif

template <int N>
inline void TwistFpgaFFT(std::array<uint64_t, N> &res, const std::array<double, N> &a)
{
    fft.execute_direct_torus64(res.data(), a.data());
}

template <int N>
inline void TwistFpgaFFT(std::array<uint32_t, N> &res, const std::array<double, N> &a)
{
    fft.execute_direct_torus32(res.data(), a.data());
}

template <int N>
inline void TwistFpgaIFFT(std::array<double, N> &res, const std::array<uint64_t, N> &a)
{
    fft.execute_reverse_torus64(res.data(), a.data());
}

template <int N>
inline void TwistFpgaIFFT(std::array<double, N> &res, const std::array<uint32_t, N> &a)
{
    fft.execute_reverse_torus32(res.data(), a.data());
}



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




