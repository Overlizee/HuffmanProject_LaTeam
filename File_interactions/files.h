#ifndef FILES_H_INCLUDED
#define FILES_H_INCLUDED

#define filename "./Text_files/text.txt"
#define filename_to_write "./Text_files/text_to_write.txt"
#define filename_decode "./Text_files/decode.txt"

int number_of_character(char filename_param[]);
Node** occurence_characters(char filename_param[]);
void create_dictionary(Tree* huffman_tree, char ascii_table_codes[256][50], char* string);
void encoding_with_huffman(char filename_param_read[], char filename_param_write[], Tree *huffman_tree);
void decode_with_huffman(char filename_param_read[],char filename_param_write[]);



#endif //FILES_H_INCLUDED