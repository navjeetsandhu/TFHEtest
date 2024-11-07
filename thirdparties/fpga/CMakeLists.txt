set(SRCS_FPGAPROC fft_processor_fftw.cpp)
set(FPGAPROC_HEADERS fft_processor_fftw.h)
add_library(fpgaproc STATIC ${SRCS_FPGAPROC} ${FPGAPROC_HEADERS})
target_include_directories(fpgaproc PUBLIC ${PROJECT_SOURCE_DIR}/include)

