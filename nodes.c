//
// Created by alon on 1/10/23.
//

#include "nodes.h"
#include "graph.h"
#include <stdlib.h>

//creating the first node of the new graph
void build_graph_cmd(pnode *head){
    pnode p = (node*)(malloc(sizeof (node)));
    if(p_new_node == NULL) {
        head = NULL;
        return;
    }
    head = &p;
    node new_node;
    new_node.node_num = 0;
    new_node.next = 0;
    new_node.edges = 0;
    *(*head) = new_node;
}

//inserting new node to the end of the graph-list
void insert_node_cmd(pnode *head){
    int nodeNum = 0;
    pnode p_new_node = (node*)(malloc(sizeof (node)));
    if(p_new_node == NULL) {
        head = NULL;
        return;
    }
    pnode current = *head;
    node new_node;
    new_node.next = 0;
    new_node.edges=0;
    *p_new_node = new_node;
    while (current->next != NULL){
        current = current->next;
        nodeNum ++;
    }
    current->next = p_new_node;
    p_new_node->next=nodeNum
}

void delete_node_cmd(pnode *head, pnode to_delete){
    nodeNum = to_delete -> node_num;
    pnode current = *head;
    pnode prev;
    while (*current != NULL ){
        if((current->next)->node_num != nodeNum){
            prev = current;

        }
        pedge current_edge = current->edges;
        while (current_edge != NULL && current_edge -> endpoint -> node_num != nodeNum){
            current_edge = current_edge->next;
        }
        if(current_edge != NULL){
            pedge deleteEdge = current_edge->next;
            current_edge->next = deleteEdge -> next;
            free(deleteEdge);
        }
        current = current ->next;
    }
    prev->next = to_delete->next;
    freeNode(to_delete);
}

void freeNode(pnode toFree){
    freeEdges(toFree->edges);
    free(toFree);
}

freeEdges(pedge toFree){
    if(toFree->next == NULL){
        free(teFree);
        return;
    }
    return freeEdges(toFree->next);
}