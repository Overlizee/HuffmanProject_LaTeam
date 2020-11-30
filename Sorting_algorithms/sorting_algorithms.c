#include <stdio.h>
#include <stdlib.h>
#include "sorting_algorithms.h"

//function to swap two values
void swap_two_values(Node* a, Node* b)
{
	Node temp = *a;
	*a = *b;
	*b = temp;
}

//function to print an array of nodes
void printarr(Node *array, int n)
{
    int i;
    if (array != NULL){
        for (i = 0; i < n; i++){
            printf("There are %d : %c\n",(array+i)->number_of_character, (array+i)->character);
        }
    }
}

//we choose a "pivot" (here the last element)
//function then splits our array into three parts containing the elements that are 1. smaller 2. equal 3.higher than our pivot
void split_array_into_3(Node array[], int first_of_list, int last_of_list, int *i, int *j)
{
	// To handle 2 elements
	if (last_of_list - first_of_list <= 1) {
		if ((array+first_of_list)->number_of_character > (array+last_of_list)->number_of_character)
			swap_two_values(&array[first_of_list], &array[last_of_list]);
		*i = first_of_list;
		*j = last_of_list;
	}
    else{
        int middle_value = first_of_list;
        int our_pivot = (array+last_of_list)->number_of_character;

        //each time, we put all the "our_pivot" values in the middle, with the lower before and the higher after
        while (middle_value <= last_of_list) {
            //if lower goes before
            if ((array+middle_value)->number_of_character < our_pivot){
                swap_two_values(&array[first_of_list++], &array[middle_value++]);
            }
            //else if same, middle value takes +1
            else if ((array+middle_value)->number_of_character == our_pivot){
                middle_value++;
            }
            //else goes after
            else{
                swap_two_values(&array[middle_value], &array[last_of_list--]);
            }
        }

        // we update i and j
        *i = first_of_list - 1;
        *j = middle_value;
    }
}

// 3-way quicksort algorithm that uses the function above recursively until we have only small arrays of unique elements
void quicksort3(Node array[], int first_of_list, int last_of_list)
{
    //check if there are at least 2 elements
	if (first_of_list < last_of_list){
        int i, j;

        split_array_into_3(array, first_of_list, last_of_list, &i, &j);
        // Recursivity with the two halves
        quicksort3(array, first_of_list, i);
        quicksort3(array, j, last_of_list);
    }
}
