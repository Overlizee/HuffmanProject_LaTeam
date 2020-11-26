#ifndef STRUCTURES_H_INCLUDED
#define STRUCTURES_H_INCLUDED

typedef struct Node {
    int number_of_character;
    char character;
    struct Node* left;
    struct Node* right;
} Node;

typedef Node* Tree;

typedef struct Element {
    Tree nodes;
    struct Element* next;
} Element;

typedef Element* List;

typedef struct Queue{
    List values_of_queue;
} Queue;

Element* create_Element_for_list(char letter);
Node* create_Node_for_tree(int occurences, char letter);
Queue* create_Queue();
void enqueue(Queue* queue, Node *node_to_enqueue);
int is_empty_q(Queue* queue);
Node* dequeue(Queue* queue);
void trees_free_tree(Node* tree);
void print_tree(Tree tree);
int trees_count_nodes(Node** tree);
void add_BST(Node** tree, int occurences, char val);

#endif //STRUCTURES_H_INCLUDED