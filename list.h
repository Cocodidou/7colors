#ifndef LIST_H
#define LIST_H

#include <stdlib.h>

typedef struct list {
    int i;
    int j;
    struct list* succ;
} list ;

list* concat(int i, int j, list* succ);

#endif
