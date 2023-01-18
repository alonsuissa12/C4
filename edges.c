//
// Created by alon on 1/10/23.
//

#include "graph.h"

int addEdges(pnode head,int index) {

    int dest;
    int weight;
    // while the input is numbers
    while(scanf(" %d",&dest) == 1) {
        scanf(" %d", &weight);

        pedge edge_to_add = (pedge) (malloc(sizeof(edge)));
        if (edge_to_add == NULL) {
            return 0;
        }

        pnode sorce = NULL;
        pnode destenation = NULL;
        pnode temp = head;
        int found_sorce = 0;
        int found_dest = 0;
        while ((!found_dest) || (!found_sorce)) {
            if (temp->node_num == index) {
                sorce = temp;
                found_sorce = 1;
            }
            if (temp->node_num == dest) {
                destenation = temp;
                found_dest = 1;
            }
            temp = temp->next;
        }
        pedge head_edge = sorce->edges;
        edge_to_add->endpoint = destenation;
        edge_to_add->weight = weight;
        edge_to_add->next = head_edge;
        edge_to_add->is_option = 0;
        sorce->edges = edge_to_add;
    }

    return 1;
}