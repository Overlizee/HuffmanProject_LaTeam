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
    Element *element;
    Tree huffman_tree;

    //display_number_of_character(filename);
    //display_number_of_character(filename_to_write);

    test_occurence = occurence_characters(filename);
    //print_tree(*test_occurence);
    //printf("\n");

    sorted_array=from_avl_to_sorted_array(test_occurence);
    //printarr(*sorted_array, trees_count_nodes(test_occurence));

    huffman_tree = create_huffman_tree(sorted_array, trees_count_nodes(test_occurence));
    //be careful, to activate this you have to assign a letter you know you won't 
    //use to the nodes where we don't, to win space and time.
    //print_tree(huffman_tree);

    float time;
    clock_t t1,t2;

    t1 = clock();
    encoding_with_huffman(filename,filename_to_write, &huffman_tree);

    t2 = clock();
    decode_with_huffman(filename_to_write,filename_decode);

    time = (float)(t2-t1)/CLOCKS_PER_SEC;
    printf("temps = %f\n", time);

    return 0;
}
