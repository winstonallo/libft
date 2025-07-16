#include "cipher.h"
#include "bit.h"
#include "mem.h"
#include <assert.h>
#include <linux/limits.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

__attribute__((always_inline)) static inline void
GcmMul(const uint8_t X[16], const uint8_t Y[16], uint8_t out[16]) {
    uint8_t Z[16] = {0};
    uint8_t V[16];

    ft_memcpy(V, Y, 16);

    for (int i = 0; i < 128; ++i) {
        int bit = (X[i / 8] >> (7 - (i % 8))) & 1;

        if (bit == 1) {
            for (int j = 0; j < 16; ++j) {
                Z[j] ^= V[j];
            }
        }

        int lsb = V[15] & 1;

        for (int j = 15; j > 0; --j) {
            V[j] = (V[j] >> 1) | ((V[j - 1] & 1) << 7);
        }
        V[0] >>= 1;

        if (lsb == 1) {
            V[0] ^= 0xe1;
        }
    }

    ft_memcpy(out, Z, 16);
}

__attribute__((always_inline, unused)) static inline void
GHASH(const uint8_t H[16], const uint8_t *const data, size_t len, uint8_t out[16]) {
    uint8_t Y[16] = {0};

    for (size_t i = 0; i < len; i += 16) {
        uint8_t block[16] = {0};
        size_t block_len = (len - i) > 16 ? 16 : (len - i);

        ft_memcpy(block, data + i, block_len);

        for (int j = 0; j < 16; ++j) {
            Y[j] ^= block[j];
        }

        GcmMul(Y, H, Y);
    }

    ft_memcpy(out, Y, 16);
}

__attribute__((always_inline)) static inline void
GHASH_block(uint8_t Y[16], const uint8_t block[16], const uint8_t H[16]) {
    for (int i = 0; i < 16; ++i) {
        Y[i] ^= block[i];
    }
    GcmMul(Y, H, Y);
}

// `Y->msg.data` is expected to have at least `X->msg.len` bytes allocated.
// `X->msg.data` and `Y->msg.data` may overlap.
__attribute__((always_inline)) static inline void
GCTR(const uint8_t *const restrict ICB, const Aes256Data *const X, Aes256Data *const Y) {
    if (X->msg.len == 0) {
        ft_memcpy(Y->key, X->key, sizeof(X->key));
        ft_memcpy(Y->expanded_key, X->expanded_key, 60 * sizeof(uint32_t));
        Y->msg.len = 0;
        Y->msg.data = NULL;
        return;
    }

    uint8_t CB[16];
    ft_memcpy(CB, ICB, 16);

    const size_t n_complete_blocks = X->msg.len / AES256_BLOCK_SIZE_BYTES;
    const size_t partial_block_len = X->msg.len % AES256_BLOCK_SIZE_BYTES;
    for (size_t i = 0; i < n_complete_blocks; ++i) {
        uint8_t Ei[AES256_BLOCK_SIZE_BYTES];

        Cipher(CB, Ei, (uint32_t *)X->expanded_key);

        for (int j = 0; j < AES256_BLOCK_SIZE_BYTES; ++j) {
            Y->msg.data[(AES256_BLOCK_SIZE_BYTES * i) + j] = X->msg.data[(AES256_BLOCK_SIZE_BYTES * i) + j] ^ Ei[j];
        }

        if (i < n_complete_blocks - 1 || partial_block_len > 0) {
            uint32_t *counter_part = (uint32_t *)((uint8_t *)&CB + 12);
            *counter_part = BSWAP_32(BSWAP_32(*counter_part) + 1);
        }
    }

    if (partial_block_len > 0) {

        uint8_t Ei[AES256_BLOCK_SIZE_BYTES];
        Cipher(CB, Ei, (uint32_t *)X->expanded_key);

        for (size_t j = 0; j < partial_block_len; ++j) {
            Y->msg.data[(AES256_BLOCK_SIZE_BYTES * n_complete_blocks) + j] = X->msg.data[(AES256_BLOCK_SIZE_BYTES * n_complete_blocks) + j] ^ Ei[j];
        }
    }

    ft_memcpy(Y->key, X->key, sizeof(X->key));
    ft_memcpy(Y->expanded_key, X->expanded_key, sizeof(X->expanded_key));
    Y->msg.len = X->msg.len;
}

