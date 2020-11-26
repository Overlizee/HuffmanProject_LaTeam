#include <stdio.h>
#include <stdlib.h>
#include "../Structure_types/structures.h"
#include "../Huffman_tree/huffman_tree_creation.h"


void display_number_of_character(char filename_param[]) {
    int c, number_of_characters = 0;
    FILE *file_to_read;
    file_to_read = fopen(filename_param,"r");
    if(file_to_read == NULL) {
        printf("ERROR while opening file : %s \n",filename_param);
    } else {
        c = fgetc(file_to_read);
        while(c != EOF) {
            number_of_characters += 1;
            c =  fgetc(file_to_read);
        }
        printf("There are %d characters in the text file\n",number_of_characters);
    }
}

//function to get the AVL tree of the number of occurences of each character
Node** occurence_characters(char filename_param[]){
    int c;
    Node **bst_characters=NULL, *temp;
    FILE *file_to_read;
    file_to_read = fopen(filename_param,"r");

    if(file_to_read == NULL) {
        printf("ERROR while opening file : %s \n",filename_param);
    } 
    else {
        bst_characters = (Node**)malloc(sizeof(Node*));
        *bst_characters = NULL;
        c = fgetc(file_to_read);
        //we check for each letter of the text
        while(c != EOF) {
            //we go through the list to see if the character being checked is in it
            temp = *bst_characters;
            while( (temp != NULL) && (temp->character != c) ){
                if(c < temp->character){
                    temp = temp->left;
                }
                else{
                    temp = temp->right;
                }
            }
            //if not we add it to the list
            if (temp == NULL){
                add_BST(bst_characters, 1, c);
                balance_BST(bst_characters);
            }
            //if it is, its number of occurrences increases
            else{
                temp->number_of_character++;
            }
            c = fgetc(file_to_read);
        }
    }
    return bst_characters;
}
