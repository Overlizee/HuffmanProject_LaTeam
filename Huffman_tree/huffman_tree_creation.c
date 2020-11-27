#include <stdio.h>
#include <stdlib.h>
#include "huffman_tree_creation.h"
#include "../Structure_types/structures.h"
#include "../Sorting_algorithms/sorting_algorithms.h"

//Some functions are taken directly from what we had already done during the courses
//to get the depth of a tree
int depth(Node* tree){
    int depth_left, depth_right;
    if(tree == NULL){
        return 0;
    }
    else{
        depth_left = depth(tree->left);
        depth_right = depth(tree->right);
        if(depth_left > depth_right){
            return 1 + depth_left;
        }
        else{
            return 1 + depth_right;
        }
    }
}

//to get the balance factor of a tree
int bf(Node* tree){
    if(tree == NULL) {
        return 0;
    }
    else{
        return depth(tree->right) - depth(tree->left);
    }
}

//to make a right rotation in case we need to balance the tree
void right_rotation(Node** tree){
    if (*tree != NULL){
        Node* temp = (*tree)->left;
        (*tree)->left = temp->right;
        temp->right = *tree;
        *tree = temp;
    }
}

//to make a left rotation in case we need to balance the tree
void left_rotation(Node** tree){
    if (*tree != NULL){
        Node* temp = (*tree)->right;
        (*tree)->right = temp->left;
        temp->left = *tree;
        *tree = temp;
    }
}

//function that balances a tree -> AVL
void balance(Node** tree){
    int balance_factor;
    if (*tree != NULL){
        balance(&((*tree)->left));// Postfix
        balance(&((*tree)->right));
        balance_factor = bf(*tree);
        if (balance_factor <= -2){// left case
            if(bf((*tree)->left) > 0){// left right case
                left_rotation(&((*tree)->left));
            }
            right_rotation(tree);// left - left
        }
        else if (balance_factor >= 2){// right case
            if(bf((*tree)->right) < 0){// right left case
                right_rotation(&((*tree)->right));
            }
            left_rotation(tree);// right - right
        }
    }
}

//function to balance BST
void balance_BST(Node** tree){
    if(*tree != 0){
        balance_BST(&((*tree)->left));
        balance_BST(&((*tree)->right));
        while(bf(*tree) >= 2 || bf(*tree) <= -2)
        {
            balance(tree);
        }
    }
}

//function that transfers a tree into an array
void tree_to_array(Tree tree, Node* array,int number_elements_tree){
    int cut_array_half;
    if((tree != NULL) && (number_elements_tree > 0)){
        array->character = tree->character;
        array->number_of_character = tree->number_of_character;
        //as there is one value "less" to deal with, we take in each tree half of the nummber of elements MINUS the one done in the function
        cut_array_half = (number_elements_tree-1)/2;
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


//function that creates the Huffman Tree
Tree* create_huffman_tree(Tree* char_occurences, int size_array) {

    Tree *huffman_tree;
    Queue *initial_queue, *temporary_queue;

    if ((char_occurences == NULL) || (*char_occurences == NULL)) {
        return NULL;
    } else {

        initial_queue = create_queue();
        temporary_queue = create_queue();
        //printf("queue : %d\n",is_empty_q(initial_queue));
        printf("wtf : %c %c\n",char_occurences[0][0].character,char_occurences[0][1].character);
        //first we put every node in the first queue (in the good order)
        for (int i = 0; i < size_array; i++) {
            printf("Node i : %d , char %c\n",i,char_occurences[0][i].character);
            enqueue(initial_queue,&(char_occurences[0][i]));
            //dequeue(initial_queue);
        }
        printf("End");


        char c_node = '*';


        Tree *node_1 = malloc(sizeof(Tree));

        int value_queue_1,value_queue_2;
        //printf("Is empty : %d\n",is_empty_q(initial_queue));
        //printf("Is empty : %d\n",is_empty_q(temporary_queue));

        //keep on until the end, when we will have 0 element in initial_queue and 1 in temporary_queue
        while ( is_empty_q(initial_queue) == 0 || is_empty_q(temporary_queue) == 1 ) {
            // we need to get the 2 nodes where the occurences are the smallest
            value_queue_1 = first_value_queue(initial_queue);
            value_queue_2 = first_value_queue(temporary_queue);
            printf("Value queue 1 :%d\n",value_queue_1);
            if (value_queue_1 == 0 ||(value_queue_1 > value_queue_2 && value_queue_2 != 0 )) {
                (*node_1)->left = dequeue(temporary_queue);
            } else {
                (*node_1)->left = dequeue(initial_queue);
            }

            value_queue_1 = first_value_queue(initial_queue);
            value_queue_2 = first_value_queue(temporary_queue);
            if (value_queue_1 == 0 || ((value_queue_1 > value_queue_2) && value_queue_2 != 0)) {
                (*node_1)->right = dequeue(temporary_queue);
            } else {
                (*node_1)->right = dequeue(initial_queue);
            }
            enqueue(temporary_queue, (*node_1));
            printf("right : %c , left %c",(*node_1)->left->character,(*node_1)->right->character);

        }
        printf("Sortie");
        (*huffman_tree) = dequeue(temporary_queue);
        return huffman_tree;
        /*
        void enqueue(Queue* queue, Node *node_to_enqueue);
        int is_empty_q(Queue* queue);
        Node* dequeue(Queue* queue);



        element= return_smallest_element(char_occurences);
        remove_element_list(char_occurences, element);
        *huffman_tree = create_Node_for_tree(element->occurence, element->character);
        free(element);

        while(*char_occurences != NULL){
            element= return_smallest_element(char_occurences);
            remove_element_list(char_occurences, element);
            *huffman_tree_temporary = *huffman_tree;
            *huffman_tree = create_Node_for_tree((element->occurence + (*huffman_tree_temporary)->number_of_character), 0);
            (*huffman_tree)->left = create_Node_for_tree(element->occurence, element->character);
            (*huffman_tree)->right = *huffman_tree_temporary;
            free(element);
        }
        return huffman_tree;
    }
    */

    }
}
