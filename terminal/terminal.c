#include "pseudo_terminal.h"
//#include "../structure/tree_parser.h"

//compile with: gcc -o terminal  terminal.c ../disk/disk.c ../structure/structure.c pseudo_terminal.c  $(pkg-config --cflags --libs gtk+-3.0)
//gcc -o terminal  terminal.c pseudo_terminal.c  $(pkg-config --cflags --libs gtk+-3.0)
//gcc -o terminal  terminal.c ../disk/disk.c ../structure/structure.c pseudo_terminal.c ../structure/tree_parser.c $(pkg-config --cflags --libs gtk+-3.0)
int main(int argc, char* argv[]){
    //Start pointer for B-tree
    
    //if(atoi(argv[2]) == 1)
    init_disk(atoi(argv[1]), atoi(argv[2]));

    //init_root();
    tree_parser_rd("../structure/output.dat", atoi(argv[2]));

    init_gtk(argc, argv);

    return 0;
}





