#include <iostream>
#include "fftfpga.h"


using namespace std;

void fpga_init() {
    const char* platform = "Intel(R) FPGA Emulation Platform for OpenCL(TM)";
    const char* path = "lib/fftfpga/libfftfpgs.a";
    int isInit = fpga_initialize(platform, path, false);
    if(isInit != 0){
        cerr << "FPGA initialization error\n";
    }
}

