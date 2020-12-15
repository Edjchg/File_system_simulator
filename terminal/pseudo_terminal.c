
#include "pseudo_terminal.h"
#include <stdio.h>
#include <stddef.h>

//gcc pseudo_terminal.c -o pseudo_terminal $(pkg-config --cflags --libs gtk+-3.0)

//https://www.youtube.com/watch?v=RYnFJg5yjl4&list=PL1xeVkd9tTFijBKZuWi9Ozw63ZuMZAOZ1&index=71

char* return_string_helper(char* string_to_return){
    int len = strlen(string_to_return);
    char *string_r = (char *)malloc(sizeof(char)*len);
    memset(string_r, '0', len);
    int counter = 0;
    while (counter < len)
    {
        string_r[counter] = string_to_return[counter];
        counter++;
    }
    string_r[counter] = '\0';
    return string_r;
}

int compare_strings(char* str1, char* str2){
    int len1 = strlen(str1);
    int len2 = strlen(str2);
    if (len1 == len2)
    {
        int index = 0;
        while (index < len1)
        {
            if (str1[index] != str2[index])
            {
                return 0;
            }
            index++;
        }
        return 1;
    }else
    {
        return 0;
    }
}
char* interpret_command(char* instruction, char* argument, char* argument2){
    printf("%s(%s, %s)\n", instruction, argument, argument2);
    char* out_put = " ";
    if (compare_strings(instruction, "mkdir"))
    {
        
        printf("Se detecto mkdir\n");
        printf("El nombre de la carpeta es: %s\n", argument);
        if (strlen(argument) == 0){
            return return_string_helper1("Missing argument.");
        }else
        {
            return mkdir_(argument);
        }
    }else if (compare_strings(instruction, "cd"))
    {
        printf("Se detecto cd\n");
        if (strlen(argument) == 0)
        {
            return return_string_helper1("Missing argument.");
        }else
        {
            return cd_(argument);
        }
    }else if (compare_strings(instruction, "ls"))
    {
        printf("Se detecto ls\n");
        //ls_();
        //return return_string_helper(out_put);
        return ls_();

    }else if (compare_strings(instruction, "rmdir"))
    {
        printf("Se detecto rmdir\n");
        if (strlen(argument) == 0)
        {
            return return_string_helper1("Missing argument.");
        }else
        {
            return rmdir_(argument);
        }
    }else if (compare_strings(instruction, "rename_file"))
    {
        printf("Se detecto rename_file\n");
        if (strlen(argument) == 0 || strlen(argument2) == 0){
            return return_string_helper1("Missing arguments.");
        }else
        {
            return rename_file(argument, argument2);
        }
    }else if (compare_strings(instruction, "touch"))
    {
        printf("Se detecto touch\n");
        if (strlen(argument) == 0)
        {
            return return_string_helper1("Missing argument.");
        }else
        {
            touch_(argument);
            return return_string_helper(out_put);
        }
    }else if (compare_strings(instruction, "mv"))
    {
        printf("Se detecto mv\n");
        if (strlen(argument) == 0 || strlen(argument2) == 0)
        {
            return return_string_helper1("Missing arguments.");
        }else
        {
            return mv(argument, argument2);
        }
    }else if (compare_strings(instruction, "rm"))
    {
        printf("Se detecto rm\n");
        if (strlen(argument) == 0)
        {
            return return_string_helper1("Missing argument.");
        }else
        {
            return rm(argument);
        }
    }else if (compare_strings(instruction, "lsattr"))
    {
        printf("Se detecto lsattr\n");
        if (strlen(argument) == 0)
        {
            return return_string_helper1("Missing argument.");
        }else
        {
            return lsattr(argument);
        }
        
    }else if(compare_strings1(instruction, "cat"){
    
    	if (strlen(argument) == 0)
        {
            return return_string_helper1("Missing argument.");
        }else
        {
            return cat_(argument);
        }
    }else
    {
        printf("No existe ese comando\n");
        return return_string_helper("Unknown command.");
        
    }
  
}
char* parse_command(gchar* command){
    char* comm = (char*)command;
    int len = strlen(command) - 1;
    printf("El len del comando es: %i\n", len);
    char instr[100];
    memset(instr, 0, 100);
    char arg[100];
    memset(arg, 0, 100);
    char arg2[100];
    memset(arg2, 0, 100);
    int index = 0;
    int index_instr = 0;
    int index_arg = 0;
    int index_arg2 = 0;
    int space_founded = 0;
    while (comm[index] != 32 && index < len) // while command is different of space do:
    {
        instr[index_instr] = comm[index];
        index_instr++;
        index++;
    }
    if(strcmp(instr, "echo") != 0){
    
    
		if (index +1 <len)
		{
		    index++;
		    while (index < len && comm[index] != 32)
		    {
		       arg[index_arg] = comm[index];
		        index_arg++;
		        index++;
		    }
		}
		
		if (index +1 < len)
		{
		    index++;
		    while (index < len)
		    {
		        arg2[index_arg2] = comm[index];
		        index_arg2++;
		        index++;
		    }
		}
    	char* interpret = interpret_command(instr, arg, arg2);
    	return interpret;
    }else{
    	char data[1000000];
        int data_index = 0;
        //memset(data, '0', 1000000);
        while (comm[index] != 62)
        {
            data[data_index] = comm[index];
            data_index++;
            index++;
        }
        index++;
        char file_name[50];
        int file_name_index = 0;
        while (index < len)
        {
            file_name[file_name_index] = comm[index];
            file_name_index++;
            index++;
        }
        printf("el comando echo tiene data: |%s| al file:|%s|\n", 	data, file_name);
        return echo_(file_name, data);
    
    }
    
    /*
    if (strlen(instr) == 0)
    {
        //instr = " ";
        strcpy(instr, " ");
    }
    if (strlen(arg) == 0)
    {
        //arg = " ";
        strcpy(arg, " ");
    }*/
    
    
    
    //printf("%i %i\n", index_instr, index_arg);

    
    
    /* Sección de prueba para poder retornar correctamente un string */
    /*
    char *string_r = (char *)malloc(sizeof(char)*index_instr);
    memset(string_r, '0', index_instr);
    int counter = 0;
    while (counter < index_instr)
    {
        string_r[counter] = instr[counter];
        counter++;
    }
    string_r[counter] = '\0';*/
    /* --------------------------------------------------------------*/

    
}

 

static void insert_text(GtkButton *button, Widgets *wid){
    GtkTextBuffer *buffer;
    GtkTextMark *mark;
    GtkTextIter iter;
    //const gchar *text;
    gchar *text;
    buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(wid->tvEditor));
    text = (gchar *)gtk_entry_get_text(GTK_ENTRY(wid->txtEntrada));
    mark = gtk_text_buffer_get_insert(buffer);
    gtk_text_buffer_get_iter_at_mark(buffer, &iter, mark);
    strcat(text, "\n");
    //gtk_text_buffer_insert(buffer, &iter, text, -1);
    printf("%s\n", text);
    char* response = parse_command(text);
    //printf("El comando que se detectó fue: %s\n", response);
    strcat(text, response);
    strcat(text, "\n");
    gtk_text_buffer_insert(buffer, &iter, text, -1);
    gtk_entry_set_text(GTK_ENTRY(wid->txtEntrada), "");
    printf("%li\n", strlen(response));
    if (strlen(response) >= 3)
    {
        printf("free the pointer\n");
        free(response);
    }
}

