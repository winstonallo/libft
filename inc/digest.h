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
    // State for the SHA-256 context, gets updated with each hashed block.
    struct Words state;
    // Stack buffer for hash input (one block).
    uint8_t buf[64];
    // Length of the buffer currently being processed (`data` in `sha256_stream_update`).
    size_t buf_len;
    // Total length of the hashed message, used for padding in the last block.
    size_t tot_len;
    // Set to `true` if the hashing process has been finalized.
    bool finalized;
} Sha256StreamingContext;

// Sets up the context with SHA-256's initial hash values and clears all buffers.
// This must be called beore any other streaming operations.
void sha256_stream_init(Sha256StreamingContext *const ctx);

// Process a chunk of data through the SHA-256 streaming context.
//
// This function can be called multiple times to incrementally hash large amounts of data. It
// handles block boundaries and buffering of incomplete blocks. For optimal performance on very
// large inputs, use a buffer of 64KB.
void sha256_stream_update(Sha256StreamingContext *const ctx, const uint8_t *data, size_t len);

// Applies SHA-256 padding, processes any remaining buffered data, and outputs the final hash
// as a NULL-terminated hex string.
void sha256_stream_final(Sha256StreamingContext *const ctx, char *out);

#endif
