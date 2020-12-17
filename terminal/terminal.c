#include "pseudo_terminal.h"
#include "../structure/tree_parser.h"

//compile with: gcc -o terminal  terminal.c ../disk/disk.c ../structure/structure.c pseudo_terminal.c  $(pkg-config --cflags --libs gtk+-3.0)
//gcc -o terminal  terminal.c pseudo_terminal.c  $(pkg-config --cflags --libs gtk+-3.0)
//gcc -o terminal  terminal.c ../disk/disk.c ../structure/structure.c pseudo_terminal.c ../structure/tree_parser.c $(pkg-config --cflags --libs gtk+-3.0)
int main(int argc, char* argv[]){
    //Start pointer for B-tree
    init_disk(atoi(argv[1]));
    init_root();
    //tree_parser_rd("../structure/output.dat");
    //Start terminal
    init_gtk(argc, argv);
    //Free all memory
    //free_all();
    return 0;
}