static void get_text(GtkButton *button, Widgets *wid){
    GtkTextBuffer *buffer;
    GtkTextIter start, end;
    gchar *text;
    
    buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(wid->tvEditor));
    gtk_text_buffer_get_selection_bounds(buffer, &start, &end);
    text = gtk_text_buffer_get_text(buffer, &start, &end, FALSE);
    //From here we can get the text written in the terminal//
    //.
    //.
    g_print("%s\n", text);
}

int init_gtk(int argc, char* argv[]){
    GtkWidget *window, *scrolled_window, *hbox, *vbox, *insert, *retrieve;

    //malloc
    Widgets *wid = g_slice_new(Widgets);
    gtk_init(&argc, &argv);
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "FS-Terminal");
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);
    gtk_widget_set_size_request(window, -1, 200);

    wid->tvEditor = gtk_text_view_new();
    wid->txtEntrada = gtk_entry_new();

    gtk_text_buffer_set_text(gtk_text_view_get_buffer(GTK_TEXT_VIEW(wid->tvEditor)), "--   *Pseudo Linux Terminal*   --\n", -1);

    insert = gtk_button_new_with_label("Insertar");
    retrieve = gtk_button_new_with_label("Obtener");

    g_signal_connect(G_OBJECT(insert), "clicked", G_CALLBACK(insert_text), (gpointer)wid);
    g_signal_connect(G_OBJECT(retrieve), "clicked", G_CALLBACK(get_text), (gpointer)wid);

    scrolled_window = gtk_scrolled_window_new(NULL, NULL);
    gtk_container_add(GTK_CONTAINER(scrolled_window), wid->tvEditor);

    hbox = gtk_hbox_new(FALSE, 5);
    gtk_box_pack_start(GTK_BOX(hbox), wid->txtEntrada, TRUE, TRUE, 5);
    gtk_box_pack_start(GTK_BOX(hbox), insert, TRUE, TRUE, 5);
    gtk_box_pack_start(GTK_BOX(hbox), retrieve, TRUE, TRUE, 5);

    vbox = gtk_vbox_new(FALSE, 5);

    gtk_box_pack_start(GTK_BOX(vbox), scrolled_window, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, TRUE, 0);

    gtk_container_add(GTK_CONTAINER(window), vbox);
    gtk_widget_show_all(window);

    gtk_main();
    //free(wid);
    return 0;
}


