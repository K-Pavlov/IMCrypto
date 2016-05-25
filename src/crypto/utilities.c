
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

void set_seed (mpz_t seed) 
{ 
    uint64_t rand_num = get_random_number();
    mpz_set_ui(seed, rand_num);
}

void generate_prime(mpz_t dest, const int key_size) 
{
    mpz_t seed;
    gmp_randstate_t rstate;    
    PrimeProbability is_prime = not_prime;
    const short reps = 40; //reason values : 15 - 50
    
    mpz_init(seed);
    set_seed(seed);
    gmp_randinit_default (rstate);
    gmp_randseed(rstate, seed);

    while(is_prime == not_prime) {// definitely prime is too slow  
        mpz_urandomb(dest, rstate, key_size);          
        is_prime = mpz_probab_prime_p(dest, reps);
    }

    mpz_clear(seed);
    gmp_randclear(rstate);
}