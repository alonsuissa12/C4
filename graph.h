#ifndef GRAPH_
#define GRAPH_
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

typedef struct GRAPH_NODE_ *pnode;

typedef struct edge_ {
    int weight;
    pnode endpoint;
    pnode startpoint;
    struct edge_ *next;
    // for stp
    int is_option;
} edge, *pedge;


typedef struct GRAPH_NODE_ {
    int node_num;
    pedge edges;
    struct GRAPH_NODE_ *next;
    // for dijkstra:
    int shortest_path;
    struct GRAPH_NODE_ *prev;
    pedge edge_to_me;
    int was_visited;
} node, *pnode;

int build_graph_cmd(pnode *head);
pnode insert_node_cmd(pnode *head, int num);
void delete_node_cmd(pnode *head, pnode to_delete);
void printGraph_cmd(pnode head); //for self debug
void deleteGraph_cmd(pnode* head);
void shortsPath_cmd(pnode head);
void TSP_cmd(pnode head);

int addEdges(pnode head,int index );
void dijkstra(pnode head,int start_num);

typedef struct str_int{
    char string[10000];
    int length;
}str_int, *p_str_int;

int * shortest_path( pnode *nodes ,int size, pnode, int * , int sum, int max_sum);
void TSP(pnode head );

int is_in_list(pnode *head, pnode n);
void findNode(pnode head ,pnode * pn, int num);

void freeEdges(pedge );
void freeNode(pnode );

#endif
