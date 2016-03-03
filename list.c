#include "list.h"

list* concat(int i, int j, list* succ) {
    list* l = (list*)malloc(sizeof(list));
    l->i = i;
    l->j = j;
    l->succ = succ;
    return l;
}
