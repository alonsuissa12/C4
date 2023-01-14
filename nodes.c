//
// Created by alon on 1/10/23.
//

#include "nodes.h"

//creating the first node of the new graph
int build_graph_cmd(pnode *head, int vertexes) {
    // creating the first node
    *head = (node *) (calloc(1, sizeof(node)));
    pnode prev = *head;
    if (*head == NULL) {
        return 0;
    }
    (*head) ->node_num = 0;
    prev->shortest_path = INT_MAX;
    //crating the rest of the nodes and connect them
    for (int i = 1; i < vertexes; i++) {
        pnode p = (node *) (calloc(1, sizeof(node)));
        if (p == NULL) {
            return 0;
        }
        p ->node_num = i;
        prev->next = p;
        p->shortest_path = INT_MAX;
        prev = p;
    }
    return 1;
}

//inserting new node to the end of the graph-list
pnode insert_node_cmd(pnode *head, int num) {
    int nodeNum = 0;
    pnode p_new_node = (node *) (malloc(sizeof(node)));
    if (p_new_node == NULL) {
        return NULL;
    }
    pnode current = *head;
    node new_node;
    new_node.next = 0;
    new_node.edges = 0;
    new_node.shortest_path = INT_MAX;
    new_node.prev = NULL;
    new_node.was_visited = 0;
    *p_new_node = new_node;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = p_new_node;
    p_new_node->node_num = num;
    return p_new_node;
}

//deleting the node from the graph (and all the edges to it)
void delete_node_cmd(pnode *head, pnode to_delete) {
    int nodeNum = to_delete->node_num;
    pnode current = *head;
    pnode prev;
    while (current != NULL) {
        if ((current->next) == to_delete) {
            prev = current;
        }
        //fined the edge of the current node to the delete-node (if exist)
        pedge current_edge = current->edges;
        while (current_edge != NULL && current_edge->endpoint->node_num != nodeNum) {
            current_edge = current_edge->next;
        }
        //if the edge to the delete-node exists: delete it.
        if (current_edge != NULL) {
            pedge deleteEdge = current_edge->next;
            current_edge->next = deleteEdge->next;
            free(deleteEdge);
        }
        current = current->next;
    }
    prev->next = to_delete->next;
    freeNode(to_delete);
}

void printGraph_cmd(pnode head) {
    printf("the graph start with:\n");
    while (head != NULL) {
        printf("node: %d\n", head->node_num);

        printf("it's edges: ");
        pedge current_edge = head->edges;
        while (current_edge != NULL) {
            printf("edge to: %d ", (current_edge->endpoint)->node_num);
            printf("\n in weight: %d , ", current_edge->weight);
            current_edge = current_edge->next;
        }

        printf("next node: \n");
        head = head->next;
    }
    printf("end of graph");
}

/*
*recursive function - 
*the idea is to go until the end of the list of graph nodes
*then , delete the nodes from end to start.
* I added the pointer "to_del" because "deleteGraph_cmd" getting a pointer to pointer 
*/
void deleteGraph_cmd(pnode *head) {

    pnode current = *head;
    if ((current)->next == NULL) {
        freeNode(current);
        return;
    }
    pnode *to_del = &(current->next);
    deleteGraph_cmd(to_del);
    freeNode(current);
    return;
}


void freeNode(pnode toFree) {
    freeEdges(toFree->edges);
    free(toFree);
}

void freeEdges(pedge toFree) {
    if (toFree->next == NULL) {
        free(toFree);
        return;
    }
    freeEdges(toFree->next);
    free(toFree);
    return;
}