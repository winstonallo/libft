#ifndef MAP_H
#define MAP_H

#include <stdint.h>

#define MAX_LOAD_FACTOR 0.95

typedef struct Bucket {
    const char *key;
    void *content;
    struct Bucket *next;
} Bucket;

typedef struct Map {
    Bucket **buckets;
    uint32_t n_entries;
    uint32_t n_buckets;
} Map;

#endif
