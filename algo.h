//
// Created by alon on 1/10/23.
//

#ifndef HW4_ALGO_H
#define HW4_ALGO_H
#include "nodes.h"
#include <string.h>

void dijkstra(pnode start,pnode head);

typedef struct str_int{
    char * string;
    int length;
}str_int, *p_str_int;

p_str_int shortest_path(pnode *nodes ,int size, pnode *, pnode, int *);

int is_in_list(pnode *head, pnode n);

#endif //HW4_ALGO_H

