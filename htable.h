#ifndef __HTABLE_H__
#define __HTABLE_H__
#pragma once

#include <stdbool.h>


struct htable;
typedef struct htable htable_t;

struct htable_enum;
typedef struct htable_enum htable_enum_t;


// callback function declarations
typedef unsigned int (*htable_hash)(const void *in, unsigned int seed);
typedef void *(*htable_kcopy)(void *in);
typedef bool (*htable_keq)(const void *a, const void *b);
typedef void (*htable_kfree)(void *in);
typedef void *(*htable_vcopy)(void *in);
typedef void (*htable_vfree)(void *in);

typedef struct {
    htable_kcopy key_copy;
    htable_kfree key_free;
    htable_vcopy val_copy;
    htable_vfree val_free;
} htable_cbs;

// basic create & destroy
htable_t *htable_create(htable_hash hfunc, htable_keq keq, htable_cbs *cbs);
void htable_destroy(htable_t *ht);

// basic insert & remove
void htable_insert(htable_t *ht, void *key, void *val);
void htable_remove(htable_t *ht, void *key);

// basic retrieval
bool htable_get(htable_t *ht, void *key, void **val);
void *htable_get_direct(htable_t *ht, void *key);

// allows to get back data without specifying a key
htable_enum_t *htable_enum_create(htable_t *ht);
bool htable_enum_next(htable_enum_t *he, void **key, void **val);
void htable_enum_destroy(htable_enum_t *he);

#endif /* __HTABLE_H__ */
