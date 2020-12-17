#ifndef DISK_H
#define DISK_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct file
{
    struct file* next_file;
    char* file_name;
    char* owner;
    char* creation_date;
    char* last_mod;
    int bytes;
    int blocks[1000];
}file;

void init_disk(int block_size, int flag);
void new_item(file *file_);
char * create_block(file *file_, char *bval, char *block, char *next_block, char * data);
char * find(char * item, char * block_);
char * find_aux(char * item, const char * p1, const char * p2);
char * get_free_block();
void replace_block(char * num_block, file * f, char * next_block, char * bval, char * data);
char * find_line_by_block(int num_block);
void add_data(file *f, char * data);
char * return_string_helper2(char* string_to_return);
char * get_info(char * item, char * block_);
void delete_file(char * block);
void modify_attribute(file * file_, char * data_);
#endif
