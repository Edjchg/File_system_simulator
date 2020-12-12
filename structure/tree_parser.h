
#ifndef TREE_PARSER_H
#define TREE_PARSER_H

#include "structure.h"
#include <string.h>


typedef struct restore_tree
{
    int command;//1 cd / 2 mkdir
    char n_file[100];
}restore_tree;

char *tree_parser_wr(file_system *root);
void tree_parser_aux_wr(file_system* node, char *structure_str);
file_system *tree_parser_rd(char *file_name);
file_system *tree_parser_aux_rd(char *tree_source, int *pointer_rd, struct restore_tree *commd, int *pointer_cmd);

#endif