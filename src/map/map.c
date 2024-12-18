#include <alloc.h>
#include <errno.h>
#include <map.h>
#include <mem.h>
#include <print.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <str.h>
#include <string.h>
#include <unistd.h>

__attribute__((always_inline)) static inline uint32_t
murmur3_32_scramble(uint32_t k) {
    k *= 0xcc9e2d51;
    k = (k << 15) | (k >> 17);
    k *= 0x1b873593;
    return k;
}

// Murmur3 *non-cryptographic* hash function. Used in hash tables for its good
// distribution properties.
//
// Hash output will differ based on endianness, but this does not change hash properties.
//
// https://en.wikipedia.org/wiki/MurmurHash
__attribute__((always_inline)) static inline uint32_t
murmur3_32(const uint8_t *key, uint64_t len) {
    uint32_t h = 0;
    uint32_t k;

    for (uint64_t idx = len >> 2; idx > 0; --idx) {
        ft_memcpy(&k, key, sizeof(uint32_t));
        key += sizeof(uint32_t);
        h ^= murmur3_32_scramble(k);
        h = (h << 13) | (h >> 19);
        h = h * 5 + 0xe6546b64;
    }

    k = 0;
    for (uint64_t idx = len & 3; idx > 0; --idx) {
        k <<= 8;
        k |= key[idx - 1];
    }

    h ^= murmur3_32_scramble(k);

    h ^= len;
    h ^= h >> 16;
    h *= 0x85ebca6b;
    h ^= h >> 13;
    h *= 0xc2b2ae35;
    h ^= h >> 16;
    return h;
}

// Load factor α = n / m,
// where n is the total number of entries in the hash table,
// and m is the number of allocated buckets.
//
// A high load factor will be more space efficient, but insertions/lookup
// will take longer, and vice versa.
__attribute__((always_inline)) static inline bool
max_load_factor_reached(HashMap *map) {
    return (float)map->n_entries / (float)map->n_buckets >= MAX_LOAD_FACTOR;
}

__attribute__((warn_unused_result)) HashMap *
map_new(uint32_t size) {
    HashMap *map = malloc(sizeof(HashMap));
    if (!map) {
        ft_printf(STDERR_FILENO, "map_new: could not allocate new map: %s\n", strerror(errno));
        return NULL;
    }

    map->n_buckets = size;
    map->n_entries = 0;

    map->buckets = ft_calloc(sizeof(Bucket), size);
    if (!map->buckets) {
        ft_printf(STDERR_FILENO, "map_new: could not allocate buckets for new map: %s\n", strerror(errno));
        free(map);
        return NULL;
    }

    return map;
}

__attribute__((warn_unused_result, always_inline)) static inline int
resize_and_rehash(HashMap *map) {
    Bucket *old_buckets = map->buckets;
    uint32_t old_size = map->n_buckets;

    map->buckets = ft_calloc(sizeof(Bucket), old_size * 2);
    if (!map->buckets) {
        ft_printf(STDERR_FILENO, "resize_and_rehash: memory allocation failure: %s\n", strerror(errno));
        return -1;
    }

    map->n_buckets *= 2;
    map->n_entries = 0;

    for (uint32_t i = 0; i < old_size; i++) {

        if (old_buckets[i].key != NULL) {
            int x = map_insert(map, old_buckets[i].key, old_buckets[i].content);
            (void)x;
        }
    }

    free(old_buckets);
    return 0;
}

// Inserts `content` into `map`, choosing the index based on `key`'s hash.
//
// Safety:
// - `key` is assumed to be a valid, null-terminated string.
__attribute__((warn_unused_result)) int
map_insert(HashMap *map, const char *key, void *content) {
    uint32_t idx = murmur3_32((uint8_t *)key, ft_strlen((char *)key)) % map->n_buckets;

    while (map->buckets[idx].key != NULL) {
        idx = (idx + 1) % map->n_buckets;
    }

    map->buckets[idx].key = key;
    map->buckets[idx].content = content;
    ++map->n_entries;

    if (max_load_factor_reached(map)) {
        if (resize_and_rehash(map) == -1) {
            return -1;
        }
    }

    return 0;
}

// Deletes the entry `key` from `map`.
//
// Errors:
// - `EINVAL` and `-1`: If `key` is not found in the map.
//
// Safety:
// - For performance reasons, the responsibility of freeing any allocated memory for
// the content or the key is left to the caller
__attribute__((warn_unused_result)) int
map_delete_key(HashMap *map, const char *key) {
    uint32_t idx = murmur3_32((uint8_t *)key, ft_strlen((char *)key)) % map->n_buckets;

    uint32_t tries = 0;

    while (ft_memcmp(map->buckets[idx].key, key, ft_strlen(key) + 1) != 0) {

        idx = (idx + 1) % map->n_buckets;
        if (++tries >= map->n_buckets) {
            errno = EINVAL;
            return -1;
        }
    }

    map->buckets[idx].key = NULL;
    map->buckets[idx].content = NULL;

    return 0;
}

void
map_delete(HashMap *map) {
    free(map->buckets);
    free(map);
}

// Gets the value at `key` in `map`.
//
// Errors:
// - `EINVAL` and `-1`: If `key` is not found in the map.
__attribute__((warn_unused_result)) void *
map_get(HashMap *map, const char *key) {
    uint32_t idx = murmur3_32((uint8_t *)key, ft_strlen((char *)key)) % map->n_buckets;

    for (uint32_t tries = 0; tries < map->n_buckets; ++tries) {

        if (map->buckets[idx].key && !ft_memcmp(map->buckets[idx].key, key, ft_strlen(key) + 1)) {
            return map->buckets[idx].content;
        }

        idx = (idx + 1) % map->n_buckets;
    }

    errno = EINVAL;
    return NULL;
}
