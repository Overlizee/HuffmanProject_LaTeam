#include <stdio.h>
#include <stdlib.h>
#include "Avl_module/avl.h"
#include "File_interactions/files.h"
#include "Huffman_tree/huffman_tree_creation.h"
#include "Sorting_algorithms/sorting_algorithms.h"
#include <time.h>

//Useful to launch on VSC : gcc -o go *c Avl_module/*c File_interactions/*c Huffman_tree/*c Sorting_algorithms/*c Structure_types/*c

int main() {
    Node **test_occurence, **sorted_array;
    Tree huffman_tree;
    int number_of_char;
    int value_main, nbr_char_compressed, nbr_char_decompressed;
    float time;
    clock_t t1,t2;

    value_main = display_intro();
    
    if(value_main == 0){
        t1 = clock();

        test_occurence = occurence_characters(filename);
        number_of_char = trees_count_nodes(test_occurence);        
        sorted_array=from_avl_to_sorted_array(test_occurence);
        //printarr(*sorted_array, number_of_char);
        trees_free_tree(*test_occurence);
        free(test_occurence);
        huffman_tree = create_huffman_tree(sorted_array, number_of_char);

        encoding_with_huffman(filename,filename_to_write, &huffman_tree);
        
        free(*sorted_array);
        free(sorted_array);
        t2 = clock();
        time = (float)(t2-t1)/CLOCKS_PER_SEC;

        nbr_char_decompressed = number_of_character(filename);
        nbr_char_compressed = number_of_character(filename_to_write);
        printf("Number of characters in the file to compress : %d", nbr_char_decompressed);
        if(nbr_char_decompressed != 0){
            printf("\nNumber of characters in the compressed file  : %d", nbr_char_compressed);
            printf("\n\nPercentage of compression : %d %%", (nbr_char_compressed*100)/(nbr_char_decompressed*8));
            printf("\nTime of compression : %f seconds", time);
        }

    }
    else if(value_main == 10){

        t1 = clock();
        decode_with_huffman(filename_to_write,filename_decode);
        t2 = clock();
        time = (float)(t2-t1)/CLOCKS_PER_SEC;

        nbr_char_decompressed = number_of_character(filename_decode);
        nbr_char_compressed = number_of_character(filename_to_write);
        printf("Number of characters in the compressed file   : %d", nbr_char_compressed);
        if (nbr_char_compressed != 0){
            printf("\nNumber of characters in the decompressed file : %d", nbr_char_decompressed);
            printf("\n\nPercentage of compression was : %d %%", (nbr_char_compressed*100)/(nbr_char_decompressed*8));
            printf("\nTime of decompression : %f seconds", time);
        }

    }
    else{
        printf("You have chosen to quit, see you next time !");
    }

    return 0;
}
