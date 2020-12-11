#ifndef PESUDO_TERMINAL_H
#define PESUDO_TERMINAL_H
#include <gtk/gtk.h>
#include <string.h>

typedef struct{
    GtkWidget *txtEntrada,*tvEditor;
}Widgets;
char* return_string_helper(char* string_to_return);
int compare_strings(char* str1, char* str2);
char* interpret_command(char* instruction, char* argument, char* argument2);
char* parse_command(gchar* command);
static void insert_text(GtkButton *button, Widgets *wid);
static void get_text(GtkButton *button, Widgets *wid);
int init_gtk(int argc, char* argv[]);
#endif