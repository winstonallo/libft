#include "vec.h"
#include "mem.h"
#include <assert.h>
#include <stdbool.h>
#include <stdint.h>

void
test_vec_new_capacity_0_should_allocate_n_elems() {
    Vec vec;
    uint8_t bytes[8] = {0};

    vec_new(&vec, bytes, 8, sizeof(char), 0);
    assert(vec.capacity == 8);
    assert(vec.n_elems == 8);
    vec_delete(&vec);
}

void
test_vec_new_capacity_larger_than_n_elems_should_allocate_capacity() {
    Vec vec;
    uint8_t bytes[8] = {0};

    vec_new(&vec, bytes, 8, sizeof(char), 16);
    assert(vec.capacity == 16);
    assert(vec.n_elems == 8);
    vec_delete(&vec);
}

void
test_vec_push_should_push_elem() {
    Vec vec;
    uint8_t bytes[8] = {0};
    uint8_t elem = 0x01;

    vec_new(&vec, bytes, 8, sizeof(char), 16);
    vec_push(&vec, &elem);
    assert(vec.capacity == 16);
    assert(vec.n_elems == 9);
    assert(((char *)vec.data)[8] == 0x01);
    vec_delete(&vec);
}

void
test_vec_push_should_push_elem_and_realloc_if_necessary() {
    Vec vec;
    uint8_t bytes[8] = {0};
    uint8_t elem = 0x01;

    vec_new(&vec, bytes, 8, sizeof(char), 0);
    vec_push(&vec, &elem);
    assert(vec.capacity == 16);
    assert(vec.n_elems == 9);
    assert(((char *)vec.data)[8] == 0x01);
    vec_delete(&vec);
}

void
test_vec_push_should_push_elem_complex_type() {
    Vec vec;
    Vec bytes = {0};
    Vec elem = {NULL, 42, 42, 42};

    vec_new(&vec, &bytes, 1, sizeof(Vec), 0);
    vec_push(&vec, &elem);
    assert(vec.capacity == 2);
    assert(vec.n_elems == 2);
    assert(((Vec *)vec.data)[1].capacity == 42);
    assert(((Vec *)vec.data)[1].n_elems == 42);
    assert(((Vec *)vec.data)[1].elem_size == 42);
    vec_delete(&vec);
}

void
test_vec_push_many_should_push_many() {
    Vec vec;
    uint8_t bytes[8] = {0};
    uint8_t elems[8] = {0x01, 0x02, 0x03, 0x04, 0x01, 0x02, 0x03, 0x04};

    vec_new(&vec, bytes, 8, sizeof(char), 0);
    vec_push_many(&vec, &elems, 8);
    assert(vec.capacity == 16);
    assert(vec.n_elems == 16);
    assert(ft_memcmp(vec.data + 8, elems, 8) == 0);
    vec_delete(&vec);
}

void
test_vec_push_many_should_push_many_complex_types() {
    Vec vec;
    Vec vecs[8] = {0};
    Vec elems[8] = {0};

    vec_new(&vec, vecs, 8, sizeof(Vec), 0);
    vec_push_many(&vec, &elems, 8);
    assert(vec.capacity == 16);
    assert(vec.n_elems == 16);
    assert(ft_memcmp(vec.data + 8 * sizeof(vec), elems, 8) == 0);
    vec_delete(&vec);
}

void
test_vec() {
    test_vec_new_capacity_0_should_allocate_n_elems();
    test_vec_new_capacity_larger_than_n_elems_should_allocate_capacity();
    test_vec_push_should_push_elem();
    test_vec_push_should_push_elem_complex_type();
    test_vec_push_should_push_elem_and_realloc_if_necessary();
    test_vec_push_many_should_push_many();
    test_vec_push_many_should_push_many_complex_types();
}
