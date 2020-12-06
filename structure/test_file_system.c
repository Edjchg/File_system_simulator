#include "structure.h"
#include <stdlib.h>
#include <stdio.h>
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
    init_root();
    mkdir("usr");
    mkdir("lib");
    mkdir("include");
    cd("usr");
    mkdir("game1");
    mkdir("game2");
    cd("..");
    cd("lib");
    mkdir("libgpioman");
    mkdir("libmath");
    cd("..");
    cd("include");
    mkdir("header1");
    mkdir("header2");
    cd("..");
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
    free_all();
    return 0;
}