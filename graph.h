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

int build_graph_cmd(pnode *head, int);
pnode insert_node_cmd(pnode *head, int num);
void delete_node_cmd(pnode *head, pnode to_delete);
void printGraph_cmd(pnode head); //for self debug
void deleteGraph_cmd(pnode* head);
void shortsPath_cmd(pnode head);
void TSP_cmd(pnode head);

int addEdge(pnode head,int index, int dest, int weight );
void dijkstra(pnode start,pnode head);

typedef struct str_int{
    char * string;
    int length;
}str_int, *p_str_int;

p_str_int shortest_path(pnode *nodes ,int size, pnode *, pnode, int *);

int is_in_list(pnode *head, pnode n);

void freeEdges(pedge );
void freeNode(pnode );

#endif
