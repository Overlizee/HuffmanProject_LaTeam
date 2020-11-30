#include <stdio.h>
#include <stdlib.h>
#include "avl.h"
//Some functions are taken from what we had already done during the courses

//Function to add a value to a Binary search tree
void add_BST(Node** tree, int occurences, char val){
    if (*tree == NULL){
        *tree = create_Node_for_tree(1, val);
    }
    else if (val < (*tree)->character){
        add_BST(&((*tree)->left), occurences, val);
    }
    else{
        add_BST(&((*tree)->right), occurences, val);
    }
}

//function to balance BST
void balance_BST(Tree* tree){
    if(*tree != NULL){
        balance_BST(&((*tree)->left));
        balance_BST(&((*tree)->right));
        while(bf(*tree) >= 2 || bf(*tree) <= -2)
        {
            balance(tree);
        }
    }
}

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

//function that balances a tree into an AVL
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