// https://nvlpubs.nist.gov/nistpubs/legacy/sp/nistspecialpublication800-38d.pdf
// https://nvlpubs.nist.gov/nistpubs/FIPS/NIST.FIPS.197-upd1.pdf

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

// Performs AES-256-GCM authenticated encryption.
// .
// Encrypts the plaintext in `P->msg.data` and generates an authentication
// tag. The resulting ciphertext and tag are stored in `C`.
// .
// Notes:
// - The encryption may be performed in place by passing overlapping pointers
// for `P` and `C`. This will overwrite the original plaintext (`P->msg.data`)!
// - If the encrytion is not performed in place, `C->msg.data` and `C->aad.data`
// must have `P->msg.len` and `P->aad.len` bytes allocated, respectively.
// - The IV (`P->iv`) should be unique for each encryption with the same key.
// - AAD (`P->aad.data`) is authenticated but not encrypted!
void GCM_AE(Aes256Gcm *const P, Aes256Gcm *const C);

// Performs AES-256-GCM authenticated decryption.
// .
// Decrypts the ciphertext in `C->msg.data` and verifies its authenticity using
// the provided authentication tag (`C->tag`). The decrypted plaintext is stored
// in `P->msg.data` (provided the authentication step passed).
// .
// The return value marks the status of the authentication step (0 for success,
// non-zero for failure).
// .
// Notes:
// - The decryption may be performed in place by passing overlapping pointers
// for `C` and `P`. This will overwrite the original ciphertext (`C->msg.data`)!
// - If the encrytion is not performed in place, `P->msg.data` and `P->aad.data`
// must have, `C->msg.len` and `C->aad.len` bytes allocated, respectively.
// - The function verifies authenticity before returning plaintext.
// - If authentication fails, the content of `P->msg.data` is undefined.
int GCM_AD(Aes256Gcm *const C, Aes256Gcm *const P);

// Sets up the AES-256 context by expanding the provided key and storing the message.
void AES256_Init(Aes256Data *data, const uint8_t key[AES256_KEY_SIZE_BYTES], const uint8_t *const msg, const size_t msg_len);

uint8_t *InvCipher(uint8_t *in, uint8_t *const out, uint32_t *w);
uint8_t *Cipher(const uint8_t *in, uint8_t *const out, uint32_t *w);
uint32_t *KeyExpansion(const uint8_t key[AES256_KEY_SIZE_BYTES], uint32_t *const out);

#endif
