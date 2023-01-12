//
// Created by alon on 1/10/23.
//
#include <stdio.h>
#include "nodes.h"
#include "edges.h"

int main() {
    char scan = '\0';
    pnode head = NULL;
    pnode *phead = &head;
    int num_nodes = 0;

    while (scan != EOF){
        scanf(" %c", &scan);
        if (start_letter == 'A') {
            // delete the older graph
            if(head != NULL){
                deleteGraph_cmd( phead);
            }
            // how many nodes in graph
            scanf("%d", &num_nodes);
            // initialize all the nodes in graph.
            if (!(build_graph_cmd(phead, num_nodes))) {
                printf("could not allocate");
                return 0;
            }
            scanf(" %c", &scan);
            while (scan == 'n'){

                int source = 0;
                scanf(" %d", &source);
                scanf(" %c", &scan);
                while ('1' <= scan <= '9'){
                    int dest = 0;
                    int weight = 0;

                    scanf(" %d", &weight);
                    addEdge(head, source, dest, weight );
                }
            }


        }





        // read which node we look now and initialize its edges:
        char n;
        scanf("%c", n);
        pnode current = firstnode;
        if (n == 'n') {
            int node;
            scanf("%d", node);

            while (current->node_num != node)
                current = current->next;
        }
        do {

            current->edges =

        } while (n != 'n');


    }

}