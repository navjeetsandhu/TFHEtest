file(GLOB tfhe++_sources "*.cpp")

if(ENABLE_SHARED)
  add_library(tfhe++ SHARED ${tfhe++_sources})
else()
  add_library(tfhe++ STATIC ${tfhe++_sources})
endif()

target_include_directories(
  tfhe++
  PUBLIC
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/thirdparties/spqlios
    ${PROJECT_SOURCE_DIR}/thirdparties/fftw
    ${PROJECT_SOURCE_DIR}/thirdparties/concrete-fft/cpp
    ${PROJECT_BINARY_DIR}/thirdparties/concrete-fft
    ${PROJECT_SOURCE_DIR}/thirdparties/spqliox_aarch64
    ${PROJECT_SOURCE_DIR}/thirdparties/spqliox_aarch64/xbyak_aarch64/xbyak_aarch64
    ${PROJECT_SOURCE_DIR}/thirdparties/randen
    ${PROJECT_SOURCE_DIR}/thirdparties/HLS_arbitrary_Precision_Types/include
    ${PROJECT_SOURCE_DIR}/thirdparties/cereal/include)
if(USE_RANDEN)
  target_link_libraries(tfhe++ INTERFACE randen)
endif()


if(USE_FFTW3)
  target_link_libraries(tfhe++ INTERFACE fftwproc)
  target_link_libraries(tfhe++ INTERFACE fftw3)
else()
  target_link_libraries(tfhe++ INTERFACE spqlios)
endif()
