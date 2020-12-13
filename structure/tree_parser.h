
#ifndef TREE_PARSER_H
#define TREE_PARSER_H

#include "structure.h"
#include <string.h>

typedef struct file_restore
{
    char file_name[100];
    char owner[100];
    char creation_date[100];
    char last_mod[100];
    int bytes;
}file_restore;


typedef struct restore_tree
{
    int command;//1 cd / 2 mkdir / 3 touch_restore
    char n_file[100];
    struct file_restore file_info;
}restore_tree;

char *tree_parser_wr(file_system *root);
void tree_parser_aux_wr(file_system* node, char *structure_str);
file_system *tree_parser_rd(char *file_name);
file_system *tree_parser_aux_rd(char *tree_source, int *pointer_rd, struct restore_tree *commd, int *pointer_cmd);

#endif