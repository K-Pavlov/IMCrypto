/* 
 * File:   rsa.h
 * Author: kaloyan
 *
 * Created on April 23, 2016, 11:32 PM
 */

#ifndef RSA_H
#define RSA_H

#ifdef __cplusplus
extern "C" {
#endif
    
#include <gmp.h>
#include <stdio.h>
#include "rsa_types.h"
#define RSA_BASE 10
    
    void rsa_encrypt(mpz_t encrypted, const mpz_t message, RsaKeys_t rsa_keys);
    void rsa_decrypt(mpz_t decrypted, const mpz_t encrypted, RsaKeys_t rsa_keys);
    void rsa_generate_keys(RsaKeys_t *rsaKeys);
    void rsa_keys_get(RsaKeys_t *rsa_keys);
    void rsa_keys_clear(RsaKeys_t *rsa_keys);
    RsaKeys_t* rsa_keys_init();

#ifdef __cplusplus
}
#endif

#endif /* RSA_H */

