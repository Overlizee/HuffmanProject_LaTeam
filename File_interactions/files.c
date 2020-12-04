#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Structure_types/structures.h"
#include "../Huffman_tree/huffman_tree_creation.h"
#include "../Avl_module/avl.h"
#include "files.h"

//function to display the number of characters in a whole text
int number_of_character(char filename_param[]) {
    int c, number_of_characters = 0;
    FILE *file_to_read;
    file_to_read = fopen(filename_param,"r");
    if(file_to_read == NULL) {
        printf("ERROR while opening files\n");
    } else {
        c = fgetc(file_to_read);
        while(c != EOF) {
            number_of_characters += 1;
            c =  fgetc(file_to_read);
        }
    }
    return number_of_characters;
}

//function to get the AVL tree of the number of occurences of each character
Node** occurence_characters(char filename_param[]){
    int c;
    Node **bst_characters=NULL, *temp;
    FILE *file_to_read;
    file_to_read = fopen(filename_param,"r");

    if(file_to_read == NULL) {
        printf("ERROR while opening files\n");
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

//function to create the dictionary and fill the array of character codes
void create_dictionary(Tree* huffman_tree, char ascii_table_codes[256][50], char* string){
    if ((huffman_tree != NULL) && (*huffman_tree != NULL)){
        if((*huffman_tree)->left == NULL && (*huffman_tree)->right == NULL){
            strcpy(ascii_table_codes[(*huffman_tree)->character], string);
            //printf("\nchar : %c  ->   array : %s", (*huffman_tree)->character,ascii_table_codes[(*huffman_tree)->character] );
        }
        else{
            create_dictionary(&((*huffman_tree)->left), ascii_table_codes, add_char_to_string(string, 48));
            create_dictionary(&((*huffman_tree)->right), ascii_table_codes, add_char_to_string(string, 49));
        }
    }
    free(string);
}

//function to encode the text into new file, containing dictionary and bit sequence
void encoding_with_huffman(char filename_param_read[], char filename_param_write[], Tree *huffman_tree) {
    FILE *file_to_read;
    file_to_read = fopen(filename_param_read,"r");
    int i;
    if(file_to_read == NULL) {
        printf("The file could not be opened");
    }
    else {
        //array of 256 characters where we will store the codes of all concerned characters (those in the text)
        //we use a static array to win time, as we can use more space
        char ascii_table_codes[256][50];
        for(i=0; i<256; i++){
                ascii_table_codes[i][0] = '\0';
        }
        create_dictionary(huffman_tree, ascii_table_codes, NULL);
        int nbr_char_decompressed = number_of_character(filename_param_read);
        if (nbr_char_decompressed != 0){
            FILE *file_to_write = fopen(filename_param_write,"w");

            for(i=0; i<256; i++){
                if (ascii_table_codes[i][0] != '\0')
                fprintf(file_to_write,"%c%s\n", i, ascii_table_codes[i]);
            }
            fprintf(file_to_write,"\n\n");
            int c = fgetc(file_to_read);
            while(c != EOF) {
                //we write the code of each character, stocked in the array of char* of size 256
                fprintf(file_to_write,"%s", ascii_table_codes[c]);
                c = fgetc(file_to_read);
            }
            //close both files
            fclose(file_to_write);
        }
    }
    fclose(file_to_read);
}

void decode_with_huffman(char filename_param_read[],char filename_dico[]) {
    FILE *file_to_read;
    file_to_read = fopen(filename_param_read,"r");
    Tree huffman_tree = (Node*)malloc(sizeof(Node));
    huffman_tree->left = NULL;
    huffman_tree->right = NULL;
    Queue *queue = create_queue();
    if(file_to_read == NULL) {
        printf("ERROR while opening file in function decode_with_huffman");
    } else {
        char node_character;
        char *code = malloc(sizeof(char));

        Node *node;
        int size = 0;
        int c;
        int count= 0;
        int return_line = 0;
        //printf("\n");
        do {
            c = fgetc(file_to_read);
            if(c != '\n') {
                if(return_line == 2) {
                    Tree node = (Node*)malloc(sizeof(Node));
                    node->left = NULL;
                    node->right = NULL;
                    node->character = '\n';
                }
                if(return_line != 3) {
                    return_line = 0;
                    if(c != '1' && c != '0') {
                        Tree node = (Node*)malloc(sizeof(Node));
                        node->left = NULL;
                        node->right = NULL;
                        node->character = c;
                        //printf("Node char : %c\n",node->character);
                    } else {
                        code = realloc(code,size+1);
                        code[size] = (char)c;
                        size += 1;
                    }
                } else {
                    code = realloc(code,size+1);
                    code[size] = (char)c;
                    size += 1;
                }


            } else {
                return_line += 1;
                create_huffman_to_decode(huffman_tree,node,code,size);
                memset(code, 0, sizeof(code));
                free(code);
                code = malloc(sizeof(char));
                size = 0;
            }
        }while (c != EOF);
        //printf("CODE : %s\n",code);
        Tree temp_tree = huffman_tree;

        FILE* file_to_write;
        file_to_write = fopen(filename_dico,"w+");



        for(int i = 0; i < size; i ++) {
            if(code[i] == '0') {
                temp_tree = temp_tree->left;
            } else {
                temp_tree = temp_tree->right;
            }
            if(temp_tree->left == NULL && temp_tree->right == NULL) {
                //printf("%c",temp_tree->character);
                fputc(temp_tree->character,file_to_write);
                temp_tree = huffman_tree;
            }
        }
        fclose(file_to_write);

    }
    fclose(file_to_read);
}

