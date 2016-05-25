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
#include "networking/threads.h"

/*
void* say_what(void* what) 
{
    printf("%d\n" ,*(int*) what);
    return 0;
}

int main (int argc, char** argv)
{
    
    RsaKeys_t* rsa_keys = rsa_keys_init();
    rsa_get_keys(rsa_keys);

    mpz_t message, encrypted, decrypted;
    mpz_inits(message, encrypted, decrypted, NULL);
    mpz_set_ui(message, 203040504050);
    rsa_encrypt(encrypted, message, *rsa_keys);
    gmp_printf("------------------------------Encrypted %Zd-----------------------------------", encrypted);
    rsa_decrypt(decrypted, encrypted, *rsa_keys);
    gmp_printf("------------------------------Decrypted %Zd-----------------------------------", decrypted);
    
    
    char toSay[] = "stuffec bratko";
    int i;
    for(i = 0;;i++) {
        ThreadData_t* thread_data = init_thread_data(say_what, (void*) &i);
        create_thread(*thread_data);
        void **res;
       // *res = calloc(1, sizeof(int));
        join_thread(*thread_data, NULL);
    }
    //printf("%d\n", *(int*) *res);
    //clean_thread_data(thread_data);
    return 0;
}
*/

#include "crypto/im_encryption.h"
#include "helpers/memory.h"
int main() 
{
    RsaKeys_t* rsa_keys = rsa_keys_init();
    rsa_keys_get(rsa_keys);
    
    char* buffer_n, *buffer_e;
    int size = mpz_sizeinbase(rsa_keys->public_n, 10);    
    buffer_n = im_calloc(size, sizeof(char));   
    gmp_sprintf(buffer_n, "%Zd", rsa_keys->public_n);    
    
    size = mpz_sizeinbase(rsa_keys->public_e, 10);    
    buffer_e = im_calloc(size, sizeof(char));   
    gmp_sprintf(buffer_e, "%Zd", rsa_keys->public_e);  
    
    ImEncryptionData_t *endata = init_encryption_data(buffer_n, buffer_e);
    ImDecryptionData_t *dedata = init_decryption_data(endata->message->aes_key_encrypted);
    clear_encryption_data(endata);
    clear_decryption_data(dedata);
    
    return 0;
}
