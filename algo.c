//
// Created by alon on 1/10/23.
//

#include "algo.h"

//updates every the node's shortest_path to the shortest distance from the start node (UNT_MAX if path doesn't exist).
//also updates every node's prev point to node which the shortest path to this node come from (NULL if path doesn't exist).
void dijkstra(pnode start,pnode head){
    //initialize all vertices
    pnode temp = head;
    while (temp != NULL){
        temp->shortest_path = INT_MAX;
        temp->prev = NULL;
        temp->was_visited = 0;
        temp = temp->next;
    }
    //initialize start node
    pnode current = start;
    int distance = 0;
    int next_edge_weight = 0;
    current->prev = NULL;
    current->shortest_path = 0;
    int keepGoing = 1;
    while (keepGoing){
        //fined the next node
        //for every node update the shortestPath and prev(if needed)
        pnode nextNode = NULL;
        pedge current_edge = current->edges;
        int next_node_distance = INT_MAX;
        while (current_edge != NULL){
            // check every neighbor if we found shorter path to it. if we do- we will update its shortest path and its prev
            if(current_edge->endpoint->shortest_path > distance + current_edge->weight){
                current_edge->endpoint->shortest_path = distance + current_edge->weight;
                current_edge->endpoint->prev = current;
            }
            // the next node is the unvisited neighbor with the shortest path
            if((current_edge->endpoint)->was_visited == 0){
                if(current_edge->endpoint->shortest_path < next_node_distance){
                    next_node_distance = current_edge->endpoint->shortest_path + distance;
                    nextNode = current_edge->endpoint;
                    next_edge_weight = current_edge ->weight
                }
            }
            current_edge = current_edge->next;
        }
        if(nextNode == NULL){
            keepGoing = 0;
        } else {
            //change was_visited of current node
            current->was_visited = 1;
            distance = current->shortest_path + next_edge_weight;
            current = nextNode;
        }
    }

}

