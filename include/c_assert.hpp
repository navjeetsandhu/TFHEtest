#pragma once

#include <cstdio>
#include <cstdlib>
#include<iostream>
#include <vector>

#define c_assert(condition) \
do { \
    if (!(condition)) { \
        fprintf(stderr, "Assertion failed: function %s, file %s, line %d.\n", __FUNCTION__, __FILE__, __LINE__); \
        exit(EXIT_FAILURE); \
    } \
} while (false)


template <class T>
void print_results(const std::string& msg, const T* result, T size){
    std::cout << msg << ": " << std::endl;
    for (int i = 0; i < size; ++i)
        std::cout <<  result[i] << ' ';

    std::cout << std::endl << std::endl;
}

template <int N>
void to_int64_t(std::array<int64_t, N>& out,
                const std::array<uint64_t, N>& in,
                uint64_t mod)
{
    uint64_t half_mod = mod/2;
    for (int i=0;i<N;i++)
        out[i] = in[i] > half_mod ?  in[i] -mod : in[i];
}