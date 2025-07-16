# LIBFT

When coding in C at 42, we are limited to using only basic functions and system calls. Typically allowed standard library functions include:

* `malloc`
* `free`
* `open`
* `close`
* `read`
* `write`

The very first project of the curriculum, `libft`, is about building your own library of utility functions. Back then, I was only trying to pass the project without thinking much about optimization — my printf implementation, for example, wrote output byte by byte without any buffering. I was also painfully unaware of data structures and their associated algorithms.

This repository is an improved version of my original libft. It includes optimized implementations of earlier functions (e.g., `ft_memset`, `ft_strlen`), and new ones I decided to build due to my interest in systems programming and efficient code. The idea for this "libft on steroids" started when I wrote my own implementation of the `SHA256` cryptographic hash function. Comparing the speed of my implementation to `openssl` was humbling, and it made me very interested in understanding where the huge performance gap was coming from.

## Compilation
Running `make` in the root of this repository will create a static library `libft.a`, which you can compile together with other C files.

## Features

### Core Utility Functions
_Note: This README only includes basic documentation, refer to the header files for full usage advice._
#### [Allocators](inc/alloc.h)
```c
// Allocates a buffer of size `bytes_new` and copies `old_buf` into it.
// Returns NULL on malloc failure, or if `bytes_old` is larger than `bytes_new`.
void *ft_realloc(void *old_buf, uint64_t bytes_new, uint64_t bytes_old) __attribute__((warn_unused_result));

// Allocates a buffer of size `nmemb * size`, 0-initialized bytes.
// Returns NULL on malloc failure, or if `nmemb * size` would result in a `uint64_t` overflow.
void *ft_calloc(uint64_t nmemb, uint64_t size) __attribute__((warn_unused_result));

// Returns a heap-allocated duplicate of `src`.
// Returns NULL on malloc failure.
void *ft_memdup(const void *src, const uint64_t bytes) __attribute__((warn_unused_result));
```
#### [Memory Operations](inc/mem.h)
`inc/mem.h`
```c
// Returns a pointer to the first occurence of `needle` in the first `n_bytes` of `haystack`.
// If nothing is found, returns a NULL pointer.
void *ft_memsrch(const void *haystack, int needle, uint64_t n_bytes);

// Compares the first `n_bytes` bytes `a` to `b`. Returns `0` if they are equal,
// or a non-zero u8 if not.
short ft_memcmp(const void *a, const void *b, uint64_t n_bytes);

// Copies the first `n_bytes` of `src` into `dest`.
void *ft_memcpy(void *dest, const void *src, uint64_t n_bytes);

// Sets the first `n_bytes` of `src` to `c`.
void *ft_memset(void *src, int c, uint64_t n_bytes);
```
#### [String Operations](inc/str.h)
```c
// Returns the number of bytes between `str` and the next `\0` character.
uint64_t ft_strlen(const char *str);

// Returns a heap-allocated duplicate of `str[start..start + len]`.
char *ft_substr(char const *str, unsigned int start, uint64_t len);

// Allocates and returns a new string with characters specified in `set` removed
// from the beginning and end of the input string `str`
char *ft_strtrim(char const *str, char const *set);

// Allocates and returns a string built by concatenating `a` and `b`.
char *ft_strjoin(char *a, char *b);

// Allocates and returns an array of strings built by splitting `str` by `delimiter`.
char **ft_split(char const *str, char delimiter);

// Returns a pointer to the first occurrence of `needle` in the first `n_bytes` of
// `haystack`. Returns a NULL pointer if nothing is found.
char *ft_strnstr(const char *haystack, const char *needle, uint64_t n_bytes);

// Converts all characters in `str` to lowercase.
char *ft_tolower(char *str);

// Converts all characters in `str` to uppercase.
char *ft_toupper(char *str);

// Converts a byte array `nptr` of base `base` into a `bits` bits `is_signed` integer, and stores the
// result into `out_value`.
bool ft_atob(const char *nptr, int base, int bits, void *out_value, bool is_signed);

// Converts a numeric value stored in `value` into a string representation in the specified `base`,
// and stores the result into the `buffer`.
bool ft_btoa(void *value, int base, int bits, char *buffer, uint64_t buffer_size, bool is_signed, bool uppercase);
```

#### [Output Operations](inc/print.h)
```c
ssize_t ft_printf(int fd, const char *s, ...);
```

#### [Ciphers](inc/cipher.h)
**AES-256-GCM**
```c
// Performs AES-256-GCM authenticated encryption.
// 
// Encrypts the plaintext in `P->msg.data` and generates an authentication
// tag. The resulting ciphertext and tag are stored in `C`.
void GCM_AE(Aes256Gcm *const P, Aes256Gcm *const C);

// Performs AES-256-GCM authenticated decryption.
// 
// Decrypts the ciphertext in `C->msg.data` and verifies its authenticity using
// the provided authentication tag (`C->tag`). The decrypted plaintext is stored
// in `P->msg.data` (provided the authentication step passed).
// 
// The return value marks the status of the authentication step (0 for success,
// non-zero for failure).
int GCM_AD(Aes256Gcm *const C, Aes256Gcm *const P);

// Sets up the AES-256 context by expanding the provided key and storing the message.
void AES256_Init(Aes256Data *data, const uint8_t key[AES256_KEY_SIZE_BYTES], const uint8_t *const msg, const size_t msg_len);
```
#### [Message Digests](inc/digest.h)
**SHA-256 (streaming)**
```c
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
```



### Data Structures

* **HashMap**: Hash map implementation. Collision resolution can be picked between Binary Search Tree and Linear Probing at compile time.

