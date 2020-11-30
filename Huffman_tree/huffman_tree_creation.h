#ifndef HUFFMAN_TREE_CREATION_H_INCLUDED
#define HUFFMAN_TREE_CREATION_H_INCLUDED

#include "../Structure_types/structures.h"
 
void tree_to_array(Tree tree, Node* array,int number_elements_tree);
Node** from_avl_to_sorted_array(Tree* avl_tree);
void create_temp_trees(Node **node, Queue **initial_queue, Queue **temporary_queue);
Tree create_huffman_tree(Tree *char_occurences,int sizearray);
 
#endif //HUFFMAN_TREE_CREATION_H_INCLUDED