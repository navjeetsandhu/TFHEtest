#ifdef USE_FPGA
#include "fpga.h"
#endif

void init_fpga()
{

#ifdef USE_FPGA
    fpga_initialize();
#endif
}

int main()
{
    init_fpga();
    return 0;
}