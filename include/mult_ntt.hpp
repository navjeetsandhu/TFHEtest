#pragma once
#include <memory>
#include "INTorus.hpp"
#include "cuhe++.hpp"
#include "params.hpp"
#include "utils.hpp"

namespace TFHEpp {
    inline const std::unique_ptr<
        const std::array<std::array<cuHEpp::INTorus, lvl1param::n>, 2>>
            ntttwistlvl1 = cuHEpp::TwistGen<lvl1param::nbit>();
    inline const std::unique_ptr<
        const std::array<std::array<cuHEpp::INTorus, lvl1param::n>, 2>>
            ntttablelvl1 = cuHEpp::TableGen<lvl1param::nbit>();
    inline const std::unique_ptr<
            const std::array<std::array<cuHEpp::INTorus, lvl2param::n>, 2>>
            ntttwistlvl2 = cuHEpp::TwistGen<lvl2param::nbit>();
    inline const std::unique_ptr<
            const std::array<std::array<cuHEpp::INTorus, lvl2param::n>, 2>>
            ntttablelvl2 = cuHEpp::TableGen<lvl2param::nbit>();
    inline const std::unique_ptr<
            std::array<std::array<raintt::SWord, lvl1param::n>, 2>>
            raintttwist = raintt::TwistGen<lvl1param::nbit, 3>();
    inline const std::unique_ptr<
            std::array<std::array<std::array<raintt::SWord, lvl1param::n>, 2>, 2>>
            raintttable = raintt::TableGen<lvl1param::nbit>();



template <class P>
inline void TwistNTT(Polynomial<P> &res, PolynomialNTT<P> &a)
{
    if constexpr (std::is_same_v<P, lvl1param>)
        cuHEpp::TwistNTT<typename lvl1param::T, lvl1param::nbit>(
            res, a, (*ntttablelvl1)[0], (*ntttwistlvl1)[0]);
    else if constexpr (std::is_same_v<typename P::T, uint64_t>)
        cuHEpp::TwistNTT<typename lvl2param::T, lvl2param::nbit>(
            res, a, (*ntttablelvl2)[0], (*ntttwistlvl2)[0]);
    else
        static_assert(false_v<typename P::T>, "Undefined TwistNTT!");
}


template <class P>
inline void TwistINTT(PolynomialNTT<P> &res, const Polynomial<P> &a)
{
    if constexpr (std::is_same_v<P, lvl1param>)
        cuHEpp::TwistINTT<typename P::T, P::nbit>(res, a, (*ntttablelvl1)[1],
                                                  (*ntttwistlvl1)[1]);
    else if constexpr (std::is_same_v<typename P::T, uint64_t>)
        cuHEpp::TwistINTT<typename P::T, P::nbit>(res, a, (*ntttablelvl2)[1],
                                                  (*ntttwistlvl2)[1]);
    else
        static_assert(false_v<typename P::T>, "Undefined TwistINTT!");
}


template <class P>
inline void PolyMulNtt(Polynomial<P> &res, const Polynomial<P> &a,
                        const Polynomial<P> &b)
{
    PolynomialNTT<P> ntta, nttb;
    TwistINTT<P>(ntta, a);
    TwistINTT<P>(nttb, b);
    for (int i = 0; i < P::n; i++) ntta[i] *= nttb[i];
    TwistNTT<P>(res, ntta);
}

template <class P>
std::unique_ptr<std::array<PolynomialNTT<P>, 2 * P::n>> XaittGenNTT()
{
    std::unique_ptr<std::array<PolynomialNTT<P>, 2 * P::n>> xaitt =
        std::make_unique<std::array<PolynomialNTT<P>, 2 * P::n>>();
    for (int i = 0; i < 2 * P::n; i++) {
        std::array<typename P::T, P::n> xai = {};
        xai[0] = -1;
        if (i < P::n)
            xai[i] += 1;
        else
            xai[i - P::n] -= 1;
        TwistINTT<P>((*xaitt[i]), xai);
    }
    return xaitt;
}

}  // namespace TFHEpp