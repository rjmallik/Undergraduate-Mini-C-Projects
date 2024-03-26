#include <stdlib.h>
#include <string.h>
#include "hashtable.h"
#include "set.h"

struct hashtable {
    set_t **bins; 
    int num_slots; 
};

static unsigned long hash_function(const char *key) {
    unsigned long hash = 5381;
    int c;

    while ((c = *key++)) {
        hash = ((hash << 5) + hash) + c;
    }

    return hash;
}

hashtable_t *hashtable_new(const int num_slots) {
    if (num_slots <= 0) {
        return NULL;
    }

    hashtable_t *ht = malloc(sizeof(hashtable_t));
    if (ht == NULL) {
        return NULL;
    }

    ht->bins = malloc(num_slots * sizeof(set_t *));
    if (ht->bins == NULL) {
        free(ht);
        return NULL;
    }

    for (int i = 0; i < num_slots; i++) {
        ht->bins[i] = set_new();
        if (ht->bins[i] == NULL) {
            for (int j = 0; j < i; j++) {
                set_delete(ht->bins[j], NULL);
            }
            free(ht->bins);
            free(ht);
            return NULL;
        }
    }

    ht->num_slots = num_slots;

    return ht;
}

bool hashtable_insert(hashtable_t *ht, const char *key, void *item) {
    if (ht == NULL || key == NULL || item == NULL) {
        return false;
    }

    unsigned long index = hash_function(key) % ht->num_slots;
    return set_insert(ht->bins[index], key, item);
}


void *hashtable_find(hashtable_t *ht, const char *key) {
    if (ht == NULL || key == NULL) {
        return NULL;
    }

    unsigned long index = hash_function(key) % ht->num_slots;
    return set_find(ht->bins[index], key);
}


void hashtable_print(hashtable_t *ht, FILE *fp,
                     void (*itemprint)(FILE *fp, const char *key, void *item)) {
    if (fp == NULL || ht == NULL) {
        return;
    }

    for (int i = 0; i < ht->num_slots; i++) {
        set_print(ht->bins[i], fp, itemprint);
    }
}

void hashtable_iterate(hashtable_t *ht, void *arg,
                       void (*itemfunc)(void *arg, const char *key, void *item)) {
    if (ht == NULL || itemfunc == NULL) {
        return;
    }

    for (int i = 0; i < ht->num_slots; i++) {
        set_iterate(ht->bins[i], arg, itemfunc);
    }
}


void hashtable_delete(hashtable_t *ht, void (*itemdelete)(void *item)) {
    if (ht == NULL) return;

    for (int i = 0; i < ht->num_slots; i++) {
        set_delete(ht->bins[i], itemdelete);
    }

    free(ht->bins);
    free(ht);
}
