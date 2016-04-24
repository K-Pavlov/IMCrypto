/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   utilities.h
 * Author: kaloyan
 *
 * Created on April 18, 2016, 6:38 PM
 */

#ifndef UTILITIES_H
#define UTILITIES_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdint.h>
#include <gmp.h>
#include "rsa/gen_keys.h"
    
    uint64_t get_random_number();

#ifdef __cplusplus
}
#endif

#endif /* UTILITIES_H */

