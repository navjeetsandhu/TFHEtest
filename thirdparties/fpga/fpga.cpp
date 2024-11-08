#include <iostream>
#include "fpga.h"


using namespace std;

void fpga_initialize() {
    const char* platform = "Intel(R) FPGA Emulation Platform for OpenCL(TM)";
    const char* path = "/home/solana/code/TFHEfft/thirdparties/fpga/libs/aocx/fft1d.aocx";
    int isInit = fpga_initialize(platform, path, false);
    if(isInit != 0){
        cerr << "FPGA initialization error\n";
    }
}


void fpga_close() {
    // destroy fpga state
    fpga_final();
}


/**
 * @brief  compute an out-of-place single precision complex 1D-FFT on the FPGA
 * @param  N    : integer pointer to size of FFT3d
 * @param  inp  : float2 pointer to input data of size N
 * @param  out  : float2 pointer to output data of size N
 * @param  inv  : int toggle to activate backward FFT
 * @return int : time taken in milliseconds for data transfers and execution
 */
fpga_t fpga_fft(const unsigned num, const float2 *inp, float2 *out, const bool inv)
{
    fpga_t runtime ={0, 0, 0, 0,0, false};

    try {
        runtime = fftfpgaf_c2c_1d(num, inp, out, inv, 1);
    }
    catch(const char* msg){
        cerr << msg << endl;
    }
    return runtime;
}