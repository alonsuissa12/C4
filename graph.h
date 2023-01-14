#ifndef GRAPH_
#define GRAPH_

typedef struct GRAPH_NODE_ *pnode;

typedef struct edge_ {
    int weight;
    pnode endpoint;
    struct edge_ *next;
} edge, *pedge;


typedef struct GRAPH_NODE_ {
    int node_num;
    pedge edges;
    struct GRAPH_NODE_ *next;
    // for dijkstra:
    int shortest_path;
    struct GRAPH_NODE_ *prev;
    int was_visited;
} node, *pnode;

int build_graph_cmd(pnode *head, int);
pnode insert_node_cmd(pnode *head, int num);
void delete_node_cmd(pnode *head, pnode to_delete);
void printGraph_cmd(pnode head); //for self debug
void deleteGraph_cmd(pnode* head);
void shortsPath_cmd(pnode head);
void TSP_cmd(pnode head);

#endif
