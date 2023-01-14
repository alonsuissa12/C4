//
// Created by alon on 1/10/23.
//
#include <stdio.h>
#include "nodes.h"
#include "edges.h"
#include <string.h>

int string_to_int(char *word);

int get_word(char *word);

int main() {
    char scan = '\0';
    pnode head = NULL;
    pnode *phead = &head;
    int num_nodes = 0;
    int keep_going = 1;

    while (scan != EOF && keep_going) {
        scanf(" %c", &scan);
        if (start_letter == 'A') {
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
            if (scan == 'n') {
                char word[10];
                //getting the source
                int len_of_word = get_word(word);
                int source = string_to_int(word);
                if (len_of_word == -1) {
                    keep_going = 0;
                }
                else {
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
        if (start_letter == 'B') {
            char word[10];
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
        if(scan == 'D'){
            char word[10];
            if(get_word(word) == -1){
                keep_going = 0;
            }
            int node_index = string_to_int(word);
            pnode to_delete = head;
            while(to_delete != NULL){
                if(node_index == to_delete->node_num){
                    delete_node_cmd(phead,to_delete);
                    break;
                }
                to_delete = to_delete->next;
            }
        }
        if(scan == 'S'){

        }
        if(scan == 'T'){

        }


    }

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
    char c = word[len];
    int ans = 0;
    int digit = 0;
    while (len => 0) {
        digit = c - '0';
        ans += (multy * digit);
        digit *= 10;
        len--;
        c = word[len];
    }
    return ans;
}