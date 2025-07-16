#ifndef MAP_H
#define MAP_H

#include <stdint.h>

#ifndef MAX_LOAD_FACTOR
#define MAX_LOAD_FACTOR 0.8
#endif

typedef struct Bucket {
    const char *key;
    void *content;
} Bucket;

// Hash table implemenation to store `void *` content along with `const char *` keys.
// .
// The map will self-resize as soon as the load factor (`n_entries / n_buckets`) reaches the default value of `0.8`. The
// default value can be overridden at compile time with `-DMAX_LOAD_FACTOR=<load factor>`.
// The resizing logic is a simple exponential backoff.
// .
// Collision resolution is made using linear probing.
// .
// https://en.wikipedia.org/wiki/Open_addressing
//
// https://en.wikipedia.org/wiki/Linear_probing
typedef struct HashMap {
    Bucket *buckets;
    uint32_t n_entries;
    uint32_t n_buckets;
} HashMap;

// Creates a new HashMap (hash table) with an initial number of buckets specified by `size`.
// .
// Returns a pointer to the newly allocated map if successful, or NULL if not.
// .
// Errors:
// - If memory allocation fails for the `HashMap` or its `Bucket` table, returns NULL.
HashMap *map_new(uint32_t size);

// Looks up `key` in `map`, returns a `void *` to its content.
// .
// Errors:
// - If `key` is not found in `map`, returns NULL and sets errno to `EINVAL`.
void *map_get(HashMap *map, const char *key);

// Removes the entry at `key` from `map`.
// .
// Errors:
// - If `key` is not found in `map`, returns -1 and sets errno to `EINVAL`.
// .
// Safety:
// - Note that the ownership of the `key` and `content` fields in the bucket is not taken by
// `HashMap`, meaning the responsibility to free that memory (if heap-allocated) is on the caller.
int map_delete_key(HashMap *map, const char *key);

// Inserts `content` at `key` in `map`.
// .
// Errors:
// - If `map` needs to be resized and the reallocation fails, returns -1.
// .
// Safety:
// - Note that the ownership of the `key` and `content` fields in the bucket is not taken by
// `HashMap`, meaning the responsibility to free that memory (if heap-allocated) is on the caller.
int map_insert(HashMap *map, const char *key, void *content);

// Frees all allocated memory for `map` and its `Bucket` array.
// .
// Safety:
// - Note that the ownership of the `key` and `content` fields in the bucket is not taken by
// `HashMap`, meaning the responsibility to free that memory (if heap-allocated) is on the caller.
void map_delete(HashMap *map);

#endif
