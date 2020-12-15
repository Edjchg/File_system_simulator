#include "pseudo_terminal.h"

//compile with: gcc -o terminal  terminal.c ../disk/disk.c ../structure/structure.c pseudo_terminal.c  $(pkg-config --cflags --libs gtk+-3.0)
//gcc -o terminal  terminal.c pseudo_terminal.c  $(pkg-config --cflags --libs gtk+-3.0)
int main(int argc, char* argv[]){
    //Start pointer for B-tree
    init_disk(atoi(argv[1]));
    init_root();
    //Start terminal
    init_gtk(argc, argv);
    //Free all memory
    //free_all();
    return 0;
}





