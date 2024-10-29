#pragma once
#include "INTorus.hpp"
#include "cuhe++.hpp"

namespace cuHEpp {

    constexpr int NBITS = 6; //dimension 16 (2^4) or 1024 (2^10) or 2048 (2^11)
    constexpr int N_NTT = 1 << NBITS;

    inline const std::unique_ptr<const std::array<std::array<cuHEpp::INTorus, N_NTT>, 2>>
            ntttwist = cuHEpp::TwistGen<NBITS>();
    inline const std::unique_ptr<const std::array<std::array<cuHEpp::INTorus, N_NTT>, 2>>
            ntttable = cuHEpp::TableGen<NBITS>();


    template<class T, int nbits>
    inline void TwistNTT(std::array<T, 1 << nbits> &res, std::array<cuHEpp::INTorus, 1 << nbits> &a) {
        cuHEpp::TwistNTT<T, nbits>(res, a, (*ntttable)[0], (*ntttwist)[0]);
    }

    template<class T, int nbits>
    inline void TwistINTT(std::array<cuHEpp::INTorus, 1 << nbits> &res,
                          const std::array<T, 1 << nbits> &a) {
        cuHEpp::TwistINTT<T, nbits>(res, a, (*ntttable)[1],
                                    (*ntttwist)[1]);
    }

    template<class T, int nbits>
    void PolyMulNTT(std::array<T, 1 << nbits> &res, const std::array<T, 1 << nbits> &a,
                    const std::array<T, 1 << nbits> &b) {
        constexpr int N = 1 << nbits;

        std::array<cuHEpp::INTorus, N> ntta, nttb;
        TwistINTT<T, nbits>(ntta, a);
        TwistINTT<T, nbits>(nttb, b);

        for (int i = 0; i < N; i++) ntta[i] *= nttb[i];
        TwistNTT<T, nbits>(res, ntta);
    }

}
