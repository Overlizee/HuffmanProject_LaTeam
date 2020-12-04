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

Node* create_Node_for_tree(int occurences, char letter);
Element* create_Element(Tree node_to_add);
Queue* create_queue();
void enqueue(Queue* queue, Node *node_to_enqueue);
int is_empty_q(Queue* queue);
Node* dequeue(Queue* queue);
int first_value_queue(Queue* queue);
void trees_free_tree(Node* tree);
void print_tree(Tree tree);
int trees_count_nodes(Node** tree);
char* add_char_to_string(char* string, char character);
void DisplayQueue(Queue *queue);
int display_intro();
 
#endif //STRUCTURES_H_INCLUDED