void
GCM_AE(Aes256Gcm *const P, Aes256Gcm *const C) {
    uint8_t H[AES256_BLOCK_SIZE_BYTES] = {0};
    Cipher(H, H, P->expanded_key);

    uint8_t J0[AES256_BLOCK_SIZE_BYTES] = {0};
    ft_memcpy(J0, P->iv, IV_LEN_BYTES);
    J0[15] |= 1;

    uint8_t J1[AES256_BLOCK_SIZE_BYTES] = {0};
    ft_memcpy(J1, J0, AES256_BLOCK_SIZE_BYTES);

    uint32_t *counter_part = (uint32_t *)((uint8_t *)&J1[IV_LEN_BYTES]);
    *counter_part = BSWAP_32(BSWAP_32(*counter_part) + 1);

    GCTR(J1, (Aes256Data *)P, (Aes256Data *)C);

    uint8_t Y[16] = {0};

    const size_t aad_blocks = P->aad.len / AES256_BLOCK_SIZE_BYTES;
    for (size_t i = 0; i < aad_blocks; ++i) {
        GHASH_block(Y, &P->aad.data[i * AES256_BLOCK_SIZE_BYTES], H);
    }
    const size_t aad_remainder = P->aad.len % AES256_BLOCK_SIZE_BYTES;
    if (aad_remainder > 0) {
        uint8_t padded_block[AES256_BLOCK_SIZE_BYTES] = {0};
        ft_memcpy(padded_block, P->aad.data + aad_blocks * 16, aad_remainder);
        GHASH_block(Y, padded_block, H);
    }

    const size_t msg_blocks = P->msg.len / AES256_BLOCK_SIZE_BYTES;
    for (size_t i = 0; i < msg_blocks; ++i) {
        GHASH_block(Y, &P->msg.data[i * AES256_BLOCK_SIZE_BYTES], H);
    }
    const size_t msg_remainder = P->msg.len % AES256_BLOCK_SIZE_BYTES;
    if (msg_remainder > 0) {
        uint8_t padded_block[AES256_BLOCK_SIZE_BYTES] = {0};
        ft_memcpy(padded_block, P->msg.data + msg_blocks * AES256_BLOCK_SIZE_BYTES, msg_remainder);
        GHASH_block(Y, padded_block, H);
    }

    uint64_t len_block[2] = {BSWAP_64(P->aad.len * 8), BSWAP_64(P->msg.len * 8)};
    GHASH_block(Y, (uint8_t *)len_block, H);

    uint8_t T[AES256_BLOCK_SIZE_BYTES];
    Cipher(J0, T, P->expanded_key);

    for (int i = 0; i < AES256_BLOCK_SIZE_BYTES; ++i) {
        C->tag[i] = Y[i] ^ T[i];
    }

    // tag and ciphertext are already written to C
    ft_memcpy(C->aad.data, P->aad.data, P->aad.len);
    ft_memcpy(C->iv, P->iv, IV_LEN_BYTES);
    ft_memcpy(C->expanded_key, P->expanded_key, AES256_EXPANDED_KEY_SIZE_U32);
    ft_memcpy(C->key, P->key, AES256_KEY_SIZE_BYTES);
    C->aad.len = P->aad.len;
    C->msg.len = P->msg.len;
}

int
GCM_AD(Aes256Gcm *const C, Aes256Gcm *const P) {
    uint8_t H[AES256_BLOCK_SIZE_BYTES] = {0};
    Cipher(H, H, C->expanded_key);

    uint8_t J0[AES256_BLOCK_SIZE_BYTES] = {0};
    ft_memcpy(J0, C->iv, IV_LEN_BYTES);
    J0[15] |= 1;

    uint8_t J1[AES256_BLOCK_SIZE_BYTES] = {0};
    ft_memcpy(J1, J0, AES256_BLOCK_SIZE_BYTES);
    uint32_t *counter_part = (uint32_t *)((uint8_t *)&J1[IV_LEN_BYTES]);
    *counter_part = BSWAP_32(BSWAP_32(*counter_part) + 1);

    uint8_t Y[16] = {0};

    const size_t aad_blocks = C->aad.len / AES256_BLOCK_SIZE_BYTES;
    for (size_t i = 0; i < aad_blocks; ++i) {
        GHASH_block(Y, &C->aad.data[i * AES256_BLOCK_SIZE_BYTES], H);
    }
    const size_t aad_remainder = C->aad.len % AES256_BLOCK_SIZE_BYTES;
    if (aad_remainder > 0) {
        uint8_t padded_block[AES256_BLOCK_SIZE_BYTES] = {0};
        ft_memcpy(padded_block, C->aad.data + aad_blocks * 16, aad_remainder);
        GHASH_block(Y, padded_block, H);
    }

    const size_t msg_blocks = C->msg.len / AES256_BLOCK_SIZE_BYTES;
    for (size_t i = 0; i < msg_blocks; ++i) {
        GHASH_block(Y, &C->msg.data[i * AES256_BLOCK_SIZE_BYTES], H);
    }
    const size_t msg_remainder = C->msg.len % AES256_BLOCK_SIZE_BYTES;
    if (msg_remainder > 0) {
        uint8_t padded_block[AES256_BLOCK_SIZE_BYTES] = {0};
        ft_memcpy(padded_block, C->msg.data + msg_blocks * AES256_BLOCK_SIZE_BYTES, msg_remainder);
        GHASH_block(Y, padded_block, H);
    }

    uint64_t len_block[2] = {BSWAP_64(C->aad.len * 8), BSWAP_64(C->msg.len * 8)};
    GHASH_block(Y, (uint8_t *)len_block, H);

    uint8_t T[AES256_BLOCK_SIZE_BYTES];
    Cipher(J0, T, C->expanded_key);

    uint8_t temp_tag[TAG_LEN_BYTES] = {0};
    for (int i = 0; i < AES256_BLOCK_SIZE_BYTES; ++i) {
        temp_tag[i] = Y[i] ^ T[i];
    }

    for (int i = 0; i < TAG_LEN_BYTES; ++i) {
        if (temp_tag[i] != C->tag[i]) {
            // verification failed
            return -1;
        }
    }

    // only decrypt if tag verification succeeds
    GCTR(J1, (Aes256Data *)C, (Aes256Data *)P);
    ft_memcpy(P->tag, temp_tag, TAG_LEN_BYTES);
    ft_memcpy(P->aad.data, C->aad.data, C->aad.len);
    ft_memcpy(P->iv, C->iv, IV_LEN_BYTES);
    ft_memcpy(P->expanded_key, C->expanded_key, AES256_EXPANDED_KEY_SIZE_U32);
    ft_memcpy(P->key, C->key, AES256_KEY_SIZE_BYTES);
    P->aad.len = C->aad.len;
    P->msg.len = C->msg.len;

    return 0;
}
