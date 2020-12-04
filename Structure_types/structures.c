#include <stdio.h>
#include <stdlib.h>
#include "structures.h"
#include <conio.h>
 
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
    Element * new_el = (Element*)malloc(sizeof(Element));
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
    Element *new_element = create_Element(node_to_enqueue);

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
    else{
        return 0;
    }
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
        //printf("\nThe character [%c] has [%d] occurences", tree->character, tree->number_of_character);
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

//function to add a character at the end of a string
char* add_char_to_string(char* string, char character){
 
    char* new_string;
    int size_string=0, i;
    if(string == NULL){
        new_string = (char*)malloc(2*sizeof(char));
        new_string[0] = character;
        new_string[1] = '\0';
    }
    else{
        while (string[size_string] != '\0'){
            size_string++;
        }
        new_string = (char*)malloc( (size_string+2) *sizeof(char) );
        for(i=0; i<size_string; i++){
            new_string[i] = string[i];
        }
        new_string[size_string] = character;
        new_string[size_string+1] = '\0';
    }
    for (int z = 0; z < sizeof(new_string); z++ ) {
    }
    //we don't free string because we call this function twice in a row, thus we free it there
    return new_string;
}

//display queue (very useful to test and for maintenance)
void DisplayQueue(Queue *queue) {
    if(queue == NULL) {
        exit(EXIT_FAILURE);
    }
    Element *element = queue->values_of_queue;
    while (element != NULL) {
        //printf("%c|",element->nodes->character);
        element = element->next;
    }
    //printf("\n");
}

int display_intro(){
    
    int ch1=0, value=0, i, j;
    char tab_options[5][30];

    for (i=0; i<5; i++)
    {
        for(j=0; j<30; j++)
        {
            tab_options[i][j] = 32;
        }
    }

    tab_options[2][2] = 'E';
    tab_options[2][3] = 'n';
    tab_options[2][4] = 'c';
    tab_options[2][5] = 'o';
    tab_options[2][6] = 'd';
    tab_options[2][7] = 'e';

    tab_options[2][12] = 'D';
    tab_options[2][13] = 'e';
    tab_options[2][14] = 'c';
    tab_options[2][15] = 'o';
    tab_options[2][16] = 'd';
    tab_options[2][17] = 'e';

    tab_options[2][23] = 'Q';
    tab_options[2][24] = 'u';
    tab_options[2][25] = 'i';
    tab_options[2][26] = 't';

    while(ch1 != 13)
    {

        //We create and move the box's position. The box will enable to select the option we want
        tab_options[0][value] = 201;
        tab_options[0][value+9] = 187;
        tab_options[4][value] = 200;
        tab_options[4][value+9] = 188;

        for (i=value+1; i<(value+9); i++)
        {
            tab_options[0][i] = 205;
            tab_options[4][i] = 205;
        }

        for(i=0; i<3; i++)
        {
            tab_options[i+1][value] = 186;
            tab_options[i+1][value+9] = 186;
        }


        //Every time, we print it after renewing the screen, in order to see the box surrounding the selected option move
        system("cls");
        printf("\n\nSelect with the arrows of your keyboards what you want to do :\n\n\n");

        for(i=0; i<5; i++)
        {
            printf("\n");
            for(j=0; j<30; j++)
            {
                printf("%c", tab_options[i][j]);
            }
        }

        for (i=value; i<(value+10); i++)
        {
            tab_options[0][i] = 32;
            tab_options[4][i] = 32;
        }

        for(i=0; i<3; i++)
        {
            tab_options[i+1][value] = 32;
            tab_options[i+1][value+9] = 32;
        }

        ch1 = getch();
        if(ch1 == 75){
            if (value>0)
                value -= 10;
        }
        //if user presses right arrow, box moves right if possible (not on far right)
        else if(ch1 == 77){
            if (value<20)
                value += 10;
        }
    }
    system("cls");
    return value;
}