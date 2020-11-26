
#include <stdio.h>
#include <stdlib.h>
#include "huffman_tree_creation.h"
#include "../Structure_types/structures.h"
#include "../Sorting_algorithms/sorting_algorithms.h"

//Some functions are taken directly from what we had already done during the courses
//to get the depth of a tree
int depth(Node* tree){
    
}

//to get the balance factor of a tree
int bf(Node* tree){
    
}

//to make a right rotation in case we need to balance the tree
void right_rotation(Node** tree){
    
}

//to make a left rotation in case we need to balance the tree
void left_rotation(Node** tree){
    
}

//function that balances a tree -> AVL
void balance(Node** tree){
    
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
    
}


//function that transfers our AVL of character occurences into an array of nodes
Node** from_avl_to_sorted_array(Tree* avl_tree){
    
}


//function that creates the Huffman Tree
Tree* create_huffman_tree(Tree* char_occurences, int size_array){
 
}