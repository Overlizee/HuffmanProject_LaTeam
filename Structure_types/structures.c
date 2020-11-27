#include <stdio.h>
#include <stdlib.h>
#include "structures.h"
 
//function to create a new Node
Node* create_Node_for_tree(int occurences, char letter) {
    Node *new_node = (Node*)malloc(sizeof(Node));
    new_node->number_of_character = occurences;
    new_node->character = letter;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}
 
//function to create a new Element
Element* create_Element(Tree node_to_add) {
    Element * new_el;
    new_el = (Element*)malloc(sizeof(Element));
    new_el->nodes = node_to_add;
    new_el->next = NULL;
    return new_el;
}
 
//function to create a new queue
Queue* create_queue(){
    Queue* new_queue = (Queue*)malloc(sizeof(Queue));
    new_queue->values_of_queue = NULL;
    return new_queue;
}
 
//function to add a node to a queue
void enqueue(Queue* queue, Node *node_to_enqueue){
    Element *new_element = (Element*)malloc(sizeof(Element));
    new_element->nodes = node_to_enqueue;
    new_element->next = NULL;

    if(queue->values_of_queue != NULL) {
        Element *old = queue->values_of_queue;
        while(old->next != NULL) {
            old = old->next;
        }
        old->next = new_element;
    } else {
        queue->values_of_queue = new_element;
    }

}
 
//function to check if the queue is empty or not
//returns 1 if empty, 0 if not empty and -1 if queue is NULL
int is_empty_q(Queue* queue){
    if (queue != NULL){
        if(queue->values_of_queue == NULL){
            return 1;
        }
        else{
            return 0;
        }
    }
    else{
        return -1;
    }
}
 
//function to get a node out of the queue
Node* dequeue(Queue* queue){
    Node* node_to_release = NULL;
    if(is_empty_q(queue) == 0){
        Element *old = queue->values_of_queue;  
        queue->values_of_queue = queue->values_of_queue->next;
        node_to_release = old->nodes;
        free(old);
    }
    return node_to_release;
}
// function to get the first value of occurences from a queue
int first_value_queue(Queue* queue) {
    if(is_empty_q(queue) == 0) {
        return queue->values_of_queue->nodes->number_of_character;
    }
    return 0;
}
//function to free a whole tree
void trees_free_tree(Node* tree) {
    if (tree != NULL){
        trees_free_tree(tree->left);
        trees_free_tree(tree->right);
        free(tree);
    }
}
 
//function to display a tree in prefix order
void print_tree(Tree tree){
    if (tree != NULL){
        printf("\nThe character [%c] has [%d] occurences", tree->character, tree->number_of_character);
        print_tree(tree->left);
        print_tree(tree->right);
    }
}
 
//function to count number of nodes in a tree
int trees_count_nodes(Node** tree){
    if( (tree != NULL) && (*tree != NULL)){
        return 1 + trees_count_nodes(&((*tree)->left)) + trees_count_nodes(&((*tree)->right));
    }
    else{
        return 0;
    }
}
 
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
 