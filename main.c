//
// Created by alon on 1/10/23.
//
#include "graph.h"



int string_to_int(char *word);

int get_word(char *word);

int main() {
    char scan = '\0';
    pnode head = NULL;
    pnode *phead = &head;
    int num_nodes = 0;
    int keep_going = 1;
    char word[10];
    while (scan != EOF && keep_going) {
        scanf(" %c", &scan);
        if (scan == 'A') {
            // delete the older graph
            if (head != NULL) {
                deleteGraph_cmd(phead);
            }
            // how many nodes in graph
            scanf(" %d", &num_nodes);
            // initialize all the nodes in graph.
            if (!(build_graph_cmd(phead, num_nodes))) {
                printf("could not allocate");
                return 0;
            }
            scanf(" %c", &scan);
            // if the user want to add edges
            while (scan == 'n') {
                //getting the source
                int len_of_word = get_word(word);
                int source = string_to_int(word);
                if (len_of_word == -1) {
                    keep_going = 0;
                } else {
                    while (1) {
                        len_of_word = get_word(word);
                        if (len_of_word == -1) {
                            keep_going = 0;
                            break;
                        }
                        if (len_of_word == 1) {
                            // if the length of the input is 1: check if this is the end of the adding edges input.
                            if ('0' > word[0] || word[0] > '9') {
                                //if it is: keep the input char in scan and get out of the adding edges lop.
                                scan = word[0];
                                break;
                            }
                        }
                        // getting the destination
                        int dest = string_to_int(word);
                        len_of_word = get_word(word);
                        int weight = string_to_int(word);
                        addEdge(head, source, dest, weight);
                        //if we got EOF: exit all the loops.
                        if (len_of_word == -1) {
                            keep_going = 0;
                            break;
                        }
                    }
                }
            }
        }
        if (scan == 'B') {
            if (get_word(word) == -1) {
                keep_going = 0;
            }
            int source = string_to_int(word);
            pnode current = head;
            int deleted = 0;
            while (current != NULL && deleted == 0) {
                if (current->node_num == source) {
                    delete_node_cmd(phead, current);
                    deleted = 1;
                }
                current = current->next;
            }
            insert_node_cmd(phead, source);
            //adding edges
            while (1) {
                int word_len = get_word(word);
                if (word_len == -1) {
                    keep_going = 0;
                    break;
                }
                if (word_len == 1) {
                    if (word_len < '0' || word_len > '9') {
                        scan = word[0];
                        break;
                    }
                }
                int dest = string_to_int(word);
                word_len = get_word(word);
                int weight = string_to_int(word);
                addEdge(head, source, dest, weight);
                if (word_len == -1) {
                    keep_going = 0;
                    break;
                }
            }
        }
        if (scan == 'D') {
            if (get_word(word) == -1) {
                keep_going = 0;
            }
            int node_index = string_to_int(word);
            pnode to_delete = head;
            while (to_delete != NULL) {
                if (node_index == to_delete->node_num) {
                    delete_node_cmd(phead, to_delete);
                    break;
                }
                to_delete = to_delete->next;
            }
        }
        if (scan == 'S') {
            int source = 0;
            int dest = 0;
            get_word(word);
            source = string_to_int(word);
            if (get_word(word) == -1) {
                keep_going = 0;
            }
            dest = string_to_int(word);
            pnode temp = head;
            pnode source_node = NULL;
            pnode dest_node = NULL;
            int found = 0;
            while (temp != NULL) {
                if (temp->node_num == source) {
                    source_node = temp;
                    found += 1;
                }
                if (temp->node_num == dest) {
                    dest_node = temp;
                    found += 1;
                }
                if (found == 2) {
                    break;
                }
            }
            dijkstra(source_node, head);
            int distance = dest_node->shortest_path;
            printf("%d\n", distance);
        }
        if (scan == 'T') {
            int int_nodes_to_visit[6];
            pnode nodes_to_visit[6];
            int nodes_index = 0;
            int index = 0;
            int size = 0;
            for (int i = 0; i < 6; i++) {
                int_nodes_to_visit[i] = -1;
                nodes_to_visit[i] = NULL;
            }
            // input
            word[0] = '0';
            while (word[0] >= '0' && word[0] <= '9') {
                if (get_word(word) == -1) {
                    keep_going = 0;
                }
                int_nodes_to_visit[index] = string_to_int(word);
                index++;
            }
            pnode temp = head;
            while (temp != NULL) {
                int num = temp->node_num;
                for (int i = 0; i < 6; i++) {
                    if (num == int_nodes_to_visit[i]) {
                        nodes_to_visit[nodes_index] = temp;
                        nodes_index++;
                    }
                }
                // set to zore is_option of every edge
                pedge e = temp->edges;
                while (e != NULL) {
                    e->is_option = 0;
                    e = e->next;
                }
                temp = temp->next;
            }
            size = nodes_index;
            nodes_index = 0;
            //dijkstra on each *and mark all the edges of the shortest path*
            for (int i = 0; i < size && nodes_to_visit[i] != NULL; i++) {
                dijkstra(nodes_to_visit[i], head);
                for (int j = i + 1; j < size && nodes_to_visit[j] != NULL; j++) {
                    pnode end = nodes_to_visit[j];
                    while (end != nodes_to_visit[i]) {
                        end->edge_to_me->is_option = 1;
                        end = end->prev;
                    }
                }
            }
            // check all the option paths on marked edges and choose the shortest

            p_str_int min_path = NULL;
            for (int i = 0; i < size; i++) {
                int check_in2[size];
                for (int j = 0; j < size; j++) {
                    check_in2[j] = 0;
                }
                pnode *pb_head = NULL;
                build_graph_cmd(pb_head, 1);
                (*pb_head)->node_num = -1;
                p_str_int temp_path = shortest_path(nodes_to_visit, size, pb_head, nodes_to_visit[i], check_in2);
                if (min_path == NULL) {
                    min_path = temp_path;
                } else {
                    if (temp_path != NULL) {
                        if (temp_path->length < min_path->length)
                            min_path = temp_path;
                    }
                }
                deleteGraph_cmd(pb_head);
            }
            if(min_path == NULL){
                printf("%d", -1);
            } else{
                char * to_print = min_path->string;
                //deleting the last space (' ').
                to_print[strlen(to_print)-1] = '\0';
                printf("%s",to_print);
            }


        }


    }
    return 0;
}

// get the next word from the stdin to the input string 'word'.
//return the length of the word or -1 if got EOF.
//NOTE: this function also gets one char after the word but ignoring it.
int get_word(char *word) {
    char scan = 'c';
    int i = 0;
    do {
        scan = getc(stdin);
        word[i] = scan;
        i++;
    } while (scan != '\n' && scan != ' ' && scan != '\t' && scan != '\0' && scan != EOF);
    if (scan == EOF) {
        return -1;
    }
    i -= 1;
    word[i] = '\0';
    return i;
}

// gets a String of numbers and converting it to int.
int string_to_int(char *word) {
    int len = strlen(word);
    int multy = 1;
    len --;
    char c = word[len];
    int ans = 0;
    int digit = 0;
    while (len > 0) {
        digit = c - '0';
        ans += (multy * digit);
        multy *= 10;
        len--;
        if(len > 0)
            c = word[len];
    }
    return ans;
}