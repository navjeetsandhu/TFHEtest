#include <iostream>
#include "fftfpga.h"


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