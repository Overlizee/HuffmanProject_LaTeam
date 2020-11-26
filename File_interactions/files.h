#ifndef FILES_H_INCLUDED
#define FILES_H_INCLUDED

//CHANGE FILE PATH ACCORDING TO WHERE THE FILES ARE !!

//VARIABLES LOUIS :
#define filename "./Text_files/text.txt"
#define filename_to_write "./Text_files/text_to_write.txt"
#define filename_dico "./Text_files/dico.txt"

void read_file (char filename_param_read[], char filename_param_write[]);
void display_number_of_character(char filename_param[]);
Node** occurence_characters(char filename_param[]);


#endif //FILES_H_INCLUDED