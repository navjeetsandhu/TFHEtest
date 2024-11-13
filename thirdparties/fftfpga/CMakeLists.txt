set(SRCS_FFTFPGA fftfpga.c fft1d.c svm.c opencl_utils.c misc.c)
set(FFTFPGA_HEADERS misc.h opencl_utils.h svm.h fftfpga.h)
add_library(fftfpga STATIC ${SRCS_FFTFPGA} ${FFTFPGA_HEADERS})
target_include_directories(fftfpga PUBLIC ${PROJECT_SOURCE_DIR}/include)