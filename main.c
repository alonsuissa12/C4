//
// Created by alon on 1/10/23.
//
#include <stdio.h>
#include "nodes.h"

void main () {
char start_letter='\0';
scanf("insert a char: %c" , start_letter );
if (start_letter == 'A'){
    int num_nodes;
    // how much nodes in graph
    scanf("%d" , num_nodes);
// initilaize the graph with node 0 
    pnode firstnode;
    firstnode->node_num = 0 ;
    build_graph_cmd(firstnode);
   // initialize all the nodes in graph.
    for (int i =1 ; i<num_nodes; i++ ){
        insert_node_cmd(firstnode);
    }
    // read which node we look now and initialize its edges:
    char n;
    scanf("%c" , n);
    pnode current = firstnode;
    if (n =='n'){
        int node;
        scanf("%d" , node);
        
        while (current->node_num != node)
            current  = current->next;
    }
    do {
        
        current->edges = 

    }while (n !='n');
     




    
}

}