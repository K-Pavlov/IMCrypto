#include <gmp.h> 
#include "rsa_types.h"

void encrypt(mpz_t encrypted, const mpz_t message, RsaKeys_t rsa_keys) {
    mpz_powm(encrypted, message, rsa_keys.public_e, rsa_keys.public_n);
}

void decrypt(mpz_t decrypted, const mpz_t encrypted, RsaKeys_t rsa_keys) {
    mpz_powm(decrypted, encrypted, rsa_keys.private_d, rsa_keys.public_n);
}
