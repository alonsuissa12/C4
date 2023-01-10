//
// Created by alon on 1/10/23.
//

#include "nodes.h"
#include <stdlib.h>
#include <stdio.h>

//creating the first node of the new graph
void build_graph_cmd(pnode *head){
    pnode p = (node*)(malloc(sizeof (node)));
    if(p == NULL) {
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
    p_new_node->node_num = nodeNum;
}

void delete_node_cmd(pnode *head, pnode to_delete){
    int nodeNum = to_delete -> node_num;
    pnode current = *head;
    pnode prev;
    while ( current != NULL ){
        if((current->next) == to_delete){
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

void printGraph_cmd(pnode head){
   printf ("the graph start with:\n");
    while (head != NULL){
        printf("node: %d\n" , head->node_num);
        
        printf("it's edges: ")  ;
        pedge current_edge = head->edges; 
         while (current_edge != NULL ){
            printf("edge to: %d " ,(current_edge->endpoint)->node_num );
            printf("\n in weight: %d , ", current_edge->weight);
         }

        printf("next node: \n");
        head = head->next;
    }
    printf("end of graph");
}

void deleteGraph_cmd(pnode* head){
    
}


void freeNode(pnode toFree){
    freeEdges(toFree->edges);
    free(toFree);
}

void freeEdges(pedge toFree){
    if(toFree->next == NULL){
        free(toFree);
        return;
    }
    return freeEdges(toFree->next);
}