
#include "structure.h"
#include <stdlib.h>
#include <stdio.h>

#include "../directory_view/gtktreeview.h"

//Compile with: gcc -o test_file_system test_file_system.c structure.c
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
    init_root();
    mkdir_("usr");
    mkdir_("lib");
    mkdir_("include");
    cd_("usr");
    mkdir_("game1");
    mkdir_("game2");
    cd_("..");
    cd_("lib");
    mkdir_("libgpioman");
    mkdir_("libmath");
    cd_("..");
    cd_("include");
    mkdir_("header1");
    mkdir_("header2");
    cd_("..");
    /**
    current_pointer = export_current_pointer();
    printf("El current nombre del archivo es %s\n", current_pointer->directory_name);
    cd("usr");
    current_pointer = export_current_pointer();
    printf("El current nombre del archivo es %s\n", current_pointer->directory_name);
    cd("game1");
    current_pointer = export_current_pointer();
    printf("El current nombre del archivo es %s\n", current_pointer->directory_name);
    cd("GTA");
    cd("..");
    cd("..");
    cd("lib");
    current_pointer = export_current_pointer();
    printf("El current nombre del archivo es %s\n", current_pointer->directory_name);
    cd("libmath");
    current_pointer = export_current_pointer();
    printf("El current nombre del archivo es %s\n", current_pointer->directory_name);
    cd("Hola");
    cd("..");
    cd("..");
    cd("include");
    current_pointer = export_current_pointer();
    printf("El current nombre del archivo es %s\n", current_pointer->directory_name);
    cd("header1");
    current_pointer = export_current_pointer();
    printf("El current nombre del archivo es %s\n", current_pointer->directory_name);
    cd("Vars");
    cd("..");
    cd("header2");
    current_pointer = export_current_pointer();
    printf("El current nombre del archivo es %s\n", current_pointer->directory_name);
    cd("Vars");
    ls();
    cd("..");
    ls();
    cd("..");
    ls();
    rename_file("usr", "USR");
    ls();
    rename_file("lib", "LIB");
    ls();
    rename_file("varas", "cosas");
    rmdir("USR");
    ls();
    rmdir("include");
    ls();
    cd("USR");
    rmdir("LIB");
    ls();
    //From here we add files:
    mkdir("home");
    cd("home");
    touch("prueba.txt");
    touch("prueba2.txt");
    mkdir("dentro_de_home");
    ls();
    cd("dentro_de_home");
    touch("prueba1.txt");
    touch("prueba100.txt");
    mkdir("hola");
    ls();
    mv("prueba1.txt", "varas.txt");
    touch("a.txt");
    touch("b.txt");
    ls();
    rm("a.txt");
    ls();
    lsattr("varas.txt");**/
    ls_();
    show_disk(export_root(), argc, argv);
    free_all();
    return 0;
}