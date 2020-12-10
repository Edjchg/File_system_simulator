#ifndef STRUCTURE_H
#define STRUCTURE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
//#include <json-glib/json-glib.h>
//gcc 1.c -g -o 1 $(pkg-config --cflags --libs json-glib-1.0) 
typedef struct node
{
    struct node *next;
    char* directory_name;
    //struct file_list;
}node;

typedef struct file
{
    struct file* next_file;
    char* file_name;
    char* owner;
    char* creation_date;
    char* last_mod;
    int bytes;
}file;

typedef struct file_system{
    struct file_system* brother_file;
    struct file_system* son_file;
    struct file_system* father_file;
    struct file* file_;
    char* directory_name;
    int brother_number;
    int level;
    int visited;
}file_system;




//---------Linked list-----------
void add_node(char* directory_name);
void print_list(void);
int lk_len(void);
char* get_file(int index);
int push_in(int index, char* file_name);
int push_to_head(char* file_name);
int delete_in(int index);
//------------Linked list-----------
//-----------File system------------
void init_root(void); //Init the root of the file system.
void mkdir(char* new_directory); // Create a directory inside a father directory.
void cd(char* next_directory); // Get inside a child directory.
void ls(void); // Print all the directories.
void rmdir_(char* directory); // Remove a certain directory.
void free_all(void);
file_system* export_current_pointer(void);
file_system* export_root(void);
void rename_file(char* actual_name, char* new_name);
int get_len(void);
/*to create a file.*/
void touch(char* file_name); 
/*for renaming files*/
void mv(char* old_name, char* new_name); 
/*for deleting files*/
void rm(char* file_name); 
int get_file_list_len(void);
/*for getting the attributes*/
void lsattr(char* file_name); 
void trace_file_system(void);
void trace_file_aux(file_system* node);
void trace_son(file_system* node);
char* return_directories(void);
void init_directories(void);
void save_file_h(void);
//-----------File system------------

#endif