#include <tfhe++.hpp>
#include <chrono>
#include <iostream>
using namespace TFHEpp;
using namespace std;

uint8_t AndCheck(const uint8_t in0, const uint8_t in1) { return in0 * in1; }


void RunTest()
{
    cout << "------ Testing of FFT AND gate for lvl2param ------" << endl;
    SecretKey* sk = new SecretKey();
    TFHEpp::EvalKey ek;
    ek.emplacebk<TFHEpp::lvl02param>(*sk);
    ek.emplaceiksk<TFHEpp::lvl20param>(*sk);
    vector<uint8_t> p(2, 1);
    vector<uint8_t> p2(2);
    vector<TLWE<lvl2param>> cres(1);
    vector<TLWE<lvl2param>> c(2);

    c = bootsSymEncrypt<lvl2param>(p, *sk);

    TFHEpp::HomAND<lvl20param, lvl02param, lvl2param::mu>(cres[0], c[0], c[1], ek);

    p2 = bootsSymDecrypt<lvl2param>(cres, *sk);

    c_assert(1 == p2[0]);
    cout << "------ pass ------" << endl;
    //nsandhu@Navjeets-MacBook-Pro ntt_test % ./and_gate_fft
    //zsh: segmentation fault  ./and_gate_fft
}

int main()
{
    RunTest();
    return 0;
}