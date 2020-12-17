
#include "structure.h"
#include <stdlib.h>
#include <stdio.h>

#include "../directory_view/gtktreeview.h"
#include "tree_parser.h"

//Compile with: gcc -o test_file_system test_file_system.c structure.c
// gcc -o test_file_system test_file_system.c structure.c ../directory_view/gtktreeview.c ../disk/disk.c $(pkg-config --cflags --libs gtk+-3.0)
int main(int argc, char* argv[]){
    /*
    Building a basic file system:
    root-->usr-->game1
        |     |
        |      -->game2
        |
        -->lib-->libgpioman
        |     |
        |     -->libmath
        |
        -->include --> header1
                   |
                   --> header2
    
    */
    // After all, we delete usr, lib and include: only root is alive, everything went well.
    file_system* current_pointer; 
    printf("%d \n", argc);
    /**
    init_root();
    touch_("prueba.txt");
    touch_("prueba2.txt");
    mkdir_("usr");
    mkdir_("lib");
    mkdir_("include");
    cd_("usr");
    mkdir_("game1");
    mkdir_("game2");
    touch_("prueba.txt");
    touch_("prueba2.txt");
    cd_("..");
    cd_("lib");
    mkdir_("libgpioman");
    mkdir_("libmath");
    touch_("prueba.txt");
    touch_("prueba2.txt");
    cd_("..");
    cd_("include");
    mkdir_("header1");
    mkdir_("header2");
    touch_("prueba.txt");
    touch_("prueba2.txt");
    cd_("..");

    current_pointer = export_current_pointer();
    printf("El current nombre del archivo es %s\n", current_pointer->directory_name);
    cd_("usr");
    current_pointer = export_current_pointer();
    printf("El current nombre del archivo es %s\n", current_pointer->directory_name);
    cd_("game1");
    current_pointer = export_current_pointer();
    printf("El current nombre del archivo es %s\n", current_pointer->directory_name);
    
    cd_("GTA");
    cd_("..");
    cd_("..");
    cd_("lib");
    current_pointer = export_current_pointer();
    printf("El current nombre del archivo es %s\n", current_pointer->directory_name);
    cd_("libmath");
    current_pointer = export_current_pointer();
    printf("El current nombre del archivo es %s\n", current_pointer->directory_name);
    
    cd_("Hola");
    cd_("..");
    cd_("..");
    cd_("include");
    current_pointer = export_current_pointer();
    printf("El current nombre del archivo es %s\n", current_pointer->directory_name);
    cd_("header1");
    current_pointer = export_current_pointer();
    printf("El current nombre del archivo es %s\n", current_pointer->directory_name);
    
    cd_("Vars");
    cd_("..");
    cd_("header2");
    current_pointer = export_current_pointer();
    printf("El current nombre del archivo es %s\n", current_pointer->directory_name);
    
    cd_("Vars");
    ls_();
    cd_("..");
    ls_();
    cd_("..");
    ls_();
    rename_file("usr", "USR");
    
    ls_();
    rename_file("lib", "LIB");
    ls_();
    rename_file("varas", "cosas");
    
    //rmdir_("USR");
    ls_();
    //rmdir_("include");
    ls_();
    cd_("USR");
    
    //rmdir_("LIB");
    ls_();
    //From here we add files:
    mkdir_("home");
    cd_("home");
    
    touch_("prueba.txt");
    touch_("prueba2.txt");
    mkdir_("dentro_de_home");
    //ls_();
    cd_("dentro_de_home");
    touch_("prueba1.txt");
    touch_("prueba100.txt");
    
    mkdir_("hola");
    //ls_();
    //mv("prueba1.txt", "varas.txt");
    cd_("hola");
    touch_("a.txt");
    touch_("b.txt");
    //ls_();

    cd_("..");
    cd_("..");
    cd_("..");
    cd_("..");
    

    cd_("LIB");
    
    //rmdir_("LIB");
    ls_();
    //From here we add files:
    mkdir_("home");
    cd_("libmath");
    
    touch_("prueba.txt");
    touch_("prueba2.txt");
    mkdir_("dentro_de_home");
    //ls_();
    cd_("dentro_de_home");
    touch_("prueba1.txt");
    touch_("prueba100.txt");
    
    mkdir_("hola");
    //ls_();
    //mv("prueba1.txt", "varas.txt");
    cd_("hola");
    touch_("a.txt");
    touch_("b.txt");
    //ls_();

    cd_("..");
    cd_("..");
    cd_("..");
    cd_("..");



    cd_("include");
    
    //rmdir_("LIB");
    ls_();
    //From here we add files:
    mkdir_("home");
    cd_("header1");
    
    touch_("prueba.txt");
    touch_("prueba2.txt");
    mkdir_("dentro_de_home");
    //ls_();
    cd_("dentro_de_home");
    touch_("prueba1.txt");
    touch_("prueba100.txt");
    
    mkdir_("hola");
    //ls_();
    //mv("prueba1.txt", "varas.txt");
    cd_("hola");
    touch_("a.txt");
    touch_("b.txt");
    echo_("b.txt", "ibfuiwebfvwivbwievnwevbwehvwejvw");
    cat_("b.txt");
    //ls_();

    cd_("..");
    cd_("..");
    cd_("..");
    cd_("..");

    ls_();
    //rm("a.txt");
    //ls_();
    //lsattr("varas.txt");
    //ls_();
    tree_parser_wr(export_root());**/
    tree_parser_rd("../structure/output.dat");
    //show_disk(export_root(), argc, argv);
    ls_();
    cd_("USR");
    touch_("fhg.txt");
    mkdir_("oitu");
    ls_();
    show_disk(export_root(), argc, argv);
    free_all();
    return 0;
}