/* 
 * File:   rsa.c
 * Author: kaloyan
 *
 * Created on April 23, 2016, 11:32 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

#include "gen_keys.h"
#include "encrypt_decrypt.h"
#include "rsa_types.h"
#include "../../helpers/memory.h"
#include "../../helpers/folders.h"
#define BASE 10

void read_key_from_file(mpz_t number, FILE *fp);
void write_key_to_file(mpz_t number, FILE *fp);

void rsa_encrypt(mpz_t encrypted, const mpz_t message, RsaKeys_t rsa_keys) 
{
    encrypt(encrypted, message, rsa_keys);
}

void rsa_decrypt(mpz_t decrypted, const mpz_t encrypted, RsaKeys_t rsa_keys) 
{
    decrypt(decrypted, encrypted, rsa_keys);
}

void rsa_generate_keys(RsaKeys_t *rsa_keys) 
{
    generate_keys(rsa_keys);
}

void rsa_write_keys_to_file(RsaKeys_t rsa_keys, FILE *fp) 
{
    write_key_to_file(rsa_keys.public_e, fp);
    write_key_to_file(rsa_keys.public_n, fp);
    write_key_to_file(rsa_keys.private_d, fp);
}

void write_key_to_file(mpz_t number, FILE *fp) 
{
    char *buffer;
    int size = mpz_sizeinbase(number, 10);
    
    fwrite(&size, sizeof(size), 1, fp);
    buffer = im_calloc(size, sizeof(char));
    
    gmp_sprintf(buffer, "%Zd", number);
    fwrite(buffer, sizeof(char), size, fp);
    free(buffer);
}

void rsa_read_keys_from_file(RsaKeys_t *rsa_keys, FILE *fp) 
{
    read_key_from_file(rsa_keys->public_e, fp);
    read_key_from_file(rsa_keys->public_n, fp);
    read_key_from_file(rsa_keys->private_d, fp);
}

void read_key_from_file(mpz_t number, FILE *fp) 
{
    int length;
    char *buffer;
    
    fread(&length, sizeof(length), 1, fp);
    buffer = im_calloc(length + 1, sizeof(char));
    
    fread(buffer, sizeof(char), length, fp);
    mpz_set_str(number, buffer, BASE);
    free(buffer);
}

void rsa_keys_init(RsaKeys_t *rsa_keys) 
{
    init_keys(rsa_keys);
}

void rsa_get_keys(RsaKeys_t *rsa_keys) {
    if(file_exist("keys.bin")) {
        FILE *fp = fopen("keys.bin", "rb");
        rsa_read_keys_from_file(rsa_keys, fp);
        fclose(fp);
    } else {
        FILE *fp = fopen("keys.bin", "wb");
        rsa_generate_keys(rsa_keys);
        rsa_write_keys_to_file(*rsa_keys, fp);
        fclose(fp);
    }
}

void rsa_keys_clear(RsaKeys_t *rsa_keys) 
{
    clear_keys(rsa_keys);
}
