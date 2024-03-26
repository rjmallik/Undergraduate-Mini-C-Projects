#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"
#include "set.h"

struct hashtable {
    int slots;
    set_t **bins;
};

hashtable_t *hashtable_new(const int slots) {
    hashtable_t *ht = malloc(sizeof(hashtable_t));
    if (ht == NULL) {
        return NULL;
    }

    ht->slots = slots;
    ht->bins = malloc(slots * sizeof(set_t *));
    if (ht->bins == NULL) {
        free(ht);
        return NULL;
    }

    for (int i = 0; i < slots; i++) {
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

    return ht;
}

static int hash_function(hashtable_t *ht, const char *key) {
    int key_as_int = 0;
    for (int i = 0; key[i] != '\0'; i++) {
        key_as_int += key[i];
    }
    return key_as_int % ht->slots;
}

bool hashtable_insert(hashtable_t *ht, const char *key, void *item) {
    if (ht == NULL || key == NULL || item == NULL) {
        return false;
    }

    int bin_index = hash_function(ht, key);
    set_t *bin = ht->bins[bin_index];
    return set_insert(bin, key, item);
}

void *hashtable_find(hashtable_t *ht, const char *key) {
    if (ht == NULL || key == NULL) {
        return NULL;
    }

    int bin_index = hash_function(ht, key);
    set_t *bin = ht->bins[bin_index];
    return set_find(bin, key);
}

void hashtable_print(hashtable_t *ht, FILE *fp, void (*itemprint)(FILE *fp, const char *key, void *item)) {
    if (ht == NULL) {
        return;
    }

    for (int i = 0; i < ht->slots; i++) {
        set_t *bin = ht->bins[i];
        set_print(bin, fp, itemprint);
    }
}

void hashtable_iterate(hashtable_t *ht, void *arg, void (*itemfunc)(void *arg, const char *key, void *item)) {
    if (ht == NULL || itemfunc == NULL) {
        return;
    }

    for (int i = 0; i < ht->slots; i++) {
        set_t *bin = ht->bins[i];
        set_iterate(bin, arg, itemfunc);
    }
}

void hashtable_delete(hashtable_t *ht, void (*itemdelete)(void *item)) {
    if (ht == NULL) {
        return;
    }

    for (int i = 0; i < ht->slots; i++) {
        set_t *bin = ht->bins[i];
        set_delete(bin, itemdelete);
    }

    free(ht->bins);
    free(ht);
}
