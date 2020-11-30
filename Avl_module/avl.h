#ifndef AVL_H_INCLUDED
#define AVL_H_INCLUDED

#include "../Structure_types/structures.h"

void add_BST(Node** tree, int occurences, char val);
void balance_BST(Tree* tree);
int depth(Node* tree);
int bf(Node* tree);
void right_rotation(Node** tree);
void left_rotation(Node** tree);
void balance(Node** tree);
 
#endif //AVL_H_INCLUDED