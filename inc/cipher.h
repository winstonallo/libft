
#ifndef CIPHER_H
#define CIPHER_H

#include <stddef.h>
#include <stdint.h>

#define AES256_BLOCK_SIZE_BYTES 16
#define AES256_KEY_SIZE_BYTES 32
#define AES256_EXPANDED_KEY_SIZE_U32 (4 * (14 + 1))
#define IV_LEN_BYTES 12
#define TAG_LEN_BYTES 16

typedef struct {
    uint8_t key[AES256_KEY_SIZE_BYTES];
    uint32_t expanded_key[AES256_EXPANDED_KEY_SIZE_U32];
    struct {
        uint8_t *data;
        size_t len;
    } msg;
} Aes256Data;

typedef struct {
    // Unexpanded key
    uint8_t key[AES256_KEY_SIZE_BYTES];
    // Expanded key (result of KeyExpansion(key))
    uint32_t expanded_key[AES256_EXPANDED_KEY_SIZE_U32];
    // Data to en/decrypt (P/C)
    struct {
        uint8_t *data;
        size_t len;
    } msg;
    // Additional Authenticated Data
    struct {
        uint8_t *data;
        size_t len;
    } aad;
    // Authentication tag generated during encryption
    uint8_t tag[16];
    // Initialization Vector
    uint8_t iv[12];
} Aes256Gcm;

int GCM_AD(Aes256Gcm *const C, Aes256Gcm *const P);
void GCM_AE(Aes256Gcm *const P, Aes256Gcm *const C);

void AES256_Init(Aes256Data *data, const uint8_t key[AES256_KEY_SIZE_BYTES], const uint8_t *const msg, const size_t msg_len);
uint8_t *InvCipher(uint8_t *in, uint8_t *const out, uint32_t *w);
uint8_t *Cipher(const uint8_t *in, uint8_t *const out, uint32_t *w);
uint32_t *KeyExpansion(const uint8_t key[AES256_KEY_SIZE_BYTES], uint32_t *const out);

#endif
