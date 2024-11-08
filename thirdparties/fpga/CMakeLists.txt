file(COPY libs/fftfpga/libfftfpga.a DESTINATION ${CMAKE_CURRENT_BINARY_DIR} FILE_PERMISSIONS OWNER_READ OWNER_EXECUTE)

set(SRCS_FPGAPROC fpga.cpp)
set(FPGAPROC_HEADERS fpga.h)
add_library(fpgaproc STATIC ${SRCS_FPGAPROC} ${FPGAPROC_HEADERS})
target_include_directories(fpgaproc PUBLIC ${PROJECT_SOURCE_DIR}/include)

