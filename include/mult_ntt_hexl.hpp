#pragma once
#include "hexl/hexl.hpp"
#include "params.hpp"

namespace hexl {
    static constexpr uint64_t moduli = 4611686018427365377ULL;

    inline void compute_inverse(uint64_t *result,
                                const uint64_t *operand,
                                intel::hexl::NTT& ntt){
        ntt.ComputeInverse(result, operand, 1, 1);
    }

    inline void compute_forward(uint64_t *result,
                                const uint64_t *operand,
                                intel::hexl::NTT& ntt) {
        ntt.ComputeForward(result, operand, 1, 1);
    }

    inline void eltwise_mult_mod(uint64_t *result,
                                 const uint64_t *p1,
                                 const uint64_t *p2,
                                 uint64_t degree,
                                 uint64_t modulus = moduli) {
        intel::hexl::EltwiseMultMod(result, p1, p2, degree, modulus,1);
    }

    inline void eltwise_add_mod(uint64_t *result,
                                 const uint64_t *p1,
                                 const uint64_t *p2,
                                 uint64_t degree,
                                 uint64_t modulus = moduli) {
        intel::hexl::EltwiseAddMod(result, p1, p2, degree, modulus);
    }


    template<int N>
    inline void TwistNTT(std::array<uint64_t, N> &res,
                         const std::array<uint64_t, N> &a) {
        static intel::hexl::NTT ntt(N, moduli);
        compute_inverse(res.data(), a.data(), ntt);
    }

    template<int N>
    inline void TwistINTT(std::array<uint64_t, N> &res,
                          const std::array<uint64_t, N> &a) {
        static intel::hexl::NTT ntt(N, moduli);
        compute_forward(res.data(), a.data(), ntt);
    }

    template<int N>
    inline void PolyMulNTT(std::array<uint64_t, N> &res,
                    const std::array<uint64_t, N> &a,
                    const std::array<uint64_t, N> &b)
    {
        std::array<uint64_t, N> ntta, nttb, nttc;
        TwistINTT<N>(ntta, a);
        TwistINTT<N>(nttb, b);
        eltwise_mult_mod(nttc.data(), ntta.data(), nttb.data(), N, moduli);
        TwistNTT<N>(res, nttc);
    }
}
