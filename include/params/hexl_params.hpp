#pragma once
#include <cstdint>

static constexpr std::uint32_t hexl_params_nbit = 14;  // dimension must be a power of 2 for polynomial multiplication.
static constexpr std::uint32_t hexl_params_n = 1 << hexl_params_nbit;  // degree 16384 is used by Intel FPGA

// Biggest prime number less than 2^62 and satisfies 1 mod 2N.
static constexpr uint64_t  hexl_params_moduli = 4611686018427365377ULL;  // 0x3FFFFFFFFFFFA801
