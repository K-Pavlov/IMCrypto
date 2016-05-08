/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   gen_keys.h
 * Author: kaloyan
 *
 * Created on March 20, 2016, 6:33 PM
 */

#ifndef GEN_KEYS_H
#define GEN_KEYS_H

#ifdef __cplusplus
extern "C" {
#endif
    
#include <gmp.h>  
#define KEY_SIZE 4096
    #include "rsa_types.h"
    RsaKeys_t* init_keys();
    void generate_keys(RsaKeys_t *rsa_keys);
    void clear_keys(RsaKeys_t *rsa_keys);

#ifdef __cplusplus
}
#endif

#endif /* GEN_KEYS_H */

