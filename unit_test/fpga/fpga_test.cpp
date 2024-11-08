#ifdef USE_FPGA
#include "fpga.h"
#endif

void init_fpga()
{

#ifdef USE_FPGA
    fpga_initialize();
#endif
}

void destroy_fpga()
{

#ifdef USE_FPGA
    fpga_close();
#endif
}


int main()
{
    init_fpga();
    destroy_fpga();
    return 0;
}