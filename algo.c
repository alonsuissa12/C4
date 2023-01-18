//
// Created by alon on 1/10/23.
//

#include "graph.h"

//updates every the node's shortest_path to the shortest distance from the start node (UNT_MAX if path doesn't exist).
//also updates every node's prev point to node which the shortest path to this node come from (NULL if path doesn't exist).
//also update for every node, the node that leads to it.
void dijkstra(pnode head) {
    //finding the start vertex
    int start_num = 0;
    scanf(" %d", &start_num);

    pnode start = NULL;
    pnode *pstart = &start;
    findNode(head, pstart, start_num);
    //initialize all vertices
    pnode temp = head;
    while (temp != NULL) {
        temp->shortest_path = INT_MAX;
        temp->prev = NULL;
        temp->was_visited = 0;
        temp->edge_to_me = NULL;
        temp = temp->next;

    }
    //initialize start node
    pnode current = start;
    int distance = 0;
    int next_edge_weight = 0;
    current->prev = NULL;
    current->shortest_path = 0;
    int keepGoing = 1;
    while (keepGoing) {
        //fined the next node
        //for every node update the shortestPath and prev(if needed)
        pnode nextNode = NULL;
        pedge current_edge = current->edges;
        int next_node_distance = INT_MAX;
        while (current_edge != NULL) {
            // check every neighbor if we found shorter path to it. if we do- we will update its shortest path ,prev,edge_to_me
            if (current_edge->endpoint->shortest_path > distance + current_edge->weight) {
                current_edge->endpoint->shortest_path = distance + current_edge->weight;
                current_edge->endpoint->prev = current;
                current_edge->endpoint->edge_to_me = current_edge;
            }
            // the next node is the unvisited neighbor with the shortest path
            if ((current_edge->endpoint)->was_visited == 0) {
                if (current_edge->endpoint->shortest_path < next_node_distance) {
                    next_node_distance = current_edge->endpoint->shortest_path + distance;
                    nextNode = current_edge->endpoint;
                    next_edge_weight = current_edge->weight;
                }
            }
            current_edge = current_edge->next;
        }
        if (nextNode == NULL) {
            keepGoing = 0;
        } else {
            //change was_visited of current node
            current->was_visited = 1;
            distance = current->shortest_path + next_edge_weight;
            current = nextNode;
        }
    }
}

p_str_int TSP(pnode head) {
    //set to zero is option
    pnode temp_node_to_set = head;
    while (temp_node_to_set != NULL) {
        pedge temp_edge = temp_node_to_set->edges;
        while (temp_edge != NULL) {
            temp_edge->is_option = 0;
            temp_edge = temp_edge->next;
        }
        temp_node_to_set = temp_node_to_set->next;
    }
    // input
    int dest_ints[6] = {-1, -1, -1, -1, -1, -1};
    pnode dests_nodes[6] = {NULL, NULL, NULL, NULL, NULL, NULL};
    int index = 0;
    while (scanf(" %d", &dest_ints[index])) {
        pnode pn = NULL;
        pnode *ppn = &pn;
        findNode(head, ppn, dest_ints[index]);
        dests_nodes[index] = pn;
        index++;
    }
    int size = index;
    // if we only have one destenation
    if (size == 1) {
        p_str_int ans = (p_str_int) malloc(sizeof(str_int));
        ans->length = 0;
        char str_ans[2] = {(dest_ints[0] - '0'), '\0'};
        ans->string = str_ans;
        return ans;
    }
    //mark edges
    for (int i = 0; i < size - 1; i++) {
        dijkstra(dests_nodes[i]);
        for (int j = i + 1; j < size; j++) {
            pnode cur_node = dests_nodes[j];
            // if path desent exists return -1
            if (cur_node->shortest_path == INT_MAX) {
                p_str_int ans = (p_str_int) malloc(sizeof(str_int));
                ans->length = -1;
                char str_ans[3] = {'-', '1', '\0'};
                ans->string = str_ans;
                return ans;
            }
            pedge temp_edge = cur_node->edge_to_me;
            do {
                temp_edge->is_option = 1;
            } while (temp_edge->endpoint != dests_nodes[i]);
        }
    }
    int check_in[size];
    pnode passedby = NULL;
    pnode *p_passedby = &passedby;
    p_str_int min = (p_str_int) malloc(sizeof(str_int));
    min->length = INT_MAX;
    p_str_int temp = NULL;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            check_in[j] = 0;
        }
        temp = shortest_path(dests_nodes, size, p_passedby, dests_nodes[i], check_in);
        if (temp->length < min->length) {
            free(min);
            min = temp;
        } else {
            free(temp);
        }
    }
    return min;
}


p_str_int shortest_path(pnode *nodes, int size, pnode *passedby, pnode current, int *check_in) {

    int i = 0;
    for (; i < size; i++) {
        if (check_in[i] == 0) {
            break;
        }
    }
    // if all checked in
    if (i == size) {
        p_str_int pStrInt = (p_str_int) (malloc(sizeof(str_int)));
        char c_num = current->node_num;
        char str[3] = {c_num, ' ', '\0'};
        pStrInt->string = "";
        strncat(pStrInt->string, str, 3);
        pStrInt->length = 0;
        return pStrInt;
    }
    //check_in
    for (int j = 0; j < size; j++) {
        if ((*nodes)[j].node_num == current->node_num) {
            check_in[j] = 1;
            break;
        }
    }
    // add to passed_by
    insert_node_cmd(passedby, current->node_num);

    pedge current_edge = current->edges;
    p_str_int ans = NULL;
    int edge_w = 0;
    while (current_edge != NULL) {
        if (current_edge->is_option == 1) {
            if (is_in_list(passedby, current_edge->endpoint) == 0) {
                p_str_int temp = shortest_path(nodes, size, passedby, current_edge->endpoint, check_in);
                if (ans == NULL) {
                    ans = temp;
                    edge_w = current_edge->weight;
                } else {
                    if (temp != NULL && ans->length > temp->length)
                        free(ans);
                    ans = temp;
                    edge_w = current_edge->weight;
                }
            }
        }
        current_edge = current_edge->next;
    }

    // if no way to go (and didn't pass by all)
    if (ans == NULL) {
        return NULL;
    } else {
        char c_num = current->node_num;
        char str[3] = {c_num, ' ', '\0'};
        strncat(ans->string, str, 3);
        ans->length += edge_w;
        return ans;
    }

}

int is_in_list(pnode *head, pnode n) {
    pnode temp = (*head);
    while (temp != NULL) {
        if (temp->node_num == n->node_num)
            return 1;
        temp = temp->next;
    }
    return 0;
}


