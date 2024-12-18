#ifndef MAP_H
#define MAP_H

#include <stdint.h>

#define MAX_LOAD_FACTOR 0.8

typedef struct Bucket {
    const char *key;
    void *content;
} Bucket;

typedef struct Map {
    Bucket *buckets;
    uint32_t n_entries;
    uint32_t n_buckets;
} Map;

// Looks up `key` in `map`, returns a `void *` to its content if found, else
// NULL.
void *map_get(Map *map, const char *key);
int map_delete_key(Map *map, const char *key);
int map_insert(Map *map, const char *key, void *content);
Map *map_new(uint32_t size);
void map_delete(Map *map);

#endif
