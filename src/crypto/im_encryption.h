/* 
 * File:   im_encryption.h
 * Author: kaloyan
 *
 * Created on May 25, 2016, 7:52 PM
 */

#ifndef IM_ENCRYPTION_H
#define IM_ENCRYPTION_H

#ifdef __cplusplus
extern "C" {
#endif

#include "rsa/rsa.h"
    struct ImMessageData {
        char *aes_key_encrypted;
        char *aes_key;
        char *text;
    };
    
    typedef struct ImMessageData ImMessageData_t;
    
    struct ImEncryptionData {
        RsaKeys_t *received_keys;
        ImMessageData_t *message;
    };
    
    struct ImDecryptionData {
        RsaKeys_t *personal_keys;
        ImMessageData_t *message;
    };

    typedef struct ImEncryptionData ImEncryptionData_t;
    typedef struct ImDecryptionData ImDecryptionData_t;

    ImEncryptionData_t* init_encryption_data(char* received_n, char* received_e);
    ImDecryptionData_t* init_decryption_data(char* encrypted_aes_key);
    void clear_encryption_data(ImEncryptionData_t* encryption_data);
    void clear_decryption_data(ImDecryptionData_t* decryption_data);
    
#ifdef __cplusplus
}
#endif

#endif /* IM_ENCRYPTION_H */

