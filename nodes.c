//
// Created by alon on 1/10/23.
//

#include "graph.h"

//creating the first node of the new graph
int build_graph_cmd(pnode *head) {
    //deleting the older graph
    if ((*head) != NULL) {
        deleteGraph_cmd(head);
    }
    int vertexes = 0;
    scanf(" %d", &vertexes);
    // creating the first node
    *head = (node *) (calloc(1, sizeof(node)));
    pnode prev = *head;
    if (*head == NULL) {
        return 0;
    }
    (*head)->node_num = 0;
    prev->shortest_path = INT_MAX;
    //crating the rest of the nodes and connect them
    for (int i = 1; i < vertexes; i++) {
        pnode p = (node *) (calloc(1, sizeof(node)));
        if (p == NULL) {
            return 0;
        }
        p->node_num = i;
        prev->next = p;
        p->shortest_path = INT_MAX;
        prev = p;
    }
    return 1;
}

//inserting new node to the end of the graph-list
pnode insert_node_cmd(pnode *head, int num) {
    pnode p_new_node = (node *) (malloc(sizeof(node)));
    if (p_new_node == NULL) {
        return NULL;
    }
    pnode current = *head;
    node new_node;
    new_node.next = 0;
    new_node.edges = 0;
    new_node.shortest_path = INT_MAX;
    new_node.prev = NULL;
    new_node.was_visited = 0;
    new_node.edge_to_me = NULL;
    *p_new_node = new_node;
    if (*head == NULL) {
        *head = p_new_node;
    } else {
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = p_new_node;
        p_new_node->node_num = num;
    }
    return p_new_node;
}

//deleting the node from the graph (and all the edges to it)
void delete_node_cmd(pnode *head, pnode to_delete) {
    int nodeNum = to_delete->node_num;
    pnode current = *head;
    pnode prev = NULL;
    // if we need to delete the first node
    if (to_delete == *head) {
        // check every node's edges and delete all the edged to the first node.
        while (current != NULL) {
            pedge cur_edge = current->edges;
            if (cur_edge != NULL) {
                // if the edge we want to delete its the first edge
                if (cur_edge->endpoint == to_delete) {
                    current->edges = cur_edge->next;
                    free(cur_edge);
                } else {
                    while (cur_edge->next != NULL) {
                        // if the next edge need to be deleted
                        if (cur_edge->next->endpoint == to_delete) {
                            pedge prev_egde = cur_edge;
                            pedge edge_to_del = prev_egde->next;
                            prev_egde->next = edge_to_del->next;
                            free(edge_to_del);
                            break;
                        }
                        cur_edge = cur_edge->next;
                    }
                }
            }
            current = current->next;
        }
        pnode free_node = (*head);
        (*head) = (*head)->next;
        free(free_node);
    } else {
        while (current != NULL) {
            if ((current->next) == to_delete) {
                prev = current;
            }
            //fined the edge of the current node to the delete-node (if exist)
            pedge current_edge = current->edges;

            if (current_edge != NULL) {
                //if its the first edge
                if (current_edge->endpoint->node_num == nodeNum) {
                    (current->edges) = current_edge->next;
                    free(current_edge);
                } else {
                    //at the end of the loop the current edge will be the prev edge of the edge we want to delete
                    while (current_edge->next != NULL && current_edge->next->endpoint->node_num != nodeNum) {
                        current_edge = current_edge->next;
                    }
                    //if the edge to the delete-node exists: delete it.
                    if (current_edge->next != NULL) {
                        pedge deleteEdge = current_edge->next;
                        current_edge->next = deleteEdge->next;
                        free(deleteEdge);
                    }
                }
            }
            current = current->next;
        }
        prev->next = to_delete->next;
        freeNode(to_delete);
    }
}

void printGraph_cmd(pnode head) {
    printf("the graph start with:\n");
    while (head != NULL) {
        printf("node: %d\n", head->node_num);

        pedge current_edge = head->edges;
        while (current_edge != NULL) {
            printf("\tedge to: %d ", (current_edge->endpoint)->node_num);
            printf(" in weight: %d \n", current_edge->weight);
            current_edge = current_edge->next;
        }

        printf("next node: \n");
        head = head->next;
    }
    printf("end of graph\n");
    printf("************************\n");
}

/*
*recursive function - 
*the idea is to go until the end of the list of graph nodes
*then , delete the nodes from end to start.
* I added the pointer "to_del" because "deleteGraph_cmd" getting a pointer to pointer 
*/
void deleteGraph_cmd(pnode *head) {

    pnode current = *head;
    if ((current)->next == NULL) {
        freeNode(current);
        return;
    }
    pnode pdel = current->next;
    pnode *ppdel = &pdel;
    deleteGraph_cmd(ppdel);
    freeNode(current);
    return;
}

//change pn to point on pointer to the node with node_num 'num'
void findNode(pnode head, pnode *ppn, int num) {
    pnode temp = head;
    while (temp != NULL) {
        if (temp->node_num == num) {
            *ppn = temp;
            return;
        } else {
            temp = temp->next;
        }
    }

}

void freeNode(pnode toFree) {
    freeEdges(toFree->edges);
    free(toFree);
}

void freeEdges(pedge toFree) {
    if (toFree != NULL) {
        if (toFree->next == NULL) {
            free(toFree);
            return;
        }
        freeEdges(toFree->next);
        free(toFree);
        return;
    }
}