
#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include "utilities.h"

#ifdef __unix__
uint64_t rdtsc()
{ // processor ticks
    unsigned int lo,hi;
    __asm__ __volatile__ ("rdtsc" : "=a" (lo), "=d" (hi));
    return ((unsigned long long)hi << 32) | lo;
}
#elif _WIN32
#include <intrin.h>
#pragma intrinsic(__rdtsc)

uint64_t rdtsc() 
{
    return __rdtsc();
}
#endif

uint64_t get_random_number()
{
    return rdtsc();
}