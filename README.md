# TFHEpp
TFHEpp is full Scracthed pure C++ Ver. of TFHE. TFHEpp is slightly(about 10%) faster than original [TFHE implementation](https://github.com/tfhe/tfhe). 

# Building
bash hexl_build.sh

# Supported Compiler
GCC9.1 later are primarily supported compilers.

# Third party libraries
Codes under thirdparties directory contain third-party libraries, Randen, Cereal, and SPQLIOS. See the corresponding directory to check the licenses.

## Randen
TFHEpp uses this as a Cryptographically Secure Pseudo-Random Number Generator (CSPRNG). Original repository is [here](https://github.com/google/randen).
I just removed some unnecessary codes, with no modification.

## Cereal
cereal is a header-only C++11 serialization library. TFHEpp uses this to export ciphertexts and keys. Cereal is treated by the git submodule.

## SPQLIOS
SPQLIOS is the FFT library using AVX2 that is dedicated to the ring R\[X\]/(X^N+1) for N a power of 2. These codes come from [experimental-tfhe](https://github.com/tfhe/experimental-tfhe/tree/master/circuit-bootstrapping/src/spqlios). We just renamed instances to adapt to our codes.

# FFTW3 Support
TFHEpp can use fftw3.

