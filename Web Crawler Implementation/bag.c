#include "bag.h"
#include <stdlib.h>

bag_t* bag_new() {
    bag_t* bag = malloc(sizeof(bag_t));
    if (bag != NULL) {
        bag->data = NULL;
        bag->capacity = 0;
        bag->size = 0;
    }
    return bag;
}

void bag_insert(bag_t* bag, void* item) {
    if (bag->size == bag->capacity) {
        int newCapacity = (bag->capacity == 0) ? 1 : 2 * bag->capacity;
        void** newData = realloc(bag->data, newCapacity * sizeof(void*));
        if (newData == NULL) {
            return;
        }
        bag->data = newData;
        bag->capacity = newCapacity;
    }

    bag->data[bag->size++] = item;
}

void* bag_extract(bag_t* bag) {
    if (bag->size > 0) {
        void* item = bag->data[--bag->size];
        return item;
    }
    return NULL;
}

int bag_is_empty(bag_t* bag) {
    return (bag->size == 0);
}

void bag_delete(bag_t* bag) {
    if (bag != NULL) {
        free(bag->data);
        free(bag);
    }
}