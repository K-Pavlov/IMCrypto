/* 
 * File:   main.c
 * Author: kaloyan
 *
 * Created on March 20, 2016, 6:18 PM
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include "crypto/rsa/rsa.h"
#include "helpers/logger.h"

int main (int argc, char** argv)
{
    RsaKeys_t rsa_keys; // = calloc(1, sizeof(rsa_keys));
    rsa_keys_init(&rsa_keys);
    rsa_get_keys(&rsa_keys);

    mpz_t message, encrypted, decrypted;
    mpz_inits(message, encrypted, decrypted, NULL);
    mpz_set_ui(message, 20304050);
    rsa_encrypt(encrypted, message, rsa_keys);
    gmp_printf("------------------------------Encrypted %Zd-----------------------------------", encrypted);
    rsa_decrypt(decrypted, encrypted, rsa_keys);
    gmp_printf("------------------------------Decrypted %Zd-----------------------------------", decrypted);
    return 0;
}
