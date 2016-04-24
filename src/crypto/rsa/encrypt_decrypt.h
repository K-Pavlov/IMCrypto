/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   encrypt_decrypt.h
 * Author: kaloyan
 *
 * Created on April 17, 2016, 10:57 PM
 */

#ifndef ENCRYPT_DECRYPT_H
#define ENCRYPT_DECRYPT_H

#ifdef __cplusplus
extern "C" {
#endif

#include <gmp.h> 
#include "rsa_types.h"
    
    void encrypt(mpz_t encrypted, const mpz_t message, RsaKeys_t rsa_keys);
    void decrypt(mpz_t decrypted, const mpz_t encrypted, RsaKeys_t rsa_keys);

#ifdef __cplusplus
}
#endif

#endif /* ENCRYPT_DECRYPT_H */

