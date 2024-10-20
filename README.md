# TFHEpp
TFHEpp is full Scracthed pure C++ Ver. of TFHE. TFHEpp is slightly(about 10%) faster than original [TFHE implementation](https://github.com/tfhe/tfhe). 

# Building on MAC
Only old MAC with intel processor are supported
export following variables before build:
1. export LDFLAGS="-L/usr/local/opt/libomp/lib"
2. export CPPFLAGS="-I/usr/local/opt/libomp/include"

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


## HEXL
[HEXL](https://github.com/intel/hexl.git) is the NTT library optimized for AVX512. 

TFHEpp uses the following HEXL limited functionalities in certain scenarios:
1.	Forward NTT: ComputeForward()
2.	Inverse NTT: ComputeInverse()
3.	Elementwise vector multiplication with modular reduction: EltwiseMultMod()
4.	Elementwise vector addition with modular reduction: EltwiseAddMod()

## Build
rm -rf build
mkdir build
cd build
cmake ..
make