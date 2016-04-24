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

int file_exist (char *filename)
{
  struct stat buffer;   
  return (stat (filename, &buffer) == 0);
}

int main ()
{
    RsaKeys_t rsa_keys; // = calloc(1, sizeof(rsa_keys));
    rsa_keys_init(&rsa_keys);
    //mpz_inits(rsa_keys.public_e, rsa_keys.public_n, rsa_keys.private_d, NULL);
    if(file_exist("keys.bin")) {
        FILE* fp = fopen("keys.bin", "rb");
        rsa_read_keys_from_file(&rsa_keys, fp);
        fclose(fp);
    } else {
        FILE* fp = fopen("keys.bin", "wb");
        rsa_generate_keys(&rsa_keys);
        rsa_write_keys_to_file(rsa_keys, fp);
        fclose(fp);
    }

    mpz_t message, encrypted, decrypted;
    mpz_inits(message, encrypted, decrypted, NULL);
    mpz_set_ui(message, 20304050);
    rsa_encrypt(encrypted, message, rsa_keys);
    gmp_printf("------------------------------Encrypted %Zd-----------------------------------", encrypted);
    rsa_decrypt(decrypted, encrypted, rsa_keys);
    gmp_printf("------------------------------Decrypted %Zd-----------------------------------", decrypted);
    return 0;
}
