#include <gtk/gtk.h>
//Compile with: gcc prueba3.c -o prueba3 $(pkg-config --cflags --libs gtk+-3.0)
//http://www.compsci.hunter.cuny.edu/~sweiss/course_materials/csci493.70/lecture_notes/GTK_Lesson_04.pdf
//https://developer.gnome.org/gtk-tutorial/stable/x684.html
                                                  
//https://stackoverflow.com/questions/20406594/auto-scrolling-gtkscrolledwindow-with-gtktextview-wrapped-in-gtkbox

gint main(gint argc, gchar **argv)                                      
{                                                                       
    GtkWidget *window, *scrolled_window, *text_view, *label;            

    gtk_init(&argc, &argv);                                             

    text_view = gtk_text_view_new();                                    
    gtk_text_buffer_set_text(gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view)),
                             "1\n\n\n2\n\n\n3\n\n\n4\n\n\n5\n\n\n6\n\n\n7\n\n\n8", -1);
    /* Use this to set the size you want to reserve on the right */     
    gtk_text_view_set_border_window_size(GTK_TEXT_VIEW(text_view),      
                                         GTK_TEXT_WINDOW_RIGHT,         
                                         130);                          
    /* Add whatever you want instead of a GtkLabel */                   
    gtk_text_view_add_child_in_window(GTK_TEXT_VIEW(text_view),         
                                      gtk_label_new("You badly need this"),
                                      GTK_TEXT_WINDOW_RIGHT,            
                                      0, 0);                            

    scrolled_window = gtk_scrolled_window_new(NULL, NULL);              
    gtk_container_add(GTK_CONTAINER(scrolled_window), text_view);       

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);                       
    gtk_window_set_default_size(GTK_WINDOW(window), 320, 240);                                                                                                         
    gtk_container_add(GTK_CONTAINER(window), scrolled_window);          
    gtk_widget_show_all(window);                                        

    gtk_main ();                                                        

    return 0;                                                           
}  