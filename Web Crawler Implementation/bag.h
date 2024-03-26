#ifndef BAG_H
#define BAG_H

typedef struct {
    void** data;
    int capacity;
    int size;
} bag_t;

bag_t* bag_new();
void bag_insert(bag_t* bag, void* item);
void* bag_extract(bag_t* bag);
int bag_is_empty(bag_t* bag);
void bag_delete(bag_t* bag);

#endif /* BAG_H */