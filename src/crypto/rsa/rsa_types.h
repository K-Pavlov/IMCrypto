/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   rsa_types.h
 * Author: kaloyan
 *
 * Created on April 24, 2016, 12:41 AM
 */

#ifndef RSA_TYPES_H
#define RSA_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif
    
#include <gmp.h>
    
    struct RsaKeys {
        mpz_t public_e;
        mpz_t public_n;
        mpz_t private_d;
    };

    typedef struct RsaKeys RsaKeys_t;

#ifdef __cplusplus
}
#endif

#endif /* RSA_TYPES_H */

