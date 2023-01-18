//
// Created by alon on 1/10/23.
//
#include "graph.h"
//#include "edges.c"
//#include "nodes.c"
//#include "algo.c"

int string_to_int(char *word);

int get_word(char *word);


int main() {
    pnode head = NULL;
    pnode *phead = &head;
    char flag = '0';
    while (scanf(" %c", &flag) != EOF) {


        if (flag == 'A') {
            build_graph_cmd(phead);
            head = *phead;
        }

        if (flag == 'n') {
            int source = 0;
            scanf(" %d", &source);
            addEdges(head, source);
        }

        if (flag == 'B') {
            int source = 0;
            scanf(" %d", &source);
            pnode pn = NULL;
            pnode *ppn = &pn;
            findNode(head, ppn, source);
            // if we found node
            if (pn != NULL) {
                //delete the exists node's edges
                freeEdges(pn->edges);
                pn->edges = NULL;
                // add to this node the new edges
                addEdges(head, source);
            } else {  //the node doesn't exist
                insert_node_cmd(phead, source);
                addEdges(head, source);
            }
        }

        if (flag == 'D') {
            int to_del = 0;
            if (scanf(" %d", &to_del) == 0) {
                printf("error while scanning in D case");
            }

            pnode pn = NULL;
            pnode *ppn = &pn;
            findNode(head, ppn, to_del);
            delete_node_cmd(phead, pn);
        }

        if (flag == 'S') {
            int start_num = 0;
            scanf(" %d", &start_num);
            dijkstra(head,start_num);
            //find dest node
            int dest_num;
            scanf(" %d", &dest_num);
            pnode pn = NULL;
            pnode *ppn = &pn;
            findNode(head, ppn, dest_num);
            //print the shortest path
            printf("Dijsktra shortest path: %d\n", pn->shortest_path);
        }

        if (flag == 'T') {
            p_str_int ans = TSP(head);
            printf("TSP shortest path: %d\n",ans->length);
            free(ans);
        }
        //printGraph_cmd(head);
        //printf("last input: %c\n", flag);

    }

}
