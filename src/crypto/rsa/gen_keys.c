#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <gmp.h> 

#include "../utilities.h"
#include "gen_keys.h"
#include "rsa_types.h"
#include "../../helpers/memory.h"

void get_e(mpz_t e, const mpz_t max)
{
    mpz_t seed, gcd; //gdc - greatest common divider
    gmp_randstate_t rstate; 
    PrimeProbability is_prime = not_prime;
    const short reps = 40;
    
    mpz_inits(gcd, seed, NULL);
    set_seed(seed);
    gmp_randinit_mt(rstate);
    gmp_randseed(rstate, seed);
    
    do {
        mpz_urandomm(e, rstate, max);
        mpz_gcd(gcd, e, max);
        is_prime = mpz_probab_prime_p(e, reps);
    } while(mpz_cmp_si(gcd, 1) && is_prime == not_prime);
    
    mpz_clears(gcd, seed, NULL);
    gmp_randclear(rstate);
}

void generate_keys(RsaKeys_t *rsa_keys) 
{
    mpz_t p, q, totient;    
    mpz_inits(p, q, totient, NULL);
    generate_prime(p, KEY_SIZE);
    generate_prime(q, KEY_SIZE);
    
    mpz_mul(rsa_keys->public_n, p, q);
    mpz_sub_ui(p, p, 1);
    mpz_sub_ui(q, q, 1);
    mpz_mul(totient, p, q);
    get_e(rsa_keys->public_e, totient);
    mpz_invert(rsa_keys->private_d, rsa_keys->public_e, totient);
    
    mpz_clears(p, q, totient, NULL);
}

RsaKeys_t* init_keys() 
{
    RsaKeys_t *rsa_keys = im_calloc(1, sizeof(RsaKeys_t));
    mpz_inits(rsa_keys->public_n, rsa_keys->private_d, rsa_keys->public_e, NULL);
    return rsa_keys;
}

void clear_keys(RsaKeys_t *rsa_keys) 
{
    mpz_clears(rsa_keys->public_e, rsa_keys->public_n, rsa_keys->private_d, NULL);
    free(rsa_keys);
}
