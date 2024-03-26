#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lru.h"

typedef struct lru_node {
    char* key;
    void* item;
    struct lru_node* prev;
    struct lru_node* next;
} lru_node_t;

typedef struct lru {
    int max_size;
    int size;
    lru_node_t* head;
    lru_node_t* tail;
    lru_node_t** cache;
} lru_t;

unsigned long hash(const char* str) {
    unsigned long hash = 5381;
    int c;

    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c;
    }

    return hash;
}

lru_t* lru_new(const int max_size) {
    if (max_size <= 0) {
        return NULL;
    }

    lru_t* lru = malloc(sizeof(lru_t));
    if (lru == NULL) {
        return NULL;
    }

    lru->max_size = max_size;
    lru->size = 0;
    lru->head = NULL;
    lru->tail = NULL;

    lru->cache = calloc(max_size, sizeof(lru_node_t*));
    if (lru->cache == NULL) {
        free(lru);
        return NULL;
    }

    return lru;
}

bool lru_insert(lru_t* lru, const char* key, void* item) {
    if (lru == NULL || key == NULL || item == NULL) {
        return false;
    }

    unsigned long index = hash(key) % lru->max_size;
    lru_node_t* node = lru->cache[index];

    while (node != NULL) {
        if (strcmp(node->key, key) == 0) {
            return false;
        }
        node = node->next;
    }

    lru_node_t* new_node = malloc(sizeof(lru_node_t));
    if (new_node == NULL) {
        return false;
    }

    new_node->key = strdup(key);
    if (new_node->key == NULL) {
        free(new_node);
        return false;
    }

    new_node->item = item;
    new_node->prev = NULL;
    new_node->next = NULL;

    if (lru->head == NULL) {
        lru->head = new_node;
        lru->tail = new_node;
    } else {
        new_node->next = lru->head;
        lru->head->prev = new_node;
        lru->head = new_node;
    }

    lru->cache[index] = new_node;

    if (lru->size == lru->max_size) {
        lru_node_t* remove_node = lru->tail;
        lru->tail = remove_node->prev;
        lru->tail->next = NULL;

        unsigned long remove_index = hash(remove_node->key) % lru->max_size;
        lru->cache[remove_index] = NULL;

        free(remove_node->key);
        free(remove_node);
    } else {
        lru->size++;
    }

    return true;
}

void* lru_find(lru_t* lru, const char* key) {
    if (lru == NULL || key == NULL) {
        return NULL;
    }

    unsigned long index = hash(key) % lru->max_size;
    lru_node_t* node = lru->cache[index];

    while (node != NULL) {
        if (strcmp(node->key, key) == 0) {
            if (node != lru->head) {
                if (node == lru->tail) {
                    lru->tail = node->prev;
                    lru->tail->next = NULL;
                } else {
                    node->prev->next = node->next;
                    node->next->prev = node->prev;
                }

                node->prev = NULL;
                node->next = lru->head;
                lru->head->prev = node;
                lru->head = node;
            }

            return node->item;
        }

        node = node->next;
    }

    return NULL;
}

void lru_print(lru_t* lru, FILE* fp, void (*itemprint)(FILE* fp, const char* key, void* item)) {
    if (lru == NULL) {
        fprintf(fp, "(null)\n");
        return;
    }

    if (itemprint == NULL) {
        fprintf(fp, "\n");
        return;
    }

    lru_node_t* node = lru->head;
    while (node != NULL) {
        itemprint(fp, node->key, node->item);
        node = node->next;
    }
}

void lru_iterate(lru_t* lru, void* arg, void (*itemfunc)(void* arg, const char* key, void* item)) {
    if (lru == NULL || itemfunc == NULL) {
        return;
    }

    lru_node_t* node = lru->head;
    while (node != NULL) {
        itemfunc(arg, node->key, node->item);
        node = node->next;
    }
}

void lru_delete(lru_t* lru, void (*itemdelete)(void* item)) {
    if (lru == NULL) {
        return;
    }

    lru_node_t* node = lru->head;
    while (node != NULL) {
        lru_node_t* next = node->next;
        if (itemdelete != NULL) {
            itemdelete(node->item);
        }
        free(node->key);
        free(node);
        node = next;
    }

    free(lru->cache);
    free(lru);
}
