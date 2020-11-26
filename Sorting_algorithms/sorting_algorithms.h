#ifndef SORTING_ALGORITHMS_H_INCLUDED
#define SORTING_ALGORITHMS_H_INCLUDED

#include "../Structure_types/structures.h"

void swap_two_values(Node* a, Node* b);
void printarr(Node *array, int n);
void split_array_into_3(Node array[], int first_of_list, int last_of_list, int *i, int *j);
void quicksort3(Node array[], int first_of_list, int last_of_list);


#endif //SORTING_ALGORITHMS_H_INCLUDED