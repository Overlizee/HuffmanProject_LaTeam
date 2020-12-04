#include <stdio.h>
#include <stdlib.h>

#include "huffman_tree_creation.h"
#include "../Sorting_algorithms/sorting_algorithms.h"

//function that transfers a tree into an array
void tree_to_array(Tree tree, Node* array,int number_elements_tree){
    if((tree != NULL) && (number_elements_tree > 0)){
        array->character = tree->character;
        array->number_of_character = tree->number_of_character;
        array->left=NULL;
        array->right=NULL;
        //as there is one value "less" to deal with, we take in each tree half of the nummber of elements MINUS the one done in the function
        tree_to_array(tree->left, array+1, trees_count_nodes(&(tree->left)));
        tree_to_array(tree->right, array+1+trees_count_nodes(&(tree->left)), trees_count_nodes(&(tree->right)));
    }
}

//function that transfers our AVL of character occurences into an array of nodes
Node** from_avl_to_sorted_array(Tree* avl_tree){
    int size_occurence_list;
    Node** occurence_list=NULL;

    if ((avl_tree != NULL) && (*avl_tree != NULL)){
        size_occurence_list = trees_count_nodes(avl_tree);
        occurence_list = (Node**)malloc(sizeof(Node*));
        *occurence_list = (Node*)malloc(size_occurence_list*sizeof(Node));
        tree_to_array(*avl_tree, *occurence_list, size_occurence_list);
        //function to sort an array of Nodes depending on the number of occurences of each character
        //have selected 3 way Quicksort as the initial order will be random, and as there will potentially
        //be a lot of common values, for rare characters in particular.
        quicksort3(*occurence_list, 0, size_occurence_list-1);
    }
    return occurence_list;
}

//functions that enables to dequeue the correcte queue depending on the values of the 2 queues
void create_temp_trees(Node **node, Queue **initial_queue, Queue **temporary_queue){

    int value_queue_1 = first_value_queue(*initial_queue);
    int value_queue_2 = first_value_queue(*temporary_queue);
    if((value_queue_1 == 0) || ((value_queue_1 >= value_queue_2) && (value_queue_2 != 0)) ) {
        *node = dequeue(*temporary_queue);
    }
    else if((value_queue_2 == 0) || ((value_queue_2 > value_queue_1) && (value_queue_1 != 0 ))) {
        *node = dequeue(*initial_queue);
    }
}

//function that creates the Huffman Tree
Tree create_huffman_tree(Tree *char_occurences, int size_array) {
    Tree huffman_tree;
    Queue *initial_queue, *temporary_queue;
    Node* node_1;
    if ((char_occurences == NULL) || (*char_occurences == NULL)) {
        return NULL;
    } 
    else {
        initial_queue = create_queue();
        temporary_queue = create_queue();
        //first we put every node in the first queue (in the good order)
        for (int i = 0; i < size_array; i++) {
            enqueue(initial_queue, &(char_occurences[0][i]));
            //DisplayQueue(initial_queue);
        } 

        //keep on until the end, when we will have 0 element in initial_queue and 1 in temporary_queue
        while( (is_empty_q(initial_queue) == 0) || ((is_empty_q(temporary_queue) == 0) && (temporary_queue->values_of_queue->next != NULL)) ){
            // we need to get the 2 nodes where the occurences are the smallest
            node_1 = (Node*)malloc(sizeof(Node));
            //The lign below is only to activate ONLY if you wan't to visualise the tree BUT you have 
            //to choose a character you know there won't be in the text
            //node_1->character = '*';
            node_1->left = NULL;
            node_1->right = NULL;
            create_temp_trees(&(node_1->left), &initial_queue, &temporary_queue);
            create_temp_trees(&(node_1->right), &initial_queue, &temporary_queue);
            if (node_1->left == NULL){
                node_1->number_of_character = node_1->right->number_of_character;
            }
            else if (node_1->right == NULL){
                node_1->number_of_character = node_1->left->number_of_character;
            }
            else{
                node_1->number_of_character = node_1->left->number_of_character + node_1->right->number_of_character;
            }
            enqueue(temporary_queue, node_1);
            
            //printf("\nQueue 1 ");
            //DisplayQueue(initial_queue);
            //printf("Queue 2 ");
            //DisplayQueue(temporary_queue);
            //printf("\n------------------------");
        }
        huffman_tree = dequeue(temporary_queue);
        free(initial_queue);
        free(temporary_queue);
        return huffman_tree;
    }
}
Tree create_huffman_to_decode(Tree huffman_tree,Node *node, char code[],int size) {
    int i = 0;
    Tree temp_tree = huffman_tree;
    for(i = 0; i < size; i ++) {
        //printf("i : %d\n",i);
        if (i < size - 1) {
            if (code[i] == '0') {
                if (temp_tree->left == NULL) {
                    Node *new_node = (Node*)malloc(sizeof(Node));
                    new_node->left = NULL;
                    new_node->right = NULL;
                    temp_tree->left = new_node;
                }
                temp_tree = temp_tree->left;
            } else {
                if(temp_tree->right == NULL) {
                    Node *new_node = (Node*)malloc(sizeof(Node));
                    new_node->left = NULL;
                    new_node->right = NULL;
                    temp_tree->right = new_node;
                }
                temp_tree = temp_tree->right;
            }
        } else {
            //printf("AHHH\n");
            if(code[i] == '0') {
                //printf("Current tree : %c",temp_tree->character);
                //printf("Node char : %c",node->character);
                temp_tree->left = node;
            } else {
                temp_tree->right = node;
            }
        }
    }
    return huffman_tree;

}
