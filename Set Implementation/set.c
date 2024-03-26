#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "set.h"

typedef struct node {
    char *key;
    void *item;
    struct node *next;
} node_t;

typedef struct set {
    node_t *head;
} set_t;

set_t *set_new(void) {
    set_t *set = malloc(sizeof(set_t));
    if (set != NULL) {
        set->head = NULL;
    }
    return set;
}

bool set_insert(set_t *set, const char *key, void *item) {
    if (set == NULL || key == NULL || item == NULL) {
        return false;
    }

    node_t *current = set->head;
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            return false;  
        }
        current = current->next;
    }

    node_t *new_node = malloc(sizeof(node_t));
    if (new_node == NULL) {
        return false; 
    }
    new_node->key = strdup(key); 
    new_node->item = item;
    new_node->next = set->head;
    set->head = new_node;

    return true;
}

void *set_find(set_t *set, const char *key) {
    if (set == NULL || key == NULL) {
        return NULL;
    }

    node_t *current = set->head;
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            return current->item; 
        }
        current = current->next;
    }

    return NULL;  
}


void set_print(set_t *set, FILE *fp, void (*itemprint)(FILE *fp, const char *key, void *item)) {
    if (fp == NULL) {
        return;
    }

    if (set == NULL) {
        fprintf(fp, "(null)\n");
        return;
    }

    node_t *current = set->head;
    while (current != NULL) {
        itemprint(fp, current->key, current->item);
        current = current->next;
    }
}


void set_iterate(set_t *set, void *arg, void (*itemfunc)(void *arg, const char *key, void *item)) {
    if (set == NULL || itemfunc == NULL) {
        return;
    }

    node_t *current = set->head;
    while (current != NULL) {
        itemfunc(arg, current->key, current->item);
        current = current->next;
    }
}

void set_delete(set_t *set, void (*itemdelete)(void *item)) {
    if (set == NULL) {
        return;
    }

    node_t *current = set->head;
    while (current != NULL) {
        node_t *next = current->next;
        if (itemdelete != NULL) {
            itemdelete(current->item);
        }
        free(current->key);
        free(current);
        current = next;
    }

    free(set);
}
