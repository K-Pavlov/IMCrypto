/* 
 * File:   im_encryption.h
 * Author: kaloyan
 *
 * Created on May 25, 2016, 7:52 PM
 */

#include <stdlib.h>
#include <gmp.h>
#include "im_encryption.h"
#include "rsa/rsa.h"
#include "rsa/gen_keys.h"
#include "utilities.h"
#include "../helpers/memory.h"
#include "../../lib/aes256.h"
#define AES_KEY_SIZE 256

void im_encrypt(ImEncryptionData_t *encryption_data) 
{

}

void im_decrypt(ImDecryptionData_t *decryption_data) 
{
    
}

void set_aes_encryption_data(ImEncryptionData_t *encryption_data)
{
    mpz_t aes_rand_key, aes_rand_key_encrypted;
    mpz_inits(aes_rand_key, aes_rand_key_encrypted, NULL);
    generate_prime(aes_rand_key, AES_KEY_SIZE);
    rsa_encrypt(aes_rand_key_encrypted, aes_rand_key, *encryption_data->received_keys);
    
    int size = mpz_sizeinbase(aes_rand_key, BASE);    
    encryption_data->message->aes_key = im_calloc(size, sizeof(char));   
    gmp_sprintf(encryption_data->message->aes_key, "%Zd", aes_rand_key);
    
    size = mpz_sizeinbase(aes_rand_key_encrypted, BASE);
    encryption_data->message->aes_key_encrypted = im_calloc(size, sizeof(char));
    gmp_sprintf(encryption_data->message->aes_key_encrypted, "%Zd", aes_rand_key_encrypted);
    
    mpz_clears(aes_rand_key, aes_rand_key_encrypted, NULL);
}

ImEncryptionData_t* init_encryption_data(char* received_n, char* received_e)  
{
    ImEncryptionData_t *encryption_data = im_calloc(1, sizeof(ImEncryptionData_t));
    RsaKeys_t *keys = rsa_keys_init();
    ImMessageData_t *message = im_calloc(1, sizeof(ImMessageData_t));
    encryption_data->message = message;
    mpz_set_str(keys->public_n, received_n, RSA_BASE);
    mpz_set_str(keys->public_e, received_e, RSA_BASE); 
    encryption_data->received_keys = keys;
    
    set_aes_encryption_data(encryption_data);
    
    return encryption_data;
}

void set_aes_decrypted_data(ImDecryptionData_t *decryption_data, char* encrypted_aes_key)
{
    mpz_t encrypted, decrypted;
    mpz_inits(encrypted, decrypted, NULL);
    mpz_set_str(encrypted, encrypted_aes_key, BASE);
    
    rsa_decrypt(decrypted, encrypted, *decryption_data->personal_keys);
    int size = mpz_sizeinbase(decrypted, BASE);    
    decryption_data->message->aes_key = im_calloc(size, sizeof(char));   
    gmp_sprintf(decryption_data->message->aes_key, "%Zd", decrypted);    
    
    mpz_clears(encrypted, decrypted, NULL);
}

ImDecryptionData_t* init_decryption_data(char* encrypted_aes_key) 
{
    ImDecryptionData_t *decryption_data = im_calloc(1, sizeof(ImDecryptionData_t));
    RsaKeys_t *keys = rsa_keys_init();
    ImMessageData_t *message = im_calloc(1, sizeof(ImMessageData_t));
    decryption_data->message = message;
    rsa_keys_get(keys);
    decryption_data->personal_keys = keys;
    
    set_aes_decrypted_data(decryption_data, encrypted_aes_key);
    
    return decryption_data;
}

void clear_encryption_data(ImEncryptionData_t* encryption_data) 
{
    rsa_keys_clear(encryption_data->received_keys);
    free(encryption_data->message->aes_key);
    free(encryption_data->message->text);
    free(encryption_data);
}

void clear_decryption_data(ImDecryptionData_t* decryption_data) 
{
    rsa_keys_clear(decryption_data->personal_keys);
    free(decryption_data->message->aes_key);
    free(decryption_data->message->text);
    free(decryption_data);
}