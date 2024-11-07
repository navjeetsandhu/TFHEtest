set(SRCS_FPGAPROC fpga.cpp)
set(FPGAPROC_HEADERS fpga.h)
add_library(fpgaproc STATIC ${SRCS_FPGAPROC} ${FPGAPROC_HEADERS})
target_include_directories(fpgaproc PUBLIC ${PROJECT_SOURCE_DIR}/include)

