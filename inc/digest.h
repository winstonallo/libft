#ifndef DIGEST_H
#define DIGEST_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef struct Words {
    uint32_t a;
    uint32_t b;
    uint32_t c;
    uint32_t d;
    uint32_t e;
    uint32_t f;
    uint32_t g;
    uint32_t h;
} Words;

typedef struct Sha256StreamingContext {
    struct Words state;
    uint8_t buf[64];
    size_t buf_len;
    size_t tot_len;
    bool finalized;
} Sha256StreamingContext;

void sha256_stream_final(Sha256StreamingContext *const ctx, char *out);
void sha256_stream_update(Sha256StreamingContext *const ctx, const uint8_t *data, size_t len);
void sha256_stream_init(Sha256StreamingContext *const ctx);

#endif
