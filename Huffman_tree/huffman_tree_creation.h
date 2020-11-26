#ifndef HUFFMAN_TREE_CREATION_H_INCLUDED
#define HUFFMAN_TREE_CREATION_H_INCLUDED

#include "../Structure_types/structures.h"

int depth(Node* tree);
int bf(Node* tree);
void right_rotation(Node** tree);
void left_rotation(Node** tree);
void balance(Node** tree);
void balance_BST(Node** tree);
void trees_balance_BST(Node** tree);
void tree_to_array(Tree tree, Node* array,int number_elements_tree);
Node** from_avl_to_sorted_array(Tree* avl_tree);
Tree* create_huffman_tree(Tree* char_occurences,int sizearray);


#endif //HUFFMAN_TREE_CREATION_H_INCLUDED