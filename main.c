#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Structure_types/structures.h"
#include "Huffman_tree/huffman_tree_creation.h"
#include "File_interactions/files.h"
#include "Sorting_algorithms/sorting_algorithms.h"

//Useful to launch on VSC : gcc -o go *c Huffman_tree/*c Structure_types/*c File_interactions/*c Sorting_algorithms/*c

//////////////////////Elements needed ?

/*

Element* return_smallest_element(Node** list_of_elements){
    
    Element *min_temp = NULL, *temp = *list_of_elements;
    
    if( (list_of_elements != NULL) && (*list_of_elements != NULL) ){
        
        min_temp = temp;
        temp = temp->next;

        while(temp != NULL){
            if(min_temp->occurence > temp->occurence){
                min_temp = temp;
            }
            temp = temp->next;
        }
    }
    return min_temp;
}

void remove_element_list(Element** list_of_elements, Element* element_to_remove){

    struct Element **temp = list_of_elements;
    struct Element* old;

    while (*temp != NULL){
        if (*temp == element_to_remove){
            *temp = (*temp)->next;
        }
        else{
            temp = &((*temp)->next);
        }
    }
}

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
        free(string);
    }
    return new_string;
}

void create_dictionary(Tree* huffman_tree, char filename_param_write[], char* string){
    FILE *file_to_write;

    file_to_write = fopen(filename_param_write,"a+");

    if ((huffman_tree != NULL) && (*huffman_tree != NULL)){
        
        if((*huffman_tree)->left == NULL && (*huffman_tree)->left == NULL){
            
            if ((*huffman_tree)->character == '0'){
                //adapt to the 1 character
                fprintf(file_to_write, "..");
            }
            else if ((*huffman_tree)->character == '1'){
                //adapt to the 0 character
                fprintf(file_to_write, ",,");
            }
            fprintf(file_to_write,"%c%s", (*huffman_tree)->character, string);
        }
        else{
            create_dictionary(&((*huffman_tree)->left), filename_param_write, add_char_to_string(string, 48));
            create_dictionary(&((*huffman_tree)->right), filename_param_write, add_char_to_string(string, 49));
        }
    }
    fclose(file_to_write);
}

char* return_binary_code_character(char* Array,int Letter,char filename_param_dico[]) {
    FILE *file_to_read;
    file_to_read = fopen(filename_param_dico,"r");

    if(file_to_read == NULL) {
        printf("The file could not be opened");
    } else {
        int c;
        c = fgetc(file_to_read);
        if (Letter == '0'){
            while(c != EOF && c != '.') {
                c = fgetc(file_to_read);
                if (c == '.'){
                    c = fgetc(file_to_read);
                }
            }
            c = fgetc(file_to_read);
        }
        else if (Letter == '1'){
            while(c != EOF && c != ',') {
                c = fgetc(file_to_read);
                if (c == ','){
                    c = fgetc(file_to_read);
                }
            }
            c = fgetc(file_to_read);
        }
        else{
            while(c != EOF && c != Letter) {
                c = fgetc(file_to_read);
                //printf("c : %c\n",c);
            }
        }
        c = fgetc(file_to_read); // to get to the first char of the binary code
        while((c == '1') || (c == '0')) {
            Array = add_char_to_string(Array,c);
            c = fgetc(file_to_read);
        }
    }
    return Array;
}

void encoding_with_huffman(char filename_param_read[],char filename_param_dico[], char filename_param_write[]) {
    FILE *file_to_read;
    file_to_read = fopen(filename_param_read,"r");

    if(file_to_read == NULL) {
        printf("The file could not be opened");
    } else {
        FILE *file_to_write;
        file_to_write = fopen(filename_param_write,"w");

        char* buffer;
        int c;
        c = fgetc(file_to_read);

        while(c != EOF) {
            //printf("Character of the file is : %c\n",c);
            buffer = return_binary_code_character(buffer,c,filename_param_dico);

            //printf("%s , %c\n",buffer,c);
            //write these binary numbers in the file
            fwrite(buffer,1,strlen(buffer),file_to_write);
            fwrite("",1,1,file_to_write);
            free(buffer);
            c = fgetc(file_to_read);
        }
        //close both files
        fclose(file_to_write);
        fclose(file_to_read);
    }
}
*/
int main() {
    Node **test_occurence, **sorted_array;
    Element *element;
    Tree *huffman_tree;

    //read_file(filename, filename_to_write);
    //display_number_of_character(filename);
    //display_number_of_character(filename_to_write);

    test_occurence = occurence_characters(filename);
    print_tree(*test_occurence);
    printf("\n");
    
    sorted_array=from_avl_to_sorted_array(test_occurence);

    printarr(*sorted_array, trees_count_nodes(test_occurence));


    huffman_tree = create_huffman_tree(sorted_array,trees_count_nodes(test_occurence));
    printf("DONE");

    printf("\n\n%d, [%c]", (*huffman_tree)->number_of_character, (*huffman_tree)->character);
    printf("\n\n%d, [%c]", (*huffman_tree)->right->number_of_character, (*huffman_tree)->right->character);
    printf("\n\n%d, [%c]", (*huffman_tree)->left->number_of_character, (*huffman_tree)->left->character);
/*
    //BLOCK THAT GOES TOGETHER !!
    FILE *file_to_write;
    file_to_write = fopen(filename_dico,"w");
    fclose(file_to_write);
    create_dictionary(huffman_tree, filename_dico, NULL);
    //END OF BLOCK THAT GOES TOGETHER !!

    // ENCODING WITH HUFFMAN
    encoding_with_huffman(filename,filename_dico,filename_to_write);

*/
    return 0;
}
