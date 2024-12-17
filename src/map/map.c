#include <map.h>
#include <stdbool.h>

// Load factor α = n / m,
// where n is the total number of entries in the hash table,
// and m is the number of allocated buckets.
//
// A high load factor will be more space efficient, but insertions/lookup
// will take longer, and vice versa.
__attribute__((always_inline)) inline bool
max_load_factor_reached(Map *map) {
    return (float)map->n_entries / (float)map->n_buckets > MAX_LOAD_FACTOR;
}